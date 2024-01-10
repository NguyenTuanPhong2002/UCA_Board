#include <SPI.h>
#include "LoRa.h"

// Parameters you can play with :
float value;

int txPower = 14;                                                                                             // from 0 to 20, default is 14
int spreadingFactor = 12;                                                                                     // from 7 to 12, default is 12
long signalBandwidth = 125E3;                                                                                 // 7.8E3, 10.4E3, 15.6E3, 20.8E3, 31.25E3,41.7E3,62.5E3,125E3,250E3,500e3, default is 125E3
int codingRateDenominator = 5;                                                                                // Numerator is 4, and denominator from 5 to 8, default is 5
int preambleLength = 8;                                                                                       // from 2 to 20, default is 8
String payload = "";  // you can change the payload

#define SS 10
#define RST 8
#define DI0 2
#define BAND 865E6  // Here you define the frequency carrier

#define MAX_LENGTH 50  // Độ dài tối đa của chuỗi

void setup() {
  Serial.begin(115200);
  while (!Serial)
    ;

  Serial.println("LoRa Sender");
  Serial.print("SetFrequency : ");
  Serial.print(BAND);
  Serial.println("Hz");
  Serial.print("SetSpreadingFactor : SF");
  Serial.println(spreadingFactor);

  SPI.begin();
  LoRa.setPins(SS, RST, DI0);



  if (!LoRa.begin(BAND)) {
    Serial.println("Starting LoRa failed!");
    while (1)
      ;
  }
  LoRa.setTxPower(txPower, 1);
  LoRa.setSpreadingFactor(spreadingFactor);
  LoRa.setSignalBandwidth(signalBandwidth);
  LoRa.setCodingRate4(codingRateDenominator);
  LoRa.setPreambleLength(preambleLength);
  // LoRa.setPolarity(1);
  //LoRa.setFSK();
}

void loop() {

  // send packet

  LoRa.beginPacket();

  payload = "{\"CosF\":\"";
  value = random(490, 510) / 10.0;
  payload += String(value);
  payload += "\",";

  payload +="\"Voltage\":\"";
  float Voltage = random(222000, 225000) / 1000.0;
  payload += String(Voltage);
  payload += "\",";


  payload +="\"Current\":\"";
  float Current = random(0, 5) / 10.0;
  payload += String(Current);
  payload += "\",";

  payload +="\"Frequency\":\"";
  value = random(4900, 5100) / 100.0;
  payload += String(value);
  payload += "\",";

  payload +="\"ActivePowe\":\"";
  payload += String(Current*Voltage/1000);
  payload += "\",";

  payload +="\"ReactivePower\":\"";
  value = random(0, 100) / 100.0;
  payload += String(value);
  payload += "\",";

  payload +="\"3PhaseActivePower\":\"";
  value = random(0, 100) / 100.0;
  payload += String(value);
  payload += "\",";

  payload +="\"3phaseReactivePower\":\"";
  value = random(0, 100) / 100.0;
  payload += String(value);
  payload += "\",";

  payload +="\"CT1\":\"0\""
          ",\"CT2\":\"0\""
          ",\"CT3\":\"0\""
          ",\"CT4\":\"0\""
          ",\"Co1\":\"0\""
          ",\"Co2\":\"0\""
          ",\"Co3\":\"0\""
          ",\"Co4\":\"0\"}";

  LoRa.print(payload);

  LoRa.endPacket();

  Serial.print("Sending packet with payload {");
  Serial.print(payload);
  Serial.println("}");


  delay(200);
}
