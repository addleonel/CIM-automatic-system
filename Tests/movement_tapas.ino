#include <Servo.h>
// Descargar
Servo baseServo;        // Servo de la base (rotación)
Servo armServo;         // Servo del brazo
Servo forearmServo;     // Servo del antebrazo
Servo wristServo1;      // Servo de la muñeca 1
Servo wristServo2;      // Servo de la muñeca 2
Servo gripperServo;     // Servo de la garra


void setup() {
  Serial.begin(9600);
  baseServo.attach(3);        // Base en pin 3
  armServo.attach(5);         // Brazo en pin 5
  forearmServo.attach(6);     // Antebrazo en pin 6
  wristServo1.attach(9);      // Muñeca 1 en pin 9
  wristServo2.attach(10);     // Muñeca 2 en pin 10
  gripperServo.attach(11);    // Garra en pin 11

  // Serial.println("Sistema iniciado");
  // String initialMovements[] = {"base:125", "arm:150", "forearm:90", "wrist2:10", "gripper:60"};
  // executeMovements(initialMovements, 5); 
}

void loop() {
  Serial.println("Retornando a estado inicial");
  // String initialMovements[] = {"base:125", "arm:150", "forearm:90", "wrist2:10", "gripper:60"};
  Serial.println("move 1");
  String initialMovements_1[] = {"base:170", "arm:150", "forearm:90", "wrist2:40", "gripper:50"};
  executeMovements(initialMovements_1, 5);
  delay(2000);

  // Serial.println("move 2");
  // String initialMovements_2[] = {"base:70", "arm:175", "forearm:20", "wrist2:20", "gripper:50"};
  // executeMovements(initialMovements_2, 5);
  // delay(2000);
  
  Serial.println("move 2");
  String initialMovements_2[] = {"base:170", "arm:175", "forearm:10", "wrist2:20", "gripper:50"};
  executeMovements(initialMovements_2, 5);
  delay(2000);

  Serial.println("move 4");
  String initialMovements_4[] = {"gripper:20"};
  executeMovements(initialMovements_4, 1);
  delay(2000);
  
  Serial.println("move 6");
  String initialMovements_5[] = { "forearm:30", "arm:150"};
  executeMovements(initialMovements_5, 4);
  delay(2000);

  Serial.println("move 7");
  String initialMovements_6[] = {"base:73", "wrist2:20"};
  executeMovements(initialMovements_6, 4);
  delay(2000);


  Serial.println("move 8");
  String initialMovements_7[] = {"gripper:50"};
  executeMovements(initialMovements_7, 1);
  delay(2000);

  
}

void returnToInitialState() {
  Serial.println("Retornando a estado inicial");
  String initialMovements[] = {"base:180"};
  executeMovements(initialMovements, 1); 
}

// Función para mover un servo específico
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
  }
}

// Función para ejecutar una secuencia de movimientos
void executeMovements(String movements[], int numberOfMovements) {
  for (int i = 0; i < numberOfMovements; i++) {
    moveTo(movements[i]);
    delay(500); // Tiempo entre movimientos
  }
}
