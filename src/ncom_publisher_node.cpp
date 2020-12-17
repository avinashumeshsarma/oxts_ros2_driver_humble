#include "ncom_publisher_node.hpp"


int NComPublisherNode::ncom_callback(const NComRxC* nrx)
{
  //////////////////////////////////////////////////////////////////////////////
  // Construct std_msgs/msg/String
  //////////////////////////////////////////////////////////////////////////////
  auto msgString = RosNComWrapper:wrap_string (nrx);
  pubString_->publish(msgString);      
  
  if ((this->count_ % 100) == 0)
    RCLCPP_INFO(this->get_logger(), "'%d' Publishing: '%s'", 
                                    this->count_, msgString.data.c_str());
  //////////////////////////////////////////////////////////////////////////////
  // Construct nav_msgs/msg/Odometry
  //////////////////////////////////////////////////////////////////////////////
  auto msgOdometry = RosNComWrapper::wrap_odometry (nrx);
  pubOdometry_->publish(msgOdometry);
  //////////////////////////////////////////////////////////////////////////////
  // Construct sensor_msgs/msg/NavSatFix
  //////////////////////////////////////////////////////////////////////////////
  auto msgNavSatFix = RosNComWrapper::wrap_nav_sat_fix(nrx);
  pubNavSatFix_->publish(msgNavSatFix);
  



  /*
   * @TODO: Add switch statement on different messages to be output
   */    

  this->count_++;  
  return 0;
}