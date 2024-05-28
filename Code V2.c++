bool alerteLedActive = false;
bool allumageActive = false;
bool allumagePrecedent = false; // Pour stocker l'état précédent du bouton d'allumage

void setup() {
    pinMode(3, OUTPUT); //VERT
    pinMode(2, OUTPUT); // JAUNE
    pinMode(1, OUTPUT); // ROUGE
    pinMode(0, OUTPUT); //BLANC
  
    pinMode(A5, INPUT); // BOUTON ALLUMAGE
    pinMode(A4, INPUT); // CAPTEUR
    pinMode(A3, INPUT); //MODE MAINTENANCE
  
    Serial.begin(9600);
    Serial.println("SYSTEME ON");
    
    //POSITION PAR DEFAUT 
    // 3 HAUT / A4 LOW / A5 LOW / 1 / 2 / A3 LOW/ 
    digitalWrite(3, LOW); //ETAT MACHINE
    digitalWrite(1, LOW); // USELESS
    digitalWrite(2, LOW); // ETAT MACHINE
    digitalWrite(0, LOW); // OUVERTURE
}

void loop() {
    // Lire l'état des boutons
    int etatBoutonAlerte = digitalRead(A4);
    int etatBoutonAllumage = digitalRead(A5);

    // Mettre à jour les variables booléennes en fonction de l'état des boutons
    if (etatBoutonAlerte == HIGH) {
        alerteLedActive = true;
    } else {
        alerteLedActive = false;
    }

    if (etatBoutonAllumage == HIGH) {
        allumageActive = true;
    } else {
        allumageActive = false;
    }

    // Appeler les fonctions en fonction de l'état des variables booléennes
    if (alerteLedActive) {
        ALERTELED();
    }
    if (allumageActive) {
        ALLUMAGE();
    } else if (allumagePrecedent && !allumageActive) {
        // Si l'allumage était actif lors de la dernière itération mais n'est plus actif maintenant
        // C'est le moment d'éteindre quelque chose si nécessaire
        // Par exemple, éteindre une LED ici
        digitalWrite(2, LOW);
    }

    // Mettre à jour l'état précédent du bouton d'allumage pour la prochaine itération
    allumagePrecedent = allumageActive;
}

void ALERTELED() {
    // Lire l'état des boutons à l'intérieur de la fonction
    int ALLU = digitalRead(A5);
    int CAPT = digitalRead(A4);
    int MAINT = digitalRead(A3);

    if (ALLU == HIGH && CAPT == HIGH) {
        digitalWrite(0, HIGH);
        delay(100);
        digitalWrite(0, LOW);
        delay(100);
    }
}

void ALLUMAGE() {
    // Lire l'état des boutons à l'intérieur de la fonction
    int ALLU = digitalRead(A5);
    int CAPT = digitalRead(A4);
    int MAINT = digitalRead(A3);

    if (ALLU == HIGH) {
        digitalWrite(2, HIGH);
    }
}

void CAPTEUR() {

	// Lire l'état des boutons à l'intérieur de la fonction
    int ALLU = digitalRead(A5);
    int CAPT = digitalRead(A4);
    int MAINT = digitalRead(A3);
	
	if ((CAPT == HIGH) && (MAINT == HIGH))
	{
		digitalWrite(2,LOW);
		ALERTELED();
	}


void OFF(){
    
}
	 
}