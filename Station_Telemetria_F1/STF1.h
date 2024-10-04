/*
  ---------------------------------------------------------------------------------------
  LIBRERIA PARA UNA ESTACION DE TELEMETRIA PARA VEHICULOS AUTONOMOS
                                  
                                  STF1

  *Se lee una MPU6050 y se envian los datos por WifI a un servidor en ThingSpeak
  *Se muestrea cada 20segundos por lo que se pierden muchos datos 
  *Se considera cambiar a otro tipo de servidor 

  ---------------------------------------------------------------------------------------

              -------LIBRERIA CREADA POR Alexis Yerai Ovando Pérez-----------------------------------
              03/10/2024   --------------------- 7:37pm

*/


#ifndef STF1_H
#define STF1_H


#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <ESP8266WiFi.h>
#include <ThingSpeak.h>


WiFiClient client;  // Necesario para ThingSpeak
Adafruit_MPU6050 mpu;

class station {

private:
  const char* ssid;         // Tu red WiFi
  const char* password;     // Tu contraseña WiFi
  unsigned long channelID;  // ID de tu canal en ThingSpeak
  const char* APIKEY;       // API Key de escritura de ThingSpeak
  int baudrate;
  int timetosend;

public:
  station(const char* _ssid, const char* _password, unsigned long _channelID, const char* _APIKEY);
  void config(int _baudrate);
  unsigned long setData(int _timetosend);
};
//station::baudrate = 115200;

station::station(const char* _ssid, const char* _password, unsigned long _channelID, const char* _APIKEY) {
  ssid = _ssid;
  password = _password;
  channelID = _channelID;
  APIKEY = _APIKEY;
}

void station::config(int _baudrate) {
  baudrate = _baudrate;
  Serial.begin(baudrate);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a WiFi...");
  }
  Serial.println("Conectado a WiFi!");
  // Inicializar ThingSpeak
  ThingSpeak.begin(client);
  // Inicializar MPU6050
  Wire.begin();  // SDA, SCL
  if (!mpu.begin()) {
    Serial.println("No se pudo encontrar la MPU6050");
    while (1)
      ;
  } else {
    Serial.println("MPU6050 inicializada correctamente");
    Serial.println("STF1 EN LINEA");
  }
}


unsigned long station::setData(int _timetosend) {
  timetosend = _timetosend;
  // Obtener los datos del MPU6050
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // Mostrar los valores en el monitor serial
  Serial.print("Acc X: ");
  Serial.println(a.acceleration.x);
  Serial.print("Acc Y: ");
  Serial.println(a.acceleration.y);
  Serial.print("Acc Z: ");
  Serial.println(a.acceleration.z);
  Serial.print("Gyro X: ");
  Serial.println(g.gyro.x);
  Serial.print("Gyro Y: ");
  Serial.println(g.gyro.y);
  Serial.print("Gyro Z: ");
  Serial.println(g.gyro.z);
  Serial.print("Temp: ");
  Serial.println(temp.temperature);

  // Enviar los datos a ThingSpeak
  ThingSpeak.setField(1, a.acceleration.x);
  ThingSpeak.setField(2, a.acceleration.y);
  ThingSpeak.setField(3, a.acceleration.z);
  ThingSpeak.setField(4, g.gyro.x);
  ThingSpeak.setField(5, g.gyro.y);
  ThingSpeak.setField(6, g.gyro.z);
  ThingSpeak.setField(7, temp.temperature);

  // Escribir los datos en ThingSpeak
  int result = ThingSpeak.writeFields(channelID, APIKEY);

  if (result == 200) {
    Serial.println("Datos enviados correctamente a ThingSpeak");
  } else {
    Serial.println("Error enviando datos a ThingSpeak. Código: " + String(result));
  }

  // Esperar 20 segundos entre cada envío
  delay(timetosend);
  return 0;
}

#endif
