#include <Arduino.h>
#include <RF24.h>
#include <nRF24L01.h>
#include <SPI.h>


RF24 radio(22,21);  // CE, CSN
const byte address[6] = "00001"; // Endereço

byte entrada[8]; // Variável para guardar os valores em bytes ( 0 - 255 ) 8bits. Colocar uma posição a mais para /0
/*
f | t | e | d | a  | s  | p | pwm
0 | 1 | 2 | 3 | 4  | 5  | 6 | 7
0 | 2 | 4 | 8 | 16 | 32 | 64| 140 --> 255
*/

void parar(){ // Para o carrinho
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
  digitalWrite(26, LOW);
  digitalWrite(27, LOW);
}

void esquerda(){ // Vira o carrinho para a esquerda
  digitalWrite(12, HIGH);
  digitalWrite(13, LOW);
  digitalWrite(26, LOW);
  digitalWrite(27, HIGH);
}

void direita(){ // Vira o carrinho para a direita
  digitalWrite(12, LOW);
  digitalWrite(13, HIGH);
  digitalWrite(26, HIGH);
  digitalWrite(27, LOW);
}

void pulso_esquerda(){ // Pulso para o lado esquerdo e depois para o carrinho
  digitalWrite(12, HIGH);
  digitalWrite(13, LOW);
  digitalWrite(26, LOW);
  digitalWrite(27, HIGH);
  delay(100);
  parar();
}

void pulso_direita(){ // Pulso para o lado direito e depois para o carrinho
  digitalWrite(12, LOW);
  digitalWrite(13, HIGH);
  digitalWrite(26, HIGH);
  digitalWrite(27, LOW);
  delay(100);
  parar();
}

void tras(){ // Impulsiona o carrinho para trás
  digitalWrite(12, HIGH);
  digitalWrite(13, LOW);
  digitalWrite(26, HIGH);
  digitalWrite(27, LOW);
}

void frente(){ // Impulsiona o carrinho para frente
  digitalWrite(12, LOW);
  digitalWrite(13, HIGH);
  digitalWrite(26, LOW);
  digitalWrite(27, HIGH);
}

void setup() {
  Serial.begin(115200); // Inicia a serial para debugging
  radio.begin(); // Inicia o NRF24L01
  radio.openReadingPipe(0, address); // Abre a comunicação no endereço acima
  radio.setPALevel(RF24_PA_MIN); // Configura o nível do sinal. Quando mais alto, maior o consumo e a distância
  /*
  RF24_PA_MIN = -18dBm, RF24_PA_LOW = -12dBm, RF24_PA_HIGH = -6dBm, RF24_PA_MAX = 0dBm
  */
  radio.startListening(); // Define o modulo apenas para receber. Não fala, só escuta

  // MOTOR 1
  pinMode(12, OUTPUT); //in3
  pinMode(13, OUTPUT); //in4
  pinMode(14, OUTPUT); //pwm0

  // MOTOR 2
  pinMode(27, OUTPUT); //in2
  pinMode(26, OUTPUT); //in3
  pinMode(25, OUTPUT); //pwm1

  // CONFIGURAR PWM
  ledcSetup(0, 30000, 8); // Atribui ao canal 0 a frequencia de 30000Hz com resolucao de 8bits.
  ledcSetup(1, 30000, 8); // Atribui ao canal 1 a frequencia de 30000Hz com resolucao de 8bits.
  ledcAttachPin(14, 0); // Conecta a porta 14 ao canal 0. 
  ledcAttachPin(25, 1); // Conecta a porta 14 ao canal 1.

  ledcWrite(0, 160); //160 --> menor pwm para girar o motor // Valor do PWM no canal 0
  ledcWrite(1, 160); // Valor do PWM no canal 1
}
 
void loop() { 

if(radio.available()){ // Se receber algum dado pelo NRF240L1

  radio.read(&entrada, sizeof(entrada)); // Armazena os dados na variável "entrada"

  Serial.println(entrada[0]); // Mostra na serial o valor da posição 0
  Serial.println(entrada[1]);
  Serial.println(entrada[2]);
  Serial.println(entrada[3]);
  Serial.println(entrada[4]);
  Serial.println(entrada[5]);
  Serial.println(entrada[6]);
  Serial.println(entrada[7]);
  Serial.println("###########");
    
  frente(); // Move o carrinho para frente
  ledcWrite(0, entrada[7]); // Altera o valor do pwm
  ledcWrite(1, entrada[7]); // Altera o valor do pwm
  }
}