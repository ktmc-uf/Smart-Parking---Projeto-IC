#include <LiquidCrystal_I2C.h>

// ---- CONFIGURAÇÃO DOS PINOS ----
#define trig1 4
#define echo1 5
#define trig2 9
#define echo2 10

int led1Verm = 3;
int led1Verde = 2;
int led2Verm = 11;
int led2Verde = 12;

// ---- VARIÁVEIS ----
int sensor1 = 0;
int sensor2 = 0;
int vagasocupadas = 0;
int vagaslivres = 2;

// ---- LCD ----
LiquidCrystal_I2C lcd(0x27, 16, 2);

// ---- FUNÇÃO PARA LER SENSOR ULTRASSÔNICO ----
long readUltrasonicDistance(int triggerPin, int echoPin) {
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  long distance = duration / 58; // Converte tempo → cm

  if (distance == 0) return 9999; // Falha de leitura
  return distance;
}

void setup() {
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();
  lcd.clear();


  pinMode(trig1, OUTPUT);
  pinMode(echo1, INPUT);
  pinMode(trig2, OUTPUT);
  pinMode(echo2, INPUT);

  pinMode(led1Verm, OUTPUT);
  pinMode(led1Verde, OUTPUT);
  pinMode(led2Verm, OUTPUT);
  pinMode(led2Verde, OUTPUT);
}

void loop() {

  // ---- LEITURA DOS SENSORES ----
  long dist1 = readUltrasonicDistance(trig1, echo1);
  long dist2 = readUltrasonicDistance(trig2, echo2);

  Serial.print("Sensor 1: ");
  Serial.print(dist1);
  Serial.println(" cm");

  Serial.print("Sensor 2: ");
  Serial.print(dist2);
  Serial.println(" cm");

  // ---- LÓGICA DO SENSOR 1 ----
  if (dist1 > 1 && dist1 < 50) {
    digitalWrite(led1Verm, HIGH);
    digitalWrite(led1Verde, LOW);
    sensor1 = 1;
  } else {
    digitalWrite(led1Verm, LOW);
    digitalWrite(led1Verde, HIGH);
    sensor1 = 0;
  }

  // ---- LÓGICA DO SENSOR 2 ----
  if (dist2 > 1 && dist2 < 50) {
    digitalWrite(led2Verm, HIGH);
    digitalWrite(led2Verde, LOW);
    sensor2 = 1;
  } else {
    digitalWrite(led2Verm, LOW);
    digitalWrite(led2Verde, HIGH);
    sensor2 = 0;
  }

  // ---- CONTAGEM ----
  vagasocupadas = sensor1 + sensor2;
  vagaslivres = 2 - vagasocupadas;

  // ---- LCD ----
  lcd.setCursor(0, 0);
  lcd.print("Vagas livres = ");
  lcd.print(vagaslivres);

  lcd.setCursor(0, 1);
  lcd.print("Vagas ocup. = ");
  lcd.print(vagasocupadas);

  delay(200);
}
