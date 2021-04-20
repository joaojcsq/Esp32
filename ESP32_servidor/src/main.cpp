#include <Arduino.h>
#include <WiFi.h> //Inclui a lib Wifi

const char* nome_wifi = "GVT-0288"; //Adiciona o nome da rede Wifi em nome_wifi
const char* senha_wifi = "0041294166"; //Adiciona a senha do Wifi em senha_wifi

WiFiServer servidor(80); //Criar o servidor na porta 80


void setup() {
  Serial.begin(115200); //Inicia a serial para debugging (depuração)
  
  Serial.print("Conectando no wifi--> "); //Mostra na serial "Conectando no wifi--> "
  Serial.println(nome_wifi); //Mostra na serial o nome da rede wifi conectada
  
  WiFi.begin(nome_wifi, senha_wifi); //Inicia o wifi do ESP32 com o nome e a senha passados anteriormente

  while(WiFi.status() != WL_CONNECTED){ //Equanto não conectar a rede wifi, mostrar ".", a cada 500ms
    delay(500);
    Serial.print(".");
  }

  
  Serial.println("Conectado :D"); //Mostra na serial "Conectado :D"
  Serial.print("IP --> "); //Mostra na serial "IP --> "
  Serial.print(WiFi.localIP()); //Mostra na serial o número de IP disponibilizado pelo roteador wifi
  Serial.println(""); //Faz uma quebra de linha

  servidor.begin(); //Inicia o servidor

}

void loop() {
  WiFiClient client = servidor.available(); //Armazena em client TRUE se algum cliente solicitar uma página para o servidor

  if(client){ //Se algum cliente chegar, mostrar "Novo cliente"
    Serial.println("Novo cliente");
  }
}
