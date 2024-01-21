int Calculate_Eastern() { // thanks to "bospre" - https://forum.arduino.cc/t/feiertagsberechnung/308916
// according to the Gauss formula
// Return value: Date of Easter from March 1st (max=56 for April 25th)
int Ea, Eb, Ec, Ed, Ee, Ef, Ek, EM, EN, Ep, Eq;
  
  // Apply the "magic" Gauss formula:
  Ea = ye % 19;
  Eb = ye % 4;
  Ec = ye % 7;
  Ek = ye / 100;
  Ep = (8*Ek+13) / 25;
  Eq = Ek / 4;
  EM =(15 + Ek - Ep - Eq) % 30;
  EN = (4 + Ek-Eq) % 7;
  Ed = (19*Ea + EM) % 30;
  Ee = (2*Eb + 4*Ec + 6*Ed + EN) % 7;
  Ef = 22+Ed+Ee;   // Day related to March: 32 means April First etc.

  if (Ef==57) {Ef=50;}   // If April 26th is determined (31+26=57), then Easter must be on April 19th. be (19+31=50)
  /// If April 25th is determined, this only applies if d=28 and a>10
  if ((Ef==56) && (Ed==28) && (Ea>10))  {Ef=49;}
  return Ef;}

 // *************************************************************************************************
 
String First_Monday(int fm) {
int day, d1, y;
String Out;
        d1  = 1; // First Day in Month for weekday calculation
        day = 1; // First Day in Month
        y = ye; // Current Year
        //expression for converting a Gregorian date into a numerical day of the week
        int wd = ((d1 += fm < 3 ? y-- : y - 2, 23*fm/9 + d1 + 4 + y/4- y/100 + y/400)%7);
        if (wd == 0) day = day + 1;
        if (wd == 2) day = day + 6;
        if (wd == 3) day = day + 5;
        if (wd == 4) day = day + 4;
        if (wd == 5) day = day + 3; 
        if (wd == 6) day = day + 2;
        //print the date of the month that is the last Sunday
        return String(day)+"."+String(fm);
}  

 // *************************************************************************************************

String Second_Monday(int sm) {
int day, d1, y;
String Out;
        d1  = 1; // First Day in Month for weekday calculation
        day = 1; // First Day in Month
        y = ye; // Current Year
        //expression for converting a Gregorian date into a numerical day of the week
        int wd = ((d1 += sm < 3 ? y-- : y - 2, 23*sm/9 + d1 + 4 + y/4- y/100 + y/400)%7);
        if (wd == 0) day = day + 8;
        if (wd == 1) day = day + 7;
        if (wd == 2) day = day + 13;
        if (wd == 3) day = day + 12;
        if (wd == 4) day = day + 11;
        if (wd == 5) day = day + 10; 
        if (wd == 6) day = day + 9;
        //print the date of the month that is the last Sunday
        return String(day)+"."+String(sm);
}  

 // *************************************************************************************************

String Third_Monday(int tm) {
int day, d1, y;
String Out;
        d1  = 1; // First Day in Month for weekday calculation
        day = 1; // First Day in Month
        y = ye; // Current Year
        //expression for converting a Gregorian date into a numerical day of the week
        int wd = ((d1 += tm < 3 ? y-- : y - 2, 23*tm/9 + d1 + 4 + y/4- y/100 + y/400)%7);
        if (wd == 0) day = day + 15;
        if (wd == 1) day = day + 14;
        if (wd == 2) day = day + 20;
        if (wd == 3) day = day + 19;
        if (wd == 4) day = day + 18;
        if (wd == 5) day = day + 17; 
        if (wd == 6) day = day + 16;
        //print the date of the month that is the last Sunday
        return String(day)+"."+String(tm);
}  

 // *************************************************************************************************

String Last_Monday(int lm) {
int y, d1;
String Out;
    //number of days of each month
    int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    //checking if february has 28 or 29 days
    days[1] -= (y % 4) || (!(y % 100) && (y % 400));
        //get the number of days from the array for the corresponding month
        d1 = days[lm - 1];
        y = ye;
        //expression for converting a Gregorian date into a numerical day of the week
        int wd = ((d1 += lm < 3 ? y-- : y - 2, 23*lm/9 + d1 + 4 + y/4- y/100 + y/400)%7);
        int day = days[lm-1] - wd;
        if (day < days[lm-1]) day = day + 1; // Monday
        //print the date of the month that is the last Sunday
        return String(day)+"."+String(lm);
}  

 // *************************************************************************************************

String FourthThursday(int ft) {
int day, d1, y;
String Out;
        d1  = 1; // First Day in Month for weekday calculation
        day = 1; // First Day in Month
        y = ye; // Current Year
        //expression for converting a Gregorian date into a numerical day of the week
        int wd = ((d1 += ft < 3 ? y-- : y - 2, 23*ft/9 + d1 + 4 + y/4- y/100 + y/400)%7);
        if (wd == 0) day = day + 25;
        if (wd == 1) day = day + 24;
        if (wd == 2) day = day + 23;
        if (wd == 3) day = day + 22;
        if (wd == 4) day = day + 21;
        if (wd == 5) day = day + 27; 
        if (wd == 6) day = day + 26;
        //print the date of the month that is the last Sunday
        return String(day)+"."+String(ft);
} 
 // *************************************************************************************************