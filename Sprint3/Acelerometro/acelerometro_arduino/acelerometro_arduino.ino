//GND - GND
//VCC - VCC
//SDA - Pin 2
//SCL - Pin 14

#include <Wire.h>

#define    MPU9250_ADDRESS            0x68
#define    MAG_ADDRESS                0x0C

#define    GYRO_FULL_SCALE_250_DPS    0x00
#define    GYRO_FULL_SCALE_500_DPS    0x08
#define    GYRO_FULL_SCALE_1000_DPS   0x10
#define    GYRO_FULL_SCALE_2000_DPS   0x18

#define    ACC_FULL_SCALE_2_G        0x00
#define    ACC_FULL_SCALE_4_G        0x08
#define    ACC_FULL_SCALE_8_G        0x10
#define    ACC_FULL_SCALE_16_G       0x18


const int sleepTimeS = 30;


//Funcion auxiliar lectura
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





//CONFIGURACIÓN WAKE ON MOTION
void I2CwriteByte(uint8_t Address, uint8_t Register, uint8_t Data)
{
   Wire.beginTransmission(Address);
   Wire.write(Register);
   Wire.write(Data);
   Wire.endTransmission();
}

void setup()
{
   Wire.begin();
   Serial.begin(9600);
  Serial.println("Inicializando...");
  Serial.println("Configurando acelerónetro...");
   // Configurar acelerometro
   I2CwriteByte(MPU9250_ADDRESS, 28, ACC_FULL_SCALE_16_G);

   



 I2CwriteByte( MPU9250_ADDRESS, 0x6B, 0x00);//primer registro
 I2CwriteByte( MPU9250_ADDRESS, 0x6C, 0x07);//segundo registro
 I2CwriteByte( MPU9250_ADDRESS, 0x1D, 0x0F);//tercer registro
 I2CwriteByte( MPU9250_ADDRESS, 0x38, 0x40);//cuarto registro
 I2CwriteByte( MPU9250_ADDRESS, 0x69 , 0xC0);//quinto registro
 I2CwriteByte( MPU9250_ADDRESS, 0x1F,  0x80);//sexto registro
 I2CwriteByte( MPU9250_ADDRESS, 0x1E,  0x06);//séptimo registro
 I2CwriteByte( MPU9250_ADDRESS, 0x6B,  0x20);//octavo registro


}
 

void loop()
{

   // ---  Lectura acelerometro y giroscopio ---
   uint8_t Buf[14];
   int FS_ACC = 16;
   double CALIBRACION_ACX = 31.95;
   int FS_GYRO = 2000;



   I2Cread(MPU9250_ADDRESS, 0x3B, 14, Buf);

//   // Convertir registros acelerometro
   float ax = (Buf[0] << 8 | Buf[1]);
   float ay = (Buf[2] << 8 | Buf[3]);
   float az = Buf[4] << 8 | Buf[5];

   ax = (ax*FS_ACC/32768)-CALIBRACION_ACX;
   ay = ay*FS_ACC/32768 ;
   az = az*FS_ACC/32768 ;

//   // Acelerometro
   Serial.println("Lectura Acelerometro");
   Serial.print("AX=");
   Serial.print(ax , 2 );
   Serial.print("g");
   Serial.print("\t");
   Serial.print("AY=");
   Serial.print(ay, 2);
   Serial.print("g");
   Serial.print("\t");
   Serial.print("AZ=");
   Serial.print(az, 2);
   Serial.println("g");
//



   delay(1000);
     ESP.deepSleep(sleepTimeS * 1000000);
     
}
