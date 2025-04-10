#include <Wire.h>
#include <RTClib.h>

int Relay = 13;
int Relay1 = 12;

//Istanze RTC
RTC_DS3231 rtc;
DateTime now;

void setup()
{
  Serial.begin(9600);
  while(Serial.available() == 0){
  }
  Serial.println("Monitor seriale connesso");
  pinMode(Relay, OUTPUT);
  pinMode(Relay1, OUTPUT);
  digitalWrite(Relay, HIGH);  // spegne il relay
  digitalWrite(Relay1, HIGH);  // spegne il relay1
  // Controlla se il modulo RTC è connesso correttamente
  if (!rtc.begin()) {
    Serial.println("Impossibile trovare il modulo RTC");
    while (1);
  }
  // Verifica che l'RTC stia funzionando
  if (rtc.lostPower()) {
    // Impostare la data e ora iniziale (puoi cambiare la data e ora se necessario)
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));  // Imposta la data e ora di compilazione dello sketch
  }
}
void loop()
{
  // Legge la data e l'ora attuale dal modulo RTC
  DateTime now = rtc.now();
  Serial.println(now.timestamp());
  if(now.second() % 10 == 0){
    unsigned long start = millis();
    while(millis()-start < 5000){
      digitalWrite(Relay, LOW);   // accende il relay
      digitalWrite(Relay1, LOW);
    }
    digitalWrite(Relay, HIGH);
    digitalWrite(Relay1, HIGH);    // spegne il relay
  }
}