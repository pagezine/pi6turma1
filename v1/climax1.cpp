//Projeto Univesp - PI6 Grupo 22

#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>

const char* ssid = "NomeDaSuaRedeWiFi";
const char* password = "SenhaDaSuaRedeWiFi";

ESP8266WebServer server(8080);

// Pino do relé
const int relayPin = D1;

// Estado inicial do relé (desligado)
bool relayState = false;

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
}

// Função para lidar com requisições GET para /
void handleRoot() {
  // Construir a página HTML com um botão para ligar/desligar a ventoinha
  String html = "<!DOCTYPE html><html><head><title>Controle da Ventoinha</title></head><body>";
  html += "<h1>Controle da Ventoinha</h1>";
  html += "<form action='/relay' method='post'>";
  html += "<button type='submit'>";
  // Definir o texto do botão com base no estado atual do relé
  html += relayState ? "Desligar Ventoinha" : "Ligar Ventoinha";
  html += "</button>";
  html += "</form>";
  html += "</body></html>";

  // Enviar a página HTML como resposta
  server.send(200, "text/html", html);
}

// Função para lidar com requisições POST para /relay
void handleRelay() {
  // Inverter o estado do relé
  relayState = !relayState;
  // Atualizar o estado do pino do relé
  digitalWrite(relayPin, relayState ? HIGH : LOW);

  // Redirecionar de volta para a página inicial após a alteração
  server.sendHeader("Location", String("/"), true);
  server.send(302, "text/plain", "");
}
