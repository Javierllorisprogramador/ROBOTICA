/*
Fuente: simple.ino
Mover servomotores muy suave

Web: https://www.youtube.com/watch?v=jsXolwJskKM
Github: https://github.com/XRobots/ServoSmoothing
*/

int switch1 = 0;
float switch1Smoothed;
float switch1Prev;

void setup() {

  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP);//12

}

void loop() {

  switch1 = digitalRead(2);      // read switch
  switch1 = switch1 * 100;        // multiply by 100

  // *** smoothing ***

  switch1Smoothed = (switch1 * 0.05) + (switch1Prev * 0.95);

  switch1Prev = switch1Smoothed;

  // *** end of smoothing ***

  Serial.print(switch1, DEC);                  // print to serial terminal/plotter
  Serial.print(" , ");   
  Serial.println(switch1Smoothed, DEC);

  delay(10);                      // run loop 100 times/second

}
