/*
Proceso:     JLR_ErrorSystem.ino
Descripción: Control de errores/excepciones
Autor:       José Javier LLoris Roig
Email:       javierllorisprogramador@gmail.com

Librerias:
--------------------------------------------------------------------------
setjmp.h  => Libreria para el control de errores/excepciones
             El archivo de cabecera de biblioteca estándar de C setjmp.h
             se utiliza para proporcionar saltos en la ejecución del
             código y así modificar drásticamente el flujo de ejecución
             del programa.

--------------------------------------------------------------------------
Notas del autor:
--------------------------------------------------------------------------
02-09-24 => Modifico nombres de variables para mas significativas.
            Si desparcheamos las funciones setup() Y LOOP() compila bien.

02-09-24 => Información obtenida en:
            https://construyendoachispas.blog/

            Canal youtube:
            https://www.youtube.com/channel/UClJy9bx5IYmGRQmukRi8ggQ

            Fuentes:
            https://github.com/espressif

            Autor original:
            https://www.espressif.com/
            Proyectos open source basados en hardware espressif autor
            asiatico.

//******************************************Javier Alcubierre Villasol

*/

#include <setjmp.h>

jmp_buf exception_mng;  // Buffer para los mensajes de error
int nError_ValorA = 5;  // Variable para la gestión de errores
int nError_ValorB = 1;  // Variable para la gestión de errores
int nError_ValorC;      // Variable para la gestión de errores

/*----------------------------------------------------------------------*/
/* Función: myErrorSys()                                                */
/* Descripción: Control de errores y/o excepciones                      */
/* Devuelve: Nada                                                       */
/*----------------------------------------------------------------------*/
void myErrorSystem()
{ 
  switch ( setjmp( exception_mng ) )
  {
    case 0:     // Sin errores
        break;

    case 1:     // Division por cero
    //    Serial.println( "*** EXCEPTION DIVISION BY 0 ***" );
    //    exit( 0 );
        break;

    case 2:     // Divisor negativo
    //    Serial.println( "*** EXCEPTION DIVISION BY NEGATIVE NUMBER ***" );
        break;

    default: 
    //    Serial.println( "*** GENERIC EXCEPTION ***" );
    //    exit( 0 );
        break;
  }

  myCodeErrorSys();
  delay( 1000 );    
}
/*----------------------------------------------------------------------*/
/* Función:     myCodeErrorSys()                                        */
/* Descripción:                                                         */
/* Devuelve:    Nada                                                    */
/*----------------------------------------------------------------------*/
void myCodeErrorSys()
{
  nError_ValorA--;

  if( nError_ValorA == 0 ) {
    longjmp( exception_mng, 1 );
  }

  if( nError_ValorA < 0 ) {
    longjmp( exception_mng, 2 );
  }

  nError_ValorC = nError_ValorB / nError_ValorA;  
  Serial.print( "ValorB: " + String( nError_ValorB + "/" ) );
  //Serial.print( "/" );
  Serial.print( "ValorA: " + String( nError_ValorA + "=" ) );
  //Serial.print( " = " );
  Serial.println( "ValorC: " + String( nError_ValorC ) );

}
/*----------------------------------------------------------------------*/
/* Funciónes:   setup() y loop()                                        */
/* Descripción: Una vez compilado y verificado que no contiene errores  */
/*              marcar las dos funciones como comentarios               */
/* Devuelve:    Nada                                                    */
/*----------------------------------------------------------------------*/
//void setup(){}
//void loop(){}
