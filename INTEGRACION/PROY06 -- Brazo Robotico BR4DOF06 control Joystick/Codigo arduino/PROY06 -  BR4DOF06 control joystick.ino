/*
Proceso:     Brazo Robotico BR4DOF06 Joystick.ino
Descripción: Brazo Robotico ARM manejado con Joystick KY-023 y 4 servos
Fecha:       25-08-2024
Autor:       José Javier LLoris Roig
Email:       javierllorisprogramador@gmail.com

Librerias:
--------------------------------------------------------------------------
Servo.h   => Libreria para el manejo de servos
NO setjmp.h  => Libreria para el control de errores/excepciones
             El archivo de cabecera de biblioteca estándar de C setjmp.h
             se utiliza para proporcionar saltos en la ejecución del
             código y así modificar drásticamente el flujo de ejecución
             del programa.

JLR_ErrorSystem.h => Funciones que controla los errores/excepciones
JLR_Bluetooch.h   => Funciones que conecta el bluetooch

--------------------------------------------------------------------------
Documentación de servos en arduino, errores y de interés:
--------------------------------------------------------------------------
Documentación: https://docs.arduino.cc/learn/electronics/servo-motors/
Errores: https://proyectosconarduino.com/curso/errores-de-compilacion/
         https://fidiasrodriguez.com/como-evitar-los-5-errores-mas-
               comunes-cuando-hacemos-un-programa-en-arduino/
         https://www.az-delivery.de/es/blogs/azdelivery-blog-fur-arduino-
               und-raspberry-pi/kodierungsfehler-schnell-beheben   
         https://programarfacil.com/podcast/resolver-errores-arduino/            

También consultar los errores en foro de arduino:
https://forum.arduino.cc/

De interes:
https://www.b4x.com/b4r.html B4R es una herramienta de desarrollo 100%
gratuita para programas nativosde Arduino, ESP8266 y ESP32

Escalamiento y función map()
https://arduino.cl/escalamiento-y-funcion-map/
https://forum.arduino.cc/t/como-funciona-la-funcion-map/647033

--------------------------------------------------------------------------
Tarjetas para el harware:
--------------------------------------------------------------------------
Tarjeta arduino uno Rev3 = 1 x Tarjeta base arduino uno Rev
Sensor Shield V5.0       = 1 x Tarjeta para conectar 16 servomotores 
Joystcik KY-023          = 1 x Joystick modelo KY-023
Servos SG90              = 4 x Sevomotores SG90
Brazo Robotico 3D        = 1 x 4 grados de libertad 

Comprado el Brazo Robotico 3D en: https://www.sinoning.com tienen muy
buena calidad. Los nuevos los imprimiré con mi nueva impresora 3D
--------------------------------------------------------------------------
Simuladores de control para servos, nos ayuda para posicionar los servos
--------------------------------------------------------------------------

FlowArm LSS                => Simulador para 3/4/5 grados libertad en cm
Web: https://wiki.lynxmotion.com/info/wiki/lynxmotion/view/ses-software/
     lss-flowarm/

FlowArm PLTW               => Simulador para 4 grados de libertad en cm
Web: https://wiki.lynxmotion.com/info/wiki/lynxmotion/view/ses-software/
     flowarm-pltw/

LSS Configuration Software => Simulador para 1 grados de libertad en cm
Web: https://wiki.lynxmotion.com/info/wiki/lynxmotion/view/ses-v2/
     lynxmotion-smart-servo/lss-configuration-software/

--------------------------------------------------------------------------
Conexión cableado del Joystick KY-023:
--------------------------------------------------------------------------

  Debemos de posicionar el joystick KY-023 de esta forma:

                           Parte superior 
                    ----------------------------
                    ||   M  ---      ---       ||
                    ||   R  ---   ---   ---    ||
  Parte izquierda   ||   N  ---      ---       ||  Parte derecha
                    ||   A  ---                ||
                    ||   Z  ---                ||
                    ----------------------------
                         Parte inferior

  Conexión del cableado:

  M => Cable marron neutro
  R => Cable rojo fase
  N => Cable naranja
  A => Cable amarillo 
  Z => Cable azul pin digital

  INPUT_PULLUP:
  Se le agrega al pin una resistencia de pull-up interna y se configura
  como entrada.
  pinMode( BUTTON_PIN, INPUT_PULLUP ); 


Donde se instalan las librerias de arduino por defecto:
--------------------------------------------------------------------------
Documentos>Arduino>libraries.
--------------------------------------------------------------------------

--------------------------------------------------------------------------
Notas del autor:
--------------------------------------------------------------------------

*/

//-------------------------> Librerias de arduino y personales

// Libreria para el manejo de servomotores
#include <Servo.h>

//-------------------------> Librerias personales de mi programa

// Control de errores/excepciones 
//#include <JLR_ErrorSystem.h>

// Fuente que conecta el bluetooch
#include <JLR_Bluetooch.h>


// The following define selects which electronics board you have.
// Please choose the name from boards.h that matches your setup
// si hemos definido la constante MOTHERBOARD se agrega MOTHERBOARD
// y todas las que hagan falta para tal funcion.
//#ifndef MOTHERBOARD
//  #define MOTHERBOARD 33
//#endif

//#define STRING_VERSION_CONFIG_H __DATE__ " " __TIME__ // build date and time




//-------------------------> Declaración de costantes
#define VX_PIN        A0   // Pin analógico del Joystick VX al pin A0
#define VY_PIN        A1   // Pin analógico del Joystick VY al pin A1
#define BUTTON_PIN     2   // Pin digital Joystick para el botón Pull-Up
#define SPEEDSERIE  9600   // Velocidad del puerto de serie
#define TIME_MILLIS  200   // Tiempo de espera en milisegundos

#define SPEEDSERVO    40  // Velocidad de movimiento para los servos
#define GRADO_MIN      0  // Grados minimo de los servos
#define GRADO_MAX    180  // Grados maximo de los servos

// Mi nombre para el proyecto
//#define ROBOT_NAME "JLR-Robotics"

//-------------------------> Declaración de variables para el Joystick
int valX = 0;             // Variable guarda valores leidos de X
int valY = 0;             // Variable guarda valores leidos de Y
int valZ = 0;             // Variable guarda valores leidos de Z pull-up

int Valor_Xmin =    0;    // Variable del valor mínimo para X    0
int Valor_Xmax = 1023;    // Variable del valor máximo para X 1023
int Valor_Ymin =    0;    // Variable del valor mínimo para Y    0
int Valor_Ymax = 1023;    // Variable del valor máximo para Y 1023

//-------------------------> Declaramos variables para los servomotores
Servo servo1;             // Creamos el objeto Servo1 - Cadera
Servo servo2;             // Creamos el objeto Servo2 - Antebrazo
Servo servo3;             // Creamos el objeto Servo3 - Codo
Servo servo4;             // Creamos el objeto Servo4 - Pinza

const int servoPin1 = 4;  // Pin para Servo1 - Cadera
const int servoPin2 = 5;  // Pin para Servo2 - Antebrazo
const int servoPin3 = 6;  // Pin para Servo3 - Codo
const int servoPin4 = 7;  // Pin para Servo4 - Pinza

int numServo = 1;         // Número de servomotor actual 

// Control de errores
// Esta variable jmp_buf exception_mng tiene que estar así declarada
// no tocarla como esta, pertenece al archivo cabecera <setjmp.h>
/*
jmp_buf exception_mng;  // Buffer para los mensajes de error
int nError_ValorA = 5;  // Variable para la gestión de errores
int nError_ValorB = 1;  // Variable para la gestión de errores
int nError_ValorC;      // Variable para la gestión de errores
*/

//void waitResponse();
//void myConectBluetooch(); 


/*----------------------------------------------------------------------*/
/* Función:     setup()                                                 */
/* Descripción: Configura el entorno antes de ejecutarse el loop()      */
/* Devuelve:    Nada                                                    */
/*----------------------------------------------------------------------*/
void setup()
{
  // Espera 200 milisegundos. Si usas un brazo robotico en 3D no es 
  // necesario pero si es de metal, mejor realizar esta pausa
  delay( TIME_MILLIS ); 

  // Conectamos al puerto de serie. Velocidad de trasmisión en baudios
  Serial.begin( SPEEDSERIE ); 

  // Mensajes al puerto de serie
  Serial.println();
  Serial.println( "1.- CONFIGURANDO ENTORNO" );

  // Configuramos el joystick de X y de Y como entrada s
  pinMode( VX_PIN, INPUT );
  pinMode( VY_PIN, INPUT );

  // Configuramos el botón Pull-Up del joystick como entrada
  // INPUT_PULLUP. Se le agrega al pin una resistencia de pull-up
  // interna y se configura como entrada.
  pinMode( BUTTON_PIN, INPUT_PULLUP ); 

  // Colocamos la resistencia pull-Up en la entrada del pulsador que
  // la mantenga en estado alto sino pulsamos.
  digitalWrite( BUTTON_PIN, HIGH );  

  // Configuramos los pines para los servomotores
  servo1.attach( servoPin1 );  // Servo1 - Cadera
  servo2.attach( servoPin2 );  // Servo2 - Antebrazo
  servo3.attach( servoPin3 );  // Servo3 - Codo
  servo4.attach( servoPin4 );  // Servo4 - Pinza


  // Configuramos los 4 servos como salida
  /*
  pinMode( servoPin1, OUTPUT );  
  pinMode( servoPin2, OUTPUT );  
  pinMode( servoPin3, OUTPUT );  
  pinMode( servoPin4, OUTPUT );  
  */

  // Inicializamos los servos 
  InitServos();

  // Mensajes al puerto de serie
  Serial.println( "1.- CONFIGURANDO ENTORNO OK" );

  // Realizamos un baile de servos para comprobar que todos 
  // funcionam bien. 
  InitDemostration();

}
/*----------------------------------------------------------------------*/
/* Función:     InitServos()                                            */
/* Descripción: Inicializa los servos                                   */
/* Devuelve:    Nada                                                    */
/*----------------------------------------------------------------------*/
void InitServos()
{
  // Mensajes al puerto de serie
  Serial.println( "2.- INICIALIZAMOS SERVOS" );

  moveServoSmoothly( servo4, 180, SPEEDSERVO + 20 );  // Servo4 - Pinza      
  moveServoSmoothly( servo1, 180, SPEEDSERVO + 20 );  // Servo1 - Cadera     //180
  moveServoSmoothly( servo2, 170, SPEEDSERVO + 20 );  // Servo2 - Antebrazo //170
  moveServoSmoothly( servo3, 170, SPEEDSERVO + 20 );  // Servo3 - Codo       //170

  // Mensajes al puerto de serie
  Serial.println( "2.- INICIALIZAMOS SERVOS OK" );

  // Espera 700 milisegundos
  delay( TIME_MILLIS ); 

}
/*----------------------------------------------------------------------*/
/* Función:     myreadX()                                               */
/* Descripción: Lee el valor vía puerto analogico 0 para X              */
/* Devuelve:    Nada                                                    */
/*----------------------------------------------------------------------*/
void myreadX()
{
  // Leemos la entrada de X analogica
  valX = analogRead( VX_PIN );

  // Mensajes al puerto de serie
  Serial.print( "  X:" + String( valX ) );

}
/*----------------------------------------------------------------------*/
/* Función:     myreadY()                                               */
/* Descripción: Lee el valor vía puerto analogico 1 para Y              */
/* Devuelve:    Nada                                                    */
/*----------------------------------------------------------------------*/
void myreadY()
{
  // Leemos la entrada de Y analogica
  valY = analogRead( VY_PIN );

  // Mensajes al puerto de serie
  Serial.print( "  Y:" + String( valY ));

}
/*----------------------------------------------------------------------*/
/* Función:     myreadZ()                                               */
/* Descripción: Lee el valor digital para Y,botón pull-up del joystick  */
/* Devuelve:    Nada                                                    */
/*----------------------------------------------------------------------*/
void myreadZ()
{
  // Leemos la entrada de Z digital del botón Pull-up del Joystick
  // Valor 1 => No han pulsado el botón Pull-up del joystick
  // Valor 0 => Han pulsado el botón Pull-up del joystick
  valZ = ! digitalRead( BUTTON_PIN );

  // Mensajes al puerto de serie
  Serial.print( "\tZ:" + String( valZ ) );

}
/*----------------------------------------------------------------------*/
/* Función:     myvalMaxMin()                                           */
/* Descripción: Configuramos los valores Maximos y Minimos de X y Y     */
/* Devuelve:    Nada                                                    */
/*----------------------------------------------------------------------*/
void xxxmyvalMaxMin()
{
  //-------------------------> Configuramos los valores Max/Min para X

  // Movimiento del eje X del lado Izquierdo  
  if( valX > 511 )     
  {
    Valor_Xmax = 1023 - valX + 511; 
    Valor_Xmin = 0;                 
  }
  // Movimiento del eje X del lado Derecho 
  else if( valX < 511 )           
  {   
    Valor_Xmax = 1023;              
    Valor_Xmin = 511 - valX;       
  }

  //-------------------------> Configuramos los valores Max/Min para Y

  // Movimiento del eje Y hacia Arriba  
  if( valY > 511 ) 
  {                 
    Valor_Ymax = 1023 - valY + 511; 
    Valor_Ymin = 0;                 
  }
  // Movimiento del eje Y hacia Abajo 
  else if( valY < 511 )  
  {
    Valor_Ymax = 1023;              
    Valor_Ymin = 511 - valY; 
  }

}
/*----------------------------------------------------------------------*/
/* Función: moveServoSmoothly(Servo servo, int targetPos, int stepDelay)*/
/* Parametros:  servo     => Objeto servo a mover                       */
/*              targetPos => Posición destino del servo                 */
/*              stepDelay => Velocidad de movimiento del servo          */
/* Descripción: Mueve los servos rápidos o lentos en función del valor  */ 
//              stepDelay.                                              */
/* Devuelve:    Nada                                                    */
/*----------------------------------------------------------------------*/
void moveServoSmoothly(Servo servo, int targetPos, int stepDelay)
{
  int currentPos = servo.read();

  if ( currentPos < targetPos ){

    for ( int i = currentPos; i <= targetPos; i++ )
    {
      servo.write( i );
      delay( stepDelay );
    }

  }else{

    for ( int i = currentPos; i >= targetPos; i-- ) 
    {
      servo.write( i );
      delay( stepDelay );
    }

  }

/*

  if ( currentPos < targetPos )
  {

    for ( int i = currentPos; i <= targetPos; i++ )
    {
      servo.write( i );
      delay( stepDelay );
    }

  return ;
  

  }
  
  if ( currentPos < targetPos )
  { 

    for ( int i = currentPos; i >= targetPos; i-- ) 
    {
      servo.write( i );
      delay( stepDelay );
    }

  return ;

  }

//  return ;
*/

}
/*----------------------------------------------------------------------*/
/* Función:     loop()                                                  */
/* Descripción: Función que se ejecuta automaticamente en bucle         */
/* Devuelve:    Nada                                                    */
/*----------------------------------------------------------------------*/
void loop()
{
    // Control de errores 
    //myErrorSystem();

    // Leemos entrada digital de Pull-up
    myreadZ();     

    // Valor de valZ == 1 han pulsado el botón Pull-up
    // Valor de valZ == 0 NO han pulsado el botón Pull-up
    // LOW  = Baja intensidad 0v
    // HIGH = Alta intensidad 5v
    // Si han pulsado el botón Pull-up valZ valdrá LOW si no HIGH
    // También podemos hacer la comparación de este modo:
    // if ( BUTTON_PIN == LOW )
    if ( valZ == 1 ){
         numServo++;

      if ( numServo >= 5 ){
         numServo = 1;
      }
    }

    myreadX();      // Leemos entrada analogica del joystick de X 
    myreadY();      // Leemos entrada analogica del joystick de Y
    myvalMaxMin();  // Configuramos los valores Max/Min de X y Y 

    // Mensajes al puerto de serie
    Serial.print( "  NumServo: " + String( numServo ) );

    // Mapeamos los valores de X y Y.
    // La función map() reasigna un número de un rango a otro
    // La variable valX será el valor de izquierda(0°) y derecha(180°)
    // La variable valY será el valor de arriba(0°) y abajo (180°)
    valX = map ( valX, Valor_Xmin, Valor_Xmax, 0, 180 );  
    valY = map ( valY, Valor_Ymin, Valor_Ymax, 0, 180 ); 

    // Esta condición no es necesaria si tu Brazo Robotico funciona 
    // correctamente., servomotor no da golpes. 
    // En mi caso, en un brazo robotico 3D el servo 3 en la posición 
    // 0º o 180º empieza a dar golpes. Con esta condición lo soluciono
    // para que no llegue a un valor 0º o inferior o 180º o superior
    if( valY >= 180 ){
      valY = 175;
    } else if ( valY <= 0 ){
      valY = 2;
    } 

    // Mensajes al puerto de serie
    Serial.print( "  Pullup: " + String( valZ ) );
    Serial.print( "  ValorX: " + String( valX ) );
    Serial.println( "  ValorY: " + String( valY ) );

    //
    /*
    digitalWrite( servoPin1, LOW );
    digitalWrite( servoPin2, LOW );
    digitalWrite( servoPin3, LOW );
    digitalWrite( servoPin4, LOW );
    */

    // Los servos 1 y 4 Horizontal
    // Los servos 2 y 3 Vertical
    switch( numServo )
    {
        // Servo1 - Cadera - en movimiento Horizontal
        case 1:
      //    digitalWrite( servoPin1, HIGH );  
          moveServoSmoothly( servo1, valX, SPEEDSERVO ); 
          //digitalWrite( servoPin1, LOW );  
          break;

        // Servo2 - Antebrazo - en movimiento Vertical
        case 2:
        //  digitalWrite( servoPin2, HIGH );  
          moveServoSmoothly( servo2, valY, SPEEDSERVO ); 
          //digitalWrite( servoPin2, LOW );  
          break;

        // Servo3 - Codo - en movimiento Vertical
        case 3:
          //digitalWrite( servoPin3, HIGH );  
          moveServoSmoothly( servo3, valY, SPEEDSERVO ); 
          //digitalWrite( servoPin3, LOW );  
          break;

        // Servo4 - Pinza - en movimiento Horizontal
        case 4:
          //digitalWrite( servoPin4, HIGH );  
          moveServoSmoothly( servo4, valX, SPEEDSERVO ); 
          //digitalWrite( servoPin4, LOW );  
          break;
    }

    // Espera 200 milisegundos
    delay( TIME_MILLIS ); 

}

/*--------------------------------------------------------------------------------------*/
/* Función: InitDemostration()                                                                 */
/* Descripción: Realiza el baile de presentación                                        */
/* Devuelve: Nada                                                                       */
/*--------------------------------------------------------------------------------------*/
void InitDemostration()
{
  // Mensajes al puerto de serie
  Serial.println( "3.- INICIAMOS DEMOSTRACIÓN" );

  // Comenzamos la demostración del baile
  for (int repeat = 1; repeat < 2; repeat++ )
  {
    // Mueve los servos a diferentes posiciones aleatorias
    // en la primera vuelta.
    // El servos 2 y 3 le indico que el maximo hacia abajo 
    // 150 grados para que no choque con la caja de conexiones
    /*
    moveServoSmoothly( servo1, random( GRADO_MIN, GRADO_MAX ),SPEEDSERVO );
    moveServoSmoothly( servo2, random( GRADO_MIN, GRADO_MAX ),SPEEDSERVO );
    moveServoSmoothly( servo3, random( GRADO_MIN, GRADO_MAX ),SPEEDSERVO );
    moveServoSmoothly( servo4, random( GRADO_MIN, GRADO_MAX ),SPEEDSERVO );
    */
  }  

  // Inicializamos los servos 
  //InitServos();

  // Mensajes al puerto de serie
  Serial.println( "4.- POSICIONAMOS SERVOS PARA TRABAJAR" );

  //moveServoSmoothly( servo1,  90, SPEEDSERVO );
  moveServoSmoothly( servo4,  0, SPEEDSERVO );
  moveServoSmoothly( servo2, 45, SPEEDSERVO );
  moveServoSmoothly( servo3, 90, SPEEDSERVO );


  // Mensajes al puerto de serie
  Serial.println( "4.- POSICIONAMOS SERVOS PARA TRABAJAR OK" );

  // Mensajes al puerto de serie
  Serial.println( "3.- INICIAMOS DEMOSTRACIÓN OK" );

  // Espera 200 milisegundos
  delay( TIME_MILLIS ); 

  // Mensajes al puerto de serie
  Serial.println( "5.- PREPARADO PARA TRABAJAR" );
  Serial.println(); Serial.println();

  // Espera 200 milisegundos
  delay( TIME_MILLIS ); 

}   

/*----------------------------------------------------------------------*/
/* Función:     myvalMaxMin()                                           */
/* Descripción: Configuramos los valores Maximos y Minimos de X y Y     */
/* Devuelve:    Nada                                                    */
/*----------------------------------------------------------------------*/
void myvalMaxMin()
{
  //-------------------------> Configuramos los valores Max/Min para X

  // Movimiento del eje X del lado Izquierdo  
  if( valX > 511 )     
  {
    Valor_Xmax = 1023 - valX + 511; 
    Valor_Xmin = 0;                 
  }
  // Movimiento del eje X del lado Derecho 
  else if( valX < 511 )           
  {   
    Valor_Xmax = 1023;              
    Valor_Xmin = 511 - valX;       
  }

  //-------------------------> Configuramos los valores Max/Min para Y

  // Movimiento del eje Y hacia Arriba  
  if( valY > 511 ) 
  {                 
    Valor_Ymax = 1023 - valY + 511; 
    Valor_Ymin = 0;                 
  }
  // Movimiento del eje Y hacia Abajo 
  else if( valY < 511 )  
  {
    Valor_Ymax = 1023;              
    Valor_Ymin = 511 - valY; 
  }

}

/*
void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");

void loop() { // run over and over
  if (mySerial.available()) {
    Serial.write(mySerial.read());
  }
  if (Serial.available()) {
    mySerial.write(Serial.read());
  }
}

*/

