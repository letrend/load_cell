#define USE_USBCON
#include "ros.h"
#include <std_msgs/Float32.h>
#include "HX711.h" //This library can be obtained here http://librarymanager/All#Avia_HX711

#define calibration_factor 22030.0 //This value is obtained using the SparkFun_HX711_Calibration sketch

#define LOADCELL_DOUT_PIN  3
#define LOADCELL_SCK_PIN  2


ros::NodeHandle nh;

std_msgs::Float32 msg;
ros::Publisher publisher("load_cell", &msg);

HX711 scale;

void setup() {
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(calibration_factor); //This value is obtained by using the SparkFun_HX711_Calibration sketch
  scale.tare();  //Assuming there is no weight on the scale at start up, reset the scale to 0

  nh.initNode();
  nh.advertise(publisher);
}

void loop() {
  msg.data = scale.get_units();
  publisher.publish( &msg );
  nh.spinOnce();
}
