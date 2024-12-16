// Definir pines
const int sensorPin = A0;  // Pin del sensor de luz
const int relayPin = 7;    // Pin del relé
const int signalPin = 4;   // Pin para enviar señal al otro Arduino
const int signalPinFromReceiver = 8; // Pin para recibir señal del receptor
const int lightThreshold = 150; // Umbral para detectar luz (ajustar según el sensor)

int lightEventCount = 0;
unsigned long lastLightTime = 0; 
const unsigned long debounceTime = 500;

void setup() {
  pinMode(relayPin, OUTPUT);
  pinMode(signalPin, OUTPUT); 
  pinMode(signalPinFromReceiver, INPUT);
  digitalWrite(relayPin, LOW);
  digitalWrite(signalPin, LOW); 
  Serial.begin(9600);
}

void loop() {
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

  // Activar el relé si se detectan 2 eventos de luz
  if (lightEventCount == 2) {
    digitalWrite(relayPin, HIGH); // Activa el relé
    Serial.println("Relé activado: Stopper encendido");
    delay(1000);
    digitalWrite(signalPin, HIGH); // Enviar señal al receptor
    Serial.println("Señal al receptor enviado pin 4 --> 2: " + String(signalPin));
    
    Serial.println("LOW/HIGH: " + String(LOW));
    Serial.println("Señal del receptor: " + String(signalPinFromReceiver));
    Serial.println("Señal del receptor: " + String(digitalRead(signalPinFromReceiver)));
    Serial.println(String(digitalRead(signalPinFromReceiver) == LOW));
    // Esperar respuesta del receptor
    // while (digitalRead(signalPinFromReceiver) == LOW) {
    //   Serial.println("Esperando respuesta del receptor...");
    // }
    delay(30000);
    
    Serial.println("LOW/HIGH: " + String(LOW));
    Serial.println("Señal del receptor: " + String(digitalRead(signalPinFromReceiver)));
    
    if (digitalRead(signalPinFromReceiver) == HIGH) {
      Serial.println("Respuesta recibida: Tarea completada por el receptor.");
      digitalWrite(relayPin, LOW); // Apaga el relé
      digitalWrite(signalPin, LOW); // Detener la señal al receptor
      Serial.println("Relé apagado: Stopper detenido");
      lightEventCount = 0; // Reinicia el conteo de eventos
    }

    
  }
}



    