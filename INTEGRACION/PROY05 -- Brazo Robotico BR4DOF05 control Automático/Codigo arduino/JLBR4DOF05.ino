/*
Proceso: BR4DOF05.INO
Descripción: Robot Brazo Robotico con 4DOF y en modo Automático
Fecha: 11-05-2024
Autor: José Javier LLoris Roig
Email: javierllorisprogramador@gmail.com

Tarjetas para el harware:
--------------------------------------------------------------------------
Tarjeta arduino uno Rev3  = Tarjeta base arduino uno Rev
HC-06                     = Tarjeta Bluetooch con 4 pines
Sensor Shield V5.0        = Tarjeta para conectar 16 servomotores 

Musica optenida:
--------------------------------------------------------------------------
La musica es la melodia de Pac-Man, es necesario conectar un zumbador
Mas melodias en: https://github.com/robsoncouto/arduino-songs

Información adicional para el Bluetooch HC-06 
--------------------------------------------------------------------------
  Set baudrate to 9600
  AT+BAUD1  OK1200  Sets the baud rate to 1200
  AT+BAUD2  OK2400  Sets the baud rate to 2400
  AT+BAUD3  OK4800  Sets the baud rate to 4800
  AT+BAUD4  OK9600  Sets the baud rate to 9600
  AT+BAUD5  OK19200 Sets the baud rate to 19200
  AT+BAUD6  OK38400 Sets the baud rate to 38400
  AT+BAUD7  OK57600 Sets the baud rate to 57600
  AT+BAUD8  OK115200  Sets the baud rate to 115200
  AT+BAUD9  OK230400  Sets the baud rate to 230400
  AT+BAUDA  OK460800  Sets the baud rate to 460800
  AT+BAUDB  OK921600  Sets the baud rate to 921600
  AT+BAUDC  OK1382400 Sets the baud rate to 1382400

  Algunos comandos AT:
  --------------------
  AT+RESET - Reinicia el módulo
  AT+ORGL - Valores de fabrica
  AT+NAMExxxxx - Cambiar nombre
  AT+BAUDx - Cambiar velocidad
  AT+PINxxxx - Cambiar PIN de conexion

**************************************************************************
* NOTAS DEL AUTOR                                                        *
**************************************************************************  

*/

#include <Servo.h>
#include <SoftwareSerial.h>

#define ROBOT_NAME "JLR_Robotics"

// Constantes para el bluetooch
#define BLUETOOTH_SPEED  9600  // 34800
#define BLUETOOTH_PINRX     9  // Pin  9 para RX del bluetooch
#define BLUETOOTH_PINTX    10  // Pin 10 para TX del bluetooch

// Constantes para los Leds
#define LEDAZUL_PIN       11   // Pin led azul
#define LEDROJO_PIN       12   // Pin led rojo
#define LEDVERD_PIN       13   // Pin led verde

// Constante para el zumbador
#define ZUMBADOR_PIN       3   // Pin zumbador

// Constante para la velocidad de los servomotores
//---------------------------------------->#define SPEEDDELAY        15   // Pin zumbador

//******************************************************************************
// NOTA:  modificar los digitos por el nombre de la constante en la llamada
//        que mueve los servos
//******************************************************************************

// Creamos el objeto mySerial para el bluetooch
// Connect the HC-06 TX to Arduino pin 10 RX.
// Connect the HC-06 RX to Arduino pin 11 TX.
SoftwareSerial mySerial( BLUETOOTH_PINRX, BLUETOOTH_PINTX); 

//---> Define los pines para cada servomotor
const int servoPin1 = 4;  // Servo1 - Cadera
const int servoPin2 = 5;  // Servo2 - Antebrazo
const int servoPin3 = 6;  // Servo3 - Codo
const int servoPin4 = 7;  // Servo4 - Pinza

//---> Creamos los objetos para los 4 Servomotores
Servo servo1;             // Servo1 - Cadera
Servo servo2;             // Servo2 - Antebrazo
Servo servo3;             // Servo3 - Codo
Servo servo4;             // Servo4 - Pinza

/*---> Variables para el Blink LED */

// ledState used to set the LED (LOW - HIGH)
// ledState estado del LED (LOW - HIGH)
int ledState = LOW;  

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
// will store last time LED was updated

// Almacenará la última vez que se actualizó el LED
unsigned long previousMillis = 0;  
// constants won't change:
const long interval = 10; //1000;  // interval at which to blink (milliseconds) por defecto poner 500
// check to see if it's time to blink the LED; that is, if the difference
// between the current time and last time you blinked the LED is bigger than
// the interval at which you want to blink the LED.
unsigned long currentMillis = 0;
/*----------------------------------------------------------------------*/

// Creamos el objeto mySerial para el bluetooch
//SoftwareSerial mySerial( BLUETOOTH_PINRX, BLUETOOTH_PINTX); 

//---> Declaramos las variables para bluetooch
//char nBaudios ='4';   // Baudios a 9600  

//---> Declaramos las variables de lectura serie
char a;               //
//char cReadSerial;   //
String readString;    //

// Notas para la melodia del Pac-Man
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST        0

/*--------------------------------------------------------------------------------------*/
/* Función:                                                                             */
/* Descripción:                                                                         */
/* Devuelve: Nada                                                                       */
/*--------------------------------------------------------------------------------------*/
void MusicInit() {

// change this to make the song slower or faster
int tempo = 105;

// change this to whichever pin you want to use
int buzzer = 3;

// notes of the moledy followed by the duration.
// a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
// !!negative numbers are used to represent dotted notes,
// so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!
int melody[] = {

  // Pacman
  // Score available at https://musescore.com/user/85429/scores/107109
  NOTE_B4, 16, NOTE_B5, 16, NOTE_FS5, 16, NOTE_DS5, 16, //1
  NOTE_B5, 32, NOTE_FS5, -16, NOTE_DS5, 8, NOTE_C5, 16,
  NOTE_C6, 16, NOTE_G6, 16, NOTE_E6, 16, NOTE_C6, 32, NOTE_G6, -16, NOTE_E6, 8,

  NOTE_B4, 16,  NOTE_B5, 16,  NOTE_FS5, 16,   NOTE_DS5, 16,  NOTE_B5, 32,  //2
  NOTE_FS5, -16, NOTE_DS5, 8,  NOTE_DS5, 32, NOTE_E5, 32,  NOTE_F5, 32,
  NOTE_F5, 32,  NOTE_FS5, 32,  NOTE_G5, 32,  NOTE_G5, 32, NOTE_GS5, 32,  NOTE_A5, 16, NOTE_B5, 8
};

// sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
// there are two values per note (pitch and duration), so for each note there are four bytes
int notes = sizeof(melody) / sizeof(melody[0]) / 2;

// this calculates the duration of a whole note in ms
int wholenote = (60000 * 4) / tempo;

int divider = 0, noteDuration = 0;

  // iterate over the notes of the melody.
  // Remember, the array is twice the number of notes (notes + durations)
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

    // calculates the duration of each note
    divider = melody[thisNote + 1];
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }

    // we only play the note for 90% of the duration, leaving 10% as a pause
    tone(buzzer, melody[thisNote], noteDuration * 0.9);

    // Wait for the specief duration before playing the next note.
    delay(noteDuration);

    // stop the waveform generation before the next note.
    noTone(buzzer);
  }
}
/*--------------------------------------------------------------------------------------*/
/* Función: BlinkLed()                                                                  */
/* Descripción:                                                                         */
/* Devuelve: Nada                                                                       */
/*--------------------------------------------------------------------------------------*/
void BlinkLed() {

  currentMillis = millis();

  if (currentMillis - previousMillis >= interval){

     // save the last time you blinked the LED
     previousMillis = currentMillis;

     // if the LED is off turn it on and vice-versa:
     if (ledState == LOW){
        ledState = HIGH;
     } else {
       ledState = LOW;
     }

    // set the LED with the ledState of the variable:
    digitalWrite( LEDROJO_PIN, ledState);
  }
}
/*--------------------------------------------------------------------------------------*/
/* Función: ConectBluetooch()                                                           */
/* Descripción:                                                                         */
/* Devuelve: Nada                                                                       */
/*--------------------------------------------------------------------------------------*/
void ConectBluetooch() {

  //Serial.begin(BLUETOOTH_SPEED);		// comunicacion de monitor serial a 9600 bps
  //Serial.println("Listo");	// escribe Listo en el monitor
  //mySerial.begin(BLUETOOTH_SPEED);		// comunicacion serie entre Arduino y el modulo a 38400 bps

  // Configuramos la velocidad para Bluetooth
  //Serial.begin(BLUETOOTH_SPEED); 
  //mySerial.begin(BLUETOOTH_SPEED);

  // Configuramos la velocidad para Bluetooth
  Serial.begin(BLUETOOTH_SPEED); 
  mySerial.begin(BLUETOOTH_SPEED);

  // Configuramos la velocidad de consulta al puerto de serie
  mySerial.setTimeout(1);

  // Espera 20 milisegundos
  delay(20); 

  // Activamos los pin del bluetooch 
  digitalWrite(BLUETOOTH_PINRX, HIGH);
  digitalWrite(BLUETOOTH_PINTX, HIGH);

//---------------------------------------probar con attach  AQUI---------------------------------------

  // Mensajes al puerto de serie
  Serial.print("---> Listo el Bluetooch");	

  // Should respond with OK
  Serial.print("AT test command is: ");
  Serial.print("AT");
  waitResponse();

  // Set baud rate to 9600
  Serial.print("Set baud rate: ");
  mySerial.print("AT+BAUD4");
  waitResponse();

  // Should respond with its version
  Serial.print("AT version is: ");
  mySerial.print("AT+VERSION");
  waitResponse();

  // Set pin
  Serial.print("Set pin: ");
  mySerial.print("AT+PIN1234");
  waitResponse();

  // Set the name to ROBOT_NAME
  Serial.print("Set the name: ");
  String rnc = String("AT+NAME") + String(ROBOT_NAME);
  mySerial.print(rnc);
  waitResponse();

  Serial.println("The configurations are done!");
  Serial.println("---> FIN Configuramos el bluetooch");

}
/*--------------------------------------------------------------------------------------*/
/* Función: waitResponse()                                                              */
/* Descripción:                                                                         */
/* Devuelve: Nada                                                                       */
/*--------------------------------------------------------------------------------------*/
void waitResponse() {

    delay(2000);

    while (mySerial.available()) {
        Serial.write(mySerial.read());
    }

    Serial.write("\n");
}
/*--------------------------------------------------------------------------------------*/
/* Función:                                                                             */
/* Descripción:                                                                         */
/* Devuelve: Nada                                                                       */
/*--------------------------------------------------------------------------------------*/
void moveServoSmoothly(Servo servo, int targetPos, int stepDelay) {

  int currentPos = servo.read();

  if (currentPos < targetPos) {
    for (int i = currentPos; i <= targetPos; i++) {
      servo.write(i);
      delay(stepDelay);
    }
  } else {
    for (int i = currentPos; i >= targetPos; i--) {
      servo.write(i);
      delay(stepDelay);
    }
  }
}
/*--------------------------------------------------------------------------------------*/
/* Función: setup()                                                                     */
/* Descripción:                                                                         */
/* Devuelve: Nada                                                                       */
/*--------------------------------------------------------------------------------------*/
void setup() {

  // Configuramos la velocidad trasmisión del puerto de serie
  Serial.begin( BLUETOOTH_SPEED ); 

  // Mensajes al puerto de serie
  Serial.println( "        CONFIGURANDO ENTORNO" );
  Serial.println( "        --------------------" );

  // Configuramos los pines para los servomotores
  servo1.attach( servoPin1 );
  servo2.attach( servoPin2 );
  servo3.attach( servoPin3 );
  servo4.attach( servoPin4 );
 
  // Configuramos loa 4 servomotores como entradas
  pinMode( servoPin1, OUTPUT );  
  pinMode( servoPin2, OUTPUT );  
  pinMode( servoPin3, OUTPUT );  
  pinMode( servoPin4, OUTPUT );  

  // Configuramos los led como salida
  pinMode( LEDROJO_PIN, OUTPUT );     
  pinMode( LEDVERD_PIN, OUTPUT );     
  pinMode( LEDAZUL_PIN, OUTPUT );     

  // Encendemos led verde 
  digitalWrite( LEDVERD_PIN, HIGH ); 

  // Configuramos y activamos el bluetooch
  ConectBluetooch();

  // Inicia la musica para indicar que el robot se va a poner en marcha  
  MusicInit();

  // Inicia la demostración del ROBOT 
  //InitDance();
  // Desconectamos el Led rojo
  //digitalWrite(LEDROJO_PIN, LOW);
  //delay(500);
  // Conectamos el Led azul,rojo y esperamos 3000 milisegundos
  //digitalWrite(LEDAZUL_PIN, HIGH); 
  //digitalWrite(LEDVERD_PIN, HIGH); 
  //delay(3000);                       
  // Desconectamos el Led azul
  //digitalWrite(LEDAZUL_PIN, LOW);  

}
/*--------------------------------------------------------------------------------------*/
/* Función: InitDance()                                                                 */
/* Descripción:                                                                         */
/* Devuelve: Nada                                                                       */
/*--------------------------------------------------------------------------------------*/
void InitDance() {

  // Mensajes al puerto de serie
  Serial.println( "\t Inicializamos Servomotores" );  

  // Inicializamos los servomotores
  moveServoSmoothly( servo1, 180, 15 ); //90
  moveServoSmoothly( servo2, 180, 15 );//180
  moveServoSmoothly( servo3, 180, 15 );//0
  moveServoSmoothly( servo4,   0, 15 );//0

  // Espera 500 milisegundos
  delay(500); 

  // Mensajes al puerto de serie
  Serial.println( "\t ---> Iniciamos Baile" );  

  // Comenzamos la demostración del ROBOT
  for (int repeat = 1; repeat < 2; repeat++ )
  {
    // Hacemos parpadear el led rojo
    // BlinkLed();

    // Realiza el baile de los servomotores
    for (int i = 1; i < 2; i++)
    {
      if( i == 1)
      {

        Serial.println("\t Dentro del If(i == 1)");

        // Mueve los servomotores a diferentes posiciones aleatorias
        // en la primera vuelta.
        // El servomotor 2 y 3 le indico que el maximo hacia abajo 
        // 150 grados para que no choque con la caja de conexiones
        moveServoSmoothly( servo1, random( 0, 180 ), 15 );
        moveServoSmoothly( servo2, random( 0, 150 ), 15 );//180//150
        moveServoSmoothly( servo3, random( 0, 150 ), 15 );//180
        moveServoSmoothly( servo4, random( 0,  90 ), 15 );
        /*
        moveServoSmoothly( servo4, random( 0,  90 ), 15 );
        moveServoSmoothly( servo3, random( 0, 180 ), 15 );
        moveServoSmoothly( servo2, random( 0,  90 ), 15 );
        moveServoSmoothly( servo1, random( 0, 180 ), 15 );
        */
        moveServoSmoothly( servo2,   0, 15 );
        moveServoSmoothly( servo2, 150, 15 );
        moveServoSmoothly( servo2,  90, 15 );

        moveServoSmoothly( servo3,   0, 15 );
        moveServoSmoothly( servo3, 150, 15 );
        moveServoSmoothly( servo3,  90, 15 );

        moveServoSmoothly( servo1, 180, 15 );
        moveServoSmoothly( servo1,   0, 15 );

        moveServoSmoothly( servo4, 180, 15 );

      }  
      else
      {   

        Serial.println("\t Dentro del if(i != 1)");

        // Mueve los servomotores a diferentes posiciones aleatorias
        // en la segunda vuelta.
        // El servomotor 2 y 3 le indico que el maximo hacia arriba 
        // 150 grados para que no choque con la caja de conexiones
        // que le indique en el if( i == 1) anteriormente.
        moveServoSmoothly( servo1, random( 180, 0 ), 15 );
        moveServoSmoothly( servo2, random( 180, 0 ), 15 );
        moveServoSmoothly( servo3, random( 180, 0 ), 15 );
        moveServoSmoothly( servo4, random(  90, 0 ), 15 );
       /*
        moveServoSmoothly( servo4, random(  90, 0 ), 15 );
        moveServoSmoothly( servo3, random( 180, 0 ), 15 );
        moveServoSmoothly( servo2, random( 90, 0 ), 15 );
        moveServoSmoothly( servo1, random( 180, 0 ), 15 );
        */
       /*
        moveServoSmoothly( servo2,  90, 15 );
        moveServoSmoothly( servo2,  0, 15 );
        moveServoSmoothly( servo3, 180, 15 );
        moveServoSmoothly( servo3,   0, 15 );
        moveServoSmoothly( servo1,  0, 15 );
        moveServoSmoothly( servo1,  90, 15 );
        moveServoSmoothly( servo4, 0, 15 );
      */

        moveServoSmoothly( servo2,   0, 15 );
        moveServoSmoothly( servo2, 150, 15 );
        moveServoSmoothly( servo2,  90, 15 );

        moveServoSmoothly( servo3,   0, 15 );
        moveServoSmoothly( servo3, 150, 15 );
        moveServoSmoothly( servo3,  90, 15 );

        moveServoSmoothly( servo1, 180, 15 );
        moveServoSmoothly( servo1,   0, 15 );
        moveServoSmoothly( servo4, 180, 15 );

      }
    }   

  // Espera 500 milisegundos
  delay(500); 

  // Mensajes al puerto de serie
  Serial.println( "\t Total número de bailes: " + String(repeat) );
  Serial.println( "\t --------->FIN baile" );

  }

  // Mensajes al puerto de serie
  Serial.println( "\t ---> PREPARADO PARA TRABAJAR" );
    
}  
/*--------------------------------------------------------------------------------------*/
/* Función: loop()                                                                      */
/* Descripción:                                                                         */
/* Devuelve: Nada                                                                       */
/*--------------------------------------------------------------------------------------*/
void loop(){

  // Encendemos led rojo 
  digitalWrite(LEDROJO_PIN, HIGH );  

  // Llamamos a la función que realiza la demostración del ROBOT
  InitDance();

  // conectamos el Led azul
  digitalWrite(LEDAZUL_PIN, HIGH);  

  // Espera 5000 milisegundos
  delay(5000); 

  // Desconectamos el Led azul y rojo
  digitalWrite(LEDAZUL_PIN, LOW);  
  digitalWrite(LEDROJO_PIN, LOW);  

}
