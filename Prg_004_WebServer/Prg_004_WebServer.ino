#include <WiFi.h> // Librería para WiFi en ESP32
#include <WebServer.h> // Librería para crear un servidor HTTP

// Definir el nombre y la contraseña de la red WiFi a la que se desea conectar
const char* ssid = "INFINITUM18DD";      // Reemplaza con el nombre de tu red WiFi
const char* password = "P3yFu3hNaD";     // Reemplaza con la contraseña de tu red WiFi

// Definir el puerto GPIO del LED
const int ledPin = 2; // Pin GPIO para el LED (puedes usar otro pin)

WebServer server(80);  // Crea un servidor HTTP en el puerto 80

// Función para manejar la página raíz "/"
void handleRoot() {
  // Página web en HTML para controlar el LED
  String htmlPage = "<html>\
  <head><title>Control de LED</title></head>\
  <body>\
  <h1>Control de LED</h1>\
  <p>Haz clic en los botones para encender o apagar el LED.</p>\
  <p><a href=\"/led/on\"><button>Encender LED</button></a></p>\
  <p><a href=\"/led/off\"><button>Apagar LED</button></a></p>\
  </body>\
  </html>";

  server.send(200, "text/html", htmlPage); // Enviar la página HTML
}

// Función para manejar la solicitud de encendido del LED
void handleLEDOn() {
  digitalWrite(ledPin, HIGH); // Enciende el LED
  server.send(200, "text/html", "LED encendido<br><a href=\"/\">Regresar</a>"); // Respuesta HTML
}

// Función para manejar la solicitud de apagado del LED
void handleLEDOff() {
  digitalWrite(ledPin, LOW); // Apaga el LED
  server.send(200, "text/html", "LED apagado<br><a href=\"/\">Regresar</a>"); // Respuesta HTML
}

void setup() {
  // Inicializa la comunicación serial
  Serial.begin(115200);

  // Configura el pin del LED como salida
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW); // Inicializa con el LED apagado

  // Conéctate a la red WiFi
  Serial.println("Conectando a WiFi...");
  WiFi.begin(ssid, password);

  // Espera hasta que la conexión WiFi se haya establecido
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando...");
  }

  // Imprime la dirección IP obtenida
  Serial.println("Conectado a WiFi");
  Serial.print("Dirección IP: ");
  Serial.println(WiFi.localIP());

  // Define las rutas del servidor
  server.on("/", handleRoot);      // Ruta principal
  server.on("/led/on", handleLEDOn); // Ruta para encender el LED
  server.on("/led/off", handleLEDOff); // Ruta para apagar el LED

  // Inicia el servidor
  server.begin();
  Serial.println("Servidor HTTP iniciado");
}

void loop() {
  // Maneja las solicitudes del servidor
  server.handleClient();
}
