#include "STF1.h"

const char* ssid = "INFINITUM18DD";
const char* pass = "P3yFu3hNaD";
unsigned long ID = 2681745;
const char* api = "JTBYYWY0WL3TOMTR";

station miestacion(ssid, pass, ID, api);

void setup() {
  miestacion.config(115200);
}

void loop() {
  miestacion.setData(20000); //este metodo solo admite el timepo de muestreo, recomendable >15000 miliseg 
}
