# pi6turma22
Projeto Integrador Univesp PIJ610 Turma 022

Este código cria um servidor web simples que exibe uma página HTML com um botão para ligar e desligar a ventoinha. Quando o botão é pressionado, uma requisição POST é enviada para o servidor, que alterna o estado do relé (e, portanto, a ventoinha) e atualiza a página para refletir o novo estado. É necessário substituir "NomeDaSuaRedeWiFi" e "SenhaDaSuaRedeWiFi" pelo nome e senha da rede WiFi.

Na versão 2 (Climax), o código Arduino foi modificado para incluir um sensor de temperatura. Neste exemplo, é utilizado um sensor de temperatura LM35, que fornece uma saída analógica proporcional à temperatura medida em graus Celsius. Quando a temperatura medida ultrapassa um determinado limite, a ventoinha é ligada através do relé. É necessário conectar o pino de sinal do sensor de temperatura ao pino analógico A0 do ESP8266.
