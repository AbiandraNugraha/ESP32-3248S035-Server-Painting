# ESP32-3248S035C (CYD) Wi-Fi Paint Server

An interactive, responsive Wi-Fi painting application designed specifically for the **ESP32-3248S035C**, commonly known as the **Cheap Yellow Display (CYD) 3.5" model**.

This project hosts a local web server on the ESP32. Users connect via their smartphones or computers to draw on a synchronized canvas or send custom text strings directly to the integrated 480x320 TFT display in real time.

## 📌 Board Specifications
- **Core module:** ESP32-WROOM-32
- **Display Size:** 3.5 inches
- **Resolution:** 480x320 Pixels
- **Display Driver:** ST7796 (or ILI9488 depending on factory batch)
- **Touch Controller:** GT911 (Capacitive) or resistive (Note: This sketch focuses on the Wi-Fi display server aspect).

## ⚙️ Software Requirements
1. **Arduino IDE** with the ESP32 board manager installed.
2. **TFT_eSPI Library** by Bodmer (Install via Arduino Library Manager).
3. Set your IDE configurations via **Tools**:
   - **Board:** `ESP32 Dev Module`
   - **PSRAM:** `Disabled`

---

## 🔧 Library Configuration (`User_Setup.h`)

Because the Cheap Yellow Display has all of its screen tracks pre-routed on its internal PCB layout, you must configure the **TFT_eSPI** library to use the exact pins mapped by the manufacturer.

1. Open your computer's file explorer.
2. Navigate to your Arduino libraries folder:
   - **Windows:** `Documents/Arduino/libraries/TFT_eSPI/`
   - **Mac/Linux:** `~/Arduino/libraries/TFT_eSPI/`
3. Open the file named `User_Setup.h` in a text editor.
4. Replace the entire contents of the file with this layout dedicated to the 3.5" CYD:
5. Save and close the file.
---
## 🚀 Installation & Usage
1. Open your original `480x320` sketch in the Arduino IDE.
2. Click **Upload** to flash the code to your ESP32-3248S035C via its on-board micro-USB/USB-C port.
3. Once booted, connect your phone or laptop to the generated Wi-Fi network:
   - **SSID:** `ESP32-3248S035`
   - **Password:** `password123`
4. Open your web browser, go to `http://192.168.4.1`, and enjoy drawing on the larger 3.5" canvas!
