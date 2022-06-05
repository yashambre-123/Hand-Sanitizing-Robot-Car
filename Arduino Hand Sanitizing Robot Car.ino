// ..yash
// we are setting the pins of the Arduino board
int trigpin=2;
int echopin=3;
int leftir=8;
long d;
int dist;
int rightir=9;
int motorpin1=4;
int motorpin2=5;
int motorpin3=6;
int motorpin4=7;
int p=0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(trigpin,OUTPUT); // setting the pin no 2 of arduino board to OUTPUT(pin no 2 is ready to send the signals to the trigpin)
  pinMode(echopin,INPUT); //  setting the pin no 3 of arduino board to INPUT(pin no 3 is ready to recieve the signals from the ultrasonic sensor)
  pinMode(leftir,INPUT); //   setting the pin no 8 of arduino board to INPUT(pin no 8 is ready to recieve the signals from the IR sensor)
  pinMode(rightir,INPUT); //  setting the pin no 9 of arduino board to INPUT(pin no 9 is ready to recieve the signals from the IR sensor)
  // setting the pin no 4,5,6,7 of arduino board to OUTPUT(pin no 4,5,6,7 are ready to send the signals to the motor driver)  
  pinMode(motorpin1,OUTPUT);
  pinMode(motorpin2,OUTPUT);
  pinMode(motorpin3,OUTPUT);
  pinMode(motorpin4,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  // we will send a LOW signal for 2 millisecs to the trigpin of ultrasonic sensor, to clear it's voltage 
  digitalWrite(trigpin,LOW);
  delayMicroseconds(2);
  // we will send a HIGH signal for 10 millisecs to the trigpin, so that the ultrasonic sensor sends and recieves the ultrasonic sound
  digitalWrite(trigpin,HIGH);
  delayMicroseconds(10);
  // we will again send a LOW signal to the trigpin of ultrasonic sensor, to clear it's voltage 
  digitalWrite(trigpin,LOW);
  d=pulseIn(echopin,HIGH); // we send a HIGH signal to the echopin, which in turn sends us the distance of the object from itself
  dist=d*0.034/2; // we calculate the distance in cms
  Serial.print("distance");
  Serial.print(dist);
  Serial.println("cm");
  int leftirdata=digitalRead(leftir); // we read the signal(0 or 1) from the left IR sensor
  int rightirdata=digitalRead(rightir); // we read the signal(0 or 1) from the right IR sensor
  Serial.println(leftirdata);
  Serial.println(rightirdata);
  // now we compare the data from left and right IR sensor
  if ((leftirdata==LOW) && (rightirdata==LOW)){
    // These 4 signals HIGH,LOW,HIGH,LOW are used to move the motors in a forward dirction
    digitalWrite(motorpin1,HIGH);
    digitalWrite(motorpin2,LOW);
    digitalWrite(motorpin3,HIGH);
    digitalWrite(motorpin4,LOW);
    if (dist<=10){
      // These 4 signals LOW,LOW,LOW,LOW or HIGH,HIGH,HIGH,HIGH are used to stop the motors
      digitalWrite(motorpin1,LOW);
      digitalWrite(motorpin2,LOW);
      digitalWrite(motorpin3,LOW);
      digitalWrite(motorpin4,LOW);
      delay(5000);
    }
    else{
      digitalWrite(motorpin1,HIGH);
      digitalWrite(motorpin2,LOW);
      digitalWrite(motorpin3,HIGH);
      digitalWrite(motorpin4,LOW);
    }
  }
  else if ((leftirdata==LOW) && (rightirdata==HIGH)){
    // These 4 signals HIGH,LOW,LOW,LOW are used to move one motor in a forward dirction and to stop the other motor
    digitalWrite(motorpin1,HIGH);
    digitalWrite(motorpin2,LOW);
    digitalWrite(motorpin3,LOW);
    digitalWrite(motorpin4,LOW);
  }
  else if ((leftirdata==HIGH) && (rightirdata==LOW)){
    digitalWrite(motorpin1,LOW);
    digitalWrite(motorpin2,LOW);
    digitalWrite(motorpin3,HIGH);
    digitalWrite(motorpin4,LOW);
  }
  else if ((leftirdata==HIGH) && (rightirdata==HIGH)){
    digitalWrite(motorpin1,LOW);
    digitalWrite(motorpin2,LOW);
    digitalWrite(motorpin3,LOW);
    digitalWrite(motorpin4,LOW);
  }
 }
