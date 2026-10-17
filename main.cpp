#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

const char* ssid = "Control_Relee_Hadef";
const char* password = "parola1234";

const int piniRelee[] = {12, 14, 27, 26, 25};
const int nrRelee = 5;

// Variabilă pentru starea cu menținere a pinului 12
bool state12 = false;

AsyncWebServer server(80);

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
    <title>Hadef Hybrid Control</title>
    <meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1, user-scalable=no">
    <style>
        body { font-family: 'Segoe UI', sans-serif; text-align: center; background: #121212; color: #e0e0e0; margin: 0; padding: 20px; }
        h2 { color: #4CAF50; }
        .grid { display: grid; grid-template-columns: 1fr; gap: 15px; max-width: 400px; margin: 0 auto; }
        
        .btn { 
            background: #2c2c2c; border: 3px solid #4CAF50; color: white; 
            padding: 25px; font-size: 18px; width: 100%; border-radius: 15px; 
            cursor: pointer; user-select: none; -webkit-tap-highlight-color: transparent;
            transition: 0.2s;
        }
        .btn:active { background: #4CAF50; color: black; }

        /* Stil special pentru Switch P12 */
        .switch-container { background: #1e1e1e; padding: 20px; border-radius: 15px; border: 1px solid #333; margin-bottom: 20px; }
        .btn-toggle { background: #444; border: 3px solid #2196F3; }
        .btn-toggle.active { background: #2196F3; color: black; }
        
        .status-box { margin-top: 10px; font-size: 14px; font-weight: bold; }
        .status-on { color: #4CAF50; }
        .status-off { color: #f44336; }
    </style>
</head>
<body>
    <h2>Control Hadef</h2>
    
    <div class="grid">
        <!-- SECTIUNE SWITCH P12 -->
        <div class="switch-container">
            <span style="display:block; margin-bottom:10px; color:#2196F3">RELEU P12 (SWITCH)</span>
            <button id="btn12" class="btn btn-toggle" onclick="toggle12()">PORNEȘTE</button>
            <div class="status-box">STARE: <span id="stat12" class="status-off">OPRIT</span></div>
        </div>

        <!-- SECTIUNE MOMENTAN (RESTUL) -->
        <span style="color:#888; font-size:12px">CONTROL MOMENTAN (APASĂ LUNG)</span>
        <button class="btn" onmousedown="cmd(14,1)" onmouseup="cmd(14,0)" onmouseleave="cmd(14,0)" ontouchstart="cmd(14,1)" ontouchend="cmd(14,0)">RELEU P14</button>
        <button class="btn" onmousedown="cmd(27,1)" onmouseup="cmd(27,0)" onmouseleave="cmd(27,0)" ontouchstart="cmd(27,1)" ontouchend="cmd(27,0)">RELEU P27</button>
        <button class="btn" onmousedown="cmd(26,1)" onmouseup="cmd(26,0)" onmouseleave="cmd(26,0)" ontouchstart="cmd(26,1)" ontouchend="cmd(26,0)">RELEU P26</button>
        <button class="btn" onmousedown="cmd(25,1)" onmouseup="cmd(25,0)" onmouseleave="cmd(25,0)" ontouchstart="cmd(25,1)" ontouchend="cmd(25,0)">RELEU P25</button>
    </div>

    <script>
        let isP12On = false;

        function toggle12() {
            isP12On = !isP12On;
            const btn = document.getElementById('btn12');
            const stat = document.getElementById('stat12');

            if(isP12On) {
                btn.classList.add('active');
                btn.innerText = "OPREȘTE";
                stat.innerText = "PORNIT";
                stat.className = "status-on";
            } else {
                btn.classList.remove('active');
                btn.innerText = "PORNEȘTE";
                stat.innerText = "OPRIT";
                stat.className = "status-off";
            }
            fetch(`/update?pin=12&val=${isP12On ? 1 : 0}`);
        }

        function cmd(pin, stat) {
            fetch(`/update?pin=${pin}&val=${stat}`);
        }

        window.oncontextmenu = function(event) {
             event.preventDefault();
             return false;
        };
    </script>
</body>
</html>
)rawliteral";

void setup() {
    Serial.begin(115200);

    for (int i = 0; i < nrRelee; i++) {
        digitalWrite(piniRelee[i], HIGH); 
        pinMode(piniRelee[i], OUTPUT);
        digitalWrite(piniRelee[i], HIGH);
    }

    WiFi.softAP(ssid, password);
    Serial.print("IP AP: "); Serial.println(WiFi.softAPIP());

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send_P(200, "text/html", index_html);
    });

    server.on("/update", HTTP_GET, [](AsyncWebServerRequest *request){
        if (request->hasParam("pin") && request->hasParam("val")) {
            int pin = request->getParam("pin")->value().toInt();
            int val = request->getParam("val")->value().toInt();
            
            // Logica: val 1 -> LOW (ON), val 0 -> HIGH (OFF)
            digitalWrite(pin, (val == 1) ? LOW : HIGH);
        }
        request->send(200, "text/plain", "OK");
    });

    server.begin();
}

void loop() {}
