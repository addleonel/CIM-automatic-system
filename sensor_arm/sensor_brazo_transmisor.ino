#include <Servo.h>
// brazo 1
// 8-> 2

Servo baseServo;        // Servo de la base (rotación)
Servo armServo;         // Servo del brazo
Servo forearmServo;     // Servo del antebrazo
Servo wristServo1;      // Servo de la muñeca 1
Servo wristServo2;      // Servo de la muñeca 2
Servo gripperServo;     // Servo de la garra

const int sensorPin = A0;  // Pin del sensor de luz
const int relayPin = 7;    // Pin del relé
const int lightThreshold = 300; // Umbral para detectar luz (ajustar según el sensor)
const int signalPin = 8;

int lightEventCount = 0;
unsigned long lastLightTime = 0; 
const unsigned long debounceTime = 500;

void setup() {
  Serial.begin(9600);
  baseServo.attach(3);        // Base en pin 3
  armServo.attach(5);         // Brazo en pin 5
  forearmServo.attach(6);     // Antebrazo en pin 6
  wristServo1.attach(9);      // Muñeca 1 en pin 9
  wristServo2.attach(10);     // Muñeca 2 en pin 10
  gripperServo.attach(11);    // Garra en pin 11
  
  pinMode(relayPin, OUTPUT);
  pinMode(signalPin, OUTPUT);
  digitalWrite(relayPin, LOW);
  digitalWrite(signalPin, LOW);

}

void loop() {
  String initialMovements[] = {"base:60"};
  executeMovements(initialMovements, 1);

  int lightValue = analogRead(sensorPin);
  // Detectar un evento de luz
  if (lightValue > lightThreshold) { 
    Serial.println(lightValue); 
    if (millis() - lastLightTime > debounceTime) {
      lightEventCount++;
      lastLightTime = millis();
      Serial.print("Evento de luz detectado: ");
      Serial.println(lightEventCount);
      delay(500);
    }
  }

  if (lightEventCount == 2) {
    digitalWrite(relayPin, HIGH);
    delay(1000);
    digitalWrite(signalPin, HIGH);
    
    Serial.println("Señal: " + String(digitalRead(signalPin)));
    Serial.println("Relé activado: Stopper encendido");
    Serial.println("Señal recibida: ejecutando movimientos predefinidos");
    Serial.println("Operation:");

    for(int i=0; i<2; i++) {
      Serial.println("move 1");
      String move1[] = {"base:15"};
      executeMovements(move1, 1);
      delay(1000);

      Serial.println("move 2");
      String move2[] = {"base:60"};
      executeMovements(move2, 1);
      delay(1000);
    }
    
    digitalWrite(relayPin, LOW);
    delay(5000);
    digitalWrite(signalPin,LOW);
    Serial.println("Señal: " + String(digitalRead(signalPin)));
    Serial.println("Relé apagado: Stopper detenido");
    lightEventCount = 0; 
  }
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
    delay(500);
  }
}

    