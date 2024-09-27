#include <Arduino.h>
#include <WiFi.h>  // Librería WiFi específica para ESP32

// Definir el nombre y la contraseña de la red WiFi a la que se desea conectar
const char* ssid = "INFINITUM18DD";      // Reemplaza con el nombre de tu red WiFi
const char* password = "P3yFu3hNaD";     // Reemplaza con la contraseña de tu red WiFi

void setup() {
  // Inicializa la comunicación serial para la depuración
  Serial.begin(115200);
  
  // Comienza el proceso de conexión WiFi
  Serial.println("Conectando a WiFi...");
  
  // Inicia la conexión a la red WiFi
  WiFi.begin(ssid, password);

  // Espera hasta que la conexión WiFi se haya establecido
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando...");
  }

  // Una vez conectado, imprime la dirección IP obtenida
  Serial.println("Conectado a WiFi");
  Serial.print("Dirección IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Aquí puedes agregar código que necesite estar conectado a internet
}
