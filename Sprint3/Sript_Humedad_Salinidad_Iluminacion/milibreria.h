//mi libreria a continuacion

#include <Wire.h>
#include <Adafruit_ADS1015.h>

//Función para leer salinidad
//    R --> leerSalinidad --> R
//
 
int  leerSalinidad(int mediciones, int power_pin,Adafruit_ADS1115 miSensor,int input_pin,int minSalinidad ,int maxSalinidad){

  int lista[mediciones];
  int cantidadSal=0;
  double mediaMediciones;
  //Bucle para leer x mediciones y realizar la media de estas
  for(int i=0;i<mediciones;i++){
    digitalWrite( power_pin, HIGH ); //Excitar PIN
    delay(100);
    lista[i] = miSensor.readADC_SingleEnded(input_pin); // Medir el voltage
    digitalWrite( power_pin, LOW ); //Atenuar PIN
  }  
  //Bucle para sumar los valores para realizar la media de las mediciones
  for(int i=0;i<mediciones-1;i++){
    cantidadSal=cantidadSal+lista[i];
  }
  //Media de mediciones
  mediaMediciones=cantidadSal/mediciones;

  //% de salinidad a partir de la media de valores
  mediaMediciones = 100*minSalinidad/(minSalinidad-maxSalinidad)-mediaMediciones*100/(minSalinidad-maxSalinidad);
  if(mediaMediciones>100){
    mediaMediciones=100;
  } else if(mediaMediciones<0){
    mediaMediciones=0;
  }
  return mediaMediciones;
}//leerSalinidad()

//Función para leer la humedad
// R --> leerHumedad() --> R
int leerHumedad(Adafruit_ADS1115 miSensor,int pinAdc, int AirValue, int WaterValue ){

  int16_t adc0; //Tipo de dato: entero mas pequeño 16 bits soportables
  int16_t humedad;
  adc0 = miSensor.readADC_SingleEnded(pinAdc);//Indica el pin adc de donde coge la información

  //Calcular % de humedad
  humedad = 100*AirValue/(AirValue-WaterValue)-adc0*100/(AirValue-WaterValue);
  //Limitamos los valors de humedad
  if(humedad>100){
    humedad=100;
  }else if(humedad<0){
    humedad=0;
  }
  return humedad;
}//leerHumedad()

//Funcion leer temperatura
double leerTemperatura(Adafruit_ADS1115 miSensor,int pinAdc, double b, double m, double incrementoT, int mvMaximo, int bitsMinimo){

 
    int16_t adc0; // entero mas pequeño 16 bits soportables
    int16_t temperatura; // declaramos la variable humedad
    double voltajeReal;
    adc0 = miSensor.readADC_SingleEnded(pinAdc);//dice de que pin del adc va a coger la información

    voltajeReal=(adc0*mvMaximo)/bitsMinimo;
    voltajeReal=voltajeReal/1000;
    temperatura = incrementoT+(voltajeReal-b)/m;
 
 return temperatura;
}

//Función leer iluminación
// R --> leerIluminacion() --> R

double leerIluminacion(Adafruit_ADS1115 miSensor, int pinAdc,int MV_MAXIMO, int BITS_MINIMO){
  double voltajeReal;
 int adc0; //Tipo de dato: entero mas pequeño 16 bits soportables
 int16_t iluminacion; //declaramos la variable iluminacion

 

 adc0 = miSensor.readADC_SingleEnded(pinAdc);//dice de que pin del adc va a coger la información
  voltajeReal=(adc0*MV_MAXIMO)/BITS_MINIMO;
    voltajeReal=voltajeReal/1000;
double porcentajeVoltaje=(voltajeReal*100)/3.64;
  if (porcentajeVoltaje>100){
    porcentajeVoltaje=100.0;
  }
   if (porcentajeVoltaje<0){
    porcentajeVoltaje=0.0;
    
   }
   return porcentajeVoltaje;
}
