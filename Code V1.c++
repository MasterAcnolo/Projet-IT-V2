const int button1Pin = 2;    // Bouton pour allumer/éteindre la LED initiale
const int button2Pin = 3;    // Bouton pour simuler l'ouverture/fermeture de la porte
const int button3Pin = 4;    // Bouton pour activer/désactiver le mode maintenance

const int ledPin = 13;       // LED pour simuler le système
const int maintenanceLedPin = 12; // LED pour le mode maintenance

int button1State = 0;
int button2State = 0;
int button3State = 0;

bool isInitialOn = false;    // État initial de la LED
bool isDoorOpen = false;     // État de la porte
bool isMaintenanceMode = false; // État du mode maintenance

void setup() {
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);
  pinMode(button3Pin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(maintenanceLedPin, OUTPUT);
  digitalWrite(ledPin, LOW); // Assurez-vous que la LED est éteinte au démarrage
  digitalWrite(maintenanceLedPin, LOW); // Assurez-vous que la LED de maintenance est éteinte au démarrage
}

void loop() {
  // Lire l'état des boutons
  button1State = digitalRead(button1Pin);
  button2State = digitalRead(button2Pin);
  button3State = digitalRead(button3Pin);

  // Bouton 1: Allumer/éteindre la LED initiale
  if (button1State == HIGH) {
    delay(50); // Anti-rebond
    if (digitalRead(button1Pin) == HIGH) {
      isInitialOn = !isInitialOn;
      while (digitalRead(button1Pin) == HIGH); // Attendre que le bouton soit relâché
    }
  }

  // Bouton 2: Simuler l'ouverture/fermeture de la porte
  if (button2State == HIGH) {
    delay(50); // Anti-rebond
    if (digitalRead(button2Pin) == HIGH) {
      isDoorOpen = !isDoorOpen;
      while (digitalRead(button2Pin) == HIGH); // Attendre que le bouton soit relâché
    }
  }

  // Bouton 3: Activer/désactiver le mode maintenance
  if (button3State == HIGH) {
    delay(50); // Anti-rebond
    if (digitalRead(button3Pin) == HIGH) {
      isMaintenanceMode = !isMaintenanceMode;
      while (digitalRead(button3Pin) == HIGH); // Attendre que le bouton soit relâché
    }
  }

  // Gérer la LED principale et le mode maintenance
  if (isMaintenanceMode) {
    digitalWrite(ledPin, HIGH); // La LED principale reste allumée
    // Faire clignoter la LED de maintenance
    static unsigned long lastBlinkTime = 0;
    unsigned long currentTime = millis();
    if (currentTime - lastBlinkTime >= 500) { // Clignote toutes les 500 ms
      lastBlinkTime = currentTime;
      digitalWrite(maintenanceLedPin, !digitalRead(maintenanceLedPin));
    }
  } else {
    if (isInitialOn) {
      digitalWrite(ledPin, HIGH);
    } else {
      digitalWrite(ledPin, LOW);
    }
    digitalWrite(maintenanceLedPin, LOW); // Éteindre la LED de maintenance
  }

  // En cas de mode maintenance désactivé, éteindre complètement la machine
  if (!isMaintenanceMode && !isInitialOn) {
    digitalWrite(ledPin, LOW);
  }
}
