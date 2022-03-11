#include <Adafruit_INA219.h> //librería INA219 del fabricande del sensor Adafruit
#include <Wire.h> //librería para conexión A0 y A1
Adafruit_INA219 INA219_1 (0x40); // dirección I2C por defecto sin conectar A0 ni A1
Adafruit_INA219 INA219_2 (0x41); // dirección I2C con los pines de A0 conectados
//Adafruit_INA219 INA219_3 (0x45);

#include <Adafruit_MAX31865.h>
#include <SPI.h> //librería para usar el puerto de comunicación SPI
Adafruit_MAX31865 thermo = Adafruit_MAX31865(10, 11, 12, 13); //pines SPI conectados del MAX31865 al arduino
#define RREF      430.0 //Defino el valor Rref de 430ohmios determinado por el fabricante para el PT100
#define RNOMINAL  100.0 //valor ohmico de la resistencia de platino a 0°C sensor Pt100

float corriente1; //se declara las variables flotantes corriente1
float corriente2; //se declara las variables flotantesy corriente2


void setup(void) {
  Serial.begin(9600); //velocidad del puerto serial 
  INA219_1.begin(); //inicio del sensor 1
  INA219_2.begin(); ////inicio del sensor 2
  

  thermo.begin(MAX31865_3WIRE);  // Selección del RTD PT100 de tres pines RTD+, RTD- y F+
  
}

void loop(void) {

  corriente1 = INA219_1.getCurrent_mA(); //lectura del sensor INA219_1 (0x40) 

  corriente2 = INA219_2.getCurrent_mA(); //lectura del sensor INA219_1 (0x41)


  uint16_t rtdpt100 = thermo.readRTD(); //defino la lectura de 16bits de la lectura del RTD del Pt100 
  float relacion = rtdpt100; //declaro variable tipo flotante para la lectura
  relacion /= 32768; //cantidad de lecturas posibles para los 2bytes
  float temperatura=thermo.temperature(RNOMINAL, RREF); //declaro variable tipo flotante para la lectura con Rref=430ohm y Rnominal=100ohm
 
  Serial.print(temperatura); //se imprime la variable temperatura medida con el PT100
  Serial.print(","); //separador
  Serial.print((corriente1)*2); //imprimo el valor de la corriente medido con el ina219 sensor1
  Serial.print(","); //separador
  Serial.print((corriente2)*2); //imprimo el valor de la corriente medido con el ina219 sensor2
  Serial.println(";"); //separador
  delay(10000); //tiempo entre medidas de 10segundos
}
