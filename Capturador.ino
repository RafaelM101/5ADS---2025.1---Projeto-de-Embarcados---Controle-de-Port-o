#include <RCSwitch.h>

RCSwitch rfsense = RCSwitch();

void setup() {
  Serial.begin(9600);
  rfsense.enableReceive(0);  // Receptor no pino digital 2 (interrupção 0)
  
  Serial.println(F("Aguardando sinal RF 433 MHz..."));
  Serial.println(F("Pressione o botão do seu controle remoto..."));
}

void loop() {
  if (rfsense.available()) {
    // Captura todos os parâmetros do sinal recebido
    unsigned long valorRecebido = rfsense.getReceivedValue();
    unsigned int bitsRecebidos = rfsense.getReceivedBitlength();
    unsigned int delayRecebido = rfsense.getReceivedDelay();
    unsigned int protocolo = rfsense.getReceivedProtocol();
    
    Serial.println(F("\n--- Dados do Sinal Capturado ---"));
    
    if (valorRecebido == 0) {
      Serial.println(F("Sinal desconhecido ou com erro."));
    } else {
      Serial.print(F("Código Decimal: "));
      Serial.println(valorRecebido);
      
      Serial.print(F("Código Hexadecimal: 0x"));
      Serial.println(valorRecebido, HEX);
      
      Serial.print(F("Código Binário: "));
      printBinary(valorRecebido, bitsRecebidos);
      
      Serial.print(F("Tamanho (bits): "));
      Serial.println(bitsRecebidos);
      
      Serial.print(F("Protocolo: "));
      Serial.println(protocolo);
      
      Serial.print(F("Pulse Length (μs): "));
      Serial.println(delayRecebido);
    }
    
    Serial.println(F("-------------------------------"));
    Serial.println(F("Pressione o botão novamente para capturar outro sinal..."));
    
    rfsense.resetAvailable();
    delay(500);  // Pequena pausa para evitar leituras múltiplas
  }
}

// Função auxiliar para imprimir valores binários com leading zeros
void printBinary(unsigned long value, int bits) {
  for (int i = bits-1; i >= 0; i--) {
    Serial.print(bitRead(value, i));
    if (i % 4 == 0 && i != 0) Serial.print(" ");  // Espaço a cada 4 bits
  }
  Serial.println();
}