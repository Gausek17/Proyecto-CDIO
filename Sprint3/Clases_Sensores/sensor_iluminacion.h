#ifndef S_ILUMINACION_YA_INCLUIDO
#define S_ILUMINACION_YA_INCLUIDO
class SensorIluminacion {

  private:
    int pinAdc;
    int mvMaximo;
    int bitsMaximo;
    Adafruit_ADS1115 miSensor;

  public:

    SensorIluminacion() {
    }
    SensorIluminacion(int pinAdc, int mvMaximo, int bitsMaximo, Adafruit_ADS1115 & miSensor ) {
      (*this).pinAdc = pinAdc;
      (*this).mvMaximo = mvMaximo;
      (*this).bitsMaximo = bitsMaximo;
      (*this).miSensor = miSensor;
    }

    double getIluminacion()
    {
      double voltajeReal;
      int adc0; //Tipo de dato: entero mas pequeño 16 bits soportables
      int16_t iluminacion; //declaramos la variable iluminacion
      double porcentajeVoltaje;
      
      adc0 = miSensor.readADC_SingleEnded(pinAdc);//dice de que pin del adc va a coger la información
      voltajeReal = (adc0 * mvMaximo) / bitsMaximo;
      voltajeReal = voltajeReal / 1000;
      porcentajeVoltaje = (voltajeReal * 100) / 3.64;
      if(porcentajeVoltaje >= 100){
        porcentajeVoltaje= 100;
      }else if(porcentajeVoltaje >= 0){
        porcentajeVoltaje = 0;
      }
      return porcentajeVoltaje;
    }
};
#endif
