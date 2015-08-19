//example use of LCD4Bit_mod library

#include <LCD4Bit_mod.h> 
//create object to control an LCD.  
//number of lines in display=1
LCD4Bit_mod lcd = LCD4Bit_mod(2); 

//Key message
const int ldrInPin = A1;
const int Rhigh = 120; // 1 Kohms


/*

 rough formula that relates the resistance of an LDR to the light in Lux. That is:
 Rldr=500/Lux, or
 Lux=500/Rldr (in kOhm)
 
 */

uint16_t ldrValue;

void setup() { 
  pinMode(13, OUTPUT);  //we'll use the debug LED to output a heartbeat

  lcd.init();
  //optionally, now set up our application-specific display settings, overriding whatever the lcd did in lcd.init()

  lcd.clear();
  lcd.println("WWW.IoTHIVE.COM ");
  
  Serial.begin(9600);

 

}

#define CORRECTION 0.004887585
float volts;
char buff[16];

// reverses a string 'str' of length 'len'
void reverse(char *str, int len)
{
  int i=0, j=len-1, temp;
  while (i<j)
  {
    temp = str[i];
    str[i] = str[j];
    str[j] = temp;
    i++; 
    j--;
  }
}

// Converts a given integer x to string str[].  d is the number
// of digits required in output. If d is more than the number
// of digits in x, then 0s are added at the beginning.
int intToStr(int x, char str[], int d)
{
  int i = 0;
  while (x)
  {
    str[i++] = (x%10) + '0';
    x = x/10;
  }

  // If number of digits required is more, then
  // add 0s at the beginning
  while (i < d)
    str[i++] = '0';

  reverse(str, i);
  str[i] = '\0';
  return i;
}

// Converts a floating point number to string.
void ftoa(float n, char *res, int afterpoint)
{
  // Extract integer part
  int ipart = (int)n;

  // Extract floating part
  float fpart = n - (float)ipart;

  // convert integer part to string
  int i = intToStr(ipart, res, 0);

  // check for display option after point
  if (afterpoint != 0)
  {
    res[i] = '.';  // add dot

    // Get the value of fraction part upto given no.
    // of points after dot. The third parameter is needed
    // to handle cases like 233.007
    fpart = fpart * pow(10, afterpoint);

    intToStr((int)fpart, res + i + 1, afterpoint);
  }
}

void loop() {

  ldrValue = analogRead(ldrInPin);    // read the value from the sensor  
  
  
  volts = ldrValue * CORRECTION;
  
  lcd.cursorTo(2,0);
  lcd.println("                  ");
  lcd.cursorTo(2,0);
  lcd.println("LUX value=");
  
  float Rldr = ( (volts * Rhigh) / (5-volts));
  float lux = (500/ Rldr) * 100 ; 
  analogWrite(3,map(lux,0,150,100,0));
  lux = map(lux,0,150,0,100);
  
  ftoa(lux, buff,2);
  lcd.println(buff);
  lcd.println("%");
  Serial.println(buff);
  
  
  delay(100);




}




