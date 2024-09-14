/*
------------------------------------------------------------------------------------
Proceso: ServoMotor1Servo2024.ino
Descripción: Probando la velocidad lenta de un solo servomotor
Fecha: 11-05-2024
Autor: José Javier LLoris Roig
Email: javierllorisprogramador@gmail.comandos
------------------------------------------------------------------------------------
*/

// Incluimos la libreria para los servo motores
   #include <Servo.h>

// Declaramos los objetos para los 4 servo motores
   Servo servo1; // servomotor1
   int ang;      // angulo de movimiento 

//----------------------------------------------------------------------------------
// Configuramos el entorno
//----------------------------------------------------------------------------------
void setup()
{
// Configuramos los pins a cada servo motor 
   servo1.attach(4);
}

//----------------------------------------------------------------------------------
// La función loop se respite conr m,tinuamente
// Es como un bucle While .T ; End en otros lenguajes de programación
//----------------------------------------------------------------------------------
void loop()
{
   // Movimientos para el primer servomotor 1 hacia adelante
   for ( ang=0; ang<180; ang++ )
   {
    servo1.write( ang );
    delay(20);
   }
   delay(1000);

   //exit(0);

   // Movimientos para el primer servomotor 1 hacia atras
   for ( ang=180; ang>0; ang-- )
   {
    servo1.write( ang );
    delay(20);
   }
   delay(1000);

}
