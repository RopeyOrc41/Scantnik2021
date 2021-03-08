#include "Adafruit_CCS811.h"
#include <Wire.h>
#include "cactus_io_BME280_I2C.h"

const int pin = 9;//Buzzer activo


Adafruit_CCS811 ccs; // Crear objeto CCS811

BME280_I2C bme (0x76);// Usar el sensor con dirección // Crear objeto BME280


void setup() {
  Serial.begin(9600);
  
pinMode(9, OUTPUT);// Salida del buzzer
pinMode(10, OUTPUT);// Salida del Led

  Serial.println("CCS81 (CO2+compuesto organico volatil), GUVA_S12SD (radiación UV) y BME20 (Temperatura, presión y humedad) ");

if (!bme.begin()) {
Serial.println("No se ha encontrado el sensor BME280, comprobar conexiones");
while (1);
}

bme.setTempCal(-1);// Estaba leyendo la temperatura positiva por lo que resta 1

  if(!ccs.begin()){
    Serial.println("No se ha encontrado el sensor BME280, comprobar conexiones");
    while(1);
  }

  // Esperar hasta que el sensor esté listo
  while(!ccs.available());
}

void loop() {

  digitalWrite(10, HIGH); // Encender el Led
  
  if(ccs.available()){
    if(!ccs.readData()){

      Serial.print(ccs.geteCO2());
      Serial.print("ppm ");
      Serial.println(ccs.getTVOC());
      Serial.print("COV ");
    }
   
    else{
      Serial.println("ERROR!");
      while(1);
    }
  }
  bme.readSensor();
  

Serial.print(bme.getPressure_MB()); Serial.print(" mb\t"); // Presión en milibaros

Serial.print(bme.getHumidity()); Serial.print(" %\t\t"); // Porcentaje de humedad ambiente

Serial.print(bme.getTemperature_C()); Serial.print(" *C\t"); //Temperatura en grados centígrados



delay(1000); // 2 segundos de retraso

  
  float sensorVoltage; 
  float sensorValue;
 
  sensorValue = analogRead(A0);
  sensorVoltage = sensorValue/1024*5;
  Serial.print("sensor reading = ");
  Serial.print(sensorValue);
  Serial.println("");
  Serial.print("sensor voltage = ");
  Serial.print(sensorVoltage);
  Serial.println(" V");
  delay(1000);

}
