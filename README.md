This is a wireless painting canvas that uses Wi-Fi to connect to any device.
Remember,it have to be exactly ESP32-3248S035C
with 320*480 resolution,3.5" size,
ST7796 driver and GT911 touch driver.
Not the ESP32-3248S035R that uses XPT2046 touch driver,
nor ESP32-2432S028R that is 2.8".
Neither it willn't work.
You have to install TFT_eSPI 2.5.43 and change the entire
User_Setup.h in Documents\Arduino\libraries\TFT_eSPI
with the file i provided.
Neither it will fail too.
Where to use the app?
Your device have to connect its wifi "ESP32-3248S035"
with password "password123".
The app is in IP address 192.168.4.1.
Here i have the .ino file and full User_Setup.h,
and the test video for ddemonstration.
