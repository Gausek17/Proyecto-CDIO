#include <Wire.h>
#include <Adafruit_ADS1015.h>

Adafruit_ADS1115 miSensor(0x48); // Inicializar sensor en la address 0x48
//La fórmula utilizada para obtener la temperatura es la siguiente: (Vo-b)/m, siendo Vo el voltaje obtenido con el sensor
const double b=0.79;  // Valor de punto de corte con el eje de ordenadas (0Y)
const double m=0.033;  // Valor de la pendiente
const double incrementoT=2.23; //Diferencia entre la temperatura teórica y la del ambiente
const int mvMaximo=4096;
const int bitsMinimo=32767;
void setup() {
 
  Serial.begin(9600);
  Serial.println("Inicializando...");
  miSensor.begin(); //Incializar miSensor
  Serial.println("Ajustando la ganancia...");
  miSensor.setGain(GAIN_ONE);
 
  Serial.println("Toma medidas del canal AIN0");
 
  Serial.println("Rango del ADC: +/- 4.096V (1 bit=2mV)");
}

void loop() {
 
int16_t adc0; // entero mas pequeño 16 bits soportables
int16_t temperatura; // declaramos la variable humedad
double voltajeReal;
adc0 = miSensor.readADC_SingleEnded(0);//dice de que pin del adc va a coger la información

voltajeReal=(adc0*mvMaximo)/bitsMinimo;
voltajeReal=voltajeReal/1000;
temperatura = incrementoT+(voltajeReal-b)/m;

Serial.print("AIN0: ");
Serial.println(voltajeReal);
Serial.print("La temperatura es:");
Serial.print(temperatura);
Serial.println("ºC");

//delay(5000);

}
