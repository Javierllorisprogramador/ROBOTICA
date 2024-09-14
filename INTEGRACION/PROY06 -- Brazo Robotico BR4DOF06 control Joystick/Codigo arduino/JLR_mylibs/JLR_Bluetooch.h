/*
Proceso: JLR_Bluetooch.ino
Fecha:   27-08-2024
Autor:   José Javier LLoris Roig
Email:   javierllorisprogramador@gmail.com
*/

// Libreria para el manejo de bluetooch
#include <SoftwareSerial.h>

// Nombre para el proyecto
#define ROBOT_NAME "JLR-Robotics"

// Constantes para el bluetooch
#define BLUETOOTH_SPEED  9600  // Baudios puerte serie
#define BLUETOOTH_PINRX     9  // Pin  9 para RX del bluetooch
#define BLUETOOTH_PINTX    10  // Pin 10 para TX del bluetooch

// Creamos el objeto mySerialBT para el bluetooch
// Connect the HC-06 TX to Arduino pin 10 RX.
// Connect the HC-06 RX to Arduino pin 11 TX.
SoftwareSerial mySerialBT( BLUETOOTH_PINRX, BLUETOOTH_PINTX ); 

void waitResponse();

/*----------------------------------------------------------------------*/
/* Función: ConectBluetooch()                                           */
/* Descripción:                                                         */
/* Devuelve: Nada                                                       */
/*----------------------------------------------------------------------*/
void myConectBluetooch() 
{
  // Configuramos la velocidad en baudios el puerto de serie y Bluetooth
  Serial.begin( BLUETOOTH_SPEED ); 
  mySerialBT.begin( BLUETOOTH_SPEED );

  // Mensajes al puerto de serie
  Serial.print(" CONECTANDO CON BLUETOOCH HC-05" );	
  Serial.println(" ------------------------" );	

  // Configuramos la velocidad de consulta al puerto de serie
  mySerialBT.setTimeout( 1 );

  // Espera 20 milisegundos
  delay( 20 ); 

  // Activamos los pin del bluetooch 
  digitalWrite( BLUETOOTH_PINRX, HIGH );
  digitalWrite( BLUETOOTH_PINTX, HIGH );

//---------------------------------------probar con attach  AQUI

  // Mensajes al puerto de serie
  Serial.println("---> Listo el Bluetooch");	

  // Should respond with OK
  Serial.print("AT test de comandos: ");
  Serial.println("AT");
  waitResponse();

  // Set baud rate to 9600
  Serial.print( "Baudios: ") ;
  mySerialBT.println( "AT+BAUD4") ;
  waitResponse();

  // Should respond with its version
  Serial.print( "AT versión: " );
  mySerialBT.println( "AT+VERSION" );
  waitResponse();

  // Set pin
  Serial.print( "Set pin: " );
  mySerialBT.println( "AT+PIN1234" );
  waitResponse();

  // Set the name to ROBOT_NAME
  Serial.print( "Set the name: " );
  String rnc = String( "AT+NAME" ) + String( ROBOT_NAME );
  mySerialBT.println( rnc );
  waitResponse();

  // Mensajes al puerto de serie
  Serial.println(" BLUETOOCH CONECTADO" );	

}
/*----------------------------------------------------------------------*/
/* Función:     waitResponse()                                          */
/* Descripción:                                                         */
/* Devuelve: Nada                                                       */
/*----------------------------------------------------------------------*/
void waitResponse()
{
    delay( 2000 );

    while ( mySerialBT.available() ) {
        Serial.write( mySerialBT.read() );
    }

    Serial.write("\n");
}

/*----------------------------------------------------------------------*/
/* Funciónes:   setup() y loop()                                        */
/* Descripción: Una vez compilado y verificado que no contiene errores  */
/*              marcar las dos funciones como comentarios               */
/* Devuelve:    Nada                                                    */
/*----------------------------------------------------------------------*/
//void setup(){}
//void loop(){}


