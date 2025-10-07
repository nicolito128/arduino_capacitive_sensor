# capacitive sensor

Un sensor capacitivo es capaz de medir la capacitancia de un componente a través de la cargar y descargar del capacitor, siempre que se conozca el tiempo y la resistencia del circuito RC; es decir, utilizamos la siguiente fórmula:

    T = R * C

* T : Tiempo
* R : Resistencia
* C : Capacitancia

## Principio

La librería toma una serie de muestras (samples) del tiempo de carga del capacitor y devuelve el valor promedio expresado en micro faradios. Por defecto la cantidad de muestras a tomar por ciclo es de `30` y la resistencia base `330k`.

## Uso

Inicialice un nuevo `CapacitiveSensor`:

```c
    CapacitiveSensor cs = capacitive_sensor_new(CHARGE_PIN, DISCHARGE_PIN);
```

Ahora puede hacer uso de la siguiente función en el `loop`:

```c
     capacitive_sensor_read(cs);
```

## Cabeceras

```c
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

// Asigna el valor de la resistencia. Por defecto: 330
void capacitive_sensor_set_resistor(CapacitiveSensor *cs, float resistor_value);

// Realiza una lectura de la capacitancia y devuelve un valor en micro faradios.
float capacitive_sensor_read(CapacitiveSensor);
```

## Programa ejemplo

El siguiente programa para Arduino hace uso de la librería para obtener la capacitancia y encender el `LED_BUILTIN` cuando se supera un umbral:

```cpp
#include "capacitive_sensor.h"

#define CHARGE_PIN 4
#define DISCHARGE_PIN 3

CapacitiveSensor cs = capacitive_sensor_new(CHARGE_PIN, DISCHARGE_PIN);

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  Serial.begin(9600);
}

void loop(){
  float microF = capacitive_sensor_read(cs);
  long nanoF = (long)(microF * 1000.0);

  if (nanoF > 650) {
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }

  Serial.print(nanoF);
  Serial.println(" nF");
  delay(10);
}
```

