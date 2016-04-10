#include <ESP8266WiFi.h>
#include "DHT.h"
#include <SimpleTimer.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define DHTPIN 14
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#define ssid  ""
#define password  ""
#define host "192.168.1.2"

#define device_id 1

#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);


float f;
float f2;
float h;
String url = "";

SimpleTimer Timer;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  wifiConnect();

  Timer.setInterval(60000,dht_read);
  
  dht.begin();
  sensors.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  Timer.run();
  
}

void dht_read() {
  h = dht.readHumidity();
  f = dht.readTemperature(true);
  sensors.requestTemperatures();
  f2 = (sensors.getTempCByIndex(0) * 1.8 + 32.0);

  url += "GET /?device_id="+(String)device_id+"&humidity="+(String)h+"&temperature="+(String)f+"&temperature2="+(String)f2;
  Serial.print("just read dht, url is: ");
  Serial.println(url);
  
  post_data();
  
  url = "";
  
}

