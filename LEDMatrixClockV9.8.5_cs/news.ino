// **********************************(openweathermap.org)***********************************
// Test -->  http://newsapi.org/v2/top-headlines?country=de&apiKey=yourAPIKey
// *****************************************************************************************
const char *Host = "newsapi.org";
void getNews() {
/*****************************************************************************************************************************/
int authors_Count = 11;  
String authors[authors_Count] = {"The Independent", "Manchester Evening News", "The Mirror", "BBC", "Sky Sports",
                                 "The Guardian", "Financial Times", "Sky News", "The Times", "Daily Mail", "The Telegraph"};  // United Kingdom Authors
/*****************************************************************************************************************************/ 
String Country = F("gb"); // Default gb = United Kingdom English
/*****************************************************************************************************************************/
bool FailConnect, aFound;  
bool IsTitle = false;
aFound = false; // Init
WiFiClient client; // WLAN Client  
HTTPClient http;  
APINews = ""; // Initialize variable
StatusNewsAPI = F("n/a"); 
NewsAPILastConnectionDateTime = FormatedDateTimeEN(true); // Connection Time;
if (!client.connect(Host, 80)) {FailConnect = true;} else {FailConnect = false;}  
if (!FailConnect) { 
// ************************************************************************************************************  
String apiGetData = "http://" + String(Host) + "/v2/top-headlines?country=" + Country + "&apiKey=" + newsKey;
// ************************************************************************************************************
if (SerialMonitor) {
Serial.println(F(""));
Serial.println(F("Stahuji novinky – cekejte prosim ..."));} 
   http.setRedirectLimit(3); // maximum connection attempts HTTP client 
   http.begin(client, apiGetData); // Connect
   http.useHTTP10(true);
    MyWaitLoop(1000); //wait
    int httpCode = http.GET();
    if (httpCode > 0) {  // checks for connection
    if (SerialMonitor) {Serial.println("[HTTP] GET... code: " + HTTPCodeText(httpCode));}
    if(httpCode == HTTP_CODE_OK) {
    // Evaluate Data
    StaticJsonDocument<256> filter; 
    for (int i = 0; i < 20; i++) { 
    filter["articles"][i]["author"] = true;
    filter["articles"][i]["title"] = true;}

 // DynamicJsonDocument doc2(1024); // for ESP8266 
    DynamicJsonDocument doc2(ESP.getMaxFreeBlockSize() - 1024); // for ESP8266 
 // DynamicJsonDocument doc2(ESP.getMaxAllocHeap()); // for ESP32
    DeserializationError error = deserializeJson(doc2, http.getStream(), DeserializationOption::Filter(filter));
    doc2.garbageCollect();
    doc2.shrinkToFit();

    if (SerialMonitor) {
    Serial.println(F("Seznam vsech autoru:"));
    for (int i = 0; i < 20; i++) {
    String articles_author = doc2["articles"][i]["author"];
    Serial.println(String(i)+". Autor: "+ articles_author);} // for Debug*/
    Serial.println(F(""));}

    // Search Data  
    if (SerialMonitor) {Serial.println("Rozebrat autory: "+FormatedDateTimeEN(false));}
    for (int i = 0; i < 20; i++) { // There are 20 authors at NewsAPI
    String articles_author = doc2["articles"][i]["author"]; 
    articles_author.toUpperCase();  
    String articles_title = doc2["articles"][i]["title"];
    articles_title.trim();
    if (articles_author != "" && articles_author != "null"){
    for (int l = 0; l < authors_Count; l++) {  
    authors[l].toUpperCase();      
    if (articles_author == authors[l]) {aFound = true;}} // Authors-Filter
    if (aFound){ 
    if (articles_title != "") {
    if (SerialMonitor) {Serial.println("Filtr: "+String(i)+". Autor: "+ articles_author);} 
    APINews = "     +++       "+cleanText(articles_title)+"     +++              "; // for Matrix Display
    WPAPINews = "+++ "+articles_title+"     +++"; // for WebPage
    if (SerialMonitor) {Serial.println("Zpravy: +++ "+articles_title+" +++");}  // for Serial Monitor
    break;}}}}
    if (SerialMonitor) {Serial.println(F(""));}
    if (APINews != "") {StatusNewsAPI = F("OK");
    if (SerialMonitor) {Serial.println(F("Novinky byly uspesne nacteny ..."));}} else {
    StatusNewsAPI = F("enabled");
    if (SerialMonitor) {Serial.println(F("Nejsou k dispozici zadne novinky ... !"));}}
    doc2.clear();
    } else {
     APINews = F("     +++       Pripojení k serveru NewsAPI se nezdarilo !     +++              ");  
     WPAPINews = F("+++ Pripojení k serveru NewsAPI se nezdarilo ! +++");  
     StatusNewsAPI = F("Chyba"); 
     if (SerialMonitor) {
     Serial.println("[HTTP] GET... code: " + HTTPCodeText(httpCode));  
     Serial.println("Neplatny pozadavek NewsAPI ! - " + String(apiGetData)); //error message if no client connect
     Serial.println(F(""));}}} else {
    APINews = F("     +++       Pripojení k serveru NewsAPI se nezdarilo !     +++              ");  
    WPAPINews = F("+++ Pripojení k serveru NewsAPI se nezdarilo ! +++");    
    StatusNewsAPI = F("Chyba");  
    if (SerialMonitor) {
    Serial.println("[HTTP] GET... code: " + HTTPCodeText(httpCode));
    Serial.println("Pripojení k serveru NewsAPI se nezdarilo ! - " + String(apiGetData)); //error message if no client connect
    Serial.println(F(""));}}      
http.end();
client.flush();
client.stop();
} else {
APINews = F("     +++       Pripojení k serveru NewsAPI se nezdarilo !     +++              ");  
WPAPINews = F("+++ Pripojení k serveru NewsAPI se nezdarilo ! +++");    
StatusNewsAPI = F("Chyba");  
client.flush();
client.stop();  
if (SerialMonitor) {Serial.println(F("Pripojení k serveru NewsAPI se nezdarilo !"));}}} //error message if no client connect 
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++