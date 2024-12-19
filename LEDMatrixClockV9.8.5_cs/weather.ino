// **********************************(openweathermap.org) - Output Metric System ***********************************
const char *weatherHost = "api.openweathermap.org";
void getWeatherData() { 
bool FailConnect;
int ESPMaxFreeBlockSize; 
WiFiClient client; // WLAN Client  
HTTPClient http;  
OWMLastConnectionDateTime = FormatedDateTimeEN(true); // Connection Time;
if (!client.connect(weatherHost, 80)) {FailConnect = true;} else {FailConnect = false;}  
if (!FailConnect) { 
// **********************************************************************************************************************  
String apiGetData = "http://" + String(weatherHost) + "/data/2.5/weather?id="+cityID+"&units=metric&APPID="+weatherKey;
// **********************************************************************************************************************
if (SerialMonitor) {
Serial.println(F(""));
Serial.println(F("Stahovani udajů o pocasi – cekejte prosim ..."));}
   http.setRedirectLimit(3); // maximum connection attempts HTTP client
   http.begin(client, apiGetData); // Connect
   http.useHTTP10(true);
   MyWaitLoop(1000); //wait
    int httpCode = http.GET();
    if (httpCode > 0) {  // checks for connection
    if (SerialMonitor) {Serial.println("[HTTP] GET... code: " + HTTPCodeText(httpCode));}
    if(httpCode == HTTP_CODE_OK) {
    // Evaluate Data
    DynamicJsonDocument doc(1024); // for ESP8266 
 // DynamicJsonDocument doc(ESP.getMaxFreeBlockSize() - 1024); // for ESP8266 
 // DynamicJsonDocument doc(ESP.getMaxAllocHeap()); // for ESP32 
    DeserializationError error = deserializeJson(doc, http.getStream());
    doc.shrinkToFit();
    doc.garbageCollect();

    // Assign Weather Data
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

    // --------------------------------for the MAX7219 Display ------------------------------------------------------------------
    if (weatherLocation !=  "") {
    String ATemperature = String(temp, 0);
    ATemperature.replace("-0", "0");
    ATemperature.replace("+0", "0");
    ATemperature.replace("+", "");
    // ATemperature = "-10"; // only for BugFix
    // humidity = 100; // only for BugFix
    ATemperature.trim(); // Remove spaces
    if (!IsNumeric(ATemperature)) {ATemperature = "-99";} // In case of an error
    int IntATemperature = ATemperature.toInt();
    if (IntATemperature < 0) {
    ATemperature.replace("-", String(SM)); // Replace Minus Sign with "short" Minus Sign 
    if (IntATemperature > -10) { 
    ATemp = "            Teplota:      " + String(AT) + " " + ATemperature + String(deg) + "C ";} else { // only current Temperature  
    ATemp = "            Teplota:      " + String(AT2) + " " + ATemperature + String(deg) + "C";}} else { // only current Temperature
    if (IntATemperature > 9) {   
    ATemp = "            Teplota:      " + String(AT) + " " + ATemperature + String(deg) + "C ";} else { // only current Temperature
    ATemp = "            Teplota:      " + String(AT) + "  " + ATemperature + String(deg) + "C ";}} // only current Temperature
    if (humidity > 99) {
    AHum =  "            Vlhkost:      " + String(AL) + " " + String(humidity) + " %";} else {
    if (humidity < 10) { 
    AHum =  "            Vlhkost:      " + String(AL) + "   " + String(humidity) + " % ";} else {   
    AHum =  "            Vlhkost:      " + String(AL) + " " + String(humidity) + " % ";}}

    weatherString = "      +++        Aktualni udaje o pocasi pro " + String(cleanText(weatherLocation)) + ":    ---    "; // City Name
    WPweatherString = "+++ Aktualní udaje o počasí pro " + String(weatherLocation) + ":    ---    "; // City Name
    //weatherString += String(country); // Country code
    weatherString += "Teplota:   " + ATemperature + String(deg) + "C    ---    "; //Temperature
    WPweatherString += "Teplota:   " + ATemperature + "°C    ---    "; //Temperature
    // weatherString += " TempMin.: " + String(tempMin, 1) + " " + deg + "C "; //Temperature Min
    // weatherString += " TempMax.: " + String(tempMax, 1) + " " + deg + "C "; // Temperature Max
    weatherString += "Vlhkost:  " + String(humidity) + " %    ---    "; // Air Humidity
    WPweatherString += "Vlhkost:  " + String(humidity) + " %    ---    "; // Air Humidity
    weatherString += "Tlak:  " + String(pressure) + " hPa    ---    "; // Air pressure
    WPweatherString += "Tlak:  " + String(pressure) + " hPa    ---    "; // Air pressure
    weatherString += "Pravdepodobnost deste:   " + String(clouds) + " %    ---    "; // Chance of Rain
    WPweatherString += "Pravdepodobnost deště:   " + String(clouds) + " %    ---    "; // Chance of Rain
    weatherString += "Vitr:   " + String(windSpeed*3.6, 0) + " km/h       +++              "; // Wind speed
    WPweatherString += "Vitr:   " + String(windSpeed*3.6, 0) + " km/h +++"; // Wind speed
    // weatherString += String(windDeg) + deg + " "; //Wind direction in Degree
    // weatherString += arrowUp + " " + windDirection.substring(2wr,2wr+2) + " "; // Wind speed and direction

    // Current Weather Data for Serial Monitor
    if (SerialMonitor) {
    Serial.println("Udaje o pocasi z: "+FormatedDateTimeEN(false));
    Serial.println("Aktualni udaje o pocasi pro " + String(weatherLocation)+":");
    Serial.println("Venkovni teplota: " + String(temp, 0) + " °C");
    Serial.println("Minimálni teplota: " + String(tempMin, 1) + " °C");
    Serial.println("Maximálni teplota: " + String(tempMax, 1) + " °C");
    Serial.println("Vlhkost: " + String(humidity) + " %");
    Serial.println("Vlhkost: " + String(pressure) + " hPa");
    Serial.println("Moznost deste: " + String(clouds) + " %");
    Serial.println("Rychlost vetru: " + String(windSpeed*3.6, 0) + " km/h");
    Serial.println(F(""));} // for DeBug

    if (weatherLocation != "") {StatusOpenWeatherMap = F("OK");} else {StatusOpenWeatherMap = F("Error");}
    // First Data after restart
    if (FirstWeatherData && weatherLocation != "") {FirstWeatherData = false;}
    if (weatherLocation != "") {if (SerialMonitor) {Serial.println(F("Udaje o pocasi byly uspesne nacteny ..."));}} else
                               {if (SerialMonitor) {Serial.println(F("Nejsou nacteny zadne aktualni udaje o pocasi ..."));}}               
    } else {
    if (SerialMonitor) {  
    Serial.println("Nejsou k dispozici zadne aktualni udaje o pocasi! - " + String(apiGetData)); //error message if no client connect
    Serial.println();} 
    weatherString = F("     +++       Nejsou k dispozici zadne aktualni udaje o pocasi!     +++              ");  
    WPweatherString = F("+++ Nejsou k dispozici zadne aktualni udaje o pocasi! +++"); 
    ATemp = weatherString; AHum = weatherString;
    StatusOpenWeatherMap = F("Chyba");} 
    } else {
     if (SerialMonitor) { 
     Serial.println("[HTTP] GET... code: " + HTTPCodeText(httpCode));
     Serial.println("Neplatny pozadavek OpenWeatherMap! - " + String(apiGetData)); //error message if no client connect
     Serial.println(F(""));}
     weatherString = F("     +++       Pripojeni k serveru OpenWeatherMap se nezdarilo !     +++              ");  
     WPweatherString = F("+++ Pripojeni k serveru OpenWeatherMap se nezdarilo ! +++"); 
     ATemp = weatherString; AHum = weatherString;
     StatusOpenWeatherMap = F("Chyba"); 
      }} else {
    if (SerialMonitor) {  
    Serial.println("[HTTP] GET... code: " + HTTPCodeText(httpCode));
    Serial.println("Pripojeni k serveru OpenWeatherMap se nezdarilo ! - " + String(apiGetData)); //error message if no client connect
    Serial.println(F(""));} 
    weatherString = F("     +++       Pripojeni k serveru OpenWeatherMap se nezdarilo !     +++              ");  
     WPweatherString = F("+++ Pripojeni k serveru OpenWeatherMap se nezdarilo ! +++"); 
    ATemp = weatherString; AHum = weatherString;
    StatusOpenWeatherMap = F("Chyba");}   
http.end(); // HTTP Client beenden      
client.flush();
client.stop(); // Client beenden
} else { 
weatherString = F("     +++       Pripojeni k serveru OpenWeatherMap se nezdarilo !     +++              ");  
WPweatherString = F("+++ Pripojeni k serveru OpenWeatherMap se nezdarilo ! +++"); 
ATemp = weatherString; AHum = weatherString; 
StatusOpenWeatherMap = F("Chyba"); 
client.flush();
client.stop(); // Client beenden
if (SerialMonitor) {Serial.println(F("Pripojeni k serveru OpenWeatherMap se nezdarilo !"));}}} //error message if no client connect
// ==================================================================================================================================
// ==================================================================================================================================