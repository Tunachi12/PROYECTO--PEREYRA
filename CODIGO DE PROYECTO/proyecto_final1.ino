#include "Arduino.h"
#include "DFRobotDFPlayerMini.h"
#include <SoftwareSerial.h>

// Configuración del DFPlayer Mini
SoftwareSerial mySerial(10, 9); // Pines RX y TX
DFRobotDFPlayerMini myDFPlayer;

// Configuración de los sensores táctiles
const int touchPins[] = {2, 3, 4, 5, 6, 7, 8}; // Pines de sensores táctiles
const int numSensors = sizeof(touchPins) / sizeof(touchPins[0]);
bool sensorState[numSensors] = {false}; // Estado previo de los sensores

// Configuración del Rotary Encoder
const int pinCLK = 13; // Pin A del encoder
const int pinDT = 12; // Pin B del encoder
int lastCLK = LOW; // Último estado del pin CLK
int offset = 0; // Offset inicial para las pistas
const int maxOffset = 14; // Número máximo de pistas (ajustar según tu SD)

// Cola para manejar múltiples pistas
int playQueue[numSensors] = {0}; // Cola de pistas a reproducir
bool isPlaying = false; // Estado de reproducción actual

void setup() {
  // Configuración de pines de sensores táctiles
  for (int i = 0; i < numSensors; i++) {
    pinMode(touchPins[i], INPUT);
  }

  // Configuración de pines del rotary encoder
  pinMode(pinCLK, INPUT);
  pinMode(pinDT, INPUT);

  // Configuración del DFPlayer Mini
  mySerial.begin(9600);
  Serial.begin(9600);

  if (!myDFPlayer.begin(mySerial)) { // Inicializa el DFPlayer Mini
    Serial.println("No se pudo iniciar el DFPlayer Mini");
    while (true); // Detiene el programa si el DFPlayer falla
  }

  myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD); // Selecciona la tarjeta SD
}

void loop() {
  // Verifica la rotación del rotary encoder
  int currentCLK = digitalRead(pinCLK);
  if (currentCLK != lastCLK && currentCLK == HIGH) {
    if (digitalRead(pinDT) != currentCLK) {
      offset += numSensors; // Incrementa el offset
    } else {
      offset -= numSensors; // Decrementa el offset
    }
    offset = constrain(offset, 0, maxOffset); // Limita el offset dentro del rango
    Serial.print("Offset actual: ");
    Serial.println(offset);
  }
  lastCLK = currentCLK;

  // Revisión de los sensores táctiles
  for (int i = 0; i < numSensors; i++) {
    bool isTouched = digitalRead(touchPins[i]) == HIGH;

    if (isTouched && !sensorState[i]) {
      int trackNumber = offset + (i + 1); // Calcula la pista ajustada por el offset
      Serial.print("Tecla ");
      Serial.print(i + 1);
      Serial.print(" presionada. Agregando pista ");
      Serial.println(trackNumber);

      playQueue[i] = trackNumber; // Agrega la pista a la cola
      sensorState[i] = true; // Actualiza el estado del sensor
    }

    if (!isTouched && sensorState[i]) {
      sensorState[i] = false; // Actualiza el estado del sensor
    }
  }

  // Reproduce las pistas en la cola
  if (!isPlaying) {
    for (int i = 0; i < numSensors; i++) {
      if (playQueue[i] > 0) { // Si hay una pista en la cola
        myDFPlayer.play(playQueue[i]); // Reproduce la pista
        Serial.print("Reproduciendo pista ");
        Serial.println(playQueue[i]);
        playQueue[i] = 0; // Limpia la cola para esta pista
        isPlaying = true; // Indica que se está reproduciendo una pista
        delay(300); // Pausa para evitar sobrecargas 
        isPlaying = false; // Permite reproducir la siguiente pista
        break; // Sal del bucle para reproducir una pista a la vez
      }
    }
  }
}