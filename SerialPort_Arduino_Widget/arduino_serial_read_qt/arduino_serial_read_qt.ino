
//Qt C++ GUI Application Tutorial | Qt QSerialPort | How to use and connect with SerialPort
//Qt With Ketan
//https://www.youtube.com/watch?v=LXPdOFH5NLA&list=PLh0cogPqXcJMuRUNMgGZwl5WEX6ZDGqaU&index=3


const int LEDPIN = 13;
String CommandString = "";
String InputData = "";
bool IS_Data_Complete = false;


void setup() {
  pinMode(LEDPIN, OUTPUT);
  digitalWrite(LEDPIN, LOW);
  Serial.begin(9600);
  Serial.println("LED IS OFF");
}

void loop() {

  Serial_Data_Events();

  if(IS_Data_Complete == true){
    if(CommandString == "On"){
      digitalWrite(LEDPIN, HIGH);
      delay(100);
      Serial.println("LED IS ON");
    }else if(CommandString == "Off"){
      digitalWrite(LEDPIN, LOW);
      delay(100);
      Serial.println("LED IS OFF");
    }

    IS_Data_Complete = false;
    CommandString = "";
    InputData = "";
  }
}


void Serial_Data_Events(){
  Serial.flush();
  while(Serial.available()){
    char inchar = (char)Serial.read();
    if(inchar == '\n'){
      IS_Data_Complete = true;
      CommandString = InputData;
    }else{
      InputData += inchar;
    }
  }
}
