#ifndef CAPACITIVE_SENSOR_H_
#define CAPACITIVE_SENSOR_H_
#define DEFAULT_ANALOG_PIN A0
#define DEFAULT_SAMPLES 30
#define DEFAULT_RESISTOR 330.0F

/***
  CapacitiveSensor es un la abstracción que permite controlar un sensor
capacitivo para obtener el valor de capacitancia medido en micro faradios (mF).

  CapacitiveSensor hace uso de los siguientes pines:
    - charge_pin (OUTPUT) : Envía señales en HIGH
    - discharge_pin (INPUT) : Recibe las señales y se descarga
    - analog_pin : Pin analógico para medir la carga del capacitor
  Y utiliza los siguientes datos:
- samples : Cantidad de muestras a tomar en un ciclo de medición
    - resistor : Valor de la resistencia que se está utilizando
**/
typedef struct {
  int charge_pin;
  int discharge_pin;
  int analog_pin;

  int samples;

  float resistor;
} CapacitiveSensor;

// Crea y devuelve un nuevo CapacitiveSensor con valores por defecto y los pines
// de carga y descarga asignados
CapacitiveSensor capacitive_sensor_new(int charge_pin, int discharge_pin);

// Asigna un pin analógico al sensor. Por defecto: A0
void capacitive_sensor_set_analog(CapacitiveSensor *cs, int analog_pin);

// Asigna la cantidad de muestras a tomar. Por defecto: 30
void capacitive_sensor_set_samples(CapacitiveSensor *cs, int samples_value);

// Asigna el valor de la resistencia en F. Por defecto: 330.0F
void capacitive_sensor_set_resistor(CapacitiveSensor *cs, float resistor_value);

// Realiza una lectura de la capacitancia y devuelve un valor en micro faradios.
float capacitive_sensor_read(CapacitiveSensor);

#endif
