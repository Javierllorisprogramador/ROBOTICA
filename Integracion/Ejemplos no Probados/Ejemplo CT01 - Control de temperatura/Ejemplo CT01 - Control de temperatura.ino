/*
 * HeTPro 2017
 * Licencia, Creative Commons.
 * 
Reconocimiento: El autor permite copiar, reproducir, distribuir, comunicar públicamente la obra, realizar
obras derivadas (traducción, adaptación, etc.) y hacer de ella un uso comercial, siempre y cuando se cite
y reconozca al autor original.
hetpro-store.com
Autor: Dr. Ruben E-Marmolejo
1-Noviembre-2017
Sensor de temperatura: MCP9700

Web: https://hetpro-store.com/TUTORIALES/arduino-digitalwrite/

 */
int ventilador = 13;
int foco = 12;
int umbral = 35; //Grados centigrados
int canal0adc;
double temperatura;

void setup(){
  pinMode(ventilador,OUTPUT);  //Requiere de una etapa de potencia
  pinMode(foco,OUTPUT);        //Requiere de una etapa de potencia
  //Serial.begin(9600);
  
}

void loop(){
  canal0adc = analogRead(A0);
  temperatura = (double)((5*((double)canal0adc/1023))-(double)0.5)/0.01;
  //Serial.println(temperatura);
  
  if(temperatura > umbral){
    digitalWrite(ventilador,HIGH);  //Enfriar el sistema
    digitalWrite(foco,LOW);
  
  }
  else {
    digitalWrite(ventilador,LOW);   //Calentar el sistema
    digitalWrite(foco,HIGH);
  }
  delay(1000);
  
}