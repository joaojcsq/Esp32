#define trigPin 7
#define echoPin 8
String readString;
byte  v;
byte sensorInterrupt = 0;
byte sensorPin       = 2;
int vazao = 0;
int d;
float calibrationFactor = 7.5; // verificar o valor do calibrador
volatile byte pulseCount;
float flowRate = 0;
unsigned long oldTime;

void setup() {
  Serial.begin(9600);
  pinMode(7, OUTPUT);
  pinMode(8, INPUT);
  pinMode(2, INPUT);
  pinMode(11, OUTPUT);
  pinMode(3, OUTPUT); // verificar o pino
  pinMode(4, OUTPUT); // verificar o pino
  pinMode(13, OUTPUT); // verificar o pino
  digitalWrite(4, HIGH); // verificar tensao
  digitalWrite(3, LOW); // verificar tensao
  digitalWrite(2, HIGH);
  pulseCount        = 0;
  flowRate          = 0.0;
  oldTime           = 0;
  attachInterrupt(sensorInterrupt, pulseCounter, FALLING);
}

void loop()
{

  // ###################
  // RECEBE O DADO DA SERIAL
  // ###################

  while (Serial.available()) {
    delay(3);
    char c = Serial.read();
    readString += c;
  }

  if (readString.length() > 0) {
    v = readString.toInt();
    analogWrite(11, v);
    readString = "";
  }
  // ###################

  // ###################
  // VALOR DA DISTANCIA EM CM
  // ###################
  long duration;
  float distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = ((duration / 2) / 29.1) * 10;
  d = distance;


  if ((millis() - oldTime) > 1000) {
    detachInterrupt(sensorInterrupt);
    flowRate = ((1000.0 / (millis() - oldTime)) * pulseCount) / calibrationFactor;
    oldTime = millis();
    unsigned int frac;
    pulseCount = 0;
    attachInterrupt(sensorInterrupt, pulseCounter, FALLING);
  }
  vazao = flowRate * 100;

  /*  Serial.print("Distancia ==> ");
    Serial.println(d);
    Serial.print("Vazao ==> ");
    Serial.println(vazao);
    delay(200);*/
  Serial.write(d);
  Serial.write(vazao);
  delay(100); // 200
}
void pulseCounter()
{
  pulseCount++;
}
