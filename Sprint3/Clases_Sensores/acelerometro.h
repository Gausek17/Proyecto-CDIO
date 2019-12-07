#ifndef S_ACELEROMETRO_YA_INCLUIDO
#define S_ACELEROMETRO_YA_INCLUIDO
class SensorAcelerometro {

  private:
    
    uint8_t MPU9250_ADDRESS ;
    int registro;
    uint8_t escala;
    double CALIBRACION_ACX ;

  public:
    //definimos el constructor de la clase
    SensorAcelerometro() {
    }
    SensorAcelerometro( uint8_t MPU9250_ADDRESS , int registro, uint8_t escala , double CALIBRACION_ACX ) {
      
      (*this).MPU9250_ADDRESS = MPU9250_ADDRESS;
      (*this).registro = registro ;
      (*this).escala = escala;
      (*this).CALIBRACION_ACX=CALIBRACION_ACX;
    }

    void I2CwriteByte(uint8_t Address, uint8_t Register, uint8_t Data) {

      Wire.beginTransmission(Address);
      Wire.write(Register);
      Wire.write(Data);
      Wire.endTransmission();
    }
    void I2Cread(uint8_t Address, uint8_t Register, uint8_t Nbytes, uint8_t* Data)
    {
      Wire.beginTransmission(Address);
      Wire.write(Register);
      Wire.endTransmission();

      Wire.requestFrom(Address, Nbytes);
      uint8_t index = 0;
      while (Wire.available())
        Data[index++] = Wire.read();
    }


    int getAceleracion(float*datosAceleracion)
    {
      int FS_ACC = 16;
      int grandaria = 3;
      uint8_t Buf[14];
      
      I2Cread(MPU9250_ADDRESS, 0x3B, 14, Buf);

      // Convertir registros acelerometro
      float ax = (Buf[0] << 8 | Buf[1]);
      float ay = (Buf[2] << 8 | Buf[3]);
      float az = Buf[4] << 8 | Buf[5];
      ax = (ax * FS_ACC / 32768) -CALIBRACION_ACX;
      ay = ay * FS_ACC / 32768 ;
      az = az * FS_ACC / 32768 ;
      datosAceleracion[0] = ax;
      datosAceleracion[1] = ay;
      datosAceleracion[2] = az;
      

      return grandaria;
    }

};
#endif
