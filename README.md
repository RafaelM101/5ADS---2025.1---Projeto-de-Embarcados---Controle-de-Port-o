# Automação de Portão com ESP-32 e MQTT

Este projeto tem como objetivo o desenvolvimento de um sistema embarcado para automação de um portão, utilizando o microcontrolador **ESP-32**, um **módulo transmissor RF 433 MHz** e comunicação via **MQTT**. O sistema permite o controle remoto do portão de garagem por meio de uma rede Wi-Fi, utilizando um celular para enviar os comandos, sem a necessidade de um controle remoto físico.

## Descrição do Projeto

O sistema é composto por três partes principais:

1. **Captura do Sinal (Arduino Mega 2560)**: O Arduino Mega é utilizado para capturar o sinal do controle remoto original. O sinal é então convertido para um código binário, hexadecimal e decimal.
   
2. **Transmissão do Sinal (ESP-32 e Módulo RF 433 MHz)**: Após a captura, o **ESP-32** assume o controle do sistema, retransmitindo o sinal capturado via **módulo transmissor RF 433 MHz** para acionar o portão.

3. **Controle Remoto (MQTT)**: O ESP-32 se conecta a uma rede Wi-Fi e aguarda comandos via MQTT. Quando um comando é recebido, o ESP-32 retransmite o sinal correspondente para abrir ou fechar o portão.

## Funcionalidades

- Controle do portão de garagem remotamente via **MQTT**, utilizando um **smartphone** com um aplicativo como o **MyQTT**.
- **Conexão Wi-Fi**: O sistema opera enquanto o ESP-32 estiver conectado à internet, permitindo o controle em qualquer lugar.
- **Compatível com portões de 433 MHz**: A automação pode ser aplicada em qualquer portão que utilize um controle remoto RF 433 MHz.
  
## Tecnologias Utilizadas

- **ESP-32** (Microcontrolador)
- **Arduino Mega 2560** (Para captura de sinal)
- **Módulo Transmissor RF 433 MHz** (Para acionar o portão)
- **MQTT** (Para comunicação remota)
- **Wi-Fi** (Para conexão à rede)

## Componentes Necessários

- **Arduino Mega 2560**
- **ESP-32**
- **Módulo Transmissor RF 433 MHz (MX-FS-03V)**
- **Módulo Receptor RF 433 MHz (MX-05V)**
- **Protoboard (Breadboard)**
- **Fios e antena para o módulo transmissor**

## Como Executar o Projeto

### Ferramentas Necessárias

- **Arduino IDE**: Para programar os microcontroladores (Arduino Mega e ESP-32).
- **Bibliotecas MQTT**: Instalar a biblioteca MQTT para a comunicação via MQTT.
- **Software de Broker MQTT**: Utilizamos o **MyQTT**, mas você pode configurar seu próprio broker privado para maior segurança.
  
### Passo a Passo

1. **Captura do Sinal (Arduino Mega 2560)**:
   - Conecte o Arduino Mega ao seu computador.
   - Carregue o código que captura o sinal do controle remoto.
   - Aperte o controle original do portão apontando para o Arduino.
   - O Arduino irá armazenar o código RF, protocolo e tamanho do pulso.
   
2. **Configuração do ESP-32**:
   - Carregue o código para o ESP-32, incluindo as credenciais da sua rede Wi-Fi, o sinal RF capturado, o pulso e o protocolo capturado pelo Arduino.
   - Configure a conexão com o broker MQTT, para que o ESP-32 possa receber comandos remotos.
   
3. **Configuração do MQTT**:
   - No software MQTT (como o MyQTT), configure um tópico de controle, como `garagem/portao`.
   - Publique comandos no tópico, como `1` para abrir o portão e `0` para fechá-lo.
   
4. **Testes**:
   - Com tudo configurado, teste o sistema acionando o portão via aplicativo MQTT.

### Observação Importante

- **Broker MQTT**: Para testes, foi utilizado um broker público. Para um sistema real, é altamente recomendada a configuração de um broker privado para maior segurança.
- **Margem de Erro no Pulso**: Considere uma margem de erro de 4 pontos percentuais para cima no pulso emitido pelo ESP-32. (Se o Arduino capturar 493 de pulso, insira no código do ESP 497 no valor)

## Conclusão

Este projeto é uma solução prática para a automação de portões, permitindo o controle remoto sem a necessidade de um controle físico. A comunicação via MQTT e o uso do ESP-32 com Wi-Fi tornam o sistema altamente acessível, podendo ser controlado de qualquer lugar.

### Melhorias Futuras

- Implementação de um **aplicativo móvel** dedicado para controle do portão.
- **Criptografia das mensagens MQTT** para maior segurança.
- **Registro de eventos** de aberturas e fechamentos do portão.

## Links Úteis

- [Vídeo do Funcionamento do Sistema](https://drive.google.com/file/d/1b1QRKNNwDroNPS6WMcC57Xee9eTfAGMN/view?usp=drive_link)
- [Relatório Detalhado do Projeto](https://drive.google.com/file/d/1NUR3d2g19kaqDj31lN29ppwufCALMjuk/view?usp=drive_link)

