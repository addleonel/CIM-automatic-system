// Definir pines
const int sensorPin = A0;  // Pin del sensor de luz
const int relayPin = 7;    // Pin del relé
const int signalPin = 4;   // Pin para enviar señal al otro Arduino
const int signalPinFromReceiver = 12; // Pin para recibir señal del receptor
const int lightThreshold = 150; // Umbral para detectar luz (ajustar según el sensor)

// Variables para controlar eventos de luz detectados
int lightEventCount = 0;
unsigned long lastLightTime = 0; 
const unsigned long debounceTime = 500; // Tiempo para evitar rebotes (ms)

void setup() {
  pinMode(relayPin, OUTPUT);
  pinMode(signalPin, OUTPUT); // Configura el pin de señal como salida hacia el receptor
  pinMode(signalPinFromReceiver, INPUT); // Configura el pin de señal como entrada desde el receptor
  digitalWrite(relayPin, LOW); // Relé apagado inicialmente
  digitalWrite(signalPin, LOW); // Señal apagada inicialmente
  Serial.begin(9600);
}

void loop() {
  int lightValue = analogRead(sensorPin);
  Serial.println(lightValue); // Para depuración

  // Detectar un evento de luz
  if (lightValue > lightThreshold) { // Si la luz está por encima del umbral
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
    delay(2000);
    digitalWrite(signalPin, HIGH); // Enviar señal al receptor
    Serial.println("Señal al receptor enviado pin 4 --> 2");

    // Esperar respuesta del receptor
    while (digitalRead(signalPinFromReceiver) == LOW) {
      Serial.println("Esperando respuesta del receptor...");
    }
    
    if (digitalRead(signalPinFromReceiver) == HIGH) {
      Serial.println("Respuesta recibida: Tarea completada por el receptor.");
    }

    digitalWrite(relayPin, LOW); // Apaga el relé
    digitalWrite(signalPin, LOW); // Detener la señal al receptor
    Serial.println("Relé apagado: Stopper detenido");
    lightEventCount = 0; // Reinicia el conteo de eventos
  }
}
