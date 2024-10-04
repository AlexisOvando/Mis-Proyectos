#include "STF1.h"

const char* ssid = ".";
const char* pass = ".";
unsigned long ID = 1;
const char* api = ".";

station miestacion(ssid, pass, ID, api);

void setup() {
  miestacion.config(115200);
}

void loop() {
  miestacion.setData(20000); //este metodo solo admite el timepo de muestreo, recomendable >15000 miliseg 
}
