//Incluimos las bibliotecas
  #include "milibreria.h"

//Sensor salinidad
	Adafruit_ADS1115 miSensor(0x48);		// Inicializar sensor en la address 0x48
 	const int POWER_PIN_SAL = 5;			// Digital I/O pin, Global variable
	const int MAX_SALINIDAD = 20000;		//Medicion con una cantidad elevada de sal
	const int MIN_SALINIDAD = 8000;			//Medicion con poca cantidad de sal
	const int MEDICIONES_SALINIDAD = 20;	//Numero de MEDICIONES_SALINIDAD
	const int PIN_ADC_SAL = 1;

//Sensor humedad
	const int MIN_HUMEDAD = 20475;  	//Medimos valor en seco
	const int MAX_HUMEDAD = 10115;  	//Medimos valor en agua
	const int PIN_ADC_HUMEDAD =0;


//Sensor Temperatura


void setup() {
  
	Serial.begin(9600);
 	miSensor.begin();				//Inicializar miSensor

 	pinMode(POWER_PIN_SAL, OUTPUT);	//seleccionar el pin por donde saldrá el voltaje
 	miSensor.setGain(GAIN_ONE);		//seleccionar el rango en el que establecerá las medidas de V
	
	Serial.println("Rango del ADC: +/- 4.096V (1 bit=2mV)");

}//setup

void loop() {
	int resSal;
    int resHumedad;

    resSal= leerSalinidad( MEDICIONES_SALINIDAD,  POWER_PIN_SAL, miSensor, PIN_ADC_SAL, MIN_SALINIDAD ,MAX_SALINIDAD);
    Serial.print("El nivel de salinidad es del " );
    Serial.print(resSal);
    Serial.println(" %");

    resHumedad = leerHumedad( miSensor, PIN_ADC_HUMEDAD, MIN_HUMEDAD,  MAX_HUMEDAD); 
    Serial.print("El nivel de humedad es del " );
    Serial.print(resHumedad);
    Serial.println(" %");
	delay(300);
	
}//loop
