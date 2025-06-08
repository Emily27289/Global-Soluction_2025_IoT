#include <DHT.h>
//#include <WiFi.h>
//#include <HTTPClient.h>

// const char* ssid = "SSI";       
// const char* password = "1234567890";
// const char* serverName = "http://192.168.15.3:1880/entrada"; 

#define DHTPIN 4
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

#define releLuz 23
#define releBomba 15
#define pinoLDR 34

void setup() {
  Serial.begin(115200);
  dht.begin();

  pinMode(releLuz, OUTPUT);
  pinMode(releBomba, OUTPUT);
  digitalWrite(releLuz, LOW);
  digitalWrite(releBomba, LOW);

  //WiFi.begin(ssid, password);
  //while (WiFi.status() != WL_CONNECTED) {
  //  delay(1000);
  //  Serial.println("Conectando ao Wi-Fi...");
  //}
  //Serial.println("Wi-Fi conectado");
}

void loop() {
  delay(2000); // Aguarda o sensor estabilizar

  float temperatura = dht.readTemperature();
  float umidade = dht.readHumidity();
  int valorLDR = analogRead(pinoLDR);
  int luminosidade = map(valorLDR, 0, 4095, 0, 100);

  if (luminosidade < 40) {
    digitalWrite(releLuz, HIGH);
  } else {
    digitalWrite(releLuz, LOW);
  }

  if (temperatura > 30 && umidade < 40) {
    digitalWrite(releBomba, HIGH);
  } else {
    digitalWrite(releBomba, LOW);
  }

  Serial.print("Temp: "); Serial.print(temperatura);
  Serial.print(" C | Umid: "); Serial.print(umidade);
  Serial.print(" % | Luz: "); Serial.print(luminosidade);
  Serial.println(" %");

  String json = "{";
  json += "\"temperatura\":" + String(temperatura, 1) + ",";
  json += "\"umidade\":" + String(umidade, 1) + ",";
  json += "\"luminosidade\":" + String(luminosidade);
  json += "}";

  Serial.println("JSON para envio:");
  Serial.println(json);

  //if (WiFi.status() == WL_CONNECTED) {
  //  HTTPClient http;
  //  http.begin(serverName);
  //  http.addHeader("Content-Type", "application/json");

  //  int httpResponseCode = http.POST(json);
  //  Serial.print("HTTP Response: ");
  //  Serial.println(httpResponseCode);
  //  http.end();
  //} else {
  //  Serial.println("Wi-Fi desconectado");
  //}

  delay(5000);
}
