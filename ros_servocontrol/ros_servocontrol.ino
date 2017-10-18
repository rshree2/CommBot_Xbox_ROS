

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
 #include <WProgram.h>
#endif

#include <Servo.h> 
#include <ros.h>
#include <std_msgs/UInt16.h>



int i,j;
int currentpos=0;
int currentpos1=0;

ros::NodeHandle  nh;

Servo servo;
Servo servo1;

void servo_cb( const std_msgs::UInt16& str_msg)
{
  if (str_msg.data == 10)
  {
    for( i = currentpos; i <= 180;)
    {
    i=i+5;
    servo.write(i);
    currentpos=i;
    break;
    }
  }
  
  if (str_msg.data == 20)
  {
    for( i = currentpos; i >=0;)
    {
    i=i-5;
    servo.write(i);
    currentpos=i;
    break;
    }
  }

  if (str_msg.data == 30)
  {
    for( j = currentpos1; i <=100;)
    {
    j=j+5;
    servo1.write(j);
    currentpos1=j;
    break;
    }
  }

  if (str_msg.data == 40)
  {
    for( j = currentpos1; j >=50;)
    {
    j=j-5;
    servo1.write(j);
    currentpos1=j;
    break;
    }
  }

 // servo.write(str_msg.data); //set servo angle, should be from 0-180  
  digitalWrite(13, HIGH-digitalRead(13));  //toggle led  
}


ros::Subscriber<std_msgs::UInt16> sub("servo_val", servo_cb);


std_msgs::UInt16 str_msg;
ros::Publisher servo_val("servo_val", &str_msg); 


void setup()
{
  pinMode(13, OUTPUT);
 // pinMode(9, OUTPUT);
  
  servo.write(0);
  servo1.write(0);
  nh.initNode();
  nh.subscribe(sub);
  nh.advertise(servo_val);
  servo.attach(9); //attach it to pin 9
  servo1.attach(11);
}

void loop()
{
 
  servo_val.publish( &str_msg );
  nh.spinOnce();
  delay(10);
}

    
