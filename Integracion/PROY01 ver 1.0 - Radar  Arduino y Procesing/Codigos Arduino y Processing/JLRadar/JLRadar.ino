/*
------------------------------------------------------------------------------------
Proceso:     JLRadar.ino
Descripción: Mini proyecto sencillo para un Radar
Versión:     1.0
Fecha:       02-05-2024
Autor:       José Javier LLoris Roig - Valencia ( España )
Email:       javierllorisprogramador@gmail.com
Web:         https://javierlloris.blogspot.com  
             En la actualidad en periodo de actualización para incluir más programas
             con sus códigos fuentes incluidos y repositorios de donde descargarlos.
             Pronto estarán todos en GitHub.

Tarjetas para el harware:
------------------------------------------------------------------------------------
Tarjeta arduino Rev3  => Tarjeta base Arduino UNO Rev3
Sensor                => Módulo de ultrasonidos HC-SR04
ServoMotor            => 1 x servoMotor SG90
Cables                => Cables hembras y machos Dupoint

Programas:
------------------------------------------------------------------------------------
Visual Studio Code => Editor de fuentes ver 1.92.0
Arduino            => Instalar el programa ARDUINO IDE ver 2.3.3
Processing         => Instalar el programa PROCESSING VER 4.0

Adicionales:
------------------------------------------------------------------------------------
ProcesingRadar => Procesing_radar.pde
                  Programa Java que muestra en pantalla la imagen del un Radar 
                  capturando los datos del puerto de serie. 
                  A tener en cuenta: En el fuente Procesing_radar.pde para que 
                  funcione hay que modificar el número de puerto de como se compilo
                  el fuente JLRadar.ino.
                  Modificar el puerto de esta linea: ( esta en la linea 19 ), en mi 
                  caso la última modificación fue en el puerto COM27.
                  myPort = new Serial(this,"COM27", 9600);
                  Ese fuente es de código abierto ( open source ) cada uno es libre
                  de poder usarlo para sus proyectos. Desconozco el autor para ser
                  nombrqado.

Tiendas donde compro los componentes de electronica y robotica:
------------------------------------------------------------------------------------
Aliexpress china : https://es.aliexpress.com ( en español )
Turibot españa   : https://www.turibot.es/
Amazon españa    : https://www.amazon.es
Sinoning.com     : https://www.sinoning.com/
Makerbuying china: https://www.makerbuying.com/
Tiendatec españa : https://www.tiendatec.es/

Notas del autor:
------------------------------------------------------------------------------------
Experiencia en programación en multitud de lenguajes y S.O: 35 años.
En la actualidad: PreJubilado por enfermedad.
Lenguaje de programación preferido para programas de escritorio: Fivewin & Harbour 
lenguaje multiplaforma incluso puedes embeber código Borland C dentro de los fuentes
SEO Antonio linares- Malaga ( España ).
Web : https://www.fivetechsoft.com/spanish/productos.php
Foro: https://forums.fivetechsupport.com/viewforum.php?f=6

Por costumbre suele documentar los fuentes de todos mis programas lo máximo que
puedo, para que cualquier programador que quiera modificar el fuente lo tenga lo 
más fácil posible.

Este fuente es código abierto ( open source ) y puedes hacer lo que quieras con el.
Si requieres de alguna ayuda puedes mandarme un email arriba indicado.

Ojala puedas disfrutar tanto como yo de la programación, robótica y electronica. 

*/

// Incluimos el archivo de cabecera para servomotores
#include <Servo.h>

// Declaramos y asignamos los Pin al sendor ultrasonico y al servomotor
const int sensorUltraPin = 10;  // Pin sensor ultrasonidos 
const int servoMotorPin  = 11;  // Pin servoMotorPin 

// Declaramos las variables para el calculo de la distancia
long duration;
int distance;

// Creamos el objeto myServo, en este caso solo tenemos 1 servomotor
Servo myServo;

/*--------------------------------------------------------------------------------*/
/* Función setup()                                                                */
/* Descripción = Inicializa el entorno del proyecto                               */
/*--------------------------------------------------------------------------------*/
void setup() 
{
  // attach()  Nos permite indicar en que pin tenemos conectado nuestro servo
  // pinMode() Permite configurar a cada pin, de forma individual, como entrada o 
  // como salida. Valores: OUTPUT( salida ) o INPUT( entrada ).
  // Write() Escribe datos binarios a través del puerto serie, es en este caso le
  // indicamos los grados que tiene que girar el servomotor.

  pinMode(sensorUltraPin,OUTPUT); // Declaramos el sensor ultrasonico como salida
  pinMode(servoMotorPin, INPUT);  // Declaramos el servomotor como entrada
  Serial.begin(9600);             // Velocidad de transmisión en serie en baudios
  myServo.attach(12);             // Asignamos el servoMotorPin qal pin 12

  myServo.write(90);              // Situamos el servoMotorPin a 90º
  delay(30);                      // Hacemos un delay de 30 milisegundos
 
}

/*--------------------------------------------------------------------------------*/
/* Función loop()                                                                 */
/* Descripción = Realiza un bucle infinito hasta desconectar el cable USBPRINTER  */
/*               (SERIE)                                                          */
/*--------------------------------------------------------------------------------*/
void loop()
{
  // Giramos el servomotor de 0 a 180º, es decir, de izquierda a derecha
  for( int i=0; i<=180; i++ )
  { 
    moveservo( i ); 
  }

  // Giramos el servomotor de 180 a 0º, es decir, de derecha a izquierda
  for( int i=180; i>1; i-- )
  {  
    moveservo( i );
  }

}

/*--------------------------------------------------------------------------------*/
/* Función moveservo( int i )                                                     */
/* Descripción = Gira el servoMotorPin de 0 a 180º y viceversa                    */
/* Parametro int i = Recibe el valor de giro del servomotor                       */
/*--------------------------------------------------------------------------------*/
void moveservo( int i ) 
{

  myServo.write(i);                 // Movemos el servomotor según el valor de i
  delay(30);                        // Hacemos un delay de 30 milisegundos

  distance = CalculateDistance();   // Calculamos la distancia del objeto detectado

  // Enviamos al puerto serie la concatenación del valor del servomotor y distancia
  Serial.print(i);                  
  Serial.print(",");                
  Serial.print(distance);           
  Serial.print(".");                 

}

/*--------------------------------------------------------------------------------*/
/* Función CalculateDistance()                                                    */
/* Descripción = Calculamos la distancia del objeto detectado                     */
/*--------------------------------------------------------------------------------*/

int CalculateDistance()
{
  // digitalWrite() sirve para establecer un valor de HIGH o LOW en un pin digital  
  // arduino siempre y cuando se haya configurado como salida (OUTPUT) como en este
  // caso. Enviar este valor para establecerá un voltaje en el pin de 3.3 o 5V 
  // ( HIGH ) o 0V ( LOW ) dependiendo de la placa.
  digitalWrite(sensorUltraPin, LOW);       
  delayMicroseconds(2);                    
  digitalWrite(sensorUltraPin, HIGH);      
  delayMicroseconds(10);                   
  digitalWrite(sensorUltraPin, LOW);       

  // pulseIn() El método pulseIn() retorna la longitud en microsegundos en un pin 
  // de entrada digital por un periodo de tiempo desde 10 milisegundos hasta 3 min. 
  // Puede ser usado para leer sensores que retornan una serie de pulsos como 
  // algunos acelerómetros o medidores de rango.
  duration = pulseIn(servoMotorPin, HIGH); // Obtenemos la longuitud en miliseg.
  distance= duration * 0.034 / 2;          // Calculamos la distancia
  return distance;                         // Devolvemos la distancia

}
