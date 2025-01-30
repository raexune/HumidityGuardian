#include <DHT22.h>

#define DHT22_PIN 11    // Der Pin, an dem der DHT22 angeschlossen ist
#define BUZZER_PIN 13 
#define RELAIS_PIN 12  // Der Pin, an dem das Relais angeschlossen ist

DHT22 dht22(DHT22_PIN);

bool relaisEingeschaltet;

void setup() {
  Serial.begin(9600);
  Serial.println("Der Arduino funktioniert!");
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  digitalWrite(12, LOW);
}

void loop() {

 
   Serial.println("Setup abgeschlossen. Starte Schleife...");

       // Warte 2 Sekunden zwischen den Messungen
      delay(2000);
      
      float Luftfeuchtigkeit = dht22.getHumidity();
      float Temperatur = dht22.getTemperature();
      

    Serial.print("Temperatur: ");
    Serial.print(Temperatur);
    Serial.print(" °C, ");
    Serial.print("Luftfeuchtigkeit: ");
    Serial.print(Luftfeuchtigkeit);
    Serial.println(" %");


    // Aktiviere den Buzzer für eine kurze Zeit
    if (Luftfeuchtigkeit >= 60){
      tone(13, 1000, 200);  // Frequenz: 1000Hz, Dauer: 200ms
    } else if(Luftfeuchtigkeit < 50){
      noTone(13);
    }
    
        // Steuere das Relais basierend auf der Temperatur
    if (Temperatur >= 15 && !relaisEingeschaltet) {
      digitalWrite(12, HIGH);  // Relais einschalten (LOW = EIN bei den meisten Relaismodulen)
       relaisEingeschaltet = true;
      Serial.println("Relais eingeschaltet");
    } else if (Temperatur <=5 && relaisEingeschaltet) {
      digitalWrite(12, LOW);  // Relais ausschalten
       relaisEingeschaltet = false;
      Serial.println("Relais ausgeschaltet");
    }
   
    delay(1000);
  } 
