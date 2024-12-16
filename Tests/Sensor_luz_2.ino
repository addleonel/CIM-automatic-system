// Definir pines
const int sensorPin = A0;  // Pin del sensor de luz
const int relayPin = 7;    // Pin del relé
const int lightThreshold = 150; // Umbral para detectar luz (ajustar según el sensor)

// Variables para controlar eventos de luz detectados
int lightEventCount = 0;
unsigned long lastLightTime = 0; 
const unsigned long debounceTime = 500; // Tiempo para evitar rebotes (ms)

void setup() {
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW); // Relé apagado inicialmente
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
    Serial.println("Relé activado: Motor encendido");
    delay(5000); // Mantiene el motor encendido por 5 segundos
    digitalWrite(relayPin, LOW); // Apaga el relé
    Serial.println("Relé apagado: Motor detenido");
    lightEventCount = 0; // Reinicia el conteo de eventos
  }

  // delay(5000); // Retardo para estabilizar lecturas
}
