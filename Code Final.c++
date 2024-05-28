// C++ code
// CODE SANS POSSIBILITE DE RALLUMER LA MACHINE
int EtatMachine = 0;

int MaintenanceMode = 0;

int Ouverture = 0;

void setup()
{
  pinMode(1, OUTPUT);
  pinMode(A4, INPUT);
  pinMode(7, OUTPUT);
  pinMode(A5, INPUT);
  pinMode(0, OUTPUT);

  digitalWrite(1, HIGH);
}

void loop()
{
  if (digitalRead(A4) == 1) {
    digitalWrite(7, HIGH);
    if (digitalRead(A5) == 1) {
      digitalWrite(0, HIGH);
      delay(1000); // Wait for 1000 millisecond(s)
      digitalWrite(0, LOW);
      delay(1000); // Wait for 1000 millisecond(s)
    } else {
      digitalWrite(1, LOW);
      digitalWrite(0, LOW);
    }
  } else {
    digitalWrite(7, LOW);
  }
}