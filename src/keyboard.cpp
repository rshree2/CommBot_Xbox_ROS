#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/UInt16.h"
#include "std_msgs/Float32.h"
#include <sstream>
#include "base_controller/Xbox_Button_Msg.h"
#include "sound_play/sound_play.h"
//#include <unistd.h>


/*
std_msgs::UInt16 temp_f;
std_msgs::UInt16 temp_b;
std_msgs::UInt16 temp1_f;
std_msgs::UInt16 temp1_b;
std_msgs::UInt16 tempright_bump;
std_msgs::UInt16 templeft_bump;
std_msgs::float temptrigger_left;
std_msgs::float temptrigger_right;

*/

int currentpos=0;

int count = 0;


std_msgs::UInt16 msg;

int flag=0;
int flag1=0;
int flag_xx=0;
int flag_yy=0;
int flag_aa=0;
int flag_bb=0;
int flag_lt=0;
int flag_rt=0;

void chatterCallback_xbox(const base_controller::Xbox_Button_Msg::ConstPtr& button)           // callback function for the topic "xbox_controller" to describe what to do with the buttons and how to  
{                                                                                             // use them. 
  int xx = button->x;
  int yy = button->y;
  int aa = button->a;
  int bb = button->b;
  int right_bump = button->right_bumper;
  int left_bump = button->left_bumper;
  float left_trigger = button-> left_trigger;
  float right_trigger = button-> right_trigger;

 

 if( xx==1)					//button x
    {
     // temp_f.data=xx;
      flag_xx=1;
     }
 else 
     flag_xx=0;
 
 if (yy==1)					// button y
     {
     // temp_b.data=yy;
      flag_yy=1;
     }
 else 
     flag_yy=0;

 if (aa==1)					//button a
     {
       //temp1_f.data=aa;
       flag_aa=1; 
     }
 else 
     flag_aa=0;


 if ( bb==1)					// button b
     {
       //temp1_b.data=bb;
       flag_bb=1;
     }
 else 
     flag_bb=0;

 if (left_bump == 1  )				// left bumper
     { 
      // templeft_bump.data=1;
       flag= 1;
     } 
 else 
     flag=0;


if (right_bump == 1  ) 				// right bumper
     { 
       //tempright_bump.data=1;
       flag1 =1;
      }
else 
    flag1 =0;

if (  left_trigger != 1.0 /*&& left_trigger != 1.0*/)
   {
     flag_lt=1;
   }
else 
   flag_lt=0;

if (right_trigger != 1.0 /*&& right_trigger != 1.0*/)
   {
     flag_rt=1;
   }
else 
   flag_rt=0;

 
}        
  

int main(int argc, char **argv)
{

int initialpos =0;
int currentpos;

int initialpos_ltrt =0;
int currentpos_ltrt;


 ros::init(argc, argv, "keyboard");                                                             

 ros::NodeHandle n;
 sound_play::SoundClient sc;

  ros::Publisher chatter_pub = n.advertise<std_msgs::UInt16>("servo_val", 1);                   // publish the data to the topic "servo_Val"
  ros::Subscriber sub_xbox = n.subscribe("xbox_controller", 1, chatterCallback_xbox);           // subscribe data from the topic "xbox_controller" 
  ros::Rate loop_rate(25);

  


  while (ros::ok())
  { 


       
     if(flag_xx == 1)
       {
	const char *str= " Moving Forward.";
	msg.data=10;                                // for motor 1 forward direction
        chatter_pub.publish(msg);
	ROS_INFO_STREAM("value is" << msg.data);
        sc.say(str);
       }

     if(flag_yy==1)
       {
        msg.data=20;                               // for motor 1 reverse direction 
        chatter_pub.publish(msg);
	ROS_INFO_STREAM("value is" << msg.data);
        sc.say(" Moving Backward");
       }

     if(flag_aa ==1)
       {
        msg.data=30;                               // for motor 2 forward direction
        chatter_pub.publish(msg);
	ROS_INFO_STREAM("value is" << msg.data);
	sc.say("Moving left");
       }
 
     if(flag_bb==1)
       {
        msg.data=40;                               // for motor 2 reverse direction
        chatter_pub.publish(msg);
	ROS_INFO_STREAM("value is" << msg.data);
	sc.say("Moving left");
       }


     if(flag1==1)                  // for motor 3 forward direction
	{ 
             if( initialpos!=180)
                {
                  initialpos= initialpos+1;
                  msg.data=initialpos; 
	          chatter_pub.publish(msg);
 	          ROS_INFO_STREAM("value is" << msg.data);
                  currentpos=initialpos;
                }  
             else
                ROS_INFO_STREAM("cannot move forward byond" << initialpos); 
        }

   
    
     if (flag ==1 )                    // for motor 3 forward direction
	{
           if ( currentpos!= 0)
               {
                 currentpos = currentpos -1;  	
                 msg.data= currentpos;
	         chatter_pub.publish(msg);
	         ROS_INFO_STREAM("value is" << msg.data);
                 initialpos= currentpos;  
               }
           else
              ROS_INFO_STREAM("cannot move backwards byond" << currentpos);             

        }
 
     
    if ( flag_rt ==1)
       {
          if( initialpos_ltrt!= 180)
             { 
              initialpos_ltrt= initialpos_ltrt+1;
              msg.data= initialpos_ltrt;  
              chatter_pub.publish(msg);
	      ROS_INFO_STREAM("value of the left trigger is" << msg.data);
              currentpos_ltrt= initialpos_ltrt;
             }
          else
                ROS_INFO_STREAM("cannot move forward byond" << initialpos_ltrt); 

      }


    if ( flag_lt ==1)
       {
         if( initialpos_ltrt!=0)
            { 
              currentpos_ltrt= currentpos_ltrt-1;
              msg.data= currentpos_ltrt;
              chatter_pub.publish(msg);
              ROS_INFO_STREAM("value of the right triggger is" << msg.data);
              initialpos_ltrt= currentpos_ltrt;
            }    
          else
              ROS_INFO_STREAM("cannot move backwards byond" << currentpos_ltrt); 
        }

    
/*
 
     temp_f.data=0;                     enable to have the buttons work when pressed ones ( on and off) 
     temp_b.data=0;
     temp1_f.data=0; 
     temp1_b.data=0;
     temptrigger_right=0;
     temptrigger_left=0.0;

*/       
    
   

   ros::spinOnce();
   loop_rate.sleep();	
   ++count;
  }
   

  ros::spin();
  return 0;
}
