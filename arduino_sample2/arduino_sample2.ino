String data; //data from serial
//might need to change to double or float precision for your values:
String msg_x; 
String msg_y;
String msg_radius;
//values you'll work with:
int x_value; 
int y_value;
int radius_value;

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  if (Serial.available() > 0)
  {
    data = Serial.readString(); //read data as string to get full line
    msg_x = getValue(data,',',0);
    msg_y = getValue(data,',',1);
    msg_radius = getValue(data,',',2);
    x_value = msg_x.toInt(); //convert data to int, change this based on precision (double,float,etc)
    y_value = msg_y.toInt();
    radius_value = msg_radius.toInt();
    Serial.println(x_value); //not needed, debug purposes
    Serial.println(y_value);
    Serial.println(radius_value);
  }
  else
  {
    delay(20); //add small delay otherwise will loop over too many times
  }
}
//don't need to know how this works, just know it separates strings to substrings
String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }

  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
