/*
  Fichero:     Ejemplo BR-04 - OR mascara.ino
  Descripción: Ejemplo del uso de dos ojos mecatronicos 
  Autor:       José Javier LLoris Roig
*/
#include <Servo.h>//libreria para controlar servomotores

//Declaramos nuestras variables

int posicion_inicial_h=90;

int desplaza_derecha = 125;
int desplaza_izquierda= 55;

int posicion_inicial_v=80;
int desplaza_arriba = 45;
int desplaza_abajo= 115;

int velocidad = 10;             //Velocidad de desplazamiento de los servos
int intervalo = 500;            //Tiempo de espera entre movimientos

//Declaramos nuestros servos
Servo servo_horizontal;
Servo servo_vertical;


void setup() {
  
Serial.begin(9600);                             //le indicamos al arduino con que velocidad se comunicara 
  
  servo_horizontal.attach(4);                   //Configuramos pines
  servo_vertical.attach(5);

  servo_horizontal.write(posicion_inicial_h);     // Se llevan los servomotores a su posicion inicial
  servo_vertical.write(posicion_inicial_v);

  delay(5000);       
                              
}

void loop() {
     derecha_izquierda();
     arriba_abajo();    
}


void derecha_izquierda(){
    
      for(int i=posicion_inicial_h; i<=desplaza_derecha; i++){
         servo_horizontal.write(i);      
         delay(velocidad);
     }
     delay(intervalo);
     for(int i=desplaza_derecha; i>=desplaza_izquierda; i--){    
         servo_horizontal.write(i);      
         delay(velocidad);
     }
     delay(intervalo);
     for(int i=desplaza_izquierda; i<=desplaza_derecha; i++){    
         servo_horizontal.write(i);
         delay(velocidad);
     }
     delay(intervalo);
     for(int i=desplaza_derecha; i>=posicion_inicial_h; i--){    
         servo_horizontal.write(i);      
         delay(velocidad);
     }
     delay(intervalo);
}


void  arriba_abajo(){

  for(int i=posicion_inicial_v; i>=desplaza_arriba; i--){ 
         servo_vertical.write(i);
         delay(velocidad);
     }
     delay(intervalo);
     for(int i=desplaza_arriba; i<=desplaza_abajo; i++){    
         servo_vertical.write(i);
         delay(velocidad);
     }
     delay(intervalo);
     for(int i=desplaza_abajo; i>=desplaza_arriba; i--){    
         servo_vertical.write(i);
         delay(velocidad);
     }     
     delay(intervalo);
     for(int i=desplaza_arriba; i<=posicion_inicial_v; i++){    
         servo_vertical.write(i);
         delay(velocidad);
     }
     delay(intervalo);
}
