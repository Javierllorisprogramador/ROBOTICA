/*
Proceso: ServoVelocidadLenta.ino
Descripción: Probando la velocidad lenta de un solo servomotor
Fecha: 11-05-2024
Autor: José Javier LLoris Roig
Email: javierllorisprogramador@gmail.comandos

HISTORICO:
--------------------------------------------------------------------------
02-09-24 Si parcheo la parte del código que devuelve el servo a su 
         posición inicial ( que es la parte que resta en el FOR )
         funciona bien.

*/

// Incluimos la libreria para los servo motores
   #include <Servo.h>

// Declaramos los objetos para los 4 servo motores
   Servo servo1; // servomotor1
   Servo servo2; // servomotor2

// Declaramos de variables
   int ang;      // angulo de movimiento 

//------------------------------------------------------------------------
// Configuramos el entorno
//------------------------------------------------------------------------
void setup()
{

// Configuramos los pins a cada servo motor 
   servo1.attach(4);  // servomotor 1 en pin 9
   servo2.attach(6); // servomotor 2 en pin 10
}

//------------------------------------------------------------------------
// La función loop se respite conr m,tinuamente
// Es como un bucle While .T ; End en otros lenguajes de programación
//------------------------------------------------------------------------
void loop()
{

//--------------------------------------------------------------- 
// Movimientos para el servo motor 1
//--------------------------------------------------------------- 

   // Movimientos para el primer servomotor 1 hacia adelante
   for ( ang=0; ang<180; ang++ )
   {
      servo1.write( ang );
      delay(20);
   }
     delay(1000);

/*
   // Movimientos para el primer servomotor 1 hacia atras
   for ( ang=180; ang>0; ang-- )
   {
      servo1.write( ang );
      delay(20);
   }
   delay(1000);
*/   

//--------------------------------------------------------------- 
// Movimientos para el servo motor 2
//--------------------------------------------------------------- 

   // Movimientos para el primer servomotor 2 hacia adelante
   for ( ang=0; ang<180; ang++ )
   {
      servo2.write( ang );
      delay(20);
   }
   delay(1000);

   // Movimientos para el primer servomotor 2 hacia atras
   for ( ang=90; ang>0; ang-- ) 
   {
      servo2.write( ang );
      delay(20);
   }
   delay(1000);
   //exit(0);

}
