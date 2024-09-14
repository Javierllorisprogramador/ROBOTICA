/*
Fuente:      Ejemplo mover servos suaves con milisegundos.ino
Descripción: Ejemplo de como mover los servomotores suavemente y sin que 
             el servomotor retorne a su posición antes de moverse.
             Esta forma de mover los servomotores es perfecta para los 
             brazos roboticos o cualquier programa que use servomotores.

             Este programa sirve para Brazos Roboticos de 4 y 6 servos
             solo habría que desmarcar las lineas que se refieren a los
             servos 5 y 6. 

Código de ejemplo en:
--------------------------------------------------------------------------
Web:    https://www.youtube.com/watch?v=jsXolwJskKM
Github: https://github.com/XRobots/ServoSmoothing

*/

#include <Servo.h>

// Valor posición media 512 de los servomotores     
// Valor posición maxima 1023 de los servomotores     
// Valor posición inicial 0 de los servomotores      

#define VALUE_SERVO_MED   512     // Valor intermedio entre X y Y 
#define VALUE_SERVO_MAX  1023     // Valor inicial ( 0º ) de X y Y

int pot1 = VALUE_SERVO_MED;
int pot2 = VALUE_SERVO_MED;
int pot3 = VALUE_SERVO_MED;
int pot4 = VALUE_SERVO_MED;
int pot5 = VALUE_SERVO_MED;
int pot6 = VALUE_SERVO_MED;

float pot1Smoothed  = VALUE_SERVO_MED;    // smoothed = alisado
float pot2Smoothed  = VALUE_SERVO_MED;
float pot3Smoothed  = VALUE_SERVO_MED;
float pot4Smoothed  = VALUE_SERVO_MED;
float pot4aSmoothed = VALUE_SERVO_MED;
float pot5Smoothed  = VALUE_SERVO_MED;
float pot6Smoothed  = VALUE_SERVO_MED;

float pot1SmoothedPrev  = VALUE_SERVO_MED;    // smoothedPrev = alisado siguiente
float pot2SmoothedPrev  = VALUE_SERVO_MED;
float pot3SmoothedPrev  = VALUE_SERVO_MED;
float pot4SmoothedPrev  = VALUE_SERVO_MED;
float pot4aSmoothedPrev = VALUE_SERVO_MED;
float pot5SmoothedPrev  = VALUE_SERVO_MED;
float pot6SmoothedPrev  = VALUE_SERVO_MED;

float pot1Scaled;
float pot2Scaled;
float pot3Scaled;
float pot4Scaled;
float pot4aScaled;
float pot5Scaled;
float pot6Scaled;

unsigned long currentMillis;  // Milisegundos actuales
long previousMillis     = 0;  // Milisegundos siguientes
long interval           = 5;  // Intervalo de 5 milisegundos para tiempo

int stepFlag            = 0;  //
long previousStepMillis = 0;  //

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;
Servo servo7;

void setup() {

  //
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  pinMode(8, INPUT);
  pinMode(9, INPUT);

  //
  servo1.attach(4);
  servo2.attach(5);
  servo3.attach(6);
  servo4.attach(7);
  servo5.attach(8);
  servo6.attach(9);
  servo7.attach(10);

  //
  Serial.begin(9600);

//-------------------------> Declaración de funciones

/*
  // Función que inicializa los servomotores a la posición inicial
  void myInitServos();

  // Función que envia al puerto de serir los valores de los servomotores
  void myPrinterSerie()

  // Función mueve los servomotores
  void myServosWrite()

  // Función que calcula los valores para los servomotores a mover 
  void myCalculaPos()

  // Escala todos los valores en microsegundos
  void myScaleAll()

  // Valores para movimientos suaves 
  void myValueSmooth()

  // Marcar valores anteriores
  void myBookmarkPreValues()
*/

//-------------------------> Fin Declaración de funciones

  // Inicializa los servomotores
  myInitServos();

}

void loop() {

  // Actualizamos los milisegundos actuales
  currentMillis = millis();

  // Se inicia un ciclo cronometrado de 5 milisegundos
  if ( currentMillis - previousMillis >= interval )   
  {

      // Pasamos el valor actual en milisegundos a la posición siguiente
      previousMillis = currentMillis;

      // Calcula los valores para los servomotores a mover 
      myCalculaPos();  

      // Escala todos valores de rangos en microsegundos
      myScaleAll();

      // Valores para movimientos suaves 
      myValueSmooth();

      // Marcar valores anteriores
      myBookmarkPreValues();

      // Envia al puerto de serie los valores de los servomotores
      myPrinterSerie();

      // Muevo los servomotores
      myServosWrite();

  } 

  // Inicializa los servomotores
//  myInitServos();

  // Espera 20 milisegundos
  delay( 20 ); 

} 

void myInitServos()
{

  servo1.writeMicroseconds( VALUE_SERVO_MAX );
  servo2.writeMicroseconds( VALUE_SERVO_MAX );
  servo3.writeMicroseconds( VALUE_SERVO_MAX );
  servo4.writeMicroseconds( VALUE_SERVO_MAX );
  //servo5.writeMicroseconds( VALUE_SERVO_MAX );
  //servo6.writeMicroseconds( VALUE_SERVO_MAX );
  //servo7.writeMicroseconds( VALUE_SERVO_MAX );

}

void myServosWrite()
{

  servo1.writeMicroseconds(pot1Smoothed);                     // neck rotate
  servo2.writeMicroseconds(pot6Smoothed - pot5Smoothed);      // neck side-side
  servo3.writeMicroseconds(pot6Smoothed + pot5Smoothed);      // neck front-back
  //servo5.writeMicroseconds(pot2Smoothed);                   // eyeballs side-side
  //servo7.writeMicroseconds(pot2Smoothed);
  //servo4.writeMicroseconds(pot4Smoothed);                   // eyelids
  //servo6.writeMicroseconds(pot4aSmoothed); 
  servo4.writeMicroseconds(pot4Smoothed);                     // eyelids

}


void myCalculaPos()

{
      // step sequencer

      if ( stepFlag == 0 && currentMillis - previousStepMillis > 500 )  
      {

        pot1 = VALUE_SERVO_MED;
        pot6 = VALUE_SERVO_MED;
        stepFlag = 1;           
        previousStepMillis = currentMillis;

      }
      else if ( stepFlag == 1 && currentMillis - previousStepMillis > 1000 ) 
      {

        pot1 = VALUE_SERVO_MAX;
        pot2 = VALUE_SERVO_MAX;
        pot6 = 0;
        stepFlag = 2;           
        previousStepMillis = currentMillis;

      }
      else if ( stepFlag == 2 && currentMillis - previousStepMillis > 1500 )
      {

        pot1 = 0;
        pot6 = VALUE_SERVO_MAX;
        pot2 = 0;
        stepFlag = 3;           
        previousStepMillis = currentMillis;

      }

      if ( stepFlag == 3 && currentMillis - previousStepMillis > 1500 )
      {

        pot5 = VALUE_SERVO_MED;
        pot6 = 0;
        pot2 = VALUE_SERVO_MED;
        stepFlag = 4;           
        previousStepMillis = currentMillis;

      }

      if ( stepFlag == 4 && currentMillis - previousStepMillis > 1500 ) 
      {

        pot4 = 0;
        stepFlag = 5;           
        previousStepMillis = currentMillis;

      }

      if ( stepFlag == 5 && currentMillis - previousStepMillis > 1500 ) 
      {

        pot4 = VALUE_SERVO_MED;
        stepFlag = 1;           
        previousStepMillis = currentMillis;

      }

}

void myScaleAll()
{
      // escalar todos los potenciómetros para el rango de microsegundos del servo
    
      pot1Scaled  = ( ( pot1 - VALUE_SERVO_MED ) * -1.6 ) + 1200;
      pot2Scaled  = (   pot2 - VALUE_SERVO_MED ) + 1500;
      pot3Scaled  = (   pot3 - VALUE_SERVO_MED ) + 1500;
      pot4Scaled  = ( ( pot4 - VALUE_SERVO_MED ) * 1.2 )  + 1500;
      pot4aScaled = ( ( pot4 - VALUE_SERVO_MED ) * -1.2 ) + 1500;
      pot5Scaled  = (   pot5 - VALUE_SERVO_MED ) * 1.5;
      pot6Scaled  = (   pot6 - VALUE_SERVO_MED ) + 1650;

      pot4Scaled = constrain(pot4Scaled,900,1500);
      pot4aScaled = constrain(pot4aScaled,1500,2100);

}


void myValueSmooth()
{

      pot1Smoothed = (pot1Scaled * 0.01) + (pot1SmoothedPrev * 0.99);
      pot2Smoothed = (pot2Scaled * 0.01) + (pot2SmoothedPrev * 0.99);
      pot3Smoothed = (pot3Scaled * 0.01) + (pot3SmoothedPrev * 0.99);
      pot4Smoothed = (pot4Scaled * 0.05) + (pot4SmoothedPrev * 0.95);
      pot4aSmoothed = (pot4aScaled * 0.05) + (pot4aSmoothedPrev * 0.95);
      pot5Smoothed = (pot5Scaled * 0.01) + (pot5SmoothedPrev * 0.99);
      pot6Smoothed = (pot6Scaled * 0.01) + (pot6SmoothedPrev * 0.99);  

}

void myBookmarkPreValues()
{
      // bookmark previous values
      //bookmark previous values
    
      pot1SmoothedPrev  = pot1Smoothed;
      pot2SmoothedPrev  = pot2Smoothed;
      pot3SmoothedPrev  = pot3Smoothed;
      pot4SmoothedPrev  = pot4Smoothed;
      pot4aSmoothedPrev = pot4aSmoothed;
      pot5SmoothedPrev  = pot5Smoothed;
      pot6SmoothedPrev  = pot6Smoothed;

}

void myPrinterSerie()
{

  Serial.print( pot1Smoothed   + String( " - " ) );
  Serial.print( pot2Smoothed   + String( " - " ) );
  Serial.print( pot3Smoothed   + String( " - " ) );
  Serial.print( pot4Smoothed   ); //+ String( " - " ) );
  //Serial.print( pot5Smoothed   + String( " - " ) );
  //Serial.print( pot6Smoothed + String( " - " ) );
  Serial.println(); 

}
