//Incluimos las bibliotecas

#include <Wire.h>
#include <Adafruit_ADS1015.h>
#include "sensor_humedad.h";
#include "sensor_salinidad.h";
#include "sensor_temperatura.h";
#include "sensor_iluminacion.h"


//Sensor humedad
Adafruit_ADS1115 miSensor(0x48);        // Inicializar sensor en la address 0x48
const int MIN_HUMEDAD = 20475;      //Medimos valor en seco
const int MAX_HUMEDAD = 10115;      //Medimos valor en agua
const int PIN_ADC_HUMEDAD = 0;
SensorHumedad sensorHumedad;


//Sensor salinidad
const int POWER_PIN_SAL = 5;              // Digital I/O pin, Global variable
const int MAX_SALINIDAD = 20000;        //Medicion con una cantidad elevada de sal
const int MIN_SALINIDAD = 8000;            //Medicion con poca cantidad de sal
const int MEDICIONES_SALINIDAD = 20;    //Numero de MEDICIONES_SALINIDAD
const int PIN_ADC_SAL = 1;
SensorSalinidad sensorSalinidad;

//Sensor Temperatura
const double PUNTO_CORTE = 0.79; // Valor de punto de corte con el eje de ordenadas (0Y)
const double VALOR_PENDIENTE = 0.033; // Valor de la pendiente
const double INCREMENTO_T = 2.23; //Diferencia entre la temperatura teórica y la del ambiente
const int MV_MAXIMO = 4096;
const int BITS_MAXIMO = 32767;
const int PIN_ADC_TEMPERATUA = 2;
SensorTemperatura sensorTemperatura;

//Sensor ilimunación
const int PIN_ADC_ILUMINACION = 3;
SensorIluminacion sensorIluminacion;

void setup() {

  Serial.begin(9600);
  miSensor.begin();                //Inicializar miSensor
  delay(1000);
  pinMode(POWER_PIN_SAL, OUTPUT);    //seleccionar el pin por donde saldrá el voltaje
  miSensor.setGain(GAIN_ONE);        //seleccionar el rango en el que establecerá las medidas de V
  Serial.println("Rango del ADC: +/- 4.096V (1 bit=2mV)");


  sensorHumedad = SensorHumedad(PIN_ADC_HUMEDAD, MIN_HUMEDAD, MAX_HUMEDAD,  miSensor);
  sensorSalinidad = SensorSalinidad(PIN_ADC_SAL, MEDICIONES_SALINIDAD, POWER_PIN_SAL, MAX_SALINIDAD, MIN_SALINIDAD, miSensor);
  sensorTemperatura = SensorTemperatura(PIN_ADC_TEMPERATUA, PUNTO_CORTE, VALOR_PENDIENTE, INCREMENTO_T, MV_MAXIMO, BITS_MAXIMO, miSensor);
  sensorIluminacion = SensorIluminacion(PIN_ADC_ILUMINACION, MV_MAXIMO, BITS_MAXIMO, miSensor );
}//setup

void loop() {
  int resHumedad;
  int resSal;
  double resTemperatura;
  double resIluminacion;

  resHumedad = sensorHumedad.getHumedad();
  Serial.print("El nivel de humedad es del " );
  Serial.print(resHumedad);
  Serial.println(" %");
  delay(1000);

  resSal = sensorSalinidad.getSalinidad();
  Serial.print("El nivel de salinidad es del " );
  Serial.print(resSal);
  Serial.println(" %");
  delay(1000);

  resTemperatura = sensorTemperatura.getTemperatura();
  Serial.print("La temperatura es: ");
  Serial.print(resTemperatura);
  Serial.println("ºC");

  resIluminacion = sensorIluminacion.getIluminacion();
  Serial.print("La iluminacion es:");
  Serial.print(resIluminacion);
  Serial.println(" %");



}//loop