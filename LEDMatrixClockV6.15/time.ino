
void getTimeLocal()
{
  time_t tT = now();
  // local time
  time_t tTlocal = CE.toLocal(tT);
  w = weekday(tTlocal);
  d = day(tTlocal);
  mo = month(tTlocal);
  ye = year(tTlocal);
  h = hour(tTlocal);
  m = minute(tTlocal);
  s = second(tTlocal);
  //localMillisAtUpdate = millis();
  //client.stop();
}

void showSimpleClock()
{
  dx=dy=0;
  clr();
  showDigit(h/10,  4, dig4x8);
  showDigit(h%10,  12, dig4x8);
  showDigit(m/10, 21, dig4x8);
  showDigit(m%10, 29, dig4x8);
  // showDigit(s/10, 38, dig6x8);
  // showDigit(s%10, 46, dig6x8);
  setCol(15,dots ? B00100100 : 0);
  // setCol(32,dots ? B00100100 : 0);
  refreshAll();
}

// =======================================================================

void getAnimClock() {
  byte digPos[4]={1,8,17,25};
  int digHt = 12;
  int num = 4; 
  int i;
  if(del==0) {
    del = digHt;
    for(i=0; i<num; i++) digold[i] = dig[i];
    dig[0] = h/10 ? h/10 : 10;
    dig[1] = h%10;
    dig[2] = m/10;
    dig[3] = m%10;
    for(i=0; i<num; i++)  digtrans[i] = (dig[i]==digold[i]) ? 0 : digHt;
  } else
    del--;
  clr();
  for(i=0; i<num; i++) {
    if(digtrans[i]==0) {
      dy=0;
      showDigit(dig[i], digPos[i], dig6x8);
    } else {
      dy = digHt-digtrans[i];
      showDigit(digold[i], digPos[i], dig6x8);
      dy = -digtrans[i];
      showDigit(dig[i], digPos[i], dig6x8);
      digtrans[i]--;}}
  dy=0;
  setCol(15,dots ? B00100100 : 0);
  // setCol(16,dots ? B00100100 : 0);
  refreshAll();
  MyWaitLoop(ScrollClockTime); // Scrollgeschwindigkeit der Uhrzeit
}

// =======================================================================

int FormatedTime()
{
String fTime, fsh, fsm;  
getTimeLocal(); // aktuelle Zeit holen 
if (h < 10) {fsh = "0"+String(h);} else {fsh = String(h);}  
if (m < 10) {fsm = "0"+String(m);} else {fsm = String(m);}  
// if (s < 10) {fss = "0"+String(s);} else {fss = String(s);}  
fTime =fsh+fsm;
// Serial.println("Formated Time: "+fTime); // Only for Debuging 
return fTime.toInt();
}