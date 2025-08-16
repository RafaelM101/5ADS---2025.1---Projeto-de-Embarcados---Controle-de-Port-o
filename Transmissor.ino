#include <RCSwitch.h>
#include <WiFi.h>
#include <PubSubClient.h>

RCSwitch rfsense = RCSwitch();

// ===== CONFIGURAÇÕES ===== //
// WiFi
const char* SSID = "MINHAREDEWIFI";
const char* PASSWORD = "MINHASENHAWIFI";

// MQTTk
const char* MQTT_BROKER = "broker.mqtt-dashboard.com";
const int MQTT_PORT = 1883;
const char* MQTT_CLIENT_ID = "ESP32_Garagem_Final";
const char* MQTT_TOPIC = "garagem/portao";
const char* MQTT_STATUS_TOPIC = "garagem/status";

// RF
const int PINO_TX = 5;
const unsigned long CODIGO_RF = "MEUCODIGORF";
const int PROTOCOLO = "MEU PROTOCOLO";
const int PULSE_LENGTH = "TAMANHO DO PULSO";
const int RF_BIT_LENGTH = "TAMANHO DOS BITS ENVIADOS";

// Controle

const unsigned long COMMAND_COOLDOWN = 100; 
const unsigned long WIFI_RETRY_DELAY = 5000;

// ===== VARIÁVEIS GLOBAIS ===== //
WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastCommandTime = 0;



void setup_wifi() {
  Serial.println();
  Serial.print("Conectando à rede ");
  Serial.println(SSID);
  WiFi.begin(SSID, PASSWORD);
  unsigned long startAttemptTime = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 20000) {
    delay(500);
    Serial.print(".");
  }
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi conectado");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\nFalha na conexão WiFi. Reiniciando...");
    ESP.restart();
  }
}

void enviarStatus(const char* status) {
  if (client.connected()) {
    client.publish(MQTT_STATUS_TOPIC, status);
  }
}

void enviarSinalRF() {
  Serial.println("[RF] Enviando código UMA ÚNICA VEZ...");
  rfsense.send(CODIGO_RF, RF_BIT_LENGTH);
  Serial.println("[RF] Código enviado!");
  enviarStatus("rf_enviado_unicamente");
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Mensagem recebida [");
  Serial.print(topic);
  Serial.print("]: ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  if (length == 1 && (char)payload[0] == '1') {
    unsigned long currentTime = millis();
    if (currentTime - lastCommandTime >= COMMAND_COOLDOWN) {
      Serial.println("Cooldown validado. Processando comando...");
      lastCommandTime = currentTime;
      enviarStatus("comando_recebido");
      enviarSinalRF(); 
      Serial.println("Comando finalizado.");
    } else {
      Serial.println("Comando ignorado (cooldown ativo).");
      enviarStatus("ignorado:cooldown");
    }
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Conectando ao MQTT...");
    if (client.connect(MQTT_CLIENT_ID)) {
      Serial.println("Conectado!");
      client.subscribe(MQTT_TOPIC, 1);
      enviarStatus("mqtt_conectado");
    } else {
      Serial.print("Falha, rc=");
      Serial.print(client.state());
      Serial.println(" Tentando novamente em 5s...");
      delay(WIFI_RETRY_DELAY);
    }
  }
}


// ===== SETUP INICIAL ===== //
void setup() {
  Serial.begin(115200);
  
  rfsense.enableTransmit(PINO_TX);
  rfsense.setProtocol(PROTOCOLO);
  rfsense.setPulseLength(PULSE_LENGTH);
  
  rfsense.setRepeatTransmit(5);

  Serial.println("\n[RF] Transmissor configurado para envio ÚNICO!");

  setup_wifi();
  client.setServer(MQTT_BROKER, MQTT_PORT);
  client.setCallback(callback);
}

// ===== LOOP PRINCIPAL ===== //
void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}