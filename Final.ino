//Created by: Daniel Grabda//
//06 Oct 2020//

#define TINY_GSM_MODEM_SIM800
#include <TinyGsmClient.h>
#include <BlynkSimpleSIM800.h>
#include "DHT.h"

#define SerialAT Serial1
//TTGO T-CALL SIM800L//
#define SIM800L_RX     27
#define SIM800L_TX     26
#define SIM800L_PWRKEY 4
#define SIM800L_RST    5
#define SIM800L_POWER  23

//DHT SETTINGS// ADJUST "11" TO YOUR MODEL NUMBER & THE PIN TO YOUR SDA//
#define DHTTYPE DHT11   
#define DHTPIN 18

DHT dht(DHTPIN, DHTTYPE);
TinyGsm modem(SerialAT);

char auth[] = "YOUR AUTH CODE HERE";
char apn[]  = "YOUR APN";
char user[] = "YOUR USER";
char pass[] = "YOUR PASS";

void setup()
{
  dht.begin();
  pinMode(SIM800L_PWRKEY, OUTPUT);
  pinMode(SIM800L_RST, OUTPUT);
  pinMode(SIM800L_POWER, OUTPUT);
  digitalWrite(SIM800L_PWRKEY, LOW);
  digitalWrite(SIM800L_RST, HIGH);
  digitalWrite(SIM800L_POWER, HIGH);
  
  Serial.begin(9600);
  delay(100);

  SerialAT.begin(9600, SERIAL_8N1, SIM800L_TX, SIM800L_RX);
  delay(3000);

  Serial.println("Modem Starting");
  modem.init();

    Blynk.begin(auth, modem, apn, user, pass, "blynk-cloud.com", 8080);
}

void loop()
{
  Blynk.run();
      delay(3000);
          float h = dht.readHumidity();
          float t = dht.readTemperature();

            if (isnan(h) || isnan(t)) {
              Serial.println("DHT stats not found, are you sure you've selected the correct pin?");
              return;        
            }
            else{
              float finaldata = dht.computeHeatIndex(t, h, false);
                  Blynk.virtualWrite(V1,t);
                    Blynk.virtualWrite(V2,h);

            }
        
            }
