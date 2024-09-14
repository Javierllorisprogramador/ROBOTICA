/*
------------------------------------------------------------------------------------
Proceso:     JLOjoRobotico.ino
Descripción: Mini proyecto sencillo para el movimiento de un Ojo robótico
Versión:     1.0
Fecha:       15-05-2024
Autor:       José Javier LLoris Roig - Valencia ( España )
Email:       javierllorisprogramador@gmail.com
Web:         https://javierlloris.blogspot.com  
             En la actualidad en periodo de actualización para incluir más programas
             con sus códigos fuentes incluidos y repositorios de donde descargarlos.
             Pronto estarán todos en GitHub.

Tarjetas para el harware:
------------------------------------------------------------------------------------
Tarjeta arduino Rev3  => Tarjeta base Arduino UNO Rev3
ServoMotor            => 2 x servoMotor SG90
Cables                => Cables hembras y machos Dupoint
Modelo 3D Ojo         => Modelado de las piezas del ojo robotico
Modelo 3D Soporte     => Modelado del soporte para un servomotor

Programas:
------------------------------------------------------------------------------------
Visual Studio Code => Editor de fuentes ver 1.92.0
Arduino            => Instalar el programa ARDUINO IDE ver 2.3.3

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

Mejoras que se pueden hacer:
------------------------------------------------------------------------------------
- Añadir interruptor de encendido
- Añadir Led de encendido
- Añadir distintos sonidos cuando se mueva el ojo y el parpado

*/

// Libreria para el manejo de los servomotores
#include <Servo.h>

// Declaramos las variables para los movimientos de los servomotores
// para el ojo ( servo 1 ) y el parpado ( servo 2 )

int nPositionIniH = 55;   // Posicion inicial del ojo ( servo 1 )
int nRighMove     = 110;  // Posicion ojo maxima a la derecha ( servo 1 )
int nLeftMove     = 10;   // Posicion ojo maxima a la izquierda ( servo 1 )

int nPositionIniV = 160;  // Posicion inicial del parpado ( servo 2 )
int nUpMove       = 110;  // Posicion parpado maxima a hacia arriba ( servo 2 )
int nDownMove     = 180;  // Posicion parpado maxima a hacia abajo ( servo 2 )

int speed         = 10;   // Velocidad de desplazamiento de los servomotores
int interval      = 500;  // Tiempo de espera entre movimientos
int nBaudios      = 9600; // Comunicación serie a 9600 baudios

Servo nServoH;            // Declaramos el objeto servomotor para ojos(servo 1)
Servo nServoV;            // Declaramos el objeto servomotor para parpados(servo 2)

/*--------------------------------------------------------------------------------*/
/* Función setup()                                                                */
/* Descripción = Inicializa el entorno del proyecto                               */
/*--------------------------------------------------------------------------------*/
void setup()
{

  Serial.begin(nBaudios);        // Configuramos comunicación serie a 9600 baudios
  nServoH.attach(2);             // Configuramos pin para servo 1 ( rotación ojo )
  nServoV.attach(3);             // Configuramos pin para servo 2 ( parpados )
  nServoH.write(nPositionIniH);  // Posicionamos servo ojos(servo 1)posicion inicial
  nServoV.write(nPositionIniV);  // Posicionamos servo parpados(servo 2)posicion inicial
  delay(5000);       
                              
}
/*--------------------------------------------------------------------------------*/
/* Función loop()                                                                 */
/* Descripción = Realiza un bucle infinito hasta desconectar el cable USBPRINTER  */
/*               (SERIE)                                                          */
/*--------------------------------------------------------------------------------*/
void loop()
{
    MoveEyeHOR();
    MoveEyeVER();
}
/*--------------------------------------------------------------------------------*/
/*                      MOVIMIENTOS PARA EL OJO SERVO 1                           */
/*--------------------------------------------------------------------------------*/
/* Función MoveEyeHOR()                                                           */
/* Descripción = Mueve el ojo ( servo 1 ) de centro-derecha a centro-izquierda    */
/*--------------------------------------------------------------------------------*/
void MoveEyeHOR()
{

    // Movemos el ojo desde la posicion inicial a la derecha
    for(int i=nPositionIniH; i<=nRighMove; i++)
    {
        nServoH.write(i);      
        delay(speed);
    }
    delay(interval);

    // Movemos el ojo desde la derecha a la posicion inicial 
    for(int i=nRighMove; i>=nPositionIniH; i--)
    {    
        nServoH.write(i);      
        delay(speed);
    }
    delay(interval);

    // Movemos el ojo desde la posicion inicial a la izquierda
    for(int i=nPositionIniH; i>=nLeftMove; i--)
    {    
        nServoH.write(i);
        delay(speed);
    }
    delay(interval);

    // Movemos el ojo desde la izquierda a la posicion inicial 
    for(int i=nLeftMove; i<=nPositionIniH; i++)
    {    
        nServoH.write(i);      
        delay(speed);
    }
    delay(interval);

}
/*--------------------------------------------------------------------------------*/
/*                     MOVIMIENTOS PARA EL PARPADO SERVO 2                        */
/*--------------------------------------------------------------------------------*/
/* Función MoveEyeVER()                                                           */
/* Descripción = Mueve el parpado de posicion inicial al maximo de arriba y desde */
/*               arriba a la posicion inicial                                     */
/*--------------------------------------------------------------------------------*/
void MoveEyeVER()
{

    // Movemos el parpado desde posicion inicial al maximo arriba
    for(int i=nPositionIniV; i>=nUpMove; i--)
    { 
        nServoV.write(i);
        delay(speed);
    }
    delay(interval);

    // Movemos el parpado desde el maximo de arriba a la posicion inicial
    for(int i=nUpMove; i<=nPositionIniV; i++)
    {    
        nServoV.write(i);
        delay(speed);
    }
    delay(interval);

}