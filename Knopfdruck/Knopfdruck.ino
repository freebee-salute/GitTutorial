#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#define MQTTpubQos          2                            //qos of publish (see README)
const char* PSK = "deinPasswort";
const char* SSID = "deineSSID";
const char* MQTT_BROKER = "deineBrokerIP";
const int buttonPin = D1; // Button - auf D1, 3v auf S, Mittlerer Pin auf G
const int redPin = D2;       // LED - auf GND, LED G auf D2
const int bluePin = D3;     // LED B auf D3
const int greenPin = D4;   // LED R auf D4 , beschriftung auf LED scheint falsch zu sein...
const int touchSensor = D5; // Touch Sensor D0 auf D5, + auf 3v, G auf G
int zaehler = 0;            // Zähler initialisieren
int buttonStatus = 0;
int letzterButtonStatus = 0;
int touchStatus = 0;
int letzterTouchStatus = 0;


WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;
char messaegeBuffer[100];
String messaegeString;

void setup() {
  // put your setup code here, to run once:
  pinMode(buttonPin, INPUT);
  pinMode(redPin, OUTPUT);      // Pins der LED auf Output setzen
  pinMode(bluePin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(touchSensor, INPUT); 
  Serial.begin(115200);
  setup_wifi();
  client.setServer(MQTT_BROKER, 1883);
  }

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(SSID);

  WiFi.begin(SSID, PSK);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
void reconnect() {
  while (!client.connected()) {
    String client_id = "esp32-client-";
    client_id += String(WiFi.macAddress());
    Serial.print("Reconnecting...");
    //if (!client.connect(client_id.c_str(), mqtt_username, mqtt_password))
    if (!client.connect("ESP8266Client")) {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" retrying in 5 seconds");
      delay(5000);
    }
  }
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  // put your main code here, to run repeatedly:
  touchStatus = digitalRead(touchSensor); // Status des Touchsensors wird ausgelesen

 if (touchStatus != letzterTouchStatus) {  // wenn der Status des Sensors nicht mit dem gespeicherten Wert
    if (touchStatus == HIGH) {          // übereinstimmt, wird 1 hochgezählt
      zaehler++;
      Serial.println(zaehler);
    } else if (zaehler > 3){           // wenn der Zähler bei 4 steht, wird er auf 0 zurückgesetzt
      zaehler = 0;
      Serial.println(zaehler);
      } else {
    }
    delay(100);                          // kurze Pause, um falsches Auslesen zu vermeiden
 }
   letzterTouchStatus = touchStatus;       // neuen Touch Status speichern

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
    } else if (zaehler == 0) {          // Wenn Zähler = 4 -> LED ist aus
    digitalWrite(redPin, LOW);
    digitalWrite(bluePin, LOW);
    digitalWrite(greenPin, LOW);  
      }


  buttonStatus = digitalRead(buttonPin);
  if (buttonStatus != letzterButtonStatus) {
  if (buttonStatus == HIGH) {
      messaegeString = String("TPB:1:" + String(zaehler)); // "TPB:1:1"
          Serial.println(messaegeString);
          messaegeString.toCharArray(messaegeBuffer, 100);
          client.publish("home/data", messaegeBuffer);
//  Serial.println(msg);
  delay(500);
  //delay(600000); // 10 minuten delay
  }
  }
  letzterButtonStatus = buttonStatus;
}
