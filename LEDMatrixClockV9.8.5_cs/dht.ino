void DHTHTML() { 
  String HTMLString = F("");
  String RefreshTime = F("30"); // Refresh Website after X seconds
  if (InTempOffset == "999") {InTempValue = "0";} else {InTempValue = InTempMessure();} // Retrieve temperature value
  if (SerialMonitor) {Serial.println("Vnitrni teplota: "+InTempValue+" °C");}
  MyWaitLoop(500); // short wait
  if (InTempOffset == "999") {InHumValue = "0";} else {InHumValue = InHumMessure();} // Retrieve Air Humidity Value
  if (SerialMonitor) {Serial.println("Vnitrni vlhkost: "+InHumValue+" %");}
  String TempValueColor, HumValueColor, RefreshButton;
  if (InTempValue != "-" && InHumValue != "-") {
  IntInTempValue = InTempValue.toInt(); 
  IntInHumValue = InHumValue.toInt(); 
  RefreshButton = "href =\"tempvalue\"><button class=\"button\" style=\"margin-left: 100px;height: 48px; width: 180px;color: blue;font-size: 16px;\">Obnovit</button>";} else {
  RefreshButton = "href =\"/\"><button class=\"button\" style=\"margin-left: 100px;height: 48px; width: 180px;color: blue;font-size: 16px;\">Obnovit</button>";}
  // Evaluation Temperature
  if (IntInTempValue < 10) {
  TempValueColor = "<tr><td style=\"height: 10px;\">Aktuální vnitřní teplota:&nbsp;&nbsp;</td><td id='Bvalue'><span>"+InTempValue+"</span>°C</td></tr>";  
  } else {
  if (IntInTempValue >= 10 && IntInTempValue <= 28) {TempValueColor = "<tr><td style=\"height: 10px;\">Aktuální vnitřní teplota:&nbsp&nbsp</td><td id='Gvalue'><span>"+InTempValue+"</span>°C</td></tr>";} else {  
  TempValueColor = "<tr><td style=\"height: 10px;\">Aktuální vnitřní teplota:&nbsp;&nbsp;</td><td id='Rvalue'><span>"+InTempValue+"</span>°C</td></tr>";}
  }
  // Evaluation of Air Humidity
  if (IntInHumValue <= MinComfortHum || IntInHumValue >= MaxComfortHum) {
  digitalWrite(HWLEDPin, HIGH); // LED on  
  HumValueColor = "style=\"color: #FC1E17; font-size: 18px; margin-left: 430px;\">při vlhkosti vzduchu:&nbsp;"+InHumValue+"";} else { 
  digitalWrite(HWLEDPin, LOW); // LED off   
  HumValueColor = "style=\"color: lime; font-size: 18px; margin-left: 430px;\">při vlhkosti vzduchu:&nbsp;"+InHumValue+"";}
  
  HTMLString = F("<!DOCTYPE html>");
  HTMLString += F("<html lang='en-GB'>");
  HTMLString += F("<head>");
  HTMLString += F("<title>LLED hodiny - Zobrazení teploty</title>");
  HTMLString += F("<meta http-equiv='content-type' content='text/html'; charset='utf-8'>");
  HTMLString += "<meta http-equiv=\"refresh\" content=\""+RefreshTime+"\">";
  HTMLString += F("<style>");
  HTMLString += F("body { background-color: #585858; font-size: 32px; font-family: Arial, Helvetica, Sans-Serif; color: #F2F2F2; margin-left: 30px; }");
  HTMLString += F("h1 { color: #2ECCFA; margin-top: 50px; margin-bottom: 0px; }");
  HTMLString += F("h2 { font-size: 28px; margin-top: 0px; margin-bottom: 10px; }");
  HTMLString += F("h3 { font-size: 32px; margin-top: 0px; margin-bottom: 10px; }"); 
  HTMLString += F("h4 { font-size: 28px; margin-top: 0px; margin-bottom: 10px; }"); 
  HTMLString += F("#Rvalue { width: 200px; height: 80px; border: 5px solid #F2F2F2; text-align:center; padding: 1px; color: #FC1E17; background-color: #000000; font-size: 60px; }"); 
  HTMLString += F("#Gvalue { width: 200px; height: 80px; border: 5px solid #F2F2F2; text-align:center; padding: 1px; color: lime; background-color: #000000; font-size: 60px; }"); 
  HTMLString += F("#Bvalue { width: 200px; height: 80px; border: 5px solid #F2F2F2; text-align:center; padding: 1px; color: #2ECCFA; background-color: #000000; font-size: 60px; }"); 
  HTMLString += F("</style>"); 
  HTMLString += F("</head>"); 
  HTMLString += F("<body>");
  HTMLString += F("<h1>LED hodiny</h1>");
  HTMLString += F("<h3>Zobrazení teploty</h3>");
  HTMLString += F("<h2><br /></h2>");
  HTMLString += "<h4>Poslední měření: &nbsp"+LastInTempMessureDateTime+"</h4>";
  HTMLString += F("<h2><br /></h2>");
  HTMLString += "<table>"+TempValueColor+"</table>";
  HTMLString += "<a "+HumValueColor+"%</a>";
  HTMLString += F("<h2><br /></h2>");
  HTMLString += F("<h2><br /></h2>");
  HTMLString += F("<a href =\"/\"><button class=\"button\" style=\"margin-left: 10px;height: 48px; width: 180px;font-size: 16px;\">zpět na domovskou stránku</button></a>");
  HTMLString += "<a "+RefreshButton+"</a>";
  HTMLString += F("<a href =\"/dhtcalibrate\"><button class=\"button\" style=\"margin-left: 100px;height: 48px; width: 180px; color: red; font-size: 16px;\">Kalibrace senzoru</button></a>");
  HTMLString += F("</body>");
  HTMLString += F("</html>");
  SendHTMLString(HTMLString); // Send HTMLString 
  }

// =====================================================================================================================================

String InTempMessure() {
int IntITempValue = -1;  
  if (SerialMonitor) {Serial.println(F(""));
  Serial.println(F("Meri se vnitrni teplota ..."));}
  float TempWert = dht.getTemperature();
  String ITempValue = String(TempWert,0);
  ITempValue.replace("-0", "0");
  ITempValue.replace("+0", "0");
  ITempValue.replace("+", "");
  ITempValue.trim(); // Remove Spaces
  if (isnan(TempWert) || ITempValue == "" || ITempValue == "nan" || (!IsNumeric(ITempValue))) {ITempValue = F("-");} 
  if (ITempValue == "-") {
  if (SerialMonitor) {Serial.println(F("Ze senzoru nebyla prijata žadna platna hodnota !"));}
  LastInTempMessureDateTime = F("n/a / n/a");}
  else {
  IntITempValue = ITempValue.toInt();
  IntITempValue = IntITempValue + InTempOffsetInt; 
  ITempValue = String(IntITempValue);   
  if (SerialMonitor) {Serial.println("Vnitrni teplota: "+ITempValue+" °C");} // only Debugmodus
  LastInTempMessureDateTime = FormatedDateTimeEN(true);}
  return ITempValue;}

// ====================================================================================================================================

String InHumMessure() {
int IntIHumValue = -1;  
  if (SerialMonitor) {Serial.println(F(""));
  Serial.println(F("Meri se vnitrni vlhkost vzduchu ..."));}
  float LfWert = dht.getHumidity();
  String IHumValue = String(LfWert,0); 
  IHumValue.replace("-0", "0");
  IHumValue.replace("+0", "0");
  IHumValue.replace("+", "");
  IHumValue.trim(); // Remove Spaces
  if (isnan(LfWert) || IHumValue == "" || IHumValue == "nan" || (!IsNumeric(IHumValue))) {IHumValue = F("-");} 
  if (IHumValue == "-") {
  if (SerialMonitor) {Serial.println(F("Ze senzoru nebyla prijata zadna platna hodnota !"));}
  LastInTempMessureDateTime = F("n/a / n/a");}
  else {
  IntIHumValue = IHumValue.toInt();
  IntIHumValue = IntIHumValue + InHumOffsetInt; 
  IHumValue = String(IntIHumValue); 
  if (SerialMonitor) {Serial.println("Vlhkost vnitrniho vzduchu: "+IHumValue+" %");} // only Debugmodus
  LastInTempMessureDateTime = FormatedDateTimeEN(true);} 
  return IHumValue;}

// ====================================================================================================================================  

String CheckInHumidity() {
// Indoor Humidity - Message if too low or too high
String RLF = F("");
if (InHumValue != "!") {
if (InTempOffset == "999") {InHumValue = "0";} else {InHumValue = InHumMessure();} // Retrieve Air Humidity Value
MyWaitLoop(100); // short wait
  if (InHumValue != "-") {
  if (InTempOffset != "999") {    
  IntInHumValue = InHumValue.toInt();  
  if (IntInHumValue <= MinComfortHum) {
  RLF = F("MIN");  
    // Air Humidity too low       
  if (Display) {digitalWrite(HWLEDPin, HIGH);} else {digitalWrite(HWLEDPin, LOW);}  // LED switch On or Off
  InHumMessage = F("Pozor: Vlhkost vzduchu je prilis nizka !");}
  if (IntInHumValue >= MaxComfortHum) {
  RLF = F("MAX");  
  // Air Humidity too high     
  if (Display) {digitalWrite(HWLEDPin, HIGH);} else {digitalWrite(HWLEDPin, LOW);}  // LED switch On or Off 
  if (WeatherFunctions and Display){
  if (humidity >= MaxComfortHum || humidity == -1) {InHumMessage = F("Pozor: Vlhkost vzduchu je prilis vysoka !");} else 
  {InHumMessage = F("Pozor: Prilis vysoka vlhkost vzduchu! - Prosim, vyvetrejte");}
  } else {InHumMessage = F("Pozor: Vlhkost vzduchu je prilis vysoka !");}}
  if (IntInHumValue >= MinComfortHum && IntInHumValue <= MaxComfortHum) {
  RLF = F("NORMAL");  
  digitalWrite(HWLEDPin, LOW); // LED switch off
  InHumMessage = F("");}
  } else {RLF = F("NORMAL"); InHumMessage = F("DHT-Sensor deaktivován !"); digitalWrite(HWLEDPin, LOW);} // LED switch off
  } else {
  digitalWrite(HWLEDPin, LOW); // LED switch off
  InHumValue = F("!");
  RLF = F("FAIL");
  InHumMessage = F("");}} else {digitalWrite(HWLEDPin, LOW); RLF = F("FAIL");} // LED switch off and Fail
  return RLF;  
}

// ====================================================================================================================================

void DHTSensorCalibrate() {
String HTMLString;
bool MDTime;
if (!await) { 
// When saved Button was pressed 
if (server.method() == HTTP_POST) {
    // DHT Temperature Sensor Offset
    InTempOffset = server.arg("DHTTo");
    InTempOffset.replace("+", "");
    InTempOffset.trim();
    if (InTempOffset != "") {
    if (!IsNumeric(InTempOffset)) {InTempOffset = F("!");} else {
    InTempOffsetInt = InTempOffset.toInt();}
    } else {InTempOffset = F("0");}
    // DHT Humidity Sensor Offset
    InHumOffset = server.arg("DHTHo");
    InHumOffset.replace("+", "");
    InHumOffset.trim(); 
    if (InHumOffset != "") {
    if (!IsNumeric(InHumOffset)) {InHumOffset = F("!");} else {
    InHumOffsetInt = InHumOffset.toInt();} 
    } else {InHumOffset = F("0");}

    // If Input Error
    if (InTempOffset == "!" || InHumOffset == "!") {
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
    HTMLString += F("h5 { font-size: 18px; color: #f5f5f5; text-align:center; margin-top: 0px; margin-bottom: 0px;}"); 
    HTMLString += F("h6 { font-size: 14px; color: #f5f5f5; text-align:center; margin-top: 0px; margin-bottom: 10px;}"); 
    HTMLString += F("</style>");
    HTMLString += F("</head>");
    HTMLString += F("<body><main class='form-signin'>");
    HTMLString += F("<h1>LED hodiny</h1>");
    if (DHT11Sensor) {
    HTMLString += F("<h5>(Kalibrace senzoru DHT11)</h5>");} else{
    HTMLString += F("<h5>(Kalibrace senzoru DHT22)</h5>");}
    HTMLString += F("<br/>");
    HTMLString += F("<h6>Neplatné položky – prosím opravte!</h6>");
    HTMLString += F("<br/>");
    HTMLString += F("<a href =\"/dhtcalibrate\"><button>Zpět/button></a>");
    HTMLString += F("</main>");
    HTMLString += F("</body>");
    HTMLString += F("</html>");
    SendHTMLString(HTMLString); // Send HTMLString
    } else {
    if (littleFSInit){
        // *** Save entries in the File System ***
    InTempOffset.trim(); // DHT-Sensor Offset (Temperatur)
    InHumOffset.trim(); // DHT-Sensor Offset (Humidity)
    if (InTempOffset != ""){
    SetupSave("dht-intempoffset.txt", InTempOffset);} else {
    if (LittleFS.exists("/dht-intempoffset.txt")){LittleFS.remove("/dht-intempoffset.txt");}}
    if (InHumOffset != ""){
    SetupSave("dht-inhumoffset.txt", InHumOffset);} else {
    if (LittleFS.exists("/dht-inhumoffset.txt")){LittleFS.remove("/dht-inhumoffset.txt");}}
    MyWaitLoop(500); // 0,5 sek. wait
    if (SerialMonitor) {Serial.println(F("DHT-Sensor Offset Daten gespeichert... "));}
    // Website anzeigen  
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
    HTMLString += F("h5 { font-size: 18px; color: #f5f5f5; text-align:center; margin-top: 0px; margin-bottom: 0px;}"); 
    HTMLString += F("h6 { font-size: 14px; color: #f5f5f5; text-align:center; margin-top: 0px; margin-bottom: 10px;}"); 
    HTMLString += F("</style>");
    HTMLString += F("</head>");
    HTMLString += F("<body><main class='form-signin'>");
    HTMLString += F("<h1>LED hodiny</h1>");
    if (DHT11Sensor) {
    HTMLString += F("<h5>(Kalibrace senzoru DHT11)</h5>");} else{
    HTMLString += F("<h5>(Kalibrace senzoru DHT22)</h5>");}
    HTMLString += F("<br/>");
    HTMLString += F("<h6>Nastavení byla uložena</h6>");
    HTMLString += F("<br/>");
    HTMLString += F("<a href =\"/tempvalue\"><button>OK</button></a>");
    HTMLString += F("</main>");
    HTMLString += F("</body>");
    HTMLString += F("</html>");   
    SendHTMLString(HTMLString); // Send HTMLString
    CheckInHumidity();} // Indoor Humidity measurement 
    else { 
    // DHT Sensor Offset Settings were not saved
     if (SerialMonitor) {Serial.println(F("DHT Sensor Offset Settings were not saved !"));}
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
    HTMLString += F("h5 { font-size: 18px; color: #f5f5f5; text-align:center; margin-top: 0px; margin-bottom: 0px;}"); 
    HTMLString += F("h6 { font-size: 14px; color: #f5f5f5; text-align:center; margin-top: 0px; margin-bottom: 10px;}"); 
    HTMLString += F("</style>");
    HTMLString += F("</head>");
    HTMLString += F("<body><main class='form-signin'>");
    HTMLString += F("<h1>LED hodiny</h1>");
    if (DHT11Sensor) {
    HTMLString += F("<h5>(Kalibrace senzoru DHT11)</h5>");} else{
    HTMLString += F("<h5>(Kalibrace senzoru DHT22)</h5>");}
    HTMLString += F("<br/>");
    HTMLString += F("<h6>Při ukládání nastavení došlo k chybě</h6>");
    HTMLString += F("<br/>");
    HTMLString += F("<a href =\"/tempvalue\"><button>Zpět</button></a>");
    HTMLString += F("</main>");
    HTMLString += F("</body>");
    HTMLString += F("</html>"); 
    SendHTMLString(HTMLString); // Send HTMLString
    digitalWrite(HWLEDPin, LOW); // LED switch off
    }} // End Inputterror
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
    HTMLString += F("line-height:1.5;border-radius:.3rem;width:100%}.form-signin{width:100%;max-width:430px;padding:15px;margin:auto;}h1,p{text-align: center}");
    HTMLString += F("label {color: white;}");
    HTMLString += F("h1 { font-size: 42px; color: #2ECCFA; margin-top: 50px; margin-bottom: 0px; }");
    HTMLString += F("h5 { font-size: 18px; color: #f5f5f5; text-align:center; margin-top: 0px; margin-bottom: 0px;}"); 
    HTMLString += F("h6 { font-size: 12px; color: #ffcc00; text-align:center; margin-top: 15px; margin-bottom: 15px;}");
    HTMLString += F("</style>");
    HTMLString += F("</head>");
    HTMLString += F("<body><main class='form-signin'>");
    HTMLString += F("<form action='/dhtcalibrate' method='post'>");
    HTMLString += F("<h1>LED hodiny</h1>");
    if (DHT11Sensor) {
    HTMLString += F("<h5>(Kalibrace senzoru DHT11)</h5>");} else{
    HTMLString += F("<h5>(Kalibrace senzoru DHT22)</h5>");}
    // ******************************************* Parameter ****************************************************************************************************************************************************************************
    if (DHT11Sensor) { 
    HTMLString += "<div class='form-floating'><br/><label>DHT11-Posun teploty snímače* (Example: -1 or +1)</label><input type='text' maxlength='3' class='form-control' name='DHTTo' id='DHTTo' value='"+InTempOffset+"'></div>";
    HTMLString += "<div class='form-floating'><br/><label>DHT11-Senzor vlhkosti Offset (Example: -1 or +1)</label><input type='text' maxlength='3' class='form-control' name='DHTHo' id='DHTHo' value='"+InHumOffset+"'></div>";} else {
    HTMLString += "<div class='form-floating'><br/><label>DHT22-Posun teploty snímače* (Example: -1 or +1)</label><input type='text' maxlength='3' class='form-control' name='DHTTo' id='DHTTo' value='"+InTempOffset+"'></div>";
    HTMLString += "<div class='form-floating'><br/><label>DHT22-Senzor vlhkosti Offset (Example: -1 or +1)</label><input type='text' maxlength='3' class='form-control' name='DHTHo' id='DHTHo' value='"+InHumOffset+"'></div>";}
    // ******************************************* Parameter ****************************************************************************************************************************************************************************
    HTMLString += F("<h6>*) - 999 Teplota deaktivuje DHT-Sensor (žádný displej v matici LED)</h6>");
    HTMLString += F("<button type='submit'>Uložit</button>");
    HTMLString += F("<br/><br/>");
    HTMLString += F("</form>");
    HTMLString += F("<a href =\"/tempvalue\"><button>Zrušit</button></a>");
    HTMLString += F("<br/><br/>");
    HTMLString += F("</main>");
    HTMLString += F("</body>");
    HTMLString += F("</html>");  
    SendHTMLString(HTMLString);}} else {PleaseWait();}} // Send HTMLString or wait

// ====================================================================================================================================
// ====================================================================================================================================
