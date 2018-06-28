// Robot IMA impreso en 3D
// con aplicación arduino
// versión 2.0 con sensor de estacionamiento
// Sensor ultrasonido

#include <AFMotor.h>

//definir motores
AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
String hacer = "";

//Pines del sensor de ultrasonido y la alarma
#define echo A2
#define trigger 2

//Variables necesarias para medir la distancia
float distancia=50;
float tiempo;

// Constantes
const float sonido = 34300.0; // Velocidad del sonido en cm/s
const float umbral1 = 40.0;
const float umbral2 = 20.0;
const float umbral3 = 10.0;

void setup() {
  Serial.begin(9600);
  pinMode(trigger, OUTPUT); 
  pinMode(echo, INPUT); 
  Serial.println("Hola! Estoy listo para arrancar");

  // encender motores
  motor1.setSpeed(150);
  motor2.setSpeed(150);

  motor1.run(RELEASE);
  motor2.run(RELEASE);
}

void loop() {
  //Combinamos código del sensor de estacionamiento más código del auto
  /*inicia la secuencia del Trigger para comenzar a medir*/
  digitalWrite(trigger,LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH); /* Envío del pulso ultrasónico*/
  delayMicroseconds(10);
  digitalWrite(trigger,LOW);
  
  tiempo = pulseIn(echo, HIGH);
  distancia = int(tiempo * 0.000001 * sonido / 2.0);

  Serial.print("\nDistancia ");
  Serial.print(distancia);
  Serial.print(" cm");
  Serial.println();
  delay(500);
//  uint8_t i;
  hacer = "";

if (distancia > umbral1) {
  if (Serial.available()) {
    hacer = Serial.readStringUntil('\n');
      if (hacer.length()==3) {
        if (hacer == "x+;") {
          motor1.run(FORWARD);
          motor2.run(FORWARD);
          for (int i=0; i<255; i++) {
            motor1.setSpeed(i);
            motor2.setSpeed(i);
            delay(10);
          }
        } else if (hacer == "x-;") {
          motor1.run(BACKWARD);
          motor2.run(BACKWARD);
          for (int i=0; i<255; i++) {
            motor1.setSpeed(i);
            motor2.setSpeed(i);
            delay(10);
          }
        } else if (hacer == "y+;") {
          motor1.run(BACKWARD);
          motor2.run(FORWARD);
          for (int i=0; i<255; i++) {
            motor1.setSpeed(i);
            motor2.setSpeed(i);
            delay(10);
          }
        } else if (hacer == "y-;") {
          motor2.run(BACKWARD);
          motor1.run(FORWARD);
          for (int i=0; i<255; i++) {
            motor1.setSpeed(i);
            motor2.setSpeed(i);
            delay(10);
          } 
        } else if (hacer == "--;"){
          for (int i=255; i!=0; i--) {
            motor1.setSpeed(i);
            motor2.setSpeed(i);
            delay(10);
          }
          motor1.run(RELEASE);
          motor2.run(RELEASE);
          delay(1000);
        }
      } else if (hacer != ""){
        Serial.print("\nError de lectura");
        Serial.print("\nParar");
          for (int i=255; i!=0; i--) {
            motor1.setSpeed(i);
            motor2.setSpeed(i);
            delay(10);
          }
          motor1.run(RELEASE);
          motor2.run(RELEASE);
          delay(1000);
      }
    }
    } else if (distancia < umbral1 && distancia >= umbral2){
      // Bajamos la velocidad
      for (int i=255; i!=100; i--) {
            motor1.setSpeed(i);
            motor2.setSpeed(i);
            delay(10);
          }
    } else if (distancia < umbral2 && distancia > umbral3){
      delay(250);
      for (int i=100; i!=50; i--) {
            motor1.setSpeed(i);
            motor2.setSpeed(i);
            delay(10);
          }
    } else if (distancia <= umbral3){
      delay(100);
      for (int i=10; i!=0; i--) {
            motor1.setSpeed(i);
            motor2.setSpeed(i);
            delay(10);
          }
          motor1.run(RELEASE);
          motor2.run(RELEASE);
          delay(1000);
    }
}
