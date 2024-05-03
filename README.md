# Sistema de Monitoramento do Ambiente para Vinhos
Este projeto consiste em um sistema que utiliza-se de sensores de leitura do ambiente para monitorar os níveis de luminosidade, temperatura e umidade, garantindo que os vinhos em uma vinícola estejam armazenados em condições adequadas para evitar assim possíveis danos na composição e, consequentemente, no sabor do vinho.
<br> O sistema utiliza um Display, LEDs, sensores de luz/umidade/temperatura e um buzzer para indicar se as condições estão adequadas, em alerta ou em condição crítica. Sendo assim, este sistema é uma atualização do projeto anterior (CP1-EdgeComputing-ComputingScience) presente aqui no meu perfil da plataforma com melhorias referentes à leitura de novas variáveis ambientais e à forma na qual estes valores são apresentados ao usuário, formando assim um sistema mais complexo em sua estrutura que continua sendo agradável ao usuário.


## Componentes Utilizados

- 1 Sensor de Luz (LDR)
- 1 Sensor de Umidade E Temperatura DHT22
- 3 LEDs (verde, amarelo, vermelho)
- 1 Display LCD 16x2 Fundo Azul
- 1 Buzzer
- 1 Potenciômetro
- Arduino UNO R3

## Resistências utilizadas nos resistores.
- LEDs - Resistência de 200 Ohms
- Display (Pino K) - Resistência de 200 Ohms


## Configuração do Hardware
O circuito é montado de acordo com as seguintes conexões entre o Arduino UNO R3 e os componentes adicionais:

- Pino A0: Conectado ao sensor de luz (LDR)
- Pino 13: Conectado ao LED verde
- Pino 12: Conectado ao LED amarelo
- Pino 11: Conectado ao LED vermelho
- Pino 10: Conectado ao Buzzer
- Pino 9: Conectado ao Sensor DHT 22
- Pinos 7, 6, 5, 4 ,3 ,2 (Conectados ao display respectivamente em RS, E, D4, D5, D6, D7)
- Potenciômetro (Conectado ao V0 do display para controle do contraste)



## Funcionamento do Software
O código embarcado no Arduino é responsável por ler os valores analógicos dos sensores de LUMINOSIDADE, UMIDADE E TEMPERATURA, convertê os valores de LUMINOSIDADE em uma escala de 0 a 100 por cento e conserva os valores de UMIDADE e TEMPERATURA e toma ações com base nesses valores. O sistema opera da seguinte maneira:

- Configuração Inicial: Define os pinos, cria os bytes personalizados e variáveis necessárias.

## SETUP
- Inicia o som de introdução.
- Inicia a introdução Animada no DISPLAY.
- Cria os chars dos bytes personalizados.

## Loop Principal:
- Configura e executa as seções (1 LUZ, 2 UMIDADE, 3 TEMPERATURA) com as condições para serem mostradas a cada 5 segundos no DISPLAY
- Lê os valores de leitura dos sensores (DHT22, LDR).
- Converte o valor da LUMINOSIDADE em uma escala de 0 a 100 para representar a LUMINOSIDADE.
- Cria as condições OK, ALERTA e CRÍTICA e compara os valores lidos pelos sensores para determinar a condição a ser executada.
- Modifica cada seção no Display de acordo com os condições correspondentes, acende os LEDs e liga/desliga o buzzer de acordo com as condições correspondentes.
- Configura os modos que trabalham com os LEDs e o BUZZER.
- Mapeia os valores de luminosidade entre 8 e 1015 e os registra em porcentagem.
- Vermelho para condição CRÍTICA (alta luminosidade, valores excessivos ou muito baixos de temperatura e umidade acima de 70% ou abaixo de 50%).
- Amarelo para condição ALERTA (luminosidade moderada, temperatura fora da faixa adequada).
- Verde para condição OK (baixa luminosidade, temperatura e umidade adequadas).
- Configura a média móvel para trabalhar com os dados dos sensores a cada iteração.
- São printados os valores (já feita a média móvel) no Serial Monitor.
- Aguarda 200ms antes da próxima leitura.


## Componentes e suas condições determinantes.
O Display em conjunto com o Buzzer e os LEDs atuam como principais indicadores físicos das condições ambientais mundo afora, sendo cruciais para que o usuário leigo possa ver se há algum estresse causado ao vinho para poder atuar rapidamente no retorno a condições ambientais adequadas. O Serial Monitor, por ser um indicador virtual, também pode ser usado para observar tais mudanças caso seja necessário uma análise mais específica.


## Lógica por tras do código e conselhos:
Os valores limite de luminosidade devem ser calibrados de acordo com os componentes a serem utilizados e as necessidades específicas da vinícola visto que:
- A resistência do módulo LDR afeta de maneira diretamente proporcional aos valores de leitura.
- o modelo do módulo LDR também influi nos valores de leitura.

<br> Na configuração do código, inverteram-se através de um map os valores de luminosidade para seguir a lógica diretamente proporcional, isto quer dizer:
<br>
maior valor de leitura -> maior intensidade de luz
<br> O delay ao final do Loop Principal serve para evitar oscilações que ocorram no intervalo dos valores limite de leds diferentes, assim evitando possíveis 
averias nos LEDs.

## Leitura de Dados
- Os valores já processados pela média móvel de LUMINOSIDADE, UMIDADE e TEMPERATURA podem ser visualizados pelo Serial Monitor.


REPRODUÇÃO DO PROJETO NO SIMULADOR 
<br> O projeto pode ser executado no simulador feito na plataforma Wokwi através [deste link](https://wokwi.com/projects/396093448737273857)


Ao clicar no símbolo "PLAY", o projeto irá iniciar com condições ambientais modificáveis pelo usuário, ao clicar no LDR aparecerá uma barra de luminosidade onde o usuario poderá mudar os valores de luminosidade, assim como poderá clicar no sensor DHT22 para modificar a temperatura e a umidade, ao fazer isto, os LEDs, Buzzer e o DISPLAY irão responder de acordo a estas mudanças.





