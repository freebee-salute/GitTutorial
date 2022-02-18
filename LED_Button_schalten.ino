const int buttonPin = D8;    // Button - auf D8, 3v auf S
const int redPin = D0;       // LED - auf GND, G auf D0
const int bluePin = D1;     // LED B auf D1
const int greenPin = D2;   // LED R auf D2 , beschriftung auf LED scheint falsch zu sein...
        
int zaehler = 0;            // Zähler initialisieren
int buttonStatus = 0;        // Status des Buttons initialisieren
int letzterButtonStatus = 0;    // Status des Buttons auf 0 setzen

void setup() {
  pinMode(buttonPin, INPUT);    // Button auf Input setzen
  pinMode(redPin, OUTPUT);      // Pins der LED auf Output setzen
  pinMode(bluePin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  Serial.begin(115200);         // Geschwindigkeit festlegen, optional, notwendig um Serial.print auszulesen
}
void loop() {
 
  buttonStatus = digitalRead(buttonPin); // Status des Buttons wird ausgelesen

 if (buttonStatus != letzterButtonStatus) {  // wenn der Status des Buttons nicht mit dem gespeicherten Wert
    if (buttonStatus == HIGH) {          // übereinstimmt, wird 1 hochgezählt
      zaehler++;
      Serial.println(zaehler);
    } else if (zaehler >= 9){           // wenn der Zähler bei 4 steht, wird er auf 0 zurückgesetzt
      zaehler = 0;
      } else {
    }
    delay(50);                          // kurze Pause, um falsches Auslesen zu vermeiden
 }
   letzterButtonStatus = buttonStatus;       // neuen Button Status speichern

  if (zaehler == 1) {                   // Begin der Schleife, wenn Zähler = 1 -> LED ist Rot
    digitalWrite(redPin, HIGH);         
    digitalWrite(bluePin, LOW);
    digitalWrite(greenPin, LOW);
  } else if (zaehler == 2) {            // Wenn Zähler = 2 -> LED ist Blau
    digitalWrite(redPin, LOW);
    digitalWrite(bluePin, HIGH);
    digitalWrite(greenPin, LOW);
  } else if (zaehler == 3){             // Wenn Zähler = 3 -> LED ist Grün
    digitalWrite(redPin, LOW);
    digitalWrite(bluePin, LOW);
    digitalWrite(greenPin, HIGH);
    } else if (zaehler == 4) {          // Wenn Zähler = 4 -> LED ist aus
    digitalWrite(redPin, LOW);
    digitalWrite(bluePin, LOW);
    digitalWrite(greenPin, LOW);  
      }else if (zaehler == 5) {          // Wenn Zähler = 4 -> LED ist aus
    digitalWrite(redPin, HIGH);
    digitalWrite(bluePin, HIGH);
    digitalWrite(greenPin, LOW);  
      }else if (zaehler == 6) {          // Wenn Zähler = 4 -> LED ist aus
    digitalWrite(redPin, HIGH);
    digitalWrite(bluePin, LOW);
    digitalWrite(greenPin, HIGH);  
      }else if (zaehler == 7) {          // Wenn Zähler = 4 -> LED ist aus
    digitalWrite(redPin, LOW);
    digitalWrite(bluePin, HIGH);
    digitalWrite(greenPin, HIGH);  
      } else if (zaehler == 8) {          // Wenn Zähler = 4 -> LED ist aus
    digitalWrite(redPin, HIGH);
    digitalWrite(bluePin, HIGH);
    digitalWrite(greenPin, HIGH);  
      }else if (zaehler == 9) {          // Wenn Zähler = 4 -> LED ist aus
    digitalWrite(redPin, LOW);
    digitalWrite(bluePin, LOW);
    digitalWrite(greenPin, LOW); 
}
}
