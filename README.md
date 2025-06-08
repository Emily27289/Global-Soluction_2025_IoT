# 🌩️ StormTrack – Sistema de Monitoramento de Calor Extremo

## 📘 Visão Geral

O **StormTrack** é um sistema de monitoramento ambiental desenvolvido para identificar e responder a situações de calor extremo em áreas urbanas. Utilizando sensores de temperatura, umidade e luminosidade integrados a um microcontrolador ESP32, a solução é capaz de coletar dados ambientais em tempo real, processar essas informações localmente e encaminhá-las para um painel de controle inteligente por meio de comunicação HTTP no formato JSON.

A proposta visa mitigar os efeitos de desastres climáticos como ondas de calor e colapsos em infraestruturas urbanas sensíveis à variação térmica, fornecendo uma visualização prática e instantânea dos dados através de um dashboard em Node-RED.

---

## 🎯 Objetivo da Solução

* Detectar condições ambientais críticas (temperatura elevada, baixa umidade, luminosidade intensa ou deficiente).
* Atuar de forma automatizada por meio de relés que simulam sistemas de resfriamento e iluminação urbana.
* Enviar os dados para um gateway (Node-RED), que processa e exibe em tempo real um painel interativo.
* Gerar alertas visuais e práticos com base nos critérios definidos (por exemplo, bomba d'água ativada quando a temperatura ultrapassa 30°C com umidade abaixo de 40%).

---

## 🛠 Tecnologias Utilizadas

| Tecnologia  | Função                                                |
| ----------- | ----------------------------------------------------- |
| ESP32       | Microcontrolador para coleta e processamento de dados |
| Wokwi       | Simulador virtual do ESP32 e seus sensores            |
| DHT22       | Sensor de Temperatura e Umidade                       |
| LDR         | Sensor de Luminosidade                                |
| Node-RED    | Gateway e painel com dashboard em tempo real          |
| HTTP + JSON | Protocolo de comunicação entre ESP32 e Node-RED       |
| Arduino IDE | Ambiente de desenvolvimento do código C++             |

---

## 🧪 Componentes do Sistema

### Sensores e Atuadores Simulados

* ✅ **DHT22**: temperatura e umidade – conectado ao pino GPIO 4
* ✅ **LDR**: luminosidade – conectado ao pino A0 (GPIO 34)
* ✅ **Relé Luz**: pino GPIO 23
* ✅ **Relé Bomba d'Água**: pino GPIO 15

---

## 🧠 Lógica do Sistema

1. Leitura da temperatura, umidade e luminosidade a cada 5 segundos.
2. Avaliação das condições ambientais:

   * Temperatura > 30 °C **e** Umidade < 40% → Ativa bomba (releBomba)
   * Luminosidade < 40% → Ativa iluminação (releLuz)
3. Geração de um JSON com os dados atuais.
4. Envio via HTTP para o Node-RED (em um ESP real), ou visualização no Serial (em simulação).

### Exemplo de JSON Gerado:

```json
{
  "temperatura": 31.4,
  "umidade": 38,
  "luminosidade": 24
}
```

---

## 🌐 Fluxo Node-RED

### 1. Recepção de Dados:

* Nó HTTP-IN (rota `/entrada`) para ESP32 real
* (ou) Simulação com nó `inject` com JSON manual

### 2. Processamento:

* Nó `json` → conversão do payload
* Nó `function` → verificação de limites para alertas (ex: calor extremo)

### 3. Apresentação no Dashboard:

* `ui_gauge` → Temperatura e Umidade
* `ui_chart` → Histórico de Luminosidade
* `ui_text` → Alerta textual com status do ambiente

### 4. Feedback Visual:

* Painel `/ui` exibe todos os dados com atualização automática e organização por seções
* Simula impacto prático em tempo real com LED virtual e estado dos relés

---

## 🚀 Como Executar o Projeto

### Parte 1 – Wokwi (Simulação)

1. Acesse o projeto Wokwi com ESP32 configurado
2. Execute o código (arquivo `StormTrack_Esp32.ino`)
3. Veja os dados no Serial Monitor (com JSON simulando o envio)

### Parte 2 – Node-RED

1. Instale e execute o Node-RED localmente
2. Importe o fluxo `StormTrack_NodeRed_Fluxo.json`
3. Acesse `http://localhost:1880/ui`
4. Clique no botão `inject` (se em simulação)
5. Veja os dados nos gauges, gráfico e alerta textual

---
