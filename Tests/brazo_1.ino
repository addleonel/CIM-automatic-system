// 3,5,6 (5v) - 9,10,11

#include <Servo.h>

// Declaración de los objetos Servo
Servo baseServo;        // Servo de la base (rotación)
Servo forearmServo;     // Servo del antebrazo
Servo armServo;         // Servo del brazo
Servo wristPitchServo;  // Servo de la muñeca (Pitch)
Servo wristYawServo;    // Servo de la muñeca (Yaw)
Servo gripperServo;     // Servo de la garra

void setup() {
  // Inicializar los servos y asociarlos a sus pines
  Serial.begin(9600);
  baseServo.attach(3);        // Base en pin 3
  forearmServo.attach(5);     // Antebrazo en pin 5
  armServo.attach(6);         // Brazo en pin 6
  wristPitchServo.attach(9);  // Muñeca Pitch en pin 9
  wristYawServo.attach(10);    // Muñeca Yaw en pin 10
  gripperServo.attach(11);     // Garra en pin 11
}

void loop() {
  // Establecer los valores de los ángulos para cada servo (posición inicial)
  Serial.print("Initial: 0");
  int baseAngle = 0;        // Base a 90 grados
  int forearmAngle = 90;     // Antebrazo a 45 grados
  int armAngle = 90;         // Brazo a 90 grados
  int wristPitchAngle = 0; // Muñeca Pitch a 135 grados
  int wristYawAngle = 90;    // Muñeca Yaw a 90 grados
  int gripperAngle = 90;     // Garra a 30 grados (semiabierta)

  // Mover los servos a las posiciones iniciales
  baseServo.write(baseAngle);
  forearmServo.write(forearmAngle);
  armServo.write(armAngle);
  wristPitchServo.write(wristPitchAngle);
  wristYawServo.write(wristYawAngle);
  gripperServo.write(gripperAngle);

  delay(5000); // Pausa de 2 segundos

  Serial.print("Operation:");
  for (int i=0; i<5; i++){
    Serial.print("0");
    baseServo.write(0);         // Base a 45 grados
    // delay(5000);
    // forearmServo.write(90);      // Antebrazo a 90 grados
    // delay(500);
    // armServo.write(0);         // Brazo a 135 grados
    // delay(500);
    wristPitchServo.write(0);   // Muñeca Pitch a 90 grados
    // delay(500);
    // wristYawServo.write(45);     // Muñeca Yaw a 45 grados
    // delay(500);
    // gripperServo.write(0);       // Garra completamente cerrada

    delay(2000); // Pausa de 2 segundos

    Serial.print("90");
    // Cambiar los ángulos para una tercera posición
    baseServo.write(90);        // Base a 135 grados
    // delay(500);
    // forearmServo.write(45);      // Antebrazo a 45 grados
    // delay(500);
    // armServo.write(90);          // Brazo a 90 grados
    // delay(5000);
    wristPitchServo.write(90);   // Muñeca Pitch a 45 grados
    // delay(500);
    // wristYawServo.write(135);    // Muñeca Yaw a 135 grados
    // delay(500);
    // gripperServo.write(60);      // Garra semiabierta

    delay(1000); // Pausa de 2 segundos
  }
  
}
