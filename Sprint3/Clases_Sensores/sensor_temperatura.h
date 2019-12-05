#ifndef S_TEMPERATURA_YA_INCLUIDO
#define S_TEMPERATURA_YA_INCLUIDO
class SensorTemperatura {

  private:
    int pinAdc;
    double b; //Punto de corte
    double m; // Pendiente
    double incrementoT;
    int mvMaximo;
    int bitsMaximo;
    Adafruit_ADS1115 miSensor;

  public:

    SensorTemperatura() {
    }
    SensorTemperatura(int pinAdc, double b, double m, double incrementoT , int mvMaximo, int bitsMaximo, Adafruit_ADS1115 & miSensor ) {
      (*this).pinAdc = pinAdc;
      (*this).b = b;
      (*this).m = m;
      (*this).incrementoT = incrementoT;
      (*this).mvMaximo = mvMaximo;
      (*this).bitsMaximo = bitsMaximo;
      (*this).miSensor = miSensor;
    }

    double getTemperatura()
    {
      int16_t adc0; // entero mas pequeño 16 bits soportables
      double temperatura;
      double voltajeReal;
      adc0 = miSensor.readADC_SingleEnded(pinAdc);//dice de que pin del adc va a coger la información

      voltajeReal = (adc0 * mvMaximo) / bitsMaximo;
      voltajeReal = voltajeReal / 1000;
      temperatura = incrementoT + (voltajeReal - b) / m;

      return temperatura;
    }
};
#endif
