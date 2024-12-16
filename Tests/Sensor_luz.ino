#define LDR_PIN A0  // Pin analógico para LDR
#define RELAY_PIN 7 // Pin digital para el relé
int shadowCount = 0; // Contador de sombras
const int threshold = 850; // Umbral de luz/sombra
unsigned long startTime;

void setup() {
  pinMode(LDR_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW); // Asegura que el relé esté apagado
  Serial.begin(9600);
}

void loop() {
  shadowCount = 0;
  startTime = millis();
  while (millis() - startTime < 2000) { // Monitorear por 2 segundos
    int lightValue = analogRead(LDR_PIN);
    if (lightValue < threshold) { // Detecta sombra
      delay(100); // Anti rebote
      if (analogRead(LDR_PIN) < threshold) { // Confirma sombra
        shadowCount++;
        while (analogRead(LDR_PIN) < threshold); // Espera a que la luz regrese
      }
    }
  }

  // Determina el carrito según el número de sombras
  Serial.print("Sombras detectadas: ");
  Serial.println(shadowCount);
  
  if (shadowCount == 2) {
    digitalWrite(RELAY_PIN, HIGH); // Activa el relé
    delay(500); // Mantén el solenoide activo por 0.5 segundos
    digitalWrite(RELAY_PIN, LOW);
  }
}