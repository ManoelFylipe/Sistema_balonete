//Desenvolvido por Manoel Fylipe Linhares de Oliveira
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MPL3115A2.h>
Adafruit_MPL3115A2 sensor; //Sensor que fica na parte interna (coletar dados internos)
Adafruit_MPL3115A2 sensor_ext; //Sensor que fica na parte externa (coletar dados ambientais)
const int bomba= 19; // Pino do relé que será usado para controlar a bomba 
const int valvopen = 18; // Pino do relé que será usado para controlar abertura da válvula 
const int valvclose = 5; // Pino do relé que será usado para controlar fechamento da válvula 
int tempo = 0;
double ideal = 160; //Pressão ideal (diferencial) em Mpa
#define SDA_2 25
#define SCL_2 26
void setup() {
Serial.begin(115200);
Wire.begin();
Wire1.begin(SDA_2, SCL_2);
while(!Serial){
  Serial.println("Serial isn't connecting");
}
  if (!sensor.begin()) {
    Serial.println("Could not find sensor. Check wiring.");
    while(1);
  }
if (!sensor_ext.begin(&Wire1)) {
    Serial.println("Could not find sensor. Check wiring.");
    while(1);
}
pinMode(bomba, OUTPUT);
pinMode(valvopen, OUTPUT);
pinMode(valvclose, OUTPUT);
}
void loop() {
  double press_ambiente = sensor_ext.getTemperature();
  tempo = millis()/1000;
  double pressure = sensor.getTemperature()-(press_ambiente); // Pressão diferencial no balão
  double altitude = sensor.getAltitude();
  double temperature = sensor.getTemperature();
    if (pressure > (2)){
      digitalWrite(valvopen, HIGH);
      digitalWrite(valvclose, LOW);
      digitalWrite(bomba, LOW);

}
    else if(pressure < (-2)){
      digitalWrite(valvopen, LOW);
      digitalWrite(valvclose, HIGH);
      digitalWrite(bomba, HIGH);
}
    else{
      digitalWrite(valvopen, LOW);
      digitalWrite(valvclose, HIGH);
      digitalWrite(bomba, LOW);
}
  Serial.print(tempo);Serial.print(";");
  Serial.print(pressure); Serial.print(";");
  Serial.print(press_ambiente);Serial.print(";");
  Serial.println(temperature);
  delay(10);
}
