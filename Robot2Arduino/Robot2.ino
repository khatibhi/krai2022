#include <util/atomic.h>
#include <ros.h>
#include <geometry_msgs/Twist.h>

ros::NodeHandle nh;
//
//#define rpwm_m1 13
//#define lpwm_m1 12
//#define rpwm_m2 6
//#define lpwm_m2 5
//#define rpwm_m3 11
//#define lpwm_m3 10  
//#define rpwm_m4 9
//#define lpwm_m4 8

int vx_ros = 0;
int vy_ros = 0;
int w_ros = 0;

void messageCb(const geometry_msgs::Twist& stick){
  int stik[] = {stick.linear.x, stick.linear.y};
  int muter = stick.angular.z;
  if(stik[0]==1 and stik[1]==1){
    vx_ros = -100;
    vy_ros = 100;
    Serial.print("serong kanan depan");
    }
  else if(stik[0]==1 and stik[1]==-1){
    Serial.print("serong kanan belakang");
    vx_ros = -100;
    vy_ros = -100;
    }
  else if(stik[0]==0 and stik[1]==-1){
    Serial.print("belakang");
    vx_ros = 0;
    vy_ros = -100;
    }
  else if(stik[0]==-1 and stik[1]==-1){
    Serial.print("serong kiri bawah");
    vx_ros = 100;
    vy_ros = -100;
    }
  else if(stik[0]==-1 and stik[1]==0){
    Serial.print("kiri");
    vx_ros = 100;
    vy_ros = 0;
    }
  else if(stik[0]==1 and stik[1]==0){
    Serial.print("kanan");
    vx_ros = -100;
    vy_ros = 0;
    }
  else if(stik[0]==-1 and stik[1]==1){
    Serial.print("serong kiri atas");
    vx_ros = 100;
    vy_ros = 100;
    }
  else if(stik[0]==0 and stik[1]==1){
    Serial.print("atas");
    vx_ros = 0;
    vy_ros = 100;
    }
  else if(muter == -1){
    vx_ros = 0;
    vy_ros = 0;
    w_ros = 100;
    }
  else if(muter == 1){
    vx_ros = 0;
    vy_ros = 0;
    w_ros = -100;
    }
  else if(muter == 0){
    vx_ros = 0;
    vy_ros = 0;
    w_ros = 0;
    }
  else{
    vy_ros = 0;
    vx_ros = 0;
    }
  }

ros::Subscriber<geometry_msgs::Twist> sub("/cmd_vel", messageCb);

int dir;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);
  pinMode(rpwm_m1, OUTPUT);
  pinMode(lpwm_m1, OUTPUT);
  pinMode(rpwm_m2, OUTPUT);
  pinMode(lpwm_m2, OUTPUT);
  pinMode(rpwm_m3, OUTPUT);
  pinMode(lpwm_m3, OUTPUT);
  pinMode(rpwm_m4, OUTPUT);
  pinMode(lpwm_m4, OUTPUT);
  nh.initNode();
  nh.subscribe(sub);
}

void loop() {
  //  put your main code here, to run repeatedly:
  //  analogWrite(rpwm_m1, 0);
  //  analogWrite(lpwm_m1, 50);
  //  analogWrite(rpwm_m2, 0);
  //  analogWrite(lpwm_m2, 50);
  //  analogWrite(rpwm_m3, 50);
  //  analogWrite(lpwm_m3, 0);
  //  analogWrite(rpwm_m4, 0);
  //  analogWrite(lpwm_m4, 50);
  //  delay(1000);
  
  int vx = 0;
  int vy = 0;
  int w = 0;
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
    vx = vx_ros;
    vy = vy_ros;
    w = w_ros;
    }
//  int w = 0;
  nh.spinOnce();
  delay(5);
  motor_1(vx, vy, w);
  motor_2(vx, vy, w);
  motor_3(vx, vy, w);
  motor_4(vx, vy, w);
  delay(10);
}
