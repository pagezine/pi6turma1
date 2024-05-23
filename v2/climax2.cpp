//Projeto Univesp - PI6 Grupo 22
// versão com sensor temperatura

#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>

const char* ssid = "NomeDaSuaRedeWiFi";
const char* password = "SenhaDaSuaRedeWiFi";

ESP8266WebServer server(80);

// Pino do relé
const int relayPin = D1;

// Pino do sensor de temperatura
const int tempSensorPin = A0;

// Limite de temperatura para ligar a ventoinha (em graus Celsius)
const float tempLimit = 30.0;

void setup() {
  // Inicialização do Serial para depuração
  Serial.begin(115200);

  // Configuração do pino do relé como saída
  pinMode(relayPin, OUTPUT);
  // Desliga o relé inicialmente
  digitalWrite(relayPin, LOW);

  // Conectar-se à rede WiFi
  WiFi.begin(ssid, password);
  Serial.println("Conectando à rede WiFi...");

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando...");
  }

  Serial.println("Conectado à rede WiFi com sucesso!");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());

  // Rota para lidar com requisições GET para /
  server.on("/", handleRoot);
  // Rota para lidar com requisições POST para /relay
  server.on("/relay", HTTP_POST, handleRelay);
  // Iniciar o servidor web
  server.begin();
}

void loop() {
  // Lidar com as requisições do servidor web
  server.handleClient();

  // Ler a temperatura do sensor
  float tempC = analogRead(tempSensorPin) * 0.48828125; // Conversão de ADC para graus Celsius

  // Verificar se a temperatura ultrapassou o limite
  if (tempC >= tempLimit) {
    // Liga a ventoinha
    digitalWrite(relayPin, HIGH);
  } else {
    // Desliga a ventoinha
    digitalWrite(relayPin, LOW);
  }

  // Atraso para evitar leituras muito frequentes
  delay(1000);
}

// Função para lidar com requisições GET para /
void handleRoot() {
  // Construir a página HTML com um botão para ligar/desligar a ventoinha
  String html = "<!DOCTYPE html><html><head><title>Controle da Ventoinha</title></head><body>";
  html += "<h1>Controle da Ventoinha</h1>";
  html += "<p>Temperatura atual: ";
  html += analogRead(tempSensorPin) * 0.48828125; // Conversão de ADC para graus Celsius
  html += " °C</p>";
  html += "<form action='/relay' method='post'>";
  html += "<button type='submit'>";
  // Definir o texto do botão com base no estado atual do relé
  html += digitalRead(relayPin) ? "Desligar Ventoinha" : "Ligar Ventoinha";
  html += "</button>";
  html += "</form>";
  html += "</body></html>";

  // Enviar a página HTML como resposta
  server.send(200, "text/html", html);
}

// Função para lidar com requisições POST para /relay
void handleRelay() {
  // Inverter o estado do relé
  digitalWrite(relayPin, !digitalRead(relayPin));

  // Redirecionar de volta para a página inicial após a alteração
  server.sendHeader("Location", String("/"), true);
  server.send(302, "text/plain", "");
}
