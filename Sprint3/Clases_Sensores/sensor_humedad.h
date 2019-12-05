#ifndef S_HUMEDAD_YA_INCLUIDO
#define S_HUMEDAD_YA_INCLUIDO
class SensorHumedad {

  private:
    int pinAdc;
    int valorAire;
    int valorAgua;
    Adafruit_ADS1115 miSensor;

  public:

    SensorHumedad() {
    }
    SensorHumedad(int pinAdc, int valorAire, int valorAgua, Adafruit_ADS1115 & miSensor ) {
      (*this).pinAdc = pinAdc;
      (*this).valorAire = valorAire;
      (*this).valorAgua = valorAgua;
      (*this).miSensor = miSensor;
    }

    int getHumedad()
    {
      int16_t adc0; //Tipo de dato: entero mas pequeño 16 bits soportables
      int humedad;
      adc0 = miSensor.readADC_SingleEnded(pinAdc);//Indica el pin adc de donde coge la información
      //Calcular % de humedad
      humedad = 100 * valorAire / (valorAire - valorAgua) - adc0 * 100 / (valorAire - valorAgua);
      //Limitamos los valors de humedad
      if (humedad > 100) {
        humedad = 100;
      } else if (humedad < 0) {
        humedad = 0;
      }
      return humedad;
    }
};
#endif
