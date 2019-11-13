//Incluimos las bibliotecas
  #include "milibreria.h"

//Sensor salinidad

 Adafruit_ADS1115 miSensor(0x48); // Inicializar sensor en la address 0x48
  const int power_pin = 5; // Digital I/O pin, Global variable
  const int maxSalinidad = 20000;//Medicion con una cantidad elevada de sal
  const int minSalinidad = 8000;//Medicion con poca cantidad de sal
  const int mediciones = 20;//Numero de mediciones
  const int input_pin = 1; // Analog input pin sensor de Salinidad
// Sensor humedad
  //const int humedad_pin = 
  const int AirValue = 20475;  // Medimos valor en seco
  const int WaterValue = 10115;  // Medimos valor en agua
  const int pinAdc =0;//dice de que pin del adc va a coger la información

void setup() {
  // put your setup code here, to run once:

Serial.begin(9600);
  Serial.println("Inicializando...");//mensaje en pantalla
  miSensor.begin(); //Inicializar miSensor
  pinMode(power_pin, OUTPUT);//seleccionar el`pin por donde saldrá el voltaje
  Serial.println("Ajustando la ganancia...");
  miSensor.setGain(GAIN_ONE);//seleccionar el rango en el que establecerá las medidas de V
  
  Serial.println("Toma medidas del canal AIN0");//mensajes en pantalla que indican las funciones de los anteriores comandos
  
  Serial.println("Rango del ADC: +/- 4.096V (1 bit=2mV)");//mensaje en pantalla que indica el rango de medicion del ADC

}//setup

void loop() {
  // put your main code here, to run repeatedly:
     int resSal;
     int resHumedad;
     resSal= leerSalinidad( mediciones,  power_pin, miSensor, input_pin, minSalinidad ,maxSalinidad);// llamamos a la funcion de salinidad
     Serial.print("El nivel de salinidad es del " );
     Serial.print(resSal);
     Serial.println(" %");
     resHumedad = leerHumedad( miSensor, pinAdc, AirValue,  WaterValue); // llamamos a la funcion de humedad 
     Serial.print("El nivel de humedad es del " );
     Serial.print(resHumedad);
     Serial.println(" %");

  delay(300);

 
  
}//loop
