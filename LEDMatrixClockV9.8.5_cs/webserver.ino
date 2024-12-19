// Web Server Homepage
void handleRoot() { 
// send Data
if (!MEP){
server.setContentLength(CONTENT_LENGTH_UNKNOWN);  
SendHTMLString(""); // Send HTMLString                    
server.sendContent(RootHTMLString_1());  // 1. Part
server.sendContent(RootHTMLString_2());  // 2. Part
server.sendContent(RootHTMLString_3());  // 3. Part
server.sendContent(RootHTMLString_4());  // 4. Part
server.sendContent(RootHTMLString_5());  // 5. Part
server.sendContent(RootHTMLString_6());  // 6. Part
server.sendContent(RootHTMLString_7());  // 7. Part
server.sendContent(RootHTMLString_8());  // 8. Part
if (IsBuzzer) {server.sendContent(RootHTMLString_9());} // 9. Part only for passive piezo Buzzer
server.sendContent(RootHTMLString_10()); // 10. Part
server.sendContent(RootHTMLString_11()); // 11. Part
server.client().flush();
MyWaitLoop(100); // short pause so that the memory can be emptied
server.client().stop();
if (RebootNow) {
if (!Display) {
printStringWithShift("           ",ScrollTextTime);
sendCmdAll(CMD_SHUTDOWN,1); // Display on  
} // Switch on Display when off  
printStringWithShift("        +++       Hodiny se restartuji      +++           ",ScrollTextTime); 
digitalWrite(HWLEDPin, LOW); // LED off 
ESP.restart();} // Restart Clock
if (littleFSInit && ResetNow) {ResetClock();}}} // Settings to Standard - WLAN Access Data will be deleted

/********************************************************************************************************************************************************/

String RootHTMLString_1(){
/* &nbsp = Space | <meta http-equiv=\"refresh\" content=\"60\">\ = Refresh all 60 sec*/ 
String RefreshTime = F("60"); // Refresh Website after X seconds
  String HTMLString = F("");
   String InTempOnOff1 = F("");
    String InTempOnOff2 = F("");

    CheckInHumidity(); // Indoor Humidity measurement

  // Display Indoor Temperature YES/NO (DHT11 or DHT22)
  if (InTempCounter < 5) {
  if (InTempOffset == "999") {InTempValue = "0";} else {InTempValue = InTempMessure();} // Temperature measurement 
  if (InTempValue != "-") {
  IntInTempValue = InTempValue.toInt();  
  if (IntInTempValue < 10) {
  InTempOnOff1 = F("id= 'Bvalue'>Teplota v hodinach:");  
  } else {
  if (IntInTempValue >= 10 && IntInTempValue <= 28) {InTempOnOff1 = F("id= 'Gvalue'>Teplota v hodinach:");} else {  
  InTempOnOff1 =  F("id= 'Rvalue'>Teplota v hodinach:");}}
  if (InHumMessage == "") { 
  InTempOnOff2 =  F("<a href =\"/tempvalue\"><button class=\"button\" style=\"margin-right: 10px; margin-left: 3px; height: 42px; width: 150px; font-size: 14px; color: blue\">Zobrazit vnitřní teplotu</button></a>");} else {
  InTempOnOff2 =  F("<a href =\"/tempvalue\"><button class=\"button\" style=\"margin-right: 10px; margin-left: 3px; height: 42px; width: 150px; font-size: 14px; color: blue\">Zobrazit vnitřní teplotu</button></a>"); 
  InTempOnOff2 += "<h9>"+InHumMessage+"</h9>";}
  InTempOnOff2 += F("<p></p>");
  InTempOnOff2 += F("<hr style=\"border-top: 3px solid #095484;margin-left: 0px;width: auto;\">");
  } else {InTempOnOff1 = F("");
          InTempOnOff1 = F("");}
  } else {InTempOnOff1 = F("");
          InTempOnOff2 = F("");
          InTempValue = F("!");}

  // Check HTML Substring
// 1. Part of the HTML string
  HTMLString = F("<!DOCTYPE html><html lang='en-GB'>"); 
  HTMLString += F("<head>");
  HTMLString += F("<title>LED hodiny</title>");
  HTMLString += F("<meta http-equiv=\"content-type\" content=\"text/html; charset=utf-8\">");
  HTMLString += "<meta http-equiv=\"refresh\" content=\""+RefreshTime+"\">";
  HTMLString += F("<style>");
  HTMLString += F("body { background-color: #585858; font-size: 28px; font-family: Arial, Helvetica, Sans-Serif; color: #F2F2F2; margin-left: 30px; }");
  HTMLString += F("h1 { color: #2ECCFA; margin-top: 30px; margin-bottom: 0px; }");
  HTMLString += F("h2 { color: white; font-size: 16px; margin-top: 0px; margin-bottom: 10px; }");
  HTMLString += F("h3 { color: white; font-size: 16px; margin-top: 0px; margin-bottom: 10px; }");
  HTMLString += F("h4 { font-size: 14px; margin-top: 0px; margin-bottom: 0px; color: #2ECCFA;}");
  HTMLString += F("h5 { color: white;font-size: 22px; margin-left: 1px; margin-top: 0px; margin-bottom: 10px;}");
  HTMLString += F("h6 { font-size: 14px; margin-top: 0px; margin-bottom: 0px; color: #2ECCFA;}");
  HTMLString += F("h7 { font-size: 14px; margin-top: 0px; margin-bottom: 0px; color: #ffcc00;}");
  HTMLString += F("h8 { font-size: 14px; margin-top: 0px; margin-bottom: 0px; color: #f74f4f; font-weight: bold;}");
  HTMLString += F("h9 { font-size: 18px; margin-left: 80px; margin-top: 0px; margin-bottom: 0px; color: #f79d36; font-weight: bold;}");
  HTMLString += F("#Rvalue {color: #FC3A30;}");
  HTMLString += F("#Gvalue {color: lime;}");
  HTMLString += F("#Bvalue {color: #2ECCFA;}");
  HTMLString += F("</style>");
  HTMLString += F("</head>");
  HTMLString += F("<body>");
  HTMLString += F("<h1>LED hodiny</h1>");
  HTMLString += F("<hr style=\"border-top: 3px solid #095484;margin-left: 0px;width: auto;\">");
  HTMLString += "<h5 "+InTempOnOff1+"</h5>";
  HTMLString += InTempOnOff2;
  return HTMLString;}

/********************************************************************************************************************************************************/

String RootHTMLString_2(){ 
// Selection of brightness of the Matrix and Runtime of the Clock
  String HTMLString = F("");
  // 2. Teil des HTML-Strings
  HTMLString = F("<h2>Displej: ZAP / VYP / TEST / Úrovně jasu:</h2>");
  if (!Display) { 
  HTMLString += CreateButton("Display ZAP",false,"mon","","110","10",""); 
  HTMLString += CreateButton("Display VYP",true,"moff","","110","20","");
  HTMLString += CreateButton("Display TEST",false,"","","110","20","disabled");} else {
  HTMLString += CreateButton("Display ZAP",true,"mon","","110","10","");  
  HTMLString += CreateButton("Display VYP",false,"moff","","110","20","");
  HTMLString += CreateButton("Display TEST",false,"mdt","","110","20","");}

  if (!Display) {  
  if (Brightness == "L1") {HTMLString += CreateButton("Úroveň",true,""," 1","80","10","disabled");} else {HTMLString += CreateButton("Úroveň",false,""," 1","80","10","disabled");}
  if (Brightness == "L2") {HTMLString += CreateButton("Úroveň",true,""," 2","80","10","disabled");} else {HTMLString += CreateButton("Úroveň",false,""," 2","80","10","disabled");}
  if (Brightness == "L3") {HTMLString += CreateButton("Úroveň",true,""," 3","80","10","disabled");} else {HTMLString += CreateButton("Úroveň",false,""," 3","80","10","disabled");}
  if (Brightness == "L4") {HTMLString += CreateButton("Úroveň",true,""," 4","80","10","disabled");} else {HTMLString += CreateButton("Úroveň",false,""," 4","80","10","disabled");}
  if (Brightness == "L5") {HTMLString += CreateButton("Úroveň",true,""," 5","80","10","disabled");} else {HTMLString += CreateButton("Úroveň",false,""," 5","80","10","disabled");}} 
  else {
  if (Brightness == "L1") {HTMLString += CreateButton("Úroveň",true,"mb1"," 1","80","10","");} else {HTMLString += CreateButton("Úroveň",false,"mb1"," 1","80","10","");}
  if (Brightness == "L2") {HTMLString += CreateButton("Úroveň",true,"mb2"," 2","80","10","");} else {HTMLString += CreateButton("Úroveň",false,"mb2"," 2","80","10","");}
  if (Brightness == "L3") {HTMLString += CreateButton("Úroveň",true,"mb3"," 3","80","10","");} else {HTMLString += CreateButton("Uroven",false,"mb3"," 3","80","10","");}
  if (Brightness == "L4") {HTMLString += CreateButton("Úroveň",true,"mb4"," 4","80","10","");} else {HTMLString += CreateButton("Úroveň",false,"mb4"," 4","80","10","");}
  if (Brightness == "L5") {HTMLString += CreateButton("Úroveň",true,"mb5"," 5","80","10","");} else {HTMLString += CreateButton("Úroveň",false,"mb5"," 5","80","10","");}}  
  HTMLString += F("<p></p>");
  return HTMLString;}

/********************************************************************************************************************************************************/

String RootHTMLString_3(){
String HTMLString = F("");
String DisplayAutomaticOnOff = F("");  
// Display automatically ON/OFF if specified in Access Point
  if (DisplayOnTime != "" && DisplayOffTime != ""){
  DisplayAutomaticOnOff = "Automatické zapínání displeje v &nbsp;"+FDOnTime+"&nbsp;&nbsp; hodin<br />Automatické vypínání displeje v &nbsp;"+FDOffTime+"&nbsp;&nbsp; hodin";} else {
  if (DisplayOnTime == "" && DisplayOffTime == ""){
  DisplayAutomaticOnOff = F("Automatické zapínání displeje je zakázáno");} else {  
  if (DisplayOnTime != ""){
  DisplayAutomaticOnOff = "Automatické zapínání displeje v &nbsp;"+FDOnTime+"&nbsp;&nbsp; hodin";} else {
  if (DisplayOffTime != ""){
  DisplayAutomaticOnOff = "Automatické vypínání displeje v &nbsp;"+FDOffTime+"&nbsp;&nbsp; hodin";}}}}
// 3. Part of the HTML string
HTMLString = "<h4>"+DisplayAutomaticOnOff+"</h4>";
HTMLString += F("<a href =\"/cdof\"><button class=\"button\" style=\"margin-right: 10px; height: 24px; font-size: 14px; font-weight: bold; width: 80px;\">Změnit</button></a>");
HTMLString += F("<p></p>");
HTMLString += F("<hr style=\"border-top: 3px solid #095484;margin-left: 0px;width: auto;\">");
return HTMLString;}  

/********************************************************************************************************************************************************/

String RootHTMLString_4(){ // Status Doublepoint
  String HTMLString = F("");
  // 4. Part of the HTML string
  HTMLString = F("<h2>Dvojtečka v hodinách:</h2>");
  if (!Display) {
  if (DoublePointStatus == 2){
  HTMLString += CreateButton("Blikání",true,"","","80","10","disabled");} else {
  HTMLString += CreateButton("Blikání",false,"","","80","10","disabled");}
  if (DoublePointStatus == 1){
  HTMLString += CreateButton("Trvale ZAP",true,"","","130","10","disabled");} else {
  HTMLString += CreateButton("Trvale ZAP",false,"","","130","10","disabled");}
  if (DoublePointStatus == 0){
  HTMLString += CreateButton("Trvale VYP",true,"","","130","10","disabled");} else {
  HTMLString += CreateButton("Trvale VYP",false,"","","130","10","disabled");}  
  } else {
  if (DoublePointStatus == 2){
  HTMLString += CreateButton("Blikání",true,"sdflash","","80","10","");} else {
  HTMLString += CreateButton("Blikání",false,"sdflash","","80","10","");}
  if (DoublePointStatus == 1){
  HTMLString += CreateButton("Trvale ZAP",true,"sdon","","130","10","");} else {
  HTMLString += CreateButton("Trvale ZAP",false,"sdon","","130","10","");}
  if (DoublePointStatus == 0){
  HTMLString += CreateButton("Trvale VYP",true,"sdoff","","130","10","");} else {
  HTMLString += CreateButton("Trvale VYP",false,"sdoff","","130","10","");}}
  HTMLString += F("<p></p>");
  HTMLString += F("<hr style=\"border-top: 3px solid #095484;margin-left: 0px;width: auto;\">");
  return HTMLString;}

/********************************************************************************************************************************************************/

String RootHTMLString_5(){ // ScrollText Speedlevel
String HTMLString = F("");
  // 5. Part of the HTML string
  HTMLString = F("<h2>Rychlost posouvání textu:</h2>"); 
  if (!Display) { 
  if (ScrollTextTime == 60) {HTMLString += CreateButton("Úroveň",true,""," 1","80","10","disabled");} else {HTMLString += CreateButton("Úroveň",false,""," 1","80","10","disabled");}
  if (ScrollTextTime == 55) {HTMLString += CreateButton("Úroveň",true,""," 2","80","10","disabled");} else {HTMLString += CreateButton("Úroveň",false,""," 2","80","10","disabled");}
  if (ScrollTextTime == 50) {HTMLString += CreateButton("Úroveň",true,""," 3","80","10","disabled");} else {HTMLString += CreateButton("Úroveň",false,""," 3","80","10","disabled");}
  if (ScrollTextTime == 45) {HTMLString += CreateButton("Úroveň",true,""," 4","80","10","disabled");} else {HTMLString += CreateButton("Úroveň",false,""," 4","80","10","disabled");}
  if (ScrollTextTime == 40) {HTMLString += CreateButton("Úroveň",true,""," 5","80","10","disabled");} else {HTMLString += CreateButton("Úroveň",false,""," 5","80","10","disabled");}
  if (ScrollTextTime == 35) {HTMLString += CreateButton("Úroveň",true,""," 6","80","10","disabled");} else {HTMLString += CreateButton("Úroveň",false,""," 6","80","10","disabled");}
  if (ScrollTextTime == 30) {HTMLString += CreateButton("Úroveň",true,""," 7","80","10","disabled");} else {HTMLString += CreateButton("Úroveň",false,""," 7","80","10","disabled");}
  if (ScrollTextTime == 25) {HTMLString += CreateButton("Úroveň",true,""," 8","80","10","disabled");} else {HTMLString += CreateButton("Úroveň",false,""," 8","80","10","disabled");} 
  } else { 
  if (ScrollTextTime == 60) {HTMLString += CreateButton("Úroveň",true,"vlt1"," 1","80","10","");} else {HTMLString += CreateButton("Úroveň",false,"vlt1"," 1","80","10","");}
  if (ScrollTextTime == 55) {HTMLString += CreateButton("Úroveň",true,"vlt2"," 2","80","10","");} else {HTMLString += CreateButton("Úroveň",false,"vlt2"," 2","80","10","");}
  if (ScrollTextTime == 50) {HTMLString += CreateButton("Úroveň",true,"vlt3"," 3","80","10","");} else {HTMLString += CreateButton("Úroveň",false,"vlt3"," 3","80","10","");}
  if (ScrollTextTime == 45) {HTMLString += CreateButton("Úroveň",true,"vlt4"," 4","80","10","");} else {HTMLString += CreateButton("Úroveň",false,"vlt4"," 4","80","10","");}
  if (ScrollTextTime == 40) {HTMLString += CreateButton("Úroveň",true,"vlt5"," 5","80","10","");} else {HTMLString += CreateButton("Úroveň",false,"vlt5"," 5","80","10","");}
  if (ScrollTextTime == 35) {HTMLString += CreateButton("Úroveň",true,"vlt6"," 6","80","10","");} else {HTMLString += CreateButton("Úroveň",false,"vlt6"," 6","80","10","");}
  if (ScrollTextTime == 30) {HTMLString += CreateButton("Úroveň",true,"vlt7"," 7","80","10","");} else {HTMLString += CreateButton("Úroveň",false,"vlt7"," 7","80","10","");}
  if (ScrollTextTime == 25) {HTMLString += CreateButton("Úroveň",true,"vlt8"," 8","80","10","");} else {HTMLString += CreateButton("Úroveň",false,"vlt8"," 8","80","10","");}}
  HTMLString += F("<p></p>"); 
  HTMLString += F("<hr style=\"border-top: 3px solid #095484;margin-left: 0px;width: auto;\">");
  return HTMLString;}

/********************************************************************************************************************************************************/

String RootHTMLString_6(){ // Additional functions
String HTMLString = F("");
String EF = F("");
if (EnhancedFunctions) {
EF =  CreateButton("ZAP",true,"zfon","","80","10","");
EF += CreateButton("VYP",false,"zfoff","","80","10","");} else {
EF =  CreateButton("ZAP",false,"zfon","","80","10","");
EF += CreateButton("VYP",true,"zfoff","","80","10","");}
// 6. Part of the HTML string
HTMLString = F("<h2>Doplňkové funkce &nbsp;ZAP / VYP: &nbsp;(Datum, Narozeniny)</h2>");
HTMLString += EF; // Additional functions (date, birthdays) - ON/OFF
if (EnhancedFunctions && GreetingsToday && GT1 != "") { // GT1 = Birthdays and other Greetings   
HTMLString += "<a style=\"font-family:arial; color: aqua; font-size: 16px; margin-left: 40px;\">ToDay: &nbsp;&nbsp;"+GT1+"</a>";} else { // Additional features
if (EnhancedFunctions) {
HTMLString += "<a style=\"font-family:arial; color: aqua; font-size: 16px; margin-left: 40px;\">&nbsp;&nbsp;"+DateString+"</a>";} else {
HTMLString += F("<a style=\"font-family:arial; color: aqua; font-size: 16px; margin-left: 40px;\"></a>");}}
HTMLString += F("<p></p>");
HTMLString += F("<hr style=\"border-top: 3px solid #095484;margin-left: 0px;width: auto;\">");
return HTMLString;}

/********************************************************************************************************************************************************/

String RootHTMLString_7() { // Display Weather Data from OpenWeatherMap
// Enable/disable Weather Data
String HTMLString = F("");
String OWMA = F("");
// Show OpenWeatherMap Status or not
if (AccessOpenWeatherMap) {
if (WeatherFunctions) {
OWMA =  CreateButton("ZAP",true,"owmfon","","80","10","");
OWMA += CreateButton("VYP",false,"owmfoff","","80","10","");} else {
OWMA =  CreateButton("ZAP",false,"owmfon","","80","10","");  
OWMA += CreateButton("VYP",true,"owmfoff","","80","10","");}

if (WeatherFunctions && StatusOpenWeatherMap != "enabled" && Display) {
OWMA += CreateButton("POČASÍ",false,"aowmn","","80","10","");} else {
OWMA += CreateButton("POČASÍ",false,"aowmn","","80","10","disabled");}

if (!WeatherFunctions) {StatusOpenWeatherMap = F("disable");} else {
if (OWMAdjustChange) {StatusOpenWeatherMap = F("enabled"); OWMAdjustChange = false;}}
if (WeatherFunctions && StatusOpenWeatherMap == "enabled" && Display) {
OWMA += F("<a style=\"font-family:arial;color:aqua; font-size: 16px; font-weight: bold; margin-left: 40px;\">Stav: &nbsp;enabled</a>");} 
if (WeatherFunctions && StatusOpenWeatherMap == "OK" && Display) {
String WSTemp = String(temp, 0); WSTemp.trim();
if (IsNumeric(WSTemp) && IsNumeric(String(humidity))) { // Check Temperatur und Luftfeuchte 
OWMA += "<a style=\"font-family:arial;color:#27e835; font-size: 16px; font-weight: bold; margin-left: 40px;\">Stav: &nbsp;OK - "+OWMLastConnectionDateTime+"";
OWMA += "&nbsp;&nbsp;&nbsp;&nbsp;(OT=&nbsp;"+WSTemp+"°C &nbsp;/&nbsp; OH=&nbsp;"+String(humidity)+"%)</a>";} else {
OWMA += "<a style=\"font-family:arial;color:#ff525a; font-size: 16px; font-weight: bold; margin-left: 40px;\">Stav: &nbsp;Error - "+OWMLastConnectionDateTime+"</a>";}} 
if (WeatherFunctions && StatusOpenWeatherMap == "Error" && Display) {
OWMA += "<a style=\"font-family:arial;color:#ff525a; font-size: 16px; font-weight: bold; margin-left: 40px;\">Stav: &nbsp;Error - "+OWMLastConnectionDateTime+"</a>";}
if (WeatherFunctions && !Display) {
OWMA += F("<a style=\"font-family:arial;color:#ffcc00; font-size: 16px; margin-left: 40px;\">Stav: &nbsp;+++ Stahování údajů o počasí nepobíhá, když je displej vypnutý +++</a>");}
} else {
OWMA =  CreateButton("ZAP",false,"owmfon","","80","10","disabled");
OWMA += CreateButton("VYP",true,"owmfoff","","80","10","disabled");
OWMA += CreateButton("POČASÍ",false,"aowmn","","80","10","disabled");
OWMA += F("<a style=\"font-family:arial;color:#ff525a;font-size: 16px; font-weight: bold; margin-left: 40px;\">OpenWeatherMap není aktivní !");}
// 7. Part of the HTML string  
HTMLString =  F("<h2>Zobrazit aktuální údaje o počasí z ---OpenWeatherMAP--- &nbsp; ZAP / VYP / POČASÍ / STAV:</h2>");
HTMLString += OWMA;
HTMLString += F("<p></p>");
HTMLString += F("<hr style=\"border-top: 3px solid #095484;margin-left: 0px;width: auto;\">");
return HTMLString;}

/********************************************************************************************************************************************************/

String RootHTMLString_8() { // Display NewsAPI News
String HTMLString = F("");
String ANA = F("");
  if (AccessNewsAPI) {
// NewsAPI ON / OFF
if (NewsAPIFunction) {
ANA =  CreateButton("ZAP",true,"nafon","","80","10","");
ANA += CreateButton("VYP",false,"nafoff","","80","10","");} else {
ANA =  CreateButton("ZAP",false,"nafon","","80","10","");
ANA += CreateButton("VYP",true,"nafoff","","80","10","");} 

if (NewsAPIFunction && StatusNewsAPI != "enabled" && Display) {
ANA += CreateButton("NOVINKY",false,"aapin","","80","10","");} else {
ANA += CreateButton("NOVINKY",false,"aapin","","80","10","disabled");}

if (!NewsAPIFunction) {StatusNewsAPI = F("disabled");} else {
if (NAAdjustChange) {StatusNewsAPI = F("enabled"); NAAdjustChange = false;}} 

if (NewsAPIFunction && StatusNewsAPI == "enabled" && Display) {
ANA += F("<a style=\"font-family:arial;color:aqua; font-size: 16px; font-weight: bold; margin-left: 40px;\">Stav: &nbsp;enabled</a>");} 
if (NewsAPIFunction && StatusNewsAPI == "OK" && Display) {
ANA += "<a style=\"font-family:arial;color:#27e835; font-size: 16px; font-weight: bold; margin-left: 40px;\">Stav: &nbsp;OK - "+NewsAPILastConnectionDateTime+"</a>";} 
if (NewsAPIFunction && StatusNewsAPI == "Error" && Display) {
ANA += "<a style=\"font-family:arial;color:#ff525a; font-size: 16px; font-weight: bold; margin-left: 40px;\">Stav: &nbsp;Error - "+NewsAPILastConnectionDateTime+"</a>";}
if (NewsAPIFunction && !Display) {
ANA += F("<a style=\"font-family:arial;color:#ffcc00; font-size: 16px; margin-left: 40px;\">Stav: &nbsp;+++ Stahování zpráv nepobíhá, když je displej vypnutý +++</a>");}
} else {
ANA =  CreateButton("ZAP",false,"nafon","","80","10","disabled");
ANA += CreateButton("VYP",true,"nafoff","","80","10","disabled");
ANA += CreateButton("NOVINKY",false,"aapin","","80","10","disabled");
ANA += F("<a style=\"font-family:arial;color:#ff525a;font-size: 16px; font-weight: bold; margin-left: 40px;\">NewsAPI není aktivní !");}

// 8. Part of the HTML string
HTMLString = F("<h2>Zobrazit aktuální zprávy z ---NewsAPI--- &nbsp; ZAP / VYP / NOVINKY / STAV:</h2>");
HTMLString += ANA;
HTMLString += F("<p></p>");
HTMLString += F("<hr style=\"border-top: 3px solid #095484;margin-left: 0px;width: auto;\">");
return HTMLString;}

/********************************************************************************************************************************************************/  

String RootHTMLString_9() { // Settings for passive piezo Buzzer
String HTMLString = F("");
String BSS = F("");
String BHS = F("");
// Startsound ON / OFF
  if (StartSound == "On") { 
  BSS =  CreateButton("Startsound ZAP",true,"sspbson","","140","10",""); 
  BSS += CreateButton("Startsound VYP",false,"sspbsoff","","140","10","");} else {
  BSS =  CreateButton("Startsound ZAP",false,"sspbson","","140","10",""); 
  BSS += CreateButton("Startsound VYP",true,"sspbsoff","","140","10","");} 
  // Hoursound ON / OFF
  if (HourSound == "On") {
  BHS =  CreateButton("Hoursound ZAP",true,"hspbson","","140","10","");
  BHS += CreateButton("Hoursound VYP",false,"hspbsoff","","140","10","");} else {
  BHS =  CreateButton("Hoursound ZAP",false,"hspbson","","140","10","");
  BHS += CreateButton("Hoursound VYP",true,"hspbsoff","","140","10","");} 

// 9. Part of the HTML string   
HTMLString = F("<h2>Nastavení zvuku:</h2>");
HTMLString += ""+BSS+BHS+"";
HTMLString += F("<p></p>"); 
HTMLString += F("<hr style=\"border-top: 3px solid #095484;margin-left: 0px;width: auto;\">");
return HTMLString;}

/********************************************************************************************************************************************************/  

String RootHTMLString_10() { // Settings from Captiv Portal
String HTMLString = F("");
// 10. Part of the HTML string  
HTMLString = F("<h2>Nastavení z AP (Captivní portál):</h2>");
HTMLString += F("<a href =\"/cpadjust\"><button class=\"button\" style=\"margin-right: 10px; height: 26px; width: 110px;\">Nastavení</button></a>");
HTMLString += F("<p></p>");
HTMLString += F("<hr style=\"border-top: 3px solid #095484;margin-left: 0px;width: auto;\">");
return HTMLString;}

/********************************************************************************************************************************************************/  

String RootHTMLString_11() { // Softwareversion
String HTMLString = F("");
String rtime = F("");
rtime = runtime(); // Clock Runtime
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// int ESPRAM = ESP.getMaxFreeBlockSize() / 1024;  // Check RAM
int ESPRAM = ESP.getFreeHeap() / 1024; // Check RAM
String ESPCore = ESP.getCoreVersion() + "&nbsp; (LOLIN / WEMOS D1 mini)"; // Lolin (Wemos) D1 Mini Core Version
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 11. Part of the HTML string    
HTMLString = "<h7>Verze softwaru: &nbsp;"+LMCVersion+"</h7>";
HTMLString += F("<a><br /></a>");
HTMLString += "<h7>Verze hardwaru: &nbsp;"+ESPCore+"</h7>";
HTMLString += F("<a><br /></a>");
if (ESPRAM > 5) {
HTMLString += "<h7>Volná paměť: &nbsp;&nbsp;"+String(ESPRAM)+" kB / 64 kB</h7>";} else {
HTMLString += "<h8>Volná paměť: &nbsp;&nbsp;"+String(ESPRAM)+" kB / 64 kB (Nebezpečí! - příliš málo)</h8>";}
HTMLString += F("<a><br /></a>");
HTMLString += "<h7>Doba běhu hodin: &nbsp;&nbsp;"+rtime+"</h7>";
HTMLString += F("<a href =\"/reset\"><button class=\"button\" style=\"margin-right: 20px; height: 48px; width: 120px;color: red;float: right; font-size: 20px;\">Reset !</button></a>");
HTMLString += F("<a href =\"/reboot\"><button class=\"button\" style=\"margin-right: 30px; height: 48px; width: 120px;color: blue;float: right; font-size: 18px;\">Restart</button></a>");
HTMLString += F("<a><br /></a>");
HTMLString += F("<a><br /></a>");
HTMLString += F("<h6>*) - aktuálně vybráno</h6>");
HTMLString += F("</body>");
HTMLString += F("</html>");
return HTMLString;}

/********************************************************************************************************************************************************/ 

void HTMLAnswer(String WebFunction) {
String HTMLString = F("");
String HTMLAnswerString = F("");  
if (WebFunction == "MatrixOn") {HTMLAnswerString = F("LED Displej byl zapnut");} 
if (WebFunction == "MatrixOff") {HTMLAnswerString = F("LED displej je vypnut");} 
if (WebFunction == "MatrixIsOn") {HTMLAnswerString = F("LED display je již zapnutý");} 
if (WebFunction == "MatrixIsOff") {HTMLAnswerString = F("LED displej je již vypnutý");}
if (WebFunction == "RebootClock") {HTMLAnswerString = F("Když se vrátíte na domovskou stránku<br />, LED displaj se restartuje");}
if (WebFunction == "DoublePointFlash") {HTMLAnswerString = F("Nyní bude blikat dvojtečka v hodinách.");} 
if (WebFunction == "DoublePointOn") {HTMLAnswerString = F("Dvojtečka v hodinách je trvale zapnutá.");} 
if (WebFunction == "DoublePointOff") {HTMLAnswerString = F("Dvojtečka v hodinách je trvale vypnutá.");} 
if (WebFunction == "BrightnessLevel1") {HTMLAnswerString = F("Úroveň 1 jasu LED displeje byla aktivována");} 
if (WebFunction == "BrightnessLevel2") {HTMLAnswerString = F("Úroveň 2 jasu LED displeje byla aktivována");} 
if (WebFunction == "BrightnessLevel3") {HTMLAnswerString = F("Úroveň 3 jasu LED displeje byla aktivována");} 
if (WebFunction == "BrightnessLevel4") {HTMLAnswerString = F("Úroveň 4 jasu LED displeje byla aktivována");} 
if (WebFunction == "BrightnessLevel5") {HTMLAnswerString = F("Úroveň 5 jasu LED displeje byla aktivována");} 
if (WebFunction == "ScrollTextTimeLevel1") {HTMLAnswerString = F("Úroveň 1 rychlosti posouvání textu byla aktivována");} 
if (WebFunction == "ScrollTextTimeLevel2") {HTMLAnswerString = F("Úroveň 2 rychlosti posouvání textu byla aktivována");} 
if (WebFunction == "ScrollTextTimeLevel3") {HTMLAnswerString = F("Úroveň 3 rychlosti posouvání textu byla aktivována");} 
if (WebFunction == "ScrollTextTimeLevel4") {HTMLAnswerString = F("Úroveň 4 rychlosti posouvání textu byla aktivována");} 
if (WebFunction == "ScrollTextTimeLevel5") {HTMLAnswerString = F("Úroveň 5 rychlosti posouvání textu byla aktivována");} 
if (WebFunction == "ScrollTextTimeLevel6") {HTMLAnswerString = F("Úroveň 6 rychlosti posouvání textu byla aktivována");} 
if (WebFunction == "ScrollTextTimeLevel7") {HTMLAnswerString = F("Úroveň 7 rychlosti posouvání textu byla aktivována");} 
if (WebFunction == "ScrollTextTimeLevel8") {HTMLAnswerString = F("Úroveň 8 rychlosti posouvání textu byla aktivována");} 
if (WebFunction == "WeatherFunctionsON1") {HTMLAnswerString = F("Funkce OpenWeatherMap byla zapnuta");}
if (WebFunction == "WeatherFunctionsON2") {HTMLAnswerString = F("Funkce OpenWeatherMap je již zapnutá");}
if (WebFunction == "WeatherFunctionsOFF")  {HTMLAnswerString = F("Funkce OpenWeatherMap Weather Data je již vypnutá");}
if (WebFunction == "NewsAPIFunctionON1")  {HTMLAnswerString = F("NewsAPI - Aktuální zprávy byly zapnuty");}
if (WebFunction == "NewsAPIFunctionON2")  {HTMLAnswerString = F("NewsAPI - Aktuální zprávy je již zapnuto");}
if (WebFunction == "NewsAPIFunctionOFF")   {HTMLAnswerString = F("NewsAPI - Aktuální zprávy je již vypnuto");}
if (WebFunction == "EnhancedFunctionsON1") {HTMLAnswerString = F("Doplňkové funkce byly aktivovány<br />(Datum, Narozeniny)");}
if (WebFunction == "EnhancedFunctionsON2") {HTMLAnswerString = F("Doplňkové funkce jsou již zapnuté<br />(Datum, Narozeniny)");}
if (WebFunction == "EnhancedFunctionsOFF") {HTMLAnswerString = F("Doplňkové funkce jsou již vypnuté<br />(Datum, Narozeniny)");}
if (WebFunction == "StartSoundOnM") {HTMLAnswerString = F("Zvuk při spuštění hodin byl ZAPNUTÝ.");}
if (WebFunction == "StartSoundOnMIs") {HTMLAnswerString = F("Zvuk při spuštění hodin je již zapnutý.");}
if (WebFunction == "StartSoundOffM") {HTMLAnswerString = F("Zvuk při spuštění hodin je již vypnutý.");}
if (WebFunction == "StartSoundOffMIs") {HTMLAnswerString = F("Zvuk při spuštění hodin je již vypnutý.");}
if (WebFunction == "HourSoundOnM") {HTMLAnswerString = F("Zvuk hodin byl zapnut.");}
if (WebFunction == "HourSoundOnMIs") {HTMLAnswerString = F("Zvuk hodin je již zapnutý.");}
if (WebFunction == "HourSoundOffM") {HTMLAnswerString = F("Zvuk hodin byl vypnut.");}
if (WebFunction == "HourSoundOffMIs") {HTMLAnswerString = F("Zvuk hodin je již vypnutý.");}
if (WebFunction == "DisplayCheck") {HTMLAnswerString = F("Probíhá test LED displeje. Čekejte prosím...");}
if (WebFunction == "NoDisplayCheck") {HTMLAnswerString = F("********* Test displeje momentálně není možný. *********<br />Počkejte, až se znovu zobrazí čas.");}
if (WebFunction == "ResetClockYes") {HTMLAnswerString = F("Když se vrátíte na domovskou stránku,<br />spustí se přístupový bod (Captivní portál).<br />a Nastavení jsou nastavena na výchozí.");}
if (WebFunction == "TMPushoverDevice1") {HTMLAnswerString = "Zpráva o testu pushover byla odeslána na adresu "+PushoverDevice1;} 
if (WebFunction == "TMPushoverDevice2") {HTMLAnswerString = "Zpráva o testu pushover byla odeslána na adresu "+PushoverDevice2;} 
if (WebFunction == "TMPushoverDevice3") {HTMLAnswerString = "Zpráva o testu pushover byla odeslána na adresu "+PushoverDevice3;} 
HTMLString = F("<!DOCTYPE html> <html lang='en-GB'>");
HTMLString +=  F("<head>");
HTMLString +=  F("<title>LED hodiny</title>");
HTMLString +=  F("<meta http-equiv=\"content-type\" content=\"text/html; charset=utf-8\">");
HTMLString +=  F("<style>");
HTMLString +=   F("body { background-color: #585858; font-size: 36px; font-family: Arial, Helvetica, Sans-Serif; color: #F2F2F2; margin-left: 30px; }");
HTMLString +=   F("h1 { color: #2ECCFA; margin-top: 30px; margin-bottom: 0px; }");
HTMLString +=   F("h2 { font-size: 26px; margin-top: 0px; margin-bottom: 50px; }");
HTMLString +=  F("</style>");
HTMLString +=  F("</head>");
HTMLString +=    F("<body>");
HTMLString +=    F("<h1>LED hodiny</h1>");
HTMLString +=    F("<a><br /></a>");
HTMLString +=    "<h2>"+HTMLAnswerString+"</h2>";
HTMLString +=    F("<a href =\"/\"><button class=\"button\" style=\"margin-left: 10px;height: 48px; width: 180px;font-size: 16px;\">zpět na domovskou stránku/button></a>");
HTMLString +=  F("</body>");
HTMLString +=    F("</html>"); 
SendHTMLString(HTMLString); // Send HTMLString 
CheckInHumidity(); // Indoor Humidity measurement
HTMLString = F("");}

/********************************************************************************************************************************************************/

void ActualWeather() {
String HTMLString = F(""); 
if (!await) {  
HTMLString = F("<!DOCTYPE html> <html lang='en-GB'>");
HTMLString += F("<head>");
HTMLString += F("<title>LED hodiny</title>");
HTMLString += F("<meta http-equiv=\"content-type\" content=\"text/html; charset=utf-8\">");
HTMLString += F("<style>");
HTMLString += F("body { background-color: #585858; font-size: 36px; font-family: Arial, Helvetica, Sans-Serif; color: #F2F2F2; margin-left: 30px; }");
HTMLString += F("h1 { color: #2ECCFA; margin-top: 30px; margin-bottom: 0px; }");
HTMLString += F("h2 { font-size: 22px; margin-top: 0px; margin-bottom: 50px; }");
HTMLString += F("h3 { font-size: 16px; margin-top: 0px; margin-bottom: 50px; }");
HTMLString += F("</style>");
HTMLString += F("</head>");
HTMLString += F("<body>");
HTMLString += F("<h1>LED hodiny</h1>");
HTMLString += F("<a><br /></a>");
HTMLString += "<h2>Údaje o počasí z: "+OWMLastConnectionDateTime+"</h2>";
HTMLString += "<h3>"+WPweatherString+"</h3>";
HTMLString += F("<a href =\"/\"><button class=\"button\" style=\"margin-left: 10px;height: 48px; width: 180px;font-size: 16px;\">zpět na domovskou stránku</button></a>");
HTMLString += F("</body>");
HTMLString += F("</html>"); 
SendHTMLString(HTMLString); // Send HTMLString 
CheckInHumidity(); // Indoor Humidity measurement
HTMLString = F("");} else {PleaseWait();}}

/********************************************************************************************************************************************************/

void ActualAPINews() {
String HTMLString = F(""); 
if (!await) {  
HTMLString = F("<!DOCTYPE html> <html lang='en-GB'>");
HTMLString += F("<head>");
HTMLString += F("<title>LED hodiny</title>");
HTMLString += F("<meta http-equiv=\"content-type\" content=\"text/html; charset=utf-8\">");
HTMLString += F("<style>");
HTMLString += F("body { background-color: #585858; font-size: 36px; font-family: Arial, Helvetica, Sans-Serif; color: #F2F2F2; margin-left: 30px; }");
HTMLString += F("h1 { color: #2ECCFA; margin-top: 30px; margin-bottom: 0px; }");
HTMLString += F("h2 { font-size: 22px; margin-top: 0px; margin-bottom: 50px; }");
HTMLString += F("h3 { font-size: 16px; margin-top: 0px; margin-bottom: 50px; }");
HTMLString += F("</style>");
HTMLString += F("</head>");
HTMLString += F("<body>");
HTMLString += F("<h1>LED hodiny</h1>");
HTMLString += F("<a><br /></a>");
HTMLString += "<h2>Zprávy z: "+NewsAPILastConnectionDateTime+"</h2>";
HTMLString += "<h3>"+WPAPINews+"</h3>";
HTMLString += F("<a href =\"/\"><button class=\"button\" style=\"margin-left: 10px;height: 48px; width: 180px;font-size: 16px;\">zpět na domovskou stránku</button></a>");
HTMLString += F("</body>");
HTMLString += F("</html>"); 
SendHTMLString(HTMLString); // Send HTMLString 
CheckInHumidity(); // Indoor Humidity measurement
HTMLString = F("");} else {PleaseWait();}}

/********************************************************************************************************************************************************/

// Matrix On
void MatrixOn() {
if (!MEP) {  
if (!await){  
if (!Display) {
await = true;
MEP = true;    
if (SerialMonitor) {Serial.println(F("LED displej byl zapnut."));}  
printStringWithShift("           ",1);
sendCmdAll(CMD_SHUTDOWN,1); // // Display on
ClockScrollIn(); // Clock scroll in
MyWaitLoop(100); // short wait
HTMLAnswer("MatrixOn");
Display = true; MEP = false; await = false;} else {HTMLAnswer("MatrixIsOn");}
CheckInHumidity(); // Indoor Humidity measurement
} else {PleaseWait();}}}

/********************************************************************************************************************************************************/

// Matrix Off
void MatrixOff() { 
if (!await){  
if (Display) { 
await = true;   
dots = 1; // Doublepoint on  
Display = false;
if (WeatherFunctions) {StatusOpenWeatherMap = F("enabled");}  
if (NewsAPIFunction) {StatusNewsAPI = F("enabled");}   
HTMLAnswer("MatrixOff");
if (SerialMonitor) {Serial.println(F("LED displej byl vypnut."));} 
if (WatchOwner1FirstName != "") { 
SText = Politeness(true);} else {SText = Politeness(false);}
printStringWithShift(SText.c_str(),ScrollTextTime);
printStringWithShift("           ",ScrollTextTime);  
sendCmdAll(CMD_SHUTDOWN,0); await = false;} else {HTMLAnswer("MatrixIsOff");} // Display off
CheckInHumidity(); // Indoor Humidity measurement
} else {PleaseWait();}}

/********************************************************************************************************************************************************/

void DoublePointFlash() {
if (!await){      
DoublePointStatus = 2; // Make the Doublepoint of the clock flash
// Status Doublepoint
if (littleFSInit) {
SetupSave("status_doublepoint.txt", String(DoublePointStatus));}
HTMLAnswer("DoublePointFlash");
if (SerialMonitor) {Serial.println(F("Dvojtecka hodin blika."));}
} else {PleaseWait();}}

/********************************************************************************************************************************************************/

void DoublePointOn() {
if (!await){  
DoublePointStatus = 1; // The Doublepoint of the clock is permanently ON
if (littleFSInit) {
SetupSave("status_doublepoint.txt", String(DoublePointStatus));}
HTMLAnswer("DoublePointOn");
if (SerialMonitor) {Serial.println(F("Dvojtecka hodin je pernamentne zapnuta"));}
} else {PleaseWait();}}


/********************************************************************************************************************************************************/

void DoublePointOff() {
if (!await){  
DoublePointStatus = 0; // The Doublepoint of the clock is permanently OFF
if (littleFSInit) {
SetupSave("status_doublepoint.txt", String(DoublePointStatus));}
HTMLAnswer("DoublePointOff");
if (SerialMonitor) {Serial.println(F("Dvojtecka hodin je pernamentne vypnuta"));}
} else {PleaseWait();}}

/********************************************************************************************************************************************************/

// Set the brightness Levels (BrightnessLevel) of the LEDs of the Max7219 via the Web Server
void BrightnessLevel1() {SetBrightnessLevel("L1", 1);}

/********************************************************************************************************************************************************/

void BrightnessLevel2() {SetBrightnessLevel("L2", 2);}

/********************************************************************************************************************************************************/

void BrightnessLevel3() {SetBrightnessLevel("L3", 3);}

/********************************************************************************************************************************************************/

void BrightnessLevel4() {SetBrightnessLevel("L4", 4);}

/********************************************************************************************************************************************************/

void BrightnessLevel5() {SetBrightnessLevel("L5", 5);}

/********************************************************************************************************************************************************/

void SetBrightnessLevel(String BLText, int BLInt) {
if (!await){
sendCmdAll(CMD_INTENSITY, BLInt-1);
Brightness = BLText;
if (littleFSInit) {
SetupSave("matrix_brightness.txt", Brightness);}
HTMLAnswer("BrightnessLevel"+String(BLInt));
if (SerialMonitor) {Serial.println("Uroven jasu "+String(BLInt)+" enabled");}
} else {PleaseWait();}}

/********************************************************************************************************************************************************/

// Adjust the Speed of the Scrolling Text
void ScrollTextTimeLevel1() {
SetScrollTimeAndLevel(60,1);}

/********************************************************************************************************************************************************/

void ScrollTextTimeLevel2() { 
SetScrollTimeAndLevel(55,2); }

/********************************************************************************************************************************************************/

void ScrollTextTimeLevel3() { 
SetScrollTimeAndLevel(50,3);}

/********************************************************************************************************************************************************/

void ScrollTextTimeLevel4() {
SetScrollTimeAndLevel(45,4);}

/********************************************************************************************************************************************************/

void ScrollTextTimeLevel5() {  
SetScrollTimeAndLevel(40,5);}

/********************************************************************************************************************************************************/

void ScrollTextTimeLevel6() { 
SetScrollTimeAndLevel(35,6);}

/********************************************************************************************************************************************************/

void ScrollTextTimeLevel7() {  
SetScrollTimeAndLevel(30,7);}

/********************************************************************************************************************************************************/

void ScrollTextTimeLevel8() {
SetScrollTimeAndLevel(25,8);}

/********************************************************************************************************************************************************/

void SetScrollTimeAndLevel(int STTime, int STLevel){
if (!await) {
await = true;   
ScrollTextTime = STTime; // Scrolling Text Speed  
if (littleFSInit) {
SetupSave("status_scrolltexttime.txt", String(STTime));}
HTMLAnswer("ScrollTextTimeLevel"+String(STLevel)+"");
if (SerialMonitor) {Serial.println("Uroven rychlosti posouvani textu "+String(STLevel)+" aktivovana");}
if (!Display) {sendCmdAll(CMD_SHUTDOWN, 1);
printStringWithShift("        +++  Toto je test rychlosti posouvani textu  +++           ",ScrollTextTime);
sendCmdAll(CMD_SHUTDOWN, 0);} else {
printStringWithShift("        +++  Toto je test rychlosti posouvani textu  +++           ",ScrollTextTime);
ClockScrollIn();} // Scroll the Time in the Display 
await = false;} else {PleaseWait();}}

/********************************************************************************************************************************************************/

void WeatherFunctionsOn() {
if (!await) {  
if (!WeatherFunctions) {
WeatherFunctions = true;
OWMAdjustChange = true;
StatusOpenWeatherMap = F("enabled");
if (littleFSInit) {
SetupSave("status_weatherfunctions.txt", "On");} 
HTMLAnswer("WeatherFunctionsON1");
if (SerialMonitor) {Serial.println(F("OpenWeatherMap - Udaje o pocasi jsou zapnute"));}}
else {
HTMLAnswer("WeatherFunctionsON2");
if (SerialMonitor) {Serial.println(F("OpenWeatherMap - Udaje o pocasi jsou vypnute"));}}   
} else {PleaseWait();}}

/********************************************************************************************************************************************************/

void WeatherFunctionsOff() {
if (!await) {   
WeatherFunctions = false;
StatusOpenWeatherMap = F("disabled");
if (littleFSInit) {
SetupSave("status_weatherfunctions.txt", "Off");} 
HTMLAnswer("WeatherFunctionsOFF");
if (SerialMonitor) {Serial.println(F("OpenWeatherMap - Udaje o pocasi jsou vypnute"));}
} else {PleaseWait();}}

/********************************************************************************************************************************************************/

void NewsAPIFunctionOn() {
if (!await) {   
if (!NewsAPIFunction) {
NewsAPIFunction = true;
NAAdjustChange = true;
StatusNewsAPI = F("enabled");
if (littleFSInit) {
SetupSave("status_newsapifunctions.txt", "On");}  
HTMLAnswer("NewsAPIFunctionON1");
if (SerialMonitor) {Serial.println(F("NewsAPI - Aktualni zpravy zapnuty"));}}
else {
HTMLAnswer("NewsAPIFunctionON2");
if (SerialMonitor) {Serial.println(F("NewsAPI - Aktualni zpravy zapnuty"));}} 
} else {PleaseWait();}}

/********************************************************************************************************************************************************/

void NewsAPIFunctionOff() {
if (!await) {   
NewsAPIFunction = false;
StatusNewsAPI = F("disabled");
if (littleFSInit) {
SetupSave("status_newsapifunctions.txt", "Off");}  
HTMLAnswer("NewsAPIFunctionOFF");
if (SerialMonitor) {Serial.println(F("NewsAPI - Aktualni zpravy jsou již vypnuty"));}
} else {PleaseWait();}}

/********************************************************************************************************************************************************/

void EnhancedFunctionsOn() {
if (!await) {   
if (!EnhancedFunctions) {
EnhancedFunctions = true;
if (littleFSInit) {
SetupSave("status_enhancedfunctions.txt", "On");} 
HTMLAnswer("EnhancedFunctionsON1");} else {
HTMLAnswer("EnhancedFunctionsON2");}  
if (SerialMonitor) {Serial.println(F("Doplnkove funkce jsou zapnuty - (Datum, Narozeniny)"));} 
} else {PleaseWait();}}

/********************************************************************************************************************************************************/

void EnhancedFunctionsOff() {
if (!await) {   
EnhancedFunctions = false;
if (littleFSInit) {
SetupSave("status_enhancedfunctions.txt", "Off");} 
HTMLAnswer("EnhancedFunctionsOFF");
if (SerialMonitor) {Serial.println(F("Doplnkove funkce jsou vypnuty - (Datum, Narozeniny)"));}
} else {PleaseWait();}}

/********************************************************************************************************************************************************/

void GetAdjustments() {
String OWMAPI = F("");
String OWMCID = F("");
String NewsAPIKey = F("");
String CheckIP = F(""); 
String HTMLString = F("");
if (!await) { 
// Check IP-Address
if (cip.length() > 15 || cip.length() < 7) {CheckIP = F("n/a");} else {CheckIP = cip;} // Check IP-Adresse
if (AccessOpenWeatherMap){OWMAPI = weatherKey; OWMCID = cityID;} else {OWMAPI = F("n/a");OWMCID = F("n/a");}
if (newsKey != ""){NewsAPIKey = newsKey;} else {NewsAPIKey = F("n/a");}
HTMLString = F("<!DOCTYPE html><html lang='en-GB'>");
HTMLString += F("<head>");
HTMLString += F("<title>LED hodiny</title>");
HTMLString += F("<meta http-equiv=\"content-type\" content=\"text/html; charset=utf-8\">");
HTMLString += F("<style>");
HTMLString += F("body { background-color: #585858; font-size: 32px; font-family: Arial, Helvetica, Sans-Serif; color: #F2F2F2; margin-left: 30px; }");
HTMLString += F("h1 { color: #2ECCFA; margin-top: 30px; margin-bottom: 0px; }");
HTMLString += F("h2 { font-size: 18px; margin-top: 0px; margin-bottom: 10px; }");
HTMLString += F("h3 { font-size: 24px; margin-top: 0px; margin-bottom: 10px; }");
HTMLString += F("h4 { font-size: 14px; margin-top: 0px; margin-bottom: 1px; color: #ffcc00; float: right;}");
HTMLString += F("h5 { color: white; font-size: 16px; margin-top: 0px; margin-bottom: 10px; }");
HTMLString += F("</style>");
HTMLString += F("</head>");
HTMLString += F("<body>");
HTMLString += F("<h1>LED hodiny</h1>");
if (WatchOwner1FirstName != "" && WatchOwner1LastName != "") {
HTMLString += "<h2>( Majitel hodin:&nbsp;&nbsp;"+WatchOwner1FirstName+" "+WatchOwner1LastName+" )</h2>";}
HTMLString += F("<a><br /></a>");
HTMLString += F("<h3>Nastavení z captivního portálu</h3>");
HTMLString += F("<a><br /></a>");
HTMLString += "<h2>WLAN SSID:&nbsp;&nbsp;"+String(ssid)+"</h2>";
HTMLString += "<h2>IP-Adresa:&nbsp;&nbsp;&nbsp;"+CheckIP+"</h2>";
HTMLString += F("<a><br /></a>");
HTMLString += "<h2>OpenWeatherMap API-Key:&nbsp;&nbsp;"+OWMAPI+"</h2>";
if (WeatherFunctions && String(WeatherLocation) != "" && StatusOpenWeatherMap == "OK") {
HTMLString += "<h2>OpenWeatherMap City-ID:&nbsp;&nbsp;&nbsp;&nbsp;"+OWMCID+" ( "+String(WeatherLocation)+" )</h2>";} else {  
HTMLString += "<h2>OpenWeatherMap City-ID:&nbsp;&nbsp;&nbsp;&nbsp;"+OWMCID+"</h2>";}
HTMLString += F("<a><br /></a>");
HTMLString += "<h2>NewsAPI API-Key:&nbsp;&nbsp;"+NewsAPIKey+"</h2>";
HTMLString += F("<a><br /></a>");
if (IsPushover) {
HTMLString += "<h2>Pushover-SecureAppToken:  &nbsp;&nbsp;&nbsp;&nbsp;"+SecureAppToken+"</h2>";
HTMLString += "<h2>Pushover-UserToken:  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"+UserToken+"</h2>";
HTMLString += "<h2>Pushover-Devicename1:  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"+PushoverDevice1+"</h2>";
if (PushoverDevice2 != "") { 
HTMLString += "<h2>Pushover-Devicename2:  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"+PushoverDevice2+"</h2>";} else {
HTMLString += "<h2>Pushover-Devicename2:  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;n/a</h2>";}  
if (PushoverDevice3 != "") {
HTMLString += "<h2>Pushover-Devicename3:  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"+PushoverDevice3+"</h2>";} else {
HTMLString += "<h2>Pushover-Devicename3:  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;n/a</h2>";}  
HTMLString += "<h2>Pushover-Messagesound:  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"+PushoverMessageSound+"</h2>";
HTMLString += F("<a><br /></a>");}
if (IsBuzzer) {
HTMLString += F("<h2>Nainstalovaný pasivní bzučák</h2>");} else {
HTMLString += F("<h2>Pasivní bzučák není nainstalován nebo je zakázán</h2>");}
HTMLString += F("<a><br /></a>");
if (IsPushover) {
HTMLString += F("<h2><br /></h2>");
HTMLString += F("<hr style=\"border-top: 3px solid #095484;margin-left: 0px;width: auto;\">");
HTMLString += F("<h5>Odeslat zprávu testu push do zařízení:</h5>");
if (PushoverDevice1 != "") {
HTMLString += CreateButton("Zařízení 1",false,"potmdevice1","","90","10","");} else {
HTMLString += CreateButton("Zařízení 1",false,"potmdevice1","","90","10","disabled");} 
if (PushoverDevice2 != "") { 
HTMLString += CreateButton("Zařízení 2",false,"potmdevice2","","90","10","");} else {
HTMLString += CreateButton("Zařízení 2",false,"potmdevice2","","90","10","disabled");}  
if (PushoverDevice3 != "") { 
HTMLString += CreateButton("Zařízení 1",false,"potmdevice3","","90","10","");} else {
HTMLString += CreateButton("Zařízení 3",false,"potmdevice3","","90","10","disabled");}  
HTMLString += F("<hr style=\"border-top: 3px solid #095484;margin-left: 0px;width: auto;\">");
HTMLString += F("<a><br /></a>");}
HTMLString += F("<a href =\"/\"><button class=\"button\" style=\"margin-left: 1px; height: 48px; width: 160px\">zpět na domovskou stránku</button></a>");
HTMLString += F("<a><br /></a>");
HTMLString += F("<a><br /></a>");
HTMLString += F("</body>");
HTMLString += F("</html>");
SendHTMLString(HTMLString); // Send HTMLString
CheckInHumidity(); // Indoor Humidity measurement
HTMLString = F("");
if (SerialMonitor) {Serial.println(F("Vyvola se nastaveni z pristupoveho bodu (Captivni portal)."));}}
else {PleaseWait();}}

/********************************************************************************************************************************************************/

String CreateButton(String BMark, bool Bselect, String BHRef, String Blevel, String Bwidth, String BRmargin, String Bdisable) {
String HTMLString = F("");
if (Bselect) {
HTMLString  = "<a href =\"/"+BHRef+"\"><button class=\"button\" style=\"margin-right: "+BRmargin+"px; color: blue; height: 26px; width: "+Bwidth+"px;\" "+Bdisable+">"+BMark+Blevel+"*</button></a>";} else {
HTMLString += "<a href =\"/"+BHRef+"\"><button class=\"button\" style=\"margin-right: "+BRmargin+"px; height: 26px; width: "+Bwidth+"px;\" "+Bdisable+">"+BMark+Blevel+"</button></a>";}
return HTMLString;}

/********************************************************************************************************************************************************/

void ResetClockSettings() {
if (!await) {   
String HTMLString = F("");
HTMLString = F("<!DOCTYPE html> <html lang='en-GB'>\
  <head>\
  <title>LED hodiny</title>\
  <meta http-equiv=\"content-type\" content=\"text/html; charset=utf-8\">\
  <style>\
   body { background-color: #585858; font-size: 32px; font-family: Arial, Helvetica, Sans-Serif; color: #F2F2F2; margin-left: 30px; }\
   h1 { color: #2ECCFA; margin-top: 30px; margin-bottom: 0px; }\
   h2 { font-size: 22px; margin-top: 0px; margin-bottom: 10px; margin-left: 10px;}\
  </style>\
  </head>\
    <body>\
    <h1>LED hodiny</h1>\
     <h2>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;LED Hodiny Reset !</h2>\
     <h2>(Přístupová data WLAN budou vymazána)</h2>\
     <a><br /></a>\
     <h2>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Nyní resetujte maticové hodiny LED ?</h2>\
     <a><br /></a>\
     <a href =\"/goreset\"><button class=\"button\" style=\"margin-left: 70px;height: 48px; width: 110px; font-size: 22px; color: red\">Ano</button></a>\
     <a href =\"/\"><button class=\"button\" style=\"margin-left: 80px;height: 48px; width: 110px; font-size: 22px;\">Ne</button></a>\
  </body>\
    </html>");  
SendHTMLString(HTMLString); // Send HTMLString
CheckInHumidity(); // Indoor Humidity measurement
HTMLString = F("");
} else {PleaseWait();}}

/********************************************************************************************************************************************************/

void ResetClockYes() { 
/*Weiterleiter - <meta http-equiv=\"refresh\" content=\"3\" URL=\"http://www.google.de\">\     <meta http-equiv=\"refresh\" content=\"3\"; URL=\"http://"+ip1+"\">\*/
if (!await) { 
HTMLAnswer("ResetClockYes");
ResetNow = true; // Reset - Default Settings 
} else {PleaseWait();}}

/********************************************************************************************************************************************************/

void RebootClock()
{
if (!await) {   
HTMLAnswer("RebootClock");
RebootNow = true;
} else {PleaseWait();}}

/********************************************************************************************************************************************************/

void SiteNotFound(){
String HTMLString = F("");
HTMLString = F("<!DOCTYPE html> <html lang='en-GB'>\
  <head>\
  <title>LED hodiny</title>\
  <meta http-equiv=\"content-type\" content=\"text/html; charset=utf-8\">\
  <style>\
   body { background-color: #585858; font-size: 36px; font-family: Arial, Helvetica, Sans-Serif; color: #F2F2F2; margin-left: 30px; }\
   h1 { color: #2ECCFA; margin-top: 30px; margin-bottom: 0px; }\
   h2 { font-size: 26px; margin-top: 0px; margin-bottom: 50px; }\
  </style>\
  </head>\
    <body>\
    <h1>LED hodiny</h1>\
    <a><br /></a>\
    <h2>Tato stránka nebyla nalezena !</h2>\
    <a href =\"/\"><button class=\"button\" style=\"margin-left: 10px;height: 48px; width: 180px;font-size: 16px;\">zpět na domovskou stránku</button></a>\
  </body>\
    </html>"); 
SendHTMLString(HTMLString); // Send HTMLString
CheckInHumidity(); // Indoor Humidity measurement
HTMLString = F("");}

/********************************************************************************************************************************************************/

void ChangeDisplayAutoOnOff() {
String HTMLString;
bool MDTime;
if (!await) {
if (server.method() == HTTP_POST) {
    // Einstellungen speichern
    DisplayOnTime = server.arg("DOnT"); // Display On-Time
    DisplayOffTime = server.arg("DOffT"); // Display Off-Time
    DisplayOnTime.trim();
    DisplayOffTime.trim();

    // Check the plausibility of the information for Matrix Display Automatic On/Off
    if (DisplayOnTime != "") {
    MDTime = false;
    if (DisplayOnTime.length() != 5) {
    if (DisplayOnTime.length() == 4) {
    if (DisplayOnTime.indexOf(':') == 1) {
    DisplayOnTime = "0"+DisplayOnTime;
    } else {DisplayOnTime = F("!");}
    } else {DisplayOnTime = F("!");}} else {
    if (strstr(DisplayOnTime.c_str(), ":") == NULL) {DisplayOnTime = F("!");}}
    if (DisplayOnTime != "!") {
    int DP = DisplayOnTime.indexOf(':'); 
    String CheckMDHourOn = DisplayOnTime.substring(0,DP); 
    String CheckMDMinOn =  DisplayOnTime.substring(DP+1,6);
    CheckMDMinOn.trim();
    int CheckMDHourOnInt, CheckMDMinOnInt;
    if (IsNumeric(CheckMDHourOn)) {CheckMDHourOnInt = CheckMDHourOn.toInt();} else {DisplayOnTime = F("!");}
    if (IsNumeric(CheckMDMinOn))  {CheckMDMinOnInt = CheckMDMinOn.toInt();} else {DisplayOnTime = F("!");}
    if (DisplayOnTime != "" && DisplayOnTime != "!" ) {
    for (int i=0; i <= 23; i++){
    if (i ==  CheckMDHourOnInt) {MDTime = true; break;}} 
    if (!MDTime) {DisplayOnTime = F("!");} else {   
    MDTime = false;    
    for (int i=0; i <= 59; i++){
    if (i ==  CheckMDMinOnInt) {MDTime = true; break;}} 
    if (!MDTime) {DisplayOnTime = F("!");}}}}}

    if (DisplayOffTime != "") {
    MDTime = false;
    if (DisplayOffTime.length() != 5) {
    if (DisplayOffTime.length() == 4) {
    if (DisplayOffTime.indexOf(':') == 1) {
    DisplayOffTime = "0"+DisplayOffTime;
    } else {DisplayOffTime = F("!");}
    } else {DisplayOffTime = F("!");}} else {
    if (strstr(DisplayOffTime.c_str(), ":") == NULL) {DisplayOffTime = F("!");}}
    if (DisplayOffTime != "!") {
    int DP = DisplayOffTime.indexOf(':'); 
    String CheckMDHourOff = DisplayOffTime.substring(0,DP); 
    String CheckMDMinOff =  DisplayOffTime.substring(DP+1,6);
    CheckMDMinOff.trim();
    int CheckMDHourOffInt, CheckMDMinOffInt;
    if (IsNumeric(CheckMDHourOff)) {CheckMDHourOffInt = CheckMDHourOff.toInt();} else {DisplayOffTime = F("!");}
    if (IsNumeric(CheckMDMinOff))  {CheckMDMinOffInt = CheckMDMinOff.toInt();} else {DisplayOffTime = F("!");}
    if (DisplayOffTime != "" && DisplayOffTime != "!") {
    for (int i=0; i <= 23; i++){
    if (i== CheckMDHourOffInt) {MDTime = true; break;}} 
    if (!MDTime) {DisplayOffTime = F("!");} else {   
    MDTime = false;    
    for (int i=0; i <= 59; i++){
    if (i ==  CheckMDMinOffInt) {MDTime = true; break;}} 
    if (!MDTime) {DisplayOffTime = F("!");}}}}}

    FDOnTime =  DisplayOnTime; // for Display only
    FDOffTime = DisplayOffTime; // for Display only

    // If Input Error
    if (DisplayOnTime == "!" || DisplayOffTime == "!" || DisplayOnTime == DisplayOffTime) {
    if (DisplayOnTime == "!") {DisplayOnTime = F("");} 
    if (DisplayOffTime == "!") {DisplayOffTime = F("");}  
    HTMLString = F("<!doctype html><html lang='en-GB'>");
    HTMLString += F("<head><meta charset='utf-8'>");
    HTMLString += F("<meta name='viewport' content='width=device-width, initial-scale=1'>");
    HTMLString += F("<title>LED hodiny</title>");
    HTMLString += F("<style>");
    HTMLString += F("*,::after,::before{box-sizing:border-box;}body{margin:0;font-family:");
    HTMLString += F("'Segoe UI',Roboto,'Helvetica Neue',Arial,'Noto Sans','Liberation Sans';font-size:1rem;");
    HTMLString += F("font-weight:400;line-height:1.5;color:#212529;background-color:#585858;}.form-control{display:");
    HTMLString += F("block;width:100%;height:calc(1.5em + .75rem + 2px);border:1px solid #ced4da;}button{border:1px solid");
    HTMLString += F("transparent;color:#fff;background-color:#007bff;border-color:#007bff;padding:.5rem 1rem;font-size:1.25rem;");
    HTMLString += F("line-height:1.5;border-radius:.3rem;width:100%}.form-signin{width:100%;max-width:420px;padding:15px;margin:auto;}h1,p{text-align: center}");
    HTMLString += F("h1 { font-size: 42px; color: #2ECCFA; margin-top: 50px; margin-bottom: 0px; }");
    HTMLString += F("h5 { font-size: 16px; color: #f5f5f5; text-align:center; margin-top: 0px; margin-bottom: 0px;}"); 
    HTMLString += F("h6 { font-size: 14px; color: #f5f5f5; text-align:center; margin-top: 0px; margin-bottom: 10px;}"); 
    HTMLString += F("</style>");
    HTMLString += F("</head>");
    HTMLString += F("<body><main class='form-signin'>");
    HTMLString += F("<h1>LED hodiny</h1>");
    HTMLString += F("<h5>(Automatické zapínání LED displeje ZAP/VYP)</h5>");
    HTMLString += F("<br/>");
    HTMLString += F("<h6>Neplatný záznam(y) – prosím opravte!</h6>");
    HTMLString += F("<br/>");
    HTMLString += F("<a href =\"/cdof\"><button>zpět na domovskou stránku</button></a>");
    HTMLString += F("</main>");
    HTMLString += F("</body>");
    HTMLString += F("</html>");
    SendHTMLString(HTMLString); // Send HTMLString
    } else {
    if (littleFSInit){
    HTMLString = F("<!doctype html><html lang='en-GB'>");
    HTMLString += F("<head><meta charset='utf-8'>");
    HTMLString += F("<meta name='viewport' content='width=device-width, initial-scale=1'>");
    HTMLString += F("<title>LED hodiny</title>");
    HTMLString += F("<style>");
    HTMLString += F("*,::after,::before{box-sizing:border-box;}body{margin:0;font-family:");
    HTMLString += F("'Segoe UI',Roboto,'Helvetica Neue',Arial,'Noto Sans','Liberation Sans';font-size:1rem;");
    HTMLString += F("font-weight:400;line-height:1.5;color:#212529;background-color:#585858;}.form-control{display:");
    HTMLString += F("block;width:100%;height:calc(1.5em + .75rem + 2px);border:1px solid #ced4da;}button{border:1px solid");
    HTMLString += F("transparent;color:#fff;background-color:#007bff;border-color:#007bff;padding:.5rem 1rem;font-size:1.25rem;");
    HTMLString += F("line-height:1.5;border-radius:.3rem;width:100%}.form-signin{width:100%;max-width:420px;padding:15px;margin:auto;}h1,p{text-align: center}");
    HTMLString += F("h1 { font-size: 42px; color: #2ECCFA; margin-top: 50px; margin-bottom: 0px; }");
    HTMLString += F("h5 { font-size: 16px; color: #f5f5f5; text-align:center; margin-top: 0px; margin-bottom: 0px;}"); 
    HTMLString += F("h6 { font-size: 14px; color: #f5f5f5; text-align:center; margin-top: 0px; margin-bottom: 10px;}"); 
    HTMLString += F("</style>");
    HTMLString += F("</head>");
    HTMLString += F("<body><main class='form-signin'>");
    HTMLString += F("<h1>LED hodiny</h1>");
    HTMLString += F("<h5>(LED Matrix Display automatically ON/OFF)</h5>");
    HTMLString += F("<br/>");
    HTMLString += F("<h6>Nastavení byla uložena<br /><br />Po návratu na domovskou stránku se Hodiny restartují</h6>");
    HTMLString += F("<br/>");
    HTMLString += F("<a href =\"/\"><button>zpět na domovskou stránku</button></a>");
    HTMLString += F("</main>");
    HTMLString += F("</body>");
    HTMLString += F("</html>");   
    SendHTMLString(HTMLString); // Send HTMLString
    // *** Save entries in the file system ***
    // Matrix Display ON time
    if (DisplayOnTime != ""){
    SetupSave("display-on-time.txt", DisplayOnTime);} else {
    if (LittleFS.exists("/display-on-time.txt")){LittleFS.remove("/display-on-time.txt");}}
    // Matrix Display OFF time
    if (DisplayOffTime != ""){
    SetupSave("display-off-time.txt", DisplayOffTime);} else {
    if (LittleFS.exists("/display-off-time.txt")){LittleFS.remove("/display-off-time.txt");}}
    SetupSave("display-change-time.txt", "True"); // Display On/Off Daten wurden geändert
    MyWaitLoop(500); // 0,5 sek. wait 
    if (SerialMonitor) {Serial.println(F("Zobrazeni automaticky ON/OFF Data ulozena... "));} 
    // Trigger reboot when back to homepage
    RebootNow = true;
    }
     else
     { // Access data was not saved
     if (SerialMonitor) {Serial.println(F("Pristupova data a nastaveni nebyly ulozeny !"));}
    HTMLString =  F("<!doctype html><html lang='en-GB'>");
    HTMLString += F("<head><meta charset='utf-8'>");
    HTMLString += F("<meta name='viewport' content='width=device-width, initial-scale=1'>");
    HTMLString += F("<title>LED hodiny</title>");
    HTMLString += F("<style>");
    HTMLString += F("*,::after,::before{box-sizing:border-box;}body{margin:0;font-family:");
    HTMLString += F("'Segoe UI',Roboto,'Helvetica Neue',Arial,'Noto Sans','Liberation Sans';font-size:1rem;");
    HTMLString += F("font-weight:400;line-height:1.5;color:#212529;background-color:#585858;}.form-control{display:");
    HTMLString += F("block;width:100%;height:calc(1.5em + .75rem + 2px);border:1px solid #ced4da;}button{border:1px solid");
    HTMLString += F("transparent;color:#fff;background-color:#007bff;border-color:#007bff;padding:.5rem 1rem;font-size:1.25rem;");
    HTMLString += F("line-height:1.5;border-radius:.3rem;width:100%}.form-signin{width:100%;max-width:420px;padding:15px;margin:auto;}h1,p{text-align: center}"); 
    HTMLString += F("h1 { font-size: 42px; color: #2ECCFA; margin-top: 50px; margin-bottom: 0px; }");   
    HTMLString += F("h5 { font-size: 16px; color: #f5f5f5; text-align:center; margin-top: 0px; margin-bottom: 0px;}"); 
    HTMLString += F("h6 { font-size: 14px; color: #f5f5f5; text-align:center; margin-top: 0px; margin-bottom: 10px;}"); 
    HTMLString += F("</style>");
    HTMLString += F("</head>");
    HTMLString += F("<body><main class='form-signin'>");
    HTMLString += F("<h1LED hodiny</h1>");
    HTMLString += F("<h5>(Automatické zapínání LED displeje)</h5>");
    HTMLString += F("<br/>");
    HTMLString += F("<h6>Chyba při ukládání přístupových dat a nastavení<br />Hodiny se restartují</h6>");
    HTMLString += F("<br/>");
    HTMLString += F("<a href =\"/\"><button>zpět na domovskou stránku</button></a>");
    HTMLString += F("</main>");
    HTMLString += F("</body>");
    HTMLString += F("</html>"); 
    SendHTMLString(HTMLString); // Send HTMLString
    // Restart trigger
    if (!Display) {sendCmdAll(CMD_SHUTDOWN, 1);} // Switch on Display when off
    printStringWithShift("        +++       Hodiny se restartují      +++           ",ScrollTextTime);
    digitalWrite(HWLEDPin, LOW); // LED off
    ESP.restart();  
    } 
    SendHTMLString(HTMLString); // Send HTMLString 
    CheckInHumidity(); // Indoor Humidity measurement
    } // Ende Inputerror
  } else {  
    // Settings
    HTMLString =  F("<!doctype html><html lang='en-GB'>");
    HTMLString += F("<head><meta charset='utf-8'>");
    HTMLString += F("<meta name='viewport' content='width=device-width, initial-scale=1'>");
    HTMLString += F("<title>LED hodiny</title>");
    HTMLString += F("<style>");
    HTMLString += F("*,::after,::before{box-sizing:border-box;}body{margin:0;font-family:");
    HTMLString += F("'Segoe UI',Roboto,'Helvetica Neue',Arial,'Noto Sans','Liberation Sans';font-size:1rem;");
    HTMLString += F("font-weight:400;line-height:1.5;color:#212529;background-color:#585858;}.form-control{display:");
    HTMLString += F("block;width:100%;height:calc(1.5em + .75rem + 2px);border:1px solid #ced4da;}button{border:1px solid");
    HTMLString += F("transparent;color:#fff;background-color:#007bff;border-color:#007bff;padding:.5rem 1rem;font-size:1.25rem;");
    HTMLString += F("line-height:1.5;border-radius:.3rem;width:100%}.form-signin{width:100%;max-width:420px;padding:15px;margin:auto;}h1,p{text-align: center}");
    HTMLString += F("label {color: white;}");
    HTMLString += F("h1 { font-size: 42px; color: #2ECCFA; margin-top: 50px; margin-bottom: 0px; }");
    HTMLString += F("h5 { font-size: 16px; color: #f5f5f5; text-align:center; margin-top: 0px; margin-bottom: 0px;}"); 
    HTMLString += F("h6 { font-size: 12px; color: #ffcc00; text-align:center; margin-top: 15px; margin-bottom: 15px;}");
    HTMLString += F("</style>");
    HTMLString += F("</head>");
    HTMLString += F("<body><main class='form-signin'>");
    HTMLString += F("<form action='/cdof' method='post'>");
    HTMLString += F("<h1>LED hodiny</h1>");
    HTMLString += F("<h5>(Automatické zapínání LED displeje)</h5>");
    // ******************************************* Parameter ************************************************************************************************************************************
    HTMLString += "<div class='form-floating'><br/><label>Displej zapnut v čase (Např: 07:00)   -Volitelné*-</label><input type='text' maxlength='5' class='form-control' name='DOnT' id='DOnT' value='"+FDOnTime+"'></div>";
    HTMLString += "<div class='form-floating'><br/><label>Displej vypnut v čase (Např: 23:30)   -Volitelné*-</label><input type='text' maxlength='5' class='form-control' name='DOffT' id='DOffT' value='"+FDOffTime+"'></div>";
    // ******************************************* Parameter ************************************************************************************************************************************
    HTMLString += F("<h6>*) - Prázdný formulář deaktivuje funkci</h6>");
    HTMLString += F("<button type='submit'>Uložit</button>");
    HTMLString += F("<br/><br/>");
    HTMLString += F("</form>");
    HTMLString += F("<a href =\"/cdofc\"><button>Zrušit</button></a>");
    HTMLString += F("<br/><br/>");
    HTMLString += F("</main>");
    HTMLString += F("</body>");
    HTMLString += F("</html>");  
    SendHTMLString(HTMLString);}} else {PleaseWait();}}  // Send HTMLString or wait

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void DisplayCheck() {
if (!await) {
await = true; 
char  MDC   = '9' + 2; // Full Display ON
String MDCShow = "      "+String(MDC)+String(MDC)+String(MDC)+String(MDC);
HTMLAnswer("DisplayCheck");
printStringWithShift3(MDCShow.c_str(),ScrollTextTime);
HandleOTAandWebServer();  // OTA and Web Server query
digitalWrite(HWLEDPin, HIGH); // Check LED
MyWaitLoop(8000); // Short wait (8 seconds)
HandleOTAandWebServer();  // OTA and Web Server query
printStringWithShift3("      ",ScrollTextTime);
HandleOTAandWebServer();  // OTA and Web Server query
InHumidityStatus = CheckInHumidity(); // Indoor Humidity measurement
if (InHumidityStatus != "FAIL") {
if (InHumidityStatus != "MIN" && InHumidityStatus != "MAX") {
digitalWrite(HWLEDPin, LOW);}} else {digitalWrite(HWLEDPin, LOW);}
ClockScrollIn(); // Scroll the time in the Display 
await = false; 
} else {HTMLAnswer("NoDisplayCheck");}}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void ChangeDisplayAutoOnOffCancel() {
String HTMLString = F("");
  // Display switch-on time as a string
  if (littleFSInit) {
  if (LittleFS.exists("/display-on-time.txt")){
  DisplayOnTime = SetupLoad("display-on-time.txt");
  DisplayOnTime.trim(); // Remove spaces at the front and back
  } else {DisplayOnTime = F("");}} else
         {DisplayOnTime = F("");}
  // Display Ausschaltzeit als String
  if (littleFSInit) {
  if (LittleFS.exists("/display-off-time.txt")){
  DisplayOffTime = SetupLoad("display-off-time.txt");
  DisplayOffTime.trim(); // Remove spaces at the front and back
  } else {DisplayOffTime = F("");}} else
         {DisplayOffTime = F("");}

  // Check the plausibility of the information for Matrix Display Automatic On/Off
  CheckLEDMatrixDisplayOnOff();

    HTMLString = F("<!doctype html><html lang='en-GB'>");
    HTMLString += F("<head><meta charset='utf-8'>");
    HTMLString += F("<meta name='viewport' content='width=device-width, initial-scale=1'>");
    HTMLString += F("<title>LED hodiny</title>");
    HTMLString += F("<style>");
    HTMLString += F("*,::after,::before{box-sizing:border-box;}body{margin:0;font-family:");
    HTMLString += F("'Segoe UI',Roboto,'Helvetica Neue',Arial,'Noto Sans','Liberation Sans';font-size:1rem;");
    HTMLString += F("font-weight:400;line-height:1.5;color:#212529;background-color:#585858;}.form-control{display:");
    HTMLString += F("block;width:100%;height:calc(1.5em + .75rem + 2px);border:1px solid #ced4da;}button{border:1px solid");
    HTMLString += F("transparent;color:#fff;background-color:#007bff;border-color:#007bff;padding:.5rem 1rem;font-size:1.25rem;");
    HTMLString += F("line-height:1.5;border-radius:.3rem;width:100%}.form-signin{width:100%;max-width:420px;padding:15px;margin:auto;}h1,p{text-align: center}");
    HTMLString += F("h1 { font-size: 42px; color: #2ECCFA; margin-top: 50px; margin-bottom: 0px; }");
    HTMLString += F("h5 { font-size: 16px; color: #f5f5f5; text-align:center; margin-top: 0px; margin-bottom: 0px;}"); 
    HTMLString += F("h6 { font-size: 14px; color: #f5f5f5; text-align:center; margin-top: 0px; margin-bottom: 10px;}"); 
    HTMLString += F("</style>");
    HTMLString += F("</head>");
    HTMLString += F("<body><main class='form-signin'>");
    HTMLString += F("<h1>LED hodiny</h1>");
    HTMLString += F("<h5>(Automatické zapínání LED displeje)</h5>");
    HTMLString += F("<br/>");
    if (littleFSInit) {
    HTMLString += F("<h6>Zrušeno! - Staré nastavení bylo znovu načteno ...</h6>");} else {
    HTMLString += F("<h6>Zrušeno! - Nelze načíst staré nastavení !!! ...</h6>");}
    HTMLString += F("<br/>");
    HTMLString += F("<a href =\"/\"><button>zpět na domovskou stránku</button></a>");
    HTMLString += F("</main>");
    HTMLString += F("</body>");
    HTMLString += F("</html>");
    SendHTMLString(HTMLString); // Send HTMLString
    CheckInHumidity(); // Indoor Humidity measurement
 HTMLString = F("");}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void StartSoundOn() {
if (StartSound != "On") { 
if (!await) {  
await = true;
StartBuzzerBeep();    
if (littleFSInit) {
StartSound = F("On");   
SetupSave("status_startsound.txt", StartSound);} else {StartSound = F("Off");}
HTMLAnswer("StartSoundOnM");
if (SerialMonitor) {Serial.println(F("Buzzer Startsound je zapnuty"));}
await = false;} else {PleaseWait();}} else {HTMLAnswer("StartSoundOnMIs");}}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void StartSoundOff() {
if (StartSound != "Off") {  
StartSound = F("Off");     
if (littleFSInit) {  
SetupSave("status_startsound.txt", StartSound);} 
HTMLAnswer("StartSoundOffM");
if (SerialMonitor) {Serial.println(F("Buzzer Startsound je vypnuty"));}
} else {HTMLAnswer("StartSoundOffMIs");}}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void HourSoundOn() {
if (HourSound != "On") { 
if (!await) {  
await = true;
HourBuzzerBeep();   
if (littleFSInit) {
HourSound = F("On");   
SetupSave("status_hoursound.txt", HourSound);} else {HourSound = F("Off");}
HTMLAnswer("HourSoundOnM");
await = false;
if (SerialMonitor) {Serial.println(F("Buzzer Startsound je zapnutý"));}} else {PleaseWait();}
} else {HTMLAnswer("HourSoundOnMIs");}}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void HourSoundOff() {
if (HourSound != "Off") {
HourSound = F("Off");  
if (littleFSInit) {
SetupSave("status_hoursound.txt", HourSound);} 
HTMLAnswer("HourSoundOffM");
if (SerialMonitor) {Serial.println(F("Buzzer Startsound je vypnutý"));}
} else {HTMLAnswer("HourSoundOffMIs");}}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void PleaseWait() {
// Please wait, show page
String RefreshTime = F("5"); // Refresh the website after X seconds
String HTMLString;
HTMLString = F("<!DOCTYPE html><html lang='en-GB'>");
HTMLString += F("<head>");
HTMLString += F("<title>LED hodiny</title>");
HTMLString += F("<meta http-equiv=\"content-type\" content=\"text/html; charset=utf-8\">");
// HTMLString += F("<meta http-equiv=\"refresh\" content=\""+RefreshTime+"\">");
HTMLString += F("<style>");
HTMLString += F("body { background-color: #585858; font-size: 32px; font-family: Arial, Helvetica, Sans-Serif; color: #F2F2F2; text-align: center;}");
HTMLString += F("h1 { font-size: 64px; color: #2ECCFA; margin-top: 30px; margin-bottom: 0px; text-align: center;}");
HTMLString += F("h2 { font-size: 48px; margin-top: 0px; margin-bottom: 10px; text-align: center;}");
HTMLString += F("h3 { font-size: 36px; margin-top: 0px; margin-bottom: 10px; text-align: center;}");
HTMLString += F("</style>");
HTMLString += F("</head>");
HTMLString += F("<body>");
HTMLString += F("<h1>LED hodiny</h1>");
HTMLString += F("<a><br /></a>");
HTMLString += F("<h2>Čekejte prosím ...</h2>");
if (Display) {
HTMLString += F("<h3>(Dokud se čas znovu nezobrazí LED displeji)</h3>");}
HTMLString += F("<a><br /></a>");
HTMLString += F("<a href =\"/\"><button class=\"button\" style=\"margin-left: 10px;height: 48px; width: 180px;font-size: 16px;\">zpět na domovskou stránku</button></a>");
HTMLString += F("</body>");
HTMLString += F("</html>");
server.send(200, "text/html", HTMLString); 
CheckInHumidity(); // Indoor Humidity measurement 
Serial.println(F("Čekejte prosím ..."));}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

String HTTPCodeText(int httpcode) {
String TempHTTPCodeText = F("k.A.");  
if (httpcode == -1) {TempHTTPCodeText = F("ERROR_CONNECTION_REFUSED");}  
if (httpcode == -2) {TempHTTPCodeText = F("ERROR_SEND_HEADER_FAILED");} 
if (httpcode == -3) {TempHTTPCodeText = F("ERROR_SEND_PAYLOAD_FAILED");} 
if (httpcode == -4) {TempHTTPCodeText = F("ERROR_NOT_CONNECTED");} 
if (httpcode == -5) {TempHTTPCodeText = F("ERROR_CONNECTION_LOST");} 
if (httpcode == -6) {TempHTTPCodeText = F("ERROR_NO_STREAM");} 
if (httpcode == -7) {TempHTTPCodeText = F("ERROR_NO_HTTP_SERVER");} 
if (httpcode == -8) {TempHTTPCodeText = F("ERROR_TOO_LESS_RAM");} 
if (httpcode == -9) {TempHTTPCodeText = F("ERROR_ENCODING");} 
if (httpcode == -10) {TempHTTPCodeText = F("ERROR_STREAM_WRITE");} 
if (httpcode == -11) {TempHTTPCodeText = F("ERROR_READ_TIMEOUT");}

if (httpcode == 100) {TempHTTPCodeText = F("Continue");}
if (httpcode == 101) {TempHTTPCodeText = F("Switching Protocols");}
if (httpcode == 102) {TempHTTPCodeText = F("Processing (WebDAV)");}
if (httpcode == 200) {TempHTTPCodeText = F("OK");}
if (httpcode == 201) {TempHTTPCodeText = F("Created");}
if (httpcode == 202) {TempHTTPCodeText = F("Accepted");}
if (httpcode == 203) {TempHTTPCodeText = F("Non-Authoritative Information");}
if (httpcode == 204) {TempHTTPCodeText = F("No Content");}
if (httpcode == 205) {TempHTTPCodeText = F("Reset Content");}
if (httpcode == 206) {TempHTTPCodeText = F("Partial Content");}
if (httpcode == 207) {TempHTTPCodeText = F("Multi-Status (WebDAV)");}
if (httpcode == 208) {TempHTTPCodeText = F("Already Reported (WebDAV)");}
if (httpcode == 226) {TempHTTPCodeText = F("IM Used");}

if (httpcode == 300) {TempHTTPCodeText = F("Multiple Choices");}
if (httpcode == 301) {TempHTTPCodeText = F("Moved Permanently");}
if (httpcode == 302) {TempHTTPCodeText = F("Found");}
if (httpcode == 303) {TempHTTPCodeText = F("See Other");}
if (httpcode == 304) {TempHTTPCodeText = F("Not Modified");}
if (httpcode == 305) {TempHTTPCodeText = F("Use Proxy");}
if (httpcode == 306) {TempHTTPCodeText = F("(Unused)");}
if (httpcode == 307) {TempHTTPCodeText = F("Temporary Redirect");}
if (httpcode == 308) {TempHTTPCodeText = F("Permanent Redirect (experimental)");}

if (httpcode == 400) {TempHTTPCodeText = F("Bad Request");}
if (httpcode == 401) {TempHTTPCodeText = F("Unauthorized");}
if (httpcode == 402) {TempHTTPCodeText = F("Payment Required");}
if (httpcode == 403) {TempHTTPCodeText = F("Forbidden");}
if (httpcode == 404) {TempHTTPCodeText = F("Not Found");}
if (httpcode == 405) {TempHTTPCodeText = F("Method Not Allowed");}
if (httpcode == 406) {TempHTTPCodeText = F("Not Acceptable");}
if (httpcode == 407) {TempHTTPCodeText = F("Proxy Authentication Required");}
if (httpcode == 408) {TempHTTPCodeText = F("Request Timeout");}
if (httpcode == 409) {TempHTTPCodeText = F("Conflict");}
if (httpcode == 410) {TempHTTPCodeText = F("Gone");}
if (httpcode == 411) {TempHTTPCodeText = F("Length Required");}
if (httpcode == 412) {TempHTTPCodeText = F("Precondition Failed");}
if (httpcode == 413) {TempHTTPCodeText = F("Request Entity Too Large");}
if (httpcode == 414) {TempHTTPCodeText = F("Request-URI Too Long");}
if (httpcode == 415) {TempHTTPCodeText = F("Unsupported Media Type");}
if (httpcode == 416) {TempHTTPCodeText = F("Requested Range Not Satisfiable");}
if (httpcode == 417) {TempHTTPCodeText = F("Expectation Failed");}
if (httpcode == 418) {TempHTTPCodeText = F("I'm a teapot (RFC 2324)");}
if (httpcode == 420) {TempHTTPCodeText = F("Enhance Your Calm (Twitter)");}
if (httpcode == 422) {TempHTTPCodeText = F("Unprocessable Entity (WebDAV)");}
if (httpcode == 423) {TempHTTPCodeText = F("Locked (WebDAV)");}
if (httpcode == 424) {TempHTTPCodeText = F("Failed Dependency (WebDAV)");}
if (httpcode == 425) {TempHTTPCodeText = F("Reserved for WebDAV");}
if (httpcode == 426) {TempHTTPCodeText = F("Upgrade Required");}
if (httpcode == 428) {TempHTTPCodeText = F("Precondition Required");}
if (httpcode == 429) {TempHTTPCodeText = F("Too Many Requests");}
if (httpcode == 431) {TempHTTPCodeText = F("Request Header Fields Too Large");}
if (httpcode == 444) {TempHTTPCodeText = F("No Response (Nginx)");}
if (httpcode == 449) {TempHTTPCodeText = F("Retry With (Microsoft)");}
if (httpcode == 450) {TempHTTPCodeText = F("Blocked by Windows Parental Controls (Microsoft)");}
if (httpcode == 451) {TempHTTPCodeText = F("Unavailable For Legal Reasons");}
if (httpcode == 499) {TempHTTPCodeText = F("Client Closed Request (Nginx)");}

if (httpcode == 500) {TempHTTPCodeText = F("Internal Server Error");}
if (httpcode == 501) {TempHTTPCodeText = F("Not Implemented");}
if (httpcode == 502) {TempHTTPCodeText = F("Bad Gateway");}
if (httpcode == 503) {TempHTTPCodeText = F("Service Unavailable");}
if (httpcode == 504) {TempHTTPCodeText = F("Gateway Timeout");}
if (httpcode == 505) {TempHTTPCodeText = F("HTTP Version Not Supported");}
if (httpcode == 506) {TempHTTPCodeText = F("Variant Also Negotiates (Experimental)");}
if (httpcode == 507) {TempHTTPCodeText = F("Insufficient Storage (WebDAV)");}
if (httpcode == 508) {TempHTTPCodeText = F("Loop Detected (WebDAV)");}
if (httpcode == 509) {TempHTTPCodeText = F("Bandwidth Limit Exceeded (Apache)");}
if (httpcode == 510) {TempHTTPCodeText = F("Not Extended");}
if (httpcode == 511) {TempHTTPCodeText = F("Network Authentication Required");}
if (httpcode == 598) {TempHTTPCodeText = F("Network read timeout error");}
if (httpcode == 599) {TempHTTPCodeText = F("Network connect timeout error");}
return String(httpcode) + " - " + TempHTTPCodeText;}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
