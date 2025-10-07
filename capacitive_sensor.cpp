#include "capacitive_sensor.h"
#include "Arduino.h"

unsigned long start_time;   // Tiempo de inicio en cada iteración
unsigned long elapsed_time; // Tiempo transcurrido
float mF;                   // Micro Faradios

CapacitiveSensor capacitive_sensor_new(int charge_pin, int discharge_pin) {
  CapacitiveSensor cs = {};

  cs.charge_pin = charge_pin;
  cs.discharge_pin = discharge_pin;
  cs.analog_pin = DEFAULT_ANALOG_PIN;

  cs.samples = DEFAULT_SAMPLES;

  cs.resistor = DEFAULT_RESISTOR;

  return cs;
}

void capacitive_sensor_set_analog(CapacitiveSensor *cs, int analog_pin) {
  cs->analog_pin = analog_pin;
}

void capacitive_sensor_set_samples(CapacitiveSensor *cs, int samples_value) {
  if (samples_value > 0 && samples_value <= 1000) {
    cs->samples = samples_value;
  }
}

void capacitive_sensor_set_resistor(CapacitiveSensor *cs,
                                    float resistor_value) {
  cs->resistor = resistor_value;
}

float capacitive_sensor_read(CapacitiveSensor cs) {
  mF = 0;
  start_time = 0;
  elapsed_time = 0;

  for (int i = 0; i < cs.samples; ++i) {
    start_time = millis();
    digitalWrite(cs.charge_pin, HIGH);

    while (analogRead(cs.analog_pin) < 648) { // 647 es el 63.2% de 1023
    }

    elapsed_time = millis() - start_time;
    // convertimos los faradios (F) a micro faradios (mF)
    mF += ((float)elapsed_time / cs.resistor) * 1000;

    // Limpiamos los datos en los pines
    digitalWrite(cs.charge_pin, LOW);
    pinMode(cs.discharge_pin, OUTPUT);
    digitalWrite(cs.discharge_pin, LOW);
    pinMode(cs.discharge_pin, INPUT);
  }

  // Promedio de la muestra
  mF = (mF / cs.samples);
  return mF;
}
