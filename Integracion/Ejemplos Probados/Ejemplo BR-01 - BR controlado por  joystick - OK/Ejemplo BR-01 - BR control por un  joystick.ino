/*
Proceso:     Ejemplo BR controlado Joystick.ino
Descripción: Brazo Robotico manejado con Joystick KY-023 y 4 servos SG90

Web: https://robotsimpresion3d.wordpress.com/2023/03/13/el-brazo-robot-de-juan/
Descargas código: https://www.dropbox.com/scl/fi/por8zlnjhw4y6aw0ggr9b/
                  brazo_dos_joysticks.ino?
                  rlkey=kyi8zl26ahu93fgly8j1rqmfp&e=1&dl=0

*/

#include <Servo.h>

Servo base;
Servo hombro;
Servo codo;
Servo pinza;

int potpin[]            = {  1,  0,  3,  4 };
int valoresPots[]       = {  0,  0,  0,  0 };
int incrementos[]       = {  0,  0,  0,  0 };
int angulosServo[]      = { 90, 90, 90, 90 };
int limitesgrados[4][2] = { {0,180}, {45,135}, {60,150}, {0,130} };

//int limitesgrados[4][2] = { {0,180},{45,135},{60,150},{0,130},  };



void setup() {
  Serial.begin(9600);

  base.attach(4);
  hombro.attach(5);
  codo.attach(6);
  pinza.attach(7);

  pinMode(A0, INPUT_PULLUP);
  pinMode(A1, INPUT_PULLUP);
  test_servos();
}
void test_servos() {
  for (int i = 60; i < 90; i++) {
    base.write(i);
    hombro.write(i);
    codo.write(i);
    pinza.write(i);
    delay(50);
  }
}

void loop()
{
  timerServo();
}

void timerServo()
{

  const int intervaloDeActualizacion = 20;  // milisegundos entre cada ciclo de temporización
  static unsigned long ultimaActualizacion;

  if ((millis() - ultimaActualizacion) > intervaloDeActualizacion)
  {
    ultimaActualizacion = millis();
    actualizarServos2();
  }

}

void actualizarServos2()
{

  for (int i = 0; i < 4; i++)
  {
    valoresPots[i] = analogRead( potpin[i] );
    incrementos[i] = map( valoresPots[i], 0, 1023, -4, 4 );

    if(incrementos[i]==-1)
    {
      incrementos[i]= 0;
    }

    angulosServo[i] = angulosServo[i] + incrementos[i];
    angulosServo[i] = constrain(angulosServo[i], limitesgrados[i][0], limitesgrados[i][1]);

    Serial.print(incrementos[i]);
    Serial.print(" ");

    Serial.print(angulosServo[i]);
    Serial.print(" ");
  }

  Serial.println();

  base.write(angulosServo[0]);
  hombro.write(angulosServo[1]);
  codo.write(angulosServo[2]);
  pinza.write(angulosServo[3]);
  /*Serial.print(incremento);
    Serial.print(" ");
    Serial.println(anguloServo);*/
}
/*
  void actualizarServos() {
  int valorPot;
  valorPot = analogRead(potpin); // (value between 0 and 1023)
  incremento = map(valPot, 0, 1023, -10, 10);
  anguloServo = anguloServo + incremento;
  anguloServo = constrain(anguloServo, 0, 180);
  myservo.write(anguloServo);
  Serial.print(incremento);
  Serial.print(" ");
  Serial.println(anguloServo);
  }*/
