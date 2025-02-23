#include <SoftwareSerial.h>
#include "WiFiCredentials.h"

int rxPin = 10;
int txPin = 11;

SoftwareSerial esp(rxPin, txPin);
String server = "192.168.0.15";
String uri = "/users";
String data;

void setup() {
  Serial.begin(9600);
  esp.begin(115200);
  Serial.println("Basla");

  esp.println("AT");
  Serial.println("AT Yollandi");

  while (!esp.find("OK")) {
    esp.println("AT");
    Serial.println("ESP8266 Bulunamadi.");
  }

  Serial.println("OK Komutu Alindi");
  esp.println("AT+CWMODE=1");

  while (!esp.find("OK")) {
    esp.println("AT+CWMODE=1");
    Serial.println("Ayar Yapiliyor....");
  }

  Serial.println("Client olarak ayarlandi");
  Serial.println("Aga Baglaniliyor...");

  esp.println(String("AT+CWJAP=\"") + SSID + "\",\"" + PASSWORD + "\"");
  while (!esp.find("OK"))
    ;

  Serial.println("Aga Baglandi.");
}

void loop() {
  String data = "MAVI";

  esp.println("AT+CIPSTART=\"TCP\",\"" + server + "\",80");

  if (esp.find("Error")) {
    Serial.println("AT+CIPSTART Error");
    return;
  }

  Serial.println("TCP Baglantisi Baslatildi");

  esp.println("AT+CIPSEND=4");
  delay(100);

  esp.println(data);
  Serial.println(data);

  if (esp.find("SEND OK")) {
    Serial.println("Veri Gonderildi.");
  } else {
    Serial.println("Veri Gonderme Hatasi.");
  }

  esp.println("AT+CIPCLOSE");
  delay(1000);
}