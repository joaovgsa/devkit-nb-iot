<!-- # devkit-nb-iot -->

# **DevKit NB-IoT**  
Bem-vindo ao repositório oficial do nosso DevKit NB-IoT! Aqui você encontrará toda a documentação e os recursos necessários para aprender e desenvolver seus projetos utilizando o nosso DevKit NB-IoT.  

Neste repositório, você terá acesso a:  

-> Características do DevKit  
-> Especificações de Hardware  
-> Pinout detalhado  
-> Requisitos para o desenvolvimento  
-> Comandos AT para comunicação com o módulo BC660K  
-> Exemplos práticos para Arduino e ESP-IDF  
-> Material de Apoio  
-> Projetos e Artigos  
-> FAQ - Perguntas Frequentes  

Siga as instruções e utilize os recursos disponíveis para começar a criar seus projetos com eficiência!

# **Características do DevKit**  

-> ESP32-S3 (WiFi & Bluetooth)  
-> Módulo NB-IoT da Quectel, já homologado na Anatel  
-> Conector para antena externa NB-IoT  
-> Led RGB  
-> Botão multi uso    
-> Botão de reset  
-> GPIO's para uso geral  
-> Alimentação, Programação e Debug via USB  
-> Barra de alimentação 3v3, 5v e GND  

## **Dimensões físicas da placa**  
-> Comprimento: 92,8mm   
-> Largura: 28,5mm  
-> Altura: 11mm  

# **Especificações de Hardware**  

## **DevKit**  

Na pasta esquematico tem os detalhes do esquemático separado por páginas e imagens 3D da placa.  

## **BC660K**  

### **Visão Geral do Módulo BC660K**
O BC660K é um módulo de comunicação celular desenvolvido para redes NB-IoT (Narrowband Internet of Things), ideal para aplicações IoT que requerem baixo consumo de energia, longa duração da bateria e comunicação eficiente em áreas de cobertura estendida.  

### **Principais Características:**  
-> Suporte à Tecnologia NB-IoT: Compatível com as especificações do 3GPP Release 13 e 14, proporcionando conectividade em áreas urbanas e rurais.  
-> Baixo Consumo de Energia: Projetado para maximizar a vida útil da bateria, ideal para dispositivos que operam por longos períodos sem manutenção.  
-> Ampla Faixa de Frequências: Suporta múltiplas bandas de LTE, possibilitando o uso em várias regiões ao redor do mundo.  
-> Design Compacto: Fácil integração em dispositivos IoT como sensores, medidores inteligentes e dispositivos vestíveis.  
-> Alta Confiabilidade e Segurança: Oferece comunicação segura e é robusto em ambientes industriais e urbanos.  
->  Comandos AT: Utiliza comandos AT para configuração e controle, facilitando o uso e integração com diversas plataformas.  
-> Baixa Largura de Banda: Opera em até 250 kHz, adequado para transmissão de pequenos volumes de dados, como em telemetria e monitoramento.  

### **Aplicações:**  
-> Medição inteligente: Medidores de água, gás e energia elétrica.  
-> Monitoramento ambiental: Sensores para agricultura e controle climático.  
-> Dispositivos de segurança e rastreamento: Controle de ativos e segurança patrimonial.  
-> Wearables e dispositivos médicos: Rastreadores e dispositivos conectados.  
-> Cidades inteligentes: Soluções de iluminação, monitoramento de estacionamento e mais.  

### **Benefícios:**  
-> Cobertura estendida: Operando em frequências baixas, o BC660K é eficiente para uso em áreas com difícil penetração de sinal, como porões e áreas remotas.  
-> Custo acessível: Usa infraestrutura celular existente, o que reduz os custos de conectividade.  
-> Integração facilitada: Compatível com plataformas como Arduino e ESP-IDF, com exemplos práticos prontos para uso.  

Sobre: https://www.quectel.com/product/lpwa-bc660k-gl-nb2/  
Datasheet: https://www.mouser.com/datasheet/2/1052/Quectel_BC660K_GL_NB_IoT_Specification_V1_4_1-3009753.pdf  

## **ESP32-S3**   

Sobre: https://www.espressif.com/en/products/socs/esp32-s3  
Datasheet: https://www.espressif.com/sites/default/files/documentation/esp32-s3_datasheet_en.pdf  

# **Pinout detalhado**  

### Pinout Completo do ESP32-S3-WROOM-1 (N8R8)

| Pino | Nome             | Função                                      |  
|------|------------------|---------------------------------------------|
| 1    | GND              | Terra                                       |
| 2    | VDD3P3           | Alimentação 3.3V                            |
| 3    | EN               | Habilitar o módulo                          |
| 4    | IO04             | GPIO, Entrada/Saída digital				          |
| 5    | IO05             | GPIO, Entrada/Saída digital				          |
| 6    | IO06             | GPIO, Entrada/Saída digital				          |
| 7    | IO07             | GPIO, Entrada/Saída digital				          |
| 8    | IO15             | GPIO, Entrada/Saída digital				          |
| 9    | IO16             | GPIO, Entrada/Saída digital				          |
| 10   | IO17             | GPIO, Entrada/Saída digital				          |
| 11   | IO18             | GPIO, Entrada/Saída digital				          |  
| 12   | IO08             | GPIO, Entrada/Saída digital				          |
| 13   | IO19             | GPIO, Entrada/Saída digital				          |
| 14   | IO20             | GPIO, Entrada/Saída digital				          |
| 15   | IO03             | GPIO, Entrada/Saída digital				          |
| 16   | IO46             | GPIO, Entrada/Saída digital				          |
| 17   | IO09             | GPIO, Entrada/Saída digital, RX-BC		      |
| 18   | IO10             | GPIO, Entrada/Saída digital, TX-BC   	      |
| 19   | IO11             | GPIO, Entrada/Saída digital, PSM-BC  	      |
| 20   | IO12             | GPIO, Entrada/Saída digital, RST-BC 	      |
| 21   | IO13             | GPIO, Entrada/Saída digital				          |
| 22   | IO14             | GPIO, Entrada/Saída digital				          |
| 23   | IO21             | GPIO, Entrada/Saída digital				          |
| 24   | IO47             | GPIO, Entrada/Saída digital, BOTÃO		      |
| 25   | IO48             | GPIO, Entrada/Saída digital, LED		        |
| 26   | IO45             | GPIO, Entrada/Saída digital				          |
| 27   | IO00             | GPIO, Entrada/Saída digital				          |
| 28   | IO35             | GPIO, Entrada/Saída digital                 |
| 29   | IO36             | GPIO, Entrada/Saída digital                 |
| 30   | IO37             | GPIO, Entrada/Saída digital                 |
| 31   | IO38             | GPIO, Entrada/Saída digital                 |
| 32   | IO39             | GPIO, Entrada/Saída digital                 |
| 33   | IO40             | GPIO, Entrada/Saída digital                 |
| 34   | IO41             | GPIO, Entrada/Saída digital                 |
| 35   | IO42             | GPIO, Entrada/Saída digital                 |
| 36   | RXD0             | GPIO, Entrada/Saída digital                 |
| 37   | TXD0             | GPIO, Entrada/Saída digital                 |
| 38   | IO2              | GPIO, Entrada/Saída digital                 |
| 39   | IO1              | GPIO, Entrada/Saída digital                 |
| 40   | GND              | Terra                                       |
| 41   | GND              | Terra			                                  |

# **Requisitos para o desenvolvimento**

Para trabalhar com o DevKit NB-IoT você vai precisar de:  

-> DevKit  
-> Cabo USB tipo C  
-> Antena NB-IoT (acompanha no kit)  
-> SIMCARD com conectividade NB-IoT  
-> Ambiente de programação  
  - Arduino Core  
  - Arduino IDE  
  - VSCode + Platformio
  - ESP-IDF  
  - VSCode  
  - Eclipse  
  - VSCode + Platformio  

# **Comandos AT para comunicação com o módulo BC660K**  

Documentação sobre os comandos AT: https://auroraevernet.ru/upload/iblock/982/e5bcivsatkfbvd2wn8qgg5d07mc385q5.pdf  

# **Exemplos práticos para Arduino e ESP-IDF**  

Na pasta firmware tem os exemplos para Arduino e ESP-IDF e biblioteca para ser instalada e usada.  

<!-- # **Material de Apoio**  -->

<!-- # **Projetos e Artigos**  -->

<!-- # **FAQ**  -->
