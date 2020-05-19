#define USE_USBCON
#include "ros.h"
#include "std_msgs/Float32.h"
#include <Dps368.h>

// Dps368 Opject
Dps368 Dps368PressureSensor = Dps368();

const unsigned char pressureLength = 50;
unsigned char pressureCount = 0;
float  pressure[pressureLength];
unsigned char temperatureCount = 0;
const unsigned char temperatureLength = 50;
float temperature[temperatureLength];

ros::NodeHandle nh;

std_msgs::Float32 pressure_msg, temp_msg;
ros::Publisher pressure_pub = ros::Publisher("dps368/pressure", &pressure_msg);
ros::Publisher temperature_pub  = ros::Publisher("dps368/temperature", &temp_msg);

void setup()
{
//  Dps368PressureSensor.begin(Wire);
  nh.initNode();
}


void loop()
{
  float temperature;
  float pressure;
  uint8_t oversampling = 7;
  int16_t ret;

  //lets the Dps368 perform a Single temperature measurement with the last (or standard) configuration
  //The result will be written to the paramerter temperature
  //ret = Dps368PressureSensor.measureTempOnce(temperature);
  //the commented line below does exactly the same as the one above, but you can also config the precision
  //oversampling can be a value from 0 to 7
  //the Dps 368 will perform 2^oversampling internal temperature measurements and combine them to one result with higher precision
  //measurements with higher precision take more time, consult datasheet for more information
//  ret = Dps368PressureSensor.measureTempOnce(temperature, oversampling);

//  if (ret == 0)
//  {
    temp_msg.data = temperature;
    temperature_pub.publish(&temp_msg);
//  }

  //Pressure measurement behaves like temperature measurement
  //ret = Dps368PressureSensor.measurePressureOnce(pressure);
//  ret = Dps368PressureSensor.measurePressureOnce(pressure, oversampling);
//  if (ret == 0){
    pressure_msg.data = pressure;
    pressure_pub.publish(&pressure_msg);
//  }
  nh.spinOnce();
}
