// ARM 3
#include <Servo.h>
// 3,5,6 (5v) - 9,10,11
Servo baseServo;        // Servo de la base (rotación)
Servo armServo;         // Servo del brazo
Servo forearmServo;     // Servo del antebrazo
Servo wristServo1;      // Servo de la muñeca 1
Servo wristServo2;      // Servo de la muñeca 2
Servo gripperServo;     // Servo de la garra

void setup() {
  // Inicializar los servos y asociarlos a sus pines
  Serial.begin(9600);
  baseServo.attach(3);        // Base en pin 3
  armServo.attach(5);         // Brazo en pin 5
  forearmServo.attach(6);     // Antebrazo en pin 6
  wristServo1.attach(9);      // Muñeca 1 en pin 9
  wristServo2.attach(10);     // Muñeca 2 en pin 10
  gripperServo.attach(11);    // Garra en pin 11
}

void loop() {
  // Establecer posición inicial
  /** 
    base: 0-90
    gripper: 5-180
  */

  Serial.println("Initial:");
  // String initialMovements[] = {"base:90", "arm:90", "forearm:10", "wrist1:0", "wrist2:0", "gripper:180"};
  String initialMovements[] = {"gripper:0", "gripper:0", "gripper:180"};  // good
  // String initialMovements[] = {"base:180", "arm:180", "forearm:30"}; 
  executeMovements(initialMovements, 3); // Paso explícitamente la longitud del arreglo
  delay(5000);

  
}

// name:angle
void moveTo(String nameAngle) {
  int colonIndex = nameAngle.indexOf(':');
  String name = nameAngle.substring(0, colonIndex);
  int angle = nameAngle.substring(colonIndex + 1).toInt();

  if (name == "base") {
    baseServo.write(angle);
  } else if (name == "arm") {
    armServo.write(angle);
  } else if (name == "forearm") {
    forearmServo.write(angle);
  } else if (name == "wrist1") {
    wristServo1.write(angle);
  } else if (name == "wrist2") {
    wristServo2.write(angle);
  } else if (name == "gripper") {
    gripperServo.write(angle);
    Serial.println(angle);
  }
}

void executeMovements(String movements[], int numberOfMovements) {
  for (int i = 0; i < numberOfMovements; i++) {
    moveTo(movements[i]);
    delay(1000);
  }
}
