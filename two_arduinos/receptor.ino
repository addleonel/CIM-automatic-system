#include <Servo.h>

// Definir servos
Servo baseServo;        // Servo de la base (rotación)
Servo armServo;         // Servo del brazo
Servo forearmServo;     // Servo del antebrazo
Servo wristServo1;      // Servo de la muñeca 1
Servo wristServo2;      // Servo de la muñeca 2
Servo gripperServo;     // Servo de la garra

// Pin para recibir la señal del transmisor
const int signalPinFromTransmitter  = 2;
const int signalPinToTransmitter = 12;

void setup() {
  Serial.begin(9600);
  // Inicializar los servos y asociarlos a sus pines
  baseServo.attach(3);        // Base en pin 3
  armServo.attach(5);         // Brazo en pin 5
  forearmServo.attach(6);     // Antebrazo en pin 6
  wristServo1.attach(9);      // Muñeca 1 en pin 9
  wristServo2.attach(10);     // Muñeca 2 en pin 10
  gripperServo.attach(11);    // Garra en pin 11

  // Configurar el pin de señal como entrada
  pinMode(signalPinFromTransmitter, INPUT);
  pinMode(signalPinToTransmitter, OUTPUT);  // Señal para enviar señal al emisor del pin 12 -> 12
  digitalWrite(signalPinToTransmitter, LOW); // Señal inicial apagada
  Serial.println("Sistema iniciado");
}

void loop() {
  // Leer la señal del transmisor
  int signal = digitalRead(signalPinFromTransmitter);
  String initialMovements[] = {"base:180", "arm:150", "forearm:90", "wrist2:10", "gripper:180"};  // good
  executeMovements(initialMovements, 5); // Paso explícitamente la longitud del arreglo
  if (signal == HIGH) { // Si se recibe una señal alta
    Serial.println("Señal recibida: ejecutando movimientos predefinidos");
    Serial.println("Operation:");

    for(int i=0; i<5; i++) {
      Serial.println("move 1");
      String move1[] = {"base:180", "arm:180", "forearm:10"};
      executeMovements(move1, 3);
      delay(2000);

      Serial.println("gripper 1");
      String movegripper1[] = {"gripper:0"};
      executeMovements(movegripper1, 1);
      delay(2000);

      Serial.println("move 2");
      String move2[] = {"forearm:10", "arm:150", "base:90", "arm:180"};
      executeMovements(move2, 4);
      delay(2000);

      Serial.println("gripper 2");
      String movegripper2[] = {"gripper:180"};
      executeMovements(movegripper2, 1);
      delay(2000);

      Serial.println("move 3");
      String move3[] = {"arm:150"};
      executeMovements(move3, 1);
      delay(1000);
    }
    
    digitalWrite(signalPinToTransmitter, HIGH); // Encender señal del receptor al emisor del 12 -> 12
    delay(2000);
    digitalWrite(signalPinFromTransmitter, LOW); // apagar señal del transmisor 
  }

  delay(100); // Pequeño retraso para evitar lecturas constantes
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
