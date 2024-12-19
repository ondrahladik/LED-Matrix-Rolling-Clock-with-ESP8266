# LED-Matrix-Rolling-Clock-with-ESP8266
LED-Matrix-Rolling-Clock with ESP8266 (WEMOS D1 mini)

# Pinout:<br>
ESP8266 ----- Max7219 <br>
  VCC ------------ VCC <br>
  GND ----------- GND <br>
  D6  ------------- CLK <br>
  D7  ------------- CS <br>
  D8  ------------- DIN <br>
  
  VCC = 5V <br>
  
  D1 = DHT11 / DHT22 - Sensor (Optional)<br>
  D2 = Passive Buzzer KY-006 (Optional)<br>
  D3 = Hardware Button to GND (Optional but recommended)<br>
  D5 = LED to GND - for Humity Warning (Optional) <br> 
<br>
<br>
# Settings in the Arduino IDE (Menu Item “Tools”) <br>
# For ESP8266 (Wemos/LOLIN D1 Mini)

![grafik](https://github.com/user-attachments/assets/cf63eb2f-9dc9-4c2e-aa97-f560f226a1eb)

**Attention: All settings on the ESP8266 will be lost !!!**
<br>
<br>
# Installation: 
When the clock is switched on for the first time, an access point is started. (SSID: LED-Matrix-Clock)  <br>
In the captive portal (standard IP: 192.168.4.1) where you can select your own WLAN.  <br>
The API-key and the city-ID of "OpenWeatherMap" can also be entered here. (Optional)  <br>
The API-Key for "NewsAPI" can also be entered here. (Optional) <br>

<br>

# Changing the WLAN password:
When a button installed is (**pin D3 to ground**) then here. <br>
Press the button until the access point is started (10 times). <br>
The button also serves to switch the display on and off at the same time. <br>
Or changing over Webinterface right bottom of the root site. <br>

<br>

# Webinterface:
The watch also uses a web interface to make settings. <br>
The call is made via the IP address of the clock or <br>
"http://ledmatrixuhr.local" (German Version) <br>
"http://ledmatrixclock.local" (English Version)<br>
"http://ledmatricehorloge.local" (French Version) <br>

<br>

# Video:
YouTube Video: (German)<br>
https://www.youtube.com/watch?v=6Jl69GYtSMw <br>
YouTube Video: (English)<br>
https://www.youtube.com/watch?v=ZmM3IA_AyQY <br>
