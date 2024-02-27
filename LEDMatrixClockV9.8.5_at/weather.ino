// **********************************(openweathermap.org) - Ausgabe im metrischen System ***********************************
const char *weatherHost = "api.openweathermap.org";
void getWeatherData() { 
bool FailConnect;
int ESPMaxFreeBlockSize; 
WiFiClient client; // WLAN Client  
HTTPClient http;  
OWMLastConnectionDateTime = FormatedDateTimeDE(true); // Connection Time;
if (!client.connect(weatherHost, 80)) {FailConnect = true;} else {FailConnect = false;}  
if (!FailConnect) { 
// **********************************************************************************************************************  
String apiGetData = "http://" + String(weatherHost) + "/data/2.5/weather?id="+cityID+"&units=metric&APPID="+weatherKey;
// **********************************************************************************************************************
if (SerialMonitor) {
Serial.println(F(""));
Serial.println(F("Wetterdaten werden heruntergeladen - Bitte warten ..."));}
   http.setRedirectLimit(3); // maximale Verbindungsversuche HTTP Client 
   http.begin(client, apiGetData); // Connect
   http.useHTTP10(true);
   MyWaitLoop(1000); //wait
    int httpCode = http.GET();
    if (httpCode > 0) {  // Verbindung Prüfen
    if (SerialMonitor) {Serial.println("[HTTP] GET... code: " + HTTPCodeText(httpCode));}
    if(httpCode == HTTP_CODE_OK) {
    // Daten auswerten
    DynamicJsonDocument doc(1024); // for ESP8266 
 // DynamicJsonDocument doc(ESP.getMaxFreeBlockSize() - 1024); // for ESP8266 
 // DynamicJsonDocument doc(ESP.getMaxAllocHeap()); // for ESP32 
    DeserializationError error = deserializeJson(doc, http.getStream());
    doc.shrinkToFit();
    doc.garbageCollect();

    // Wetterdaten zuordnen
    String weatherMain = doc["weather"]["main"];
    String weatherLocation = doc["name"];
    WeatherLocation = weatherLocation;
    String country = doc["sys"]["country"];
    temp = doc["main"]["temp"];
    humidity =  doc["main"]["humidity"];
    int pressure = doc["main"]["pressure"];
    float tempMin =  doc["main"]["temp_min"];
    float tempMax =  doc["main"]["temp_max"];
    float windSpeed = doc["wind"]["speed"];
    int clouds = doc["clouds"]["all"];
    // int windDeg =  doc["wind"]["deg"];
    doc.clear(); //}

    // --------------------------------für die MAX7219 Anzeige ------------------------------------------------------------------
    if (weatherLocation !=  "") {
    String ATemperature = String(temp, 0);
    ATemperature.replace("-0", "0");
    ATemperature.replace("+0", "0");
    ATemperature.replace("+", "");
    // ATemperature = "-10"; // only for BugFix
    ATemperature.trim(); // Leerzeichen entfernen
    if (!IsNumeric(ATemperature)) {ATemperature = "-99";} // Im Fehlerfall
    int IntATemperature = ATemperature.toInt();
    if (IntATemperature < 0) {
    ATemperature.replace("-", String(SM)); // Minus durch "kurzes" Minus ersetzen  
    if (IntATemperature > -10) { 
    ATemp = "            Au"+String(uss)+"entemperatur:          " + String(AT) + " " + ATemperature + String(deg) + "C ";} else { // nur aktuelle Temperatur  
    ATemp = "            Au"+String(uss)+"entemperatur:          " + String(AT2) + " " + ATemperature + String(deg) + "C";}} else { // nur aktuelle Temperatur
    if (IntATemperature > 9) {   
    ATemp = "            Au"+String(uss)+"entemperatur:          " + String(AT) + " " + ATemperature + String(deg) + "C ";} else { // nur aktuelle Temperatur
    ATemp = "            Au"+String(uss)+"entemperatur:          " + String(AT) + "  " + ATemperature + String(deg) + "C ";}} // nur aktuelle Temperatur
    if (humidity > 99) {
    AHum =  "            Au"+String(uss)+"enluftfeuchte:          " + String(AL) + " " + String(humidity) + " %";} else {
    if (humidity < 10) { 
    AHum =  "            Au"+String(uss)+"enluftfeuchte:          " + String(AL) + "   " + String(humidity) + " % ";} else {   
    AHum =  "            Au"+String(uss)+"enluftfeuchte:          " + String(AL) + " " + String(humidity) + " % ";}}

    weatherString = "      +++        Die aktuellen Wetterdaten f"+String(uue)+"r " + String(cleanText(weatherLocation)) + ":    ---    "; //Ortsname
    WPweatherString = "+++ Die aktuellen Wetterdaten für " + String(weatherLocation) + ":    ---    "; //Ortsname
    //weatherString += String(country); // Länderkennung
    weatherString += "Au"+String(uss)+"entemperatur:   " + ATemperature + String(deg) + "C    ---    "; //Temperatur
    WPweatherString += "Außentemperatur:   " + ATemperature + "°C    ---    "; //Temperatur
    // weatherString += " TempMin.: " + String(tempMin, 1) + " " + deg + "C "; //Temperatur Min
    // weatherString += " TempMax.: " + String(tempMax, 1) + " " + deg + "C "; // Temperatur Max
    weatherString += "Luftfeuchte:  " + String(humidity) + " %    ---    "; // Luftfeuchtigkeit
    WPweatherString += "Luftfeuchte:  " + String(humidity) + " %    ---    "; // Luftfeuchtigkeit
    weatherString += "Luftdruck:  " + String(pressure) + " hPa    ---    "; // Luftdruck
    WPweatherString += "Luftdruck:  " + String(pressure) + " hPa    ---    "; // Luftdruck
    weatherString += "Regenwahrscheinlichkeit:   " + String(clouds) + " %    ---    "; // Regenrisiko
    WPweatherString += "Regenwahrscheinlichkeit:   " + String(clouds) + " %    ---    "; // Regenrisiko
    weatherString += "Wind:   " + String(windSpeed*3.6, 0) + " km/h       +++              "; // Windgeschwindigkeit
    WPweatherString += "Wind:   " + String(windSpeed*3.6, 0) + " km/h +++"; // Windgeschwindigkeit
    // weatherString += String(windDeg) + deg + " "; //Windrichtung in Grad
    // weatherString += arrowUp + " " + windDirection.substring(2wr,2wr+2) + " "; // Windgeschwindigkeit und Richtung

    // Aktuelle Wetterdaten für Serial Monitor
    if (SerialMonitor) {
    Serial.println("Wetterdaten von: "+FormatedDateTimeDE(false));
    Serial.println("Die aktuellen Wetterdaten für " + String(weatherLocation)+":");
    Serial.println("Außentemperatur: " + String(temp, 0) + " °C");
    Serial.println("Minimaltemperatur: " + String(tempMin, 1) + " °C");
    Serial.println("Maximaltemperatur: " + String(tempMax, 1) + " °C");
    Serial.println("Luftfeuchte: " + String(humidity) + " %");
    Serial.println("Luftdruck: " + String(pressure) + " hPa");
    Serial.println("Regenwahrscheinlichkeit: " + String(clouds) + " %");
    Serial.println("Windgeschwindigkeit: " + String(windSpeed*3.6, 0) + " km/h");
    Serial.println(F(""));} // for DeBug

    if (weatherLocation != "") {StatusOpenWeatherMap = F("OK");} else {StatusOpenWeatherMap = F("Fehler");}
    // Erste Daten nach Neustart
    if (FirstWeatherData && weatherLocation != "") {FirstWeatherData = false;}
    if (weatherLocation != "") {if (SerialMonitor) {Serial.println(F("Wetterdaten erfolgreich geladen ..."));}} else
                               {if (SerialMonitor) {Serial.println(F("keine aktuellen Wetterdaten geladen ..."));}}          
    } else {
    if (SerialMonitor) {  
    Serial.println("keine aktuellen Wetterdaten vorhanden! - " + String(apiGetData)); 
    Serial.println(F(""));} 
    weatherString = F("     +++       keine aktuellen Wetterdaten vorhanden!     +++              ");  // Fehlermeldung wenn Client nicht verbunden
    WPweatherString = F("+++ keine aktuellen Wetterdaten vorhanden! +++"); // Fehlermeldung wenn Client nicht verbunden
    ATemp = weatherString; AHum = weatherString;
    StatusOpenWeatherMap = F("Fehler");} 
    } else {
     if (SerialMonitor) { 
     Serial.println("[HTTP] GET... code: " + HTTPCodeText(httpCode));
     Serial.println("ungültiger OpenWeatherMap Request ! - " + String(apiGetData)); // Fehlermeldung wenn Client nicht verbunden
     Serial.println(F(""));}
     weatherString = F("     +++       Verbindung zum OpenWeatherMap-Server fehlgeschlagen !     +++              ");   // Fehlermeldung wenn Client nicht verbunden
     WPweatherString = F("+++ Verbindung zum OpenWeatherMap-Server fehlgeschlagen ! +++"); // Fehlermeldung wenn Client nicht verbunden
     ATemp = weatherString; AHum = weatherString;
     StatusOpenWeatherMap = F("Fehler"); 
      }} else {
    if (SerialMonitor) {  
    Serial.println("[HTTP] GET... code: " + HTTPCodeText(httpCode));
    Serial.println("Verbindung zum OpenWeatherMap-Server fehlgeschlagen ! - " + String(apiGetData)); // Fehlermeldung wenn Client nicht verbunden
    Serial.println(F(""));} 
    weatherString = F("     +++       Verbindung zum OpenWeatherMap-Server fehlgeschlagen !     +++              ");  // Fehlermeldung wenn Client nicht verbunden
    WPweatherString = F("+++ Verbindung zum OpenWeatherMap-Server fehlgeschlagen ! +++"); // Fehlermeldung wenn Client nicht verbunden
    ATemp = weatherString; AHum = weatherString;
    StatusOpenWeatherMap = F("Fehler");}   
http.end(); // HTTP Client beenden      
client.flush();
client.stop(); // Client beenden
} else { 
weatherString = F("     +++       Verbindung zum OpenWeatherMap-Server fehlgeschlagen !     +++              ");  // Fehlermeldung wenn Client nicht verbunden 
WPweatherString = F("+++ Verbindung zum OpenWeatherMap-Server fehlgeschlagen ! +++");  // Fehlermeldung wenn Client nicht verbunden
ATemp = weatherString; AHum = weatherString; 
StatusOpenWeatherMap = F("Fehler"); 
client.flush();
client.stop(); // Client beenden
if (SerialMonitor) {Serial.println(F("Verbindung zum OpenWeatherMap-Server fehlgeschlagen !"));}}} // Fehlermeldung wenn Client nicht verbunden
// ==================================================================================================================================
// ==================================================================================================================================
