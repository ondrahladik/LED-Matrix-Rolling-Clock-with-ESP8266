void SendPushoverMessage(String POMessage, String PODevice, String POSound){
bool FailConnect;
if (SerialMonitor) {
Serial.println(F(""));
Serial.println("[Pushover] - Odeslat zpravu: "+POMessage);}
WiFiClient client;
HTTPClient http;
MyWaitLoop(100);
if (!client.connect("api.pushover.net", 80)) {FailConnect = true;} else {FailConnect = false;}
if (!FailConnect) {
String postmessage = "token="+SecureAppToken+"&user="+UserToken+"&title=Message from: "+ProgramName+"&message="+POMessage+"&device="+PODevice+"&sound="+POSound;  
http.begin(client,"http://api.pushover.net/1/messages.json");
MyWaitLoop(500); //wait
int httpCode = http.POST(postmessage);
if (SerialMonitor) {Serial.println("[HTTP] POST... code: " + HTTPCodeText(httpCode));}
if(httpCode == HTTP_CODE_OK) {
if (SerialMonitor) {Serial.println(F("[Pushover] - Zprava byla uspesne odeslana"));}} else {
if (SerialMonitor) {Serial.println(F("[Pushover] - Zpravu nebylo mozne odeslat !"));
Serial.println(F(""));}}
http.end();
client.flush();
client.stop();
} else {
client.flush();
client.stop();
if (SerialMonitor) {Serial.println(F("[Pushover] - Pripojeni ke sluzbe se nezdarilo!"));
Serial.println(F(""));}}
}

// =========================================================================================================================

void PushOverAlert(String IHS) {
String MPushOverMessage;  
if (IHS == "MIN" || IHS == "MAX") {  
if (IHS == "MIN") {   
MPushOverMessage = F("Upozorneni: Vlhkost v miste hodin je prilis nizka ... !");}
if (IHS == "MAX") { 
MPushOverMessage = F("Upozorneni: Vlhkost v miste hodin je prilis vysoka...!");}     
if (PushoverDevice1 != ""){
if (SerialMonitor) {Serial.println("Odeslana zprava Pushover uzivateli "+PushoverDevice1);}    
SendPushoverMessage(MPushOverMessage,PushoverDevice1,"none");}   // Message to Device 1
if (PushoverDevice2 != ""){ 
if (SerialMonitor) {Serial.println("Odeslana zprava Pushover uzivateli "+PushoverDevice2);}   
SendPushoverMessage(MPushOverMessage,PushoverDevice2,"none");}   // Message to Device 2
if (PushoverDevice3 != ""){
if (SerialMonitor) {Serial.println("Odeslana zprava Pushover uzivateli "+PushoverDevice3);}  
SendPushoverMessage(MPushOverMessage,PushoverDevice3,"none");}}  // Message to Device 3
} 

// =========================================================================================================================

void CheckPushOver() {
SecureAppToken.trim(); UserToken.trim(); PushoverDevice1.trim(); PushoverDevice2.trim();
PushoverDevice3.trim(); PushoverMessageSound.trim(); PushoverMessageSound.toLowerCase(); 
if (PushoverMessageSound == "") {PushoverMessageSound = "none";} // Pushover Message Sound
if (PushoverMessageSound != "pushover" && PushoverMessageSound != "bike" &&  PushoverMessageSound != "bugle" &&
    PushoverMessageSound != "cashregister" && PushoverMessageSound != "classical" && PushoverMessageSound != "cosmic" &&
    PushoverMessageSound != "falling" && PushoverMessageSound != "gamelan" && PushoverMessageSound != "incoming" &&
    PushoverMessageSound != "intermission" && PushoverMessageSound != "magic" && PushoverMessageSound != "mechanical" &&
    PushoverMessageSound != "pianobar" && PushoverMessageSound != "siren" && PushoverMessageSound != "spacealarm" &&
    PushoverMessageSound != "tugboat" && PushoverMessageSound != "alien" && PushoverMessageSound != "climb" &&
    PushoverMessageSound != "persistent" && PushoverMessageSound != "echo" && PushoverMessageSound != "updown" &&
    PushoverMessageSound != "none") {PushoverMessageSound = F("none");} 
}

// =========================================================================================================================

void TMPushoverDevice1() { 
if (SerialMonitor) {Serial.println("Odeslana zprava Pushover uzivateli "+PushoverDevice1);}  
SendPushoverMessage("Testovaci zprava pro "+PushoverDevice1,PushoverDevice1,PushoverMessageSound); // Message to Device 1 
HTMLAnswer("TMPushoverDevice1");  
}

// =========================================================================================================================

void TMPushoverDevice2() { 
if (SerialMonitor) {Serial.println("Odeslana zprava Pushover uzivateli "+PushoverDevice2);}  
SendPushoverMessage("Testovaci zprava pro "+PushoverDevice2,PushoverDevice2,PushoverMessageSound); // Message to Device 2
HTMLAnswer("TMPushoverDevice2");  
}

// =========================================================================================================================

void TMPushoverDevice3() { 
if (SerialMonitor) {Serial.println("Odeslana zprava Pushover uzivateli "+PushoverDevice3);} 
SendPushoverMessage("Testovaci zprava pro "+PushoverDevice3,PushoverDevice3,PushoverMessageSound); // Message to Device 3
HTMLAnswer("TMPushoverDevice3");  
}

// =========================================================================================================================
