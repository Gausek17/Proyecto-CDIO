
#include <Wire.h>
#include <Adafruit_ADS1015.h>

//creamos la funcion para leer salinidad
//    R --> leerSalinidad --> R
//
 
 int  leerSalinidad(int mediciones, int power_pin,Adafruit_ADS1115 miSensor,int input_pin,int minSalinidad ,int maxSalinidad){
  
    int lista[mediciones];
    int cantidadSal=0;
    double mediaMediciones;
  //Bucle para leer x mediciones y realizar la media de estas
    for(int i=0;i<mediciones;i++){
     digitalWrite( power_pin, HIGH ); // Turn on sensor
     delay(100); // espera
     lista[i] = miSensor.readADC_SingleEnded(input_pin); // Measure voltage
     digitalWrite( power_pin, LOW ); // Turn off power 
    }  
  //bucle para sumar los valores para realizar la media de las mediciones
    for(int i=0;i<mediciones-1;i++){
      cantidadSal=cantidadSal+lista[i];
    }
  //Media de mediciones
    mediaMediciones=cantidadSal/mediciones;
  
  //% de salinidad a partir de la media
    mediaMediciones = 100*minSalinidad/(minSalinidad-maxSalinidad)-mediaMediciones*100/(minSalinidad-maxSalinidad);
 	  if(mediaMediciones>100){
		  mediaMediciones=100;
	  }else if(mediaMediciones<0){
		  mediaMediciones=0;
	   } 
  
    return mediaMediciones;
 
 }//leerSalinidad()

//creamos la función para leer la humedad
// R --> leerHumedad() --> R

 int leerHumedad(Adafruit_ADS1115 miSensor,int pinAdc, int AirValue, int WaterValue ){
    
  int16_t adc0; // entero mas pequeño 16 bits soportables
  int16_t humedad; // declaramos la variable humedad
  adc0 = miSensor.readADC_SingleEnded(pinAdc);//dice de que pin del adc va a coger la información
  
  //Calcular % de humedad
    humedad = 100*AirValue/(AirValue-WaterValue)-adc0*100/(AirValue-WaterValue);
    if(humedad>100){
	    humedad=100;
	  }else if(humedad<0){
		  humedad=0;
	   }
    return humedad;
}//leerHumedad()
