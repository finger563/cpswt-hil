/** @file    actuator.cpp 
 *  @author  William Emfinger
 *  @date    2016.07.20
 *  @brief   This file contains definitions of the actuator class
 *           which interfaces with a traffic light to manage its state
 */
#include "actuator.hpp"

#include "proto/hil.pb.h"

namespace zcm {

  /**
   * @brief Function required to dynamically load actuator.so
   */     
  extern "C" {
    Component* create_component() {
      return new actuator();
    }
  }  

  /**
   * @brief Construct actuator
   * Register all operations exposed by this component
   */    
  actuator::actuator() {
    register_functionality("timer_function",
			     std::bind(&actuator::timer_function, this));
    register_functionality("state_sub_operation",
			   std::bind(&actuator::state_sub_operation, this));
  }

  /**
   * @brief A timer operation for publishing the current state of the traffic light
   */     
  void actuator::timer_function() {
    TrafficLightState stateData;
    stateData.set_traffic_light_name(name);
    stateData.set_state(state);
    std::string stateString;
    stateData.SerializeToString(&stateString);
    publisher("state_pub")->send(stateString);
  }

  /**
   * @brief Subscriber operation for receiving and setting the traffic light state
   */     
  void actuator::state_sub_operation() {
    std::string receivedMessage = subscriber("state_sub")->message();
    TrafficLightState stateData;
    stateData.ParseFromString(receivedMessage);
    if (stateData.traffic_light_name() == name)
      state = stateData.state();
  }    

}
