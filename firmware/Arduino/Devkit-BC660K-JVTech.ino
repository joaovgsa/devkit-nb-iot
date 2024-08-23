#include "modem.h"
#include "mqtt_quectel.h"
#include "bc660k_quectel.h"
#include <Preferences.h>

#define UART_TX GPIO_NUM_10
#define UART_RX GPIO_NUM_9
#define RST_PIN GPIO_NUM_12
#define RGB_LED GPIO_NUM_48

time_t now;
struct tm timeinfo;

//Modem 
char mcc[32] = "72410"; // Brasil 724 = Tim / 03 São Paulo
                        // Brasil 724 = Vivo / 10

uint8_t connectionOpened = 0;

char utc[32] = "-3";

char iccid[32]  = {0};

int8_t band = 1; //0 Attach automático, 1 attach banda 3 e 28 apenas

//MQTT

char subscribeTopic[64] = "JVTECH/BC660K/Sub";

char publishTopic[64] = "JVTECH/BC660K/Pub";

char MQTTBroker[64] = "broker.emqx.io";

int32_t MQTTPort = 1883;

char MQTTUser[64] = "teste";

char MQTTPassword[64] = "teste";

char MQTTClientID[64] = "DevKit BCC60K JVTEC";

//APN

char APNName[64] = "virtueyes.com.br";

char APNUser[64] = "virtu";

char APNPassword[64] = "virtu";

// Time
char dateTime [50];

// Variaveis de controle

int8_t timeOut = 60; 

uint64_t minuto = 60000000;

// Construtores 
modem modem;
mqtt_quectel mqtt;
bc660k_quectel bc660k;
Preferences preferences;

//Variaveis Temporarias
char temp[256] = {0};
uint8_t res = 0;

void setup() {
  
  Serial.begin(115200);

  preferences.begin("jvtech", false);
  
  int32_t firstConn = 0;

  firstConn = preferences.getInt("firstConn", 1);

  // pinMode(RST_PIN, OUTPUT);

  // digitalWrite(RST_PIN, 1);  
  // delay(1000);                    
  // digitalWrite(RST_PIN, 0);   

  modem.init(UART_TX,UART_RX,UART_NUM_1,115200);

  Serial.println( "Iniciando");

  delay(500); 

  if(modem.atCmdWaitResponse("AT+QSCLK=0\r\n","OK",NULL,-1, 5000, NULL, 0 ) != 0){


    Serial.println( "Deep-sleep disabled");

  }

	if(firstConn == 1){

		Serial.println("Initialize First Connection");

		if(modem.getResponse(temp,"+CPIN: READY",sizeof(temp),2000) != 0)
		{

			Serial.println( "SIMCard is connected");
			
		}		
		else
		{

			if(modem.atCmdWaitResponse("AT+CPIN?\r\n","+CPIN: READY",NULL,-1, 5000, NULL, 0 ) != 0){


				Serial.println( "SIMCard is connected - 2");
				res = 1;

			}
			else
			{
				Serial.println( "SIMCard Fail try again");

				if(modem.atCmdWaitResponse("AT+CPIN?\r\n","+CPIN: READY",NULL,-1, 5000, NULL, 0 ) != 0){

					Serial.println( "SIMCard is connected");

					res = 1;
				
				}
				else{

					Serial.println( "SIMCard is disconnected");

					res = 0;

				}

			}

		}	
	
		if(modem.atCmdWaitResponse("ATE0\r\n","OK",NULL,-1, 5000, NULL, 0 ) != 0){

			Serial.println( "Echo mode Disabled Ok");

		}
		else{

			Serial.println( "Echo mode Disabled Fail");

		}

		bc660k.getICCID(iccid);

		Serial.print("Numero de identificação Simcard ICCID: ");
    Serial.println(iccid);


		res = bc660k.setAPN("IP",APNName,APNUser,APNPassword);

		if(res == 0){

			Serial.println("Sleeping,  Set APN Fail");

			esp_deep_sleep(minuto);
				
		}

		res = bc660k.setBAND(band);

		if(res == 0){

			Serial.println("Sleeping,  Set BAND Fail");

			esp_deep_sleep(minuto);			
				
		}
    else{

      Serial.println("Set BAND OK");
    }

		res = bc660k.enableNetworkRegister();

		if(res == 0){

			Serial.println("Sleeping,  Enable Network Fail");

			esp_deep_sleep(minuto);
				
		}
    else{

      Serial.println("Enable Network Ok");

    }

		res = bc660k.enableConnection();

		if(res == 0){

			Serial.println("Sleeping,  Enable Connection Fail");

			esp_deep_sleep(minuto);
			
		}
    else{

      Serial.println("Enable Connection Ok");

    }

		res = bc660k.setOperator(4,2,mcc);

		if(res == 0){

			Serial.println("Sleeping,  Set Operator Fail");

			esp_deep_sleep(minuto);
				
		}
    else{

      Serial.println("Set Operator Ok");

    }
    

		if(modem.getResponse(temp,"+IP:",sizeof(temp),(180 * 1000)) != 0)
		{

			Serial.println( "First Connection Success");
			
		}
		else{

			Serial.println("Sleeping,  Enable Connection Fail");

			esp_deep_sleep(minuto);


		}

    preferences.putInt("firstConn", 0);

	}
	else{

		if(modem.getResponse(temp,"+CPIN: READY",sizeof(temp),2000) != 0)
		{

			Serial.println( "SIMCard is connected");
			
		}		
		else
		{

			if(modem.atCmdWaitResponse("AT+CPIN?\r\n","+CPIN: READY",NULL,-1, 5000, NULL, 0 ) != 0){


				Serial.println( "SIMCard is connected - 2");
				res = 1;

			}
			else
			{
				Serial.println( "SIMCard Fail try again");

				if(modem.atCmdWaitResponse("AT+CPIN?\r\n","+CPIN: READY",NULL,-1, 5000, NULL, 0 ) != 0){

					Serial.println( "SIMCard is connected");

					res = 1;
				
				}
				else{

					Serial.println( "SIMCard is disconnected");

					res = 0;

				}

			}

			if(res == 0){

				Serial.println("SIMCard is not connected");

				esp_deep_sleep(minuto);

			}
				
		}

    if(modem.atCmdWaitResponse("AT+CSCON?\r\n","+CSCON: 1",NULL,-1, 10000, NULL, 0 ) != 0){

      Serial.println( "Enable connection");

      connectionOpened = 1;

    }
    else{

      if(modem.getResponse(temp,"+IP:",sizeof(temp),(timeOut * 1000)) != 0)
      {

        Serial.println( "Connection Success");

        
        
      }
      else
      {
        Serial.println("Sleeping,  Network Register Fail");

        esp_deep_sleep(minuto);
          
      }


    }
	}

	res = bc660k.getCurrentDateTime(utc);

	if(res == 0){

		bc660k.getCurrentDateTime(utc);

	}

	int8_t RSSI = bc660k.getRSSI();

	if(RSSI == 99){

		RSSI = bc660k.getRSSI();

	}

  Serial.print("RSSI: ");
  Serial.println(RSSI);

	bc660k.getOperator(mcc);

	Serial.print("  Operator Name MCC: ");
  Serial.println(mcc);

  if(connectionOpened == 0){

    if(modem.atCmdWaitResponse("AT+CSCON?\r\n","+CSCON: 1,1",NULL,-1, 10000, NULL, 0 ) != 0){

    Serial.println( "Connection Opened");

    }

  }

	mqtt.init();

	vTaskDelay(100 / portTICK_PERIOD_MS);

  // Verificar se conexão ja está aberta

  if(modem.atCmdWaitResponse("AT+QMTOPEN?\r\n","+QMTOPEN: 0,0",NULL,-1, 10000, NULL, 0 ) != 0){

    Serial.println( "MQTT Connected");

  }
  else{

    char connectionName[64] = {0};

    sprintf(connectionName,"+QMTOPEN: 0,\"%s\",%d",MQTTBroker,MQTTPort);
    if(modem.atCmdWaitResponse("AT+QMTOPEN?\r\n",connectionName,NULL,-1, 10000, NULL, 0 ) != 0){

      Serial.println( "MQTT Connected");

    }
    else{
        
      Serial.println( "MQTT not Connected");

      mqtt.openConnection(MQTTBroker,MQTTPort);

      vTaskDelay(100 / portTICK_PERIOD_MS);

      if(mqtt.connect(MQTTClientID,MQTTUser,MQTTPassword)){
          
        Serial.println("Success to Connect in MQTT");

      }
      else{

          
        Serial.println("Fail to Connect in MQTT");
      
        vTaskDelay(100 / portTICK_PERIOD_MS);

        esp_deep_sleep(minuto);		


      }


    }


  }

	vTaskDelay(100 / portTICK_PERIOD_MS);

	mqtt.subscribe(subscribeTopic,0);
	
}

void loop() {

  memset(temp,0,sizeof(temp));

  if(modem.getResponse(temp,"+QMTRECV:",sizeof(temp),100) != 0)	{

    Serial.print( "Subscribe RESPONSE ---> ");
    Serial.println(temp);

    if(strstr(temp,"red")){

      neopixelWrite(RGB_LED,255,0,0);

    }
    if(strstr(temp,"green")){

      neopixelWrite(RGB_LED,0,255,0);

    }
    if(strstr(temp,"blue")){

      neopixelWrite(RGB_LED,0,0,255);

    }

  }


	memset(temp,0,sizeof(temp));

	vTaskDelay(100 / portTICK_PERIOD_MS);

	time(&now);
	localtime_r(&now, &timeinfo);

	memset(dateTime,0,sizeof(dateTime));

	strftime(dateTime, 26, "%Y-%m-%d %H:%M:%S",&timeinfo);

	Serial.print( "Current timestamp: ");
  Serial.println(dateTime);

	if(mqtt.publish(publishTopic,dateTime,0) == 1)
	{

		Serial.println( "Publish Success");
		
	}

  //mqtt.subscribe(subscribeTopic,0);

  vTaskDelay(100 / portTICK_PERIOD_MS);

}
