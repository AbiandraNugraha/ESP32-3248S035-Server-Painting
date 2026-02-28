#include <WiFi.h>
#include <WebServer.h>
#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();
WebServer server(80);

const char* ssid = "ESP32-3248S035";
const char* password = "password123";

uint16_t hexTo565(String hex) {
  uint32_t rgb = strtol(hex.c_str(), NULL, 16);
  return tft.color565((rgb >> 16) & 0xFF, (rgb >> 8) & 0xFF, rgb & 0xFF);
}

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html><html><head><meta name="viewport" content="width=device-width, initial-scale=1.0, user-scalable=no">
<style>
  body { text-align: center; background: #000; color: #0f0; font-family: sans-serif; margin: 0; overflow-x: hidden; }
  .controls { padding: 10px; background: #111; border-bottom: 1px solid #333; position: sticky; top: 0; z-index: 10; }
  canvas { border: 1px solid #444; background: #000; touch-action: none; width: 480px; height: 320px; max-width: 95vw; height: auto; margin: 10px auto; display: block; }
  input, button { padding: 8px; margin: 2px; border-radius: 4px; border: 1px solid #444; background: #222; color: #fff; }
  #status { color: #ff0; font-size: 0.8em; margin-top: 5px; }
  .btn-clear { background: #500; border-color: #f00; }
</style></head><body>
  <div class="controls">
    <input type="color" id="col" value="#00ff00">
    <input type="text" id="txt" placeholder="Text...">
    <button onclick="prepText()">Place Text</button>
    <button class="btn-clear" onclick="clearAll()">CLEAR</button>
    <div id="status">Mode: DRAWING</div>
  </div>
  <canvas id="c" width="480" height="320"></canvas>
  <script>
    const cvs = document.getElementById('c'), ctx = cvs.getContext('2d');
    let drawing = false, mode = 'draw';

    const api = (url) => { var x = new XMLHttpRequest(); x.open("GET", url, true); x.send(); };
    
    // NEW: Function to clear both screens
    const clearAll = () => {
      ctx.clearRect(0, 0, cvs.width, cvs.height); // Clears phone canvas
      api('/clear');                             // Clears CYD screen
    };

    const getXY = (e) => {
      const r = cvs.getBoundingClientRect();
      const ev = e.touches ? e.touches[0] : e;
      const x = Math.round((ev.clientX - r.left) * (480/r.width));
      const y = Math.round((ev.clientY - r.top) * (320/r.height));
      document.getElementById('status').innerText = `Mode: ${mode.toUpperCase()} | Pixel: ${x},${y}`;
      return { x, y };
    };

    const prepText = () => { mode = 'text'; document.getElementById('status').innerText = "TAP TO PLACE TEXT"; };

    const handle = (e) => {
      const {x, y} = getXY(e); const c = document.getElementById('col').value;
      if(mode === 'text') {
        const msg = document.getElementById('txt').value;
        ctx.fillStyle = c; ctx.font = "24px Arial"; ctx.fillText(msg, x, y);
        api("/t?x="+x+"&y="+y+"&msg="+encodeURIComponent(msg)+"&c="+c.substring(1));
        mode = 'draw';
      } else {
        ctx.fillStyle = c; ctx.fillRect(x,y,4,4);
        api("/d?x="+x+"&y="+y+"&c="+c.substring(1));
      }
    };

    cvs.onmousedown = (e) => { drawing = true; handle(e); };
    cvs.onmousemove = (e) => { if(drawing && mode==='draw') handle(e); else getXY(e); };
    window.onmouseup = () => drawing = false;
    cvs.ontouchstart = (e) => { drawing = true; handle(e); e.preventDefault(); };
    cvs.ontouchmove = (e) => { if(drawing && mode==='draw') handle(e); e.preventDefault(); };
    cvs.ontouchend = () => drawing = false;
  </script>
</body></html>)rawliteral";

void setup() {
  Serial.begin(115200);
  tft.init(); tft.setRotation(1); tft.fillScreen(TFT_BLACK);
  
  WiFi.softAP(ssid, password);
  Serial.printf("\n--- BOOT SUCCESS ---\nIP: %s\n", WiFi.softAPIP().toString().c_str());

  server.on("/", []() { server.send(200, "text/html", index_html); });
  server.on("/d", []() {
    uint16_t c = server.hasArg("c") ? hexTo565(server.arg("c")) : TFT_GREEN;
    tft.fillCircle(server.arg("x").toInt(), server.arg("y").toInt(), 2, c);
    server.send(200);
  });
  server.on("/t", []() {
    uint16_t c = server.hasArg("c") ? hexTo565(server.arg("c")) : TFT_GREEN;
    tft.setTextColor(c); tft.drawString(server.arg("msg"), server.arg("x").toInt(), server.arg("y").toInt(), 4);
    server.send(200);
  });
  server.on("/clear", []() {
    tft.fillScreen(TFT_BLACK); server.send(200);
  });
  server.begin();
}

void loop() { server.handleClient(); }
