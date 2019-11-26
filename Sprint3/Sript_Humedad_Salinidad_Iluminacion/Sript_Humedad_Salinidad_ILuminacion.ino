//Incluimos las bibliotecas
  #include "milibreria.h"
 
const int SLEEP_TIME_S=20;

//Sensor salinidad
    Adafruit_ADS1115 miSensor(0x48);        // Inicializar sensor en la address 0x48
     const int POWER_PIN_SAL = 5;              // Digital I/O pin, Global variable
    const int MAX_SALINIDAD = 20000;        //Medicion con una cantidad elevada de sal
    const int MIN_SALINIDAD = 8000;            //Medicion con poca cantidad de sal
    const int MEDICIONES_SALINIDAD = 20;    //Numero de MEDICIONES_SALINIDAD
    const int PIN_ADC_SAL = 1;

//Sensor humedad
    const int MIN_HUMEDAD = 20475;      //Medimos valor en seco
    const int MAX_HUMEDAD = 10115;      //Medimos valor en agua
    const int PIN_ADC_HUMEDAD =0;


//Sensor Temperatura
 const double PUNTO_CORTE=0.79;  // Valor de punto de corte con el eje de ordenadas (0Y)
 const double VALOR_PENDIENTE=0.033;  // Valor de la pendiente
 const double INCREMENTO_T=2.23; //Diferencia entre la temperatura teórica y la del ambiente
 const int MV_MAXIMO=4096;
 const int BITS_MINIMO=32767;
 const int PIN_ADC_TEMPERATUA=2;

 //Sensor ilimunación

 const int PIN_ADC_ILUMINACION=3;

void setup() {
 
    Serial.begin(9600);
     miSensor.begin();                //Inicializar miSensor
  delay(1000);
     pinMode(POWER_PIN_SAL, OUTPUT);    //seleccionar el pin por donde saldrá el voltaje
     miSensor.setGain(GAIN_ONE);        //seleccionar el rango en el que establecerá las medidas de V
    
    Serial.println("Rango del ADC: +/- 4.096V (1 bit=2mV)");
 

}//setup

void loop() {
    int resSal;
    int resHumedad;
    double resTemperatura;
    double resIluminacion;
    resIluminacion= leerIluminacion(miSensor, PIN_ADC_ILUMINACION, MV_MAXIMO, BITS_MINIMO);
    Serial.print("La iluminacion es:");
    Serial.print(resIluminacion);
    Serial.println(" %");
    
    /*
    resTemperatura = leerTemperatura(miSensor,PIN_ADC_TEMPERATUA, PUNTO_CORTE, VALOR_PENDIENTE, INCREMENTO_T, MV_MAXIMO, BITS_MINIMO);
    
    Serial.print("La temperatura es: ");
    Serial.print(resTemperatura);
    Serial.println("ºC");

    resSal= leerSalinidad( MEDICIONES_SALINIDAD,  POWER_PIN_SAL, miSensor, PIN_ADC_SAL, MIN_SALINIDAD ,MAX_SALINIDAD);
    Serial.print("El nivel de salinidad es del " );
    Serial.print(resSal);
    Serial.println(" %");

    resHumedad = leerHumedad( miSensor, PIN_ADC_HUMEDAD, MIN_HUMEDAD,  MAX_HUMEDAD);
    Serial.print("El nivel de humedad es del " );
    Serial.print(resHumedad);
    Serial.println(" %");
    //Hibernar la placa
   // ESP.deepSleep(SLEEP_TIME_S*1000000);
    delay(1000);
    */

}//loop
