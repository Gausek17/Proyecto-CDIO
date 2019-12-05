#ifndef S_SALINIDAD_YA_INCLUIDO
#define S_SALINIDAD_YA_INCLUIDO
class SensorSalinidad {

  private:
    int pinAdc;
    int mediciones;
    int powerPin;
    int maxSalinidad;
    int minSalinidad;
    Adafruit_ADS1115 miSensor;

  public:

    SensorSalinidad() {
    }
    SensorSalinidad(int pinAdc, int mediciones, int powerPin, int maxSalinidad, int minSalinidad, Adafruit_ADS1115 & miSensor ) {
      (*this).pinAdc = pinAdc;
      (*this).mediciones = mediciones;
      (*this).powerPin = powerPin;
      (*this).maxSalinidad = maxSalinidad;
      (*this).minSalinidad = minSalinidad;
      (*this).miSensor = miSensor;
    }

    int getSalinidad()
    {
      int lista[mediciones];
      int cantidadSal = 0;
      int mediaMediciones;
      //Bucle para leer x mediciones y realizar la media de estas
      for (int i = 0; i < mediciones; i++) {
        digitalWrite( powerPin, HIGH ); //Excitar PIN
        delay(100);
        lista[i] = miSensor.readADC_SingleEnded(pinAdc); // Medir el voltage
        digitalWrite( powerPin, LOW ); //Atenuar PIN
      }
      //Bucle para sumar los valores para realizar la media de las mediciones
      for (int i = 0; i < mediciones - 1; i++) {
        cantidadSal = cantidadSal + lista[i];
      }
      //Media de mediciones
      mediaMediciones = cantidadSal / mediciones;

      //% de salinidad a partir de la media de valores
      mediaMediciones = 100 * minSalinidad / (minSalinidad - maxSalinidad) - mediaMediciones * 100 / (minSalinidad - maxSalinidad);
      if (mediaMediciones > 100) {
        mediaMediciones = 100;
      } else if (mediaMediciones < 0) {
        mediaMediciones = 0;
      }
      return mediaMediciones;

    }
};
#endif
