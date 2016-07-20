/** @file    proxy.cpp 
 *  @author  William Emfinger
 *  @date    2016.07.20
 *  @brief   This file contains definitions of the proxy class
 */

#include "proxy.hpp"

#include "proto/hil.pb.h"
#include "proto/service_interface.pb.h"

namespace zcm {

  /**
   * @brief Function required to dynamically load proxy.so
   */     
  extern "C" {
    Component* create_component() {
      return new proxy();
    }
  }  

  /**
   * @brief Construct proxy
   * Register all operations exposed by this component
   */   
  proxy::proxy() {
    register_functionality("timer_function",
			   std::bind(&proxy::timer_function, this));
    register_functionality("sensor_sub_function",
			   std::bind(&proxy::sensor_sub_function, this));
    register_functionality("state_sub_function",
			   std::bind(&proxy::state_sub_function, this));
  }

  /**
   * @brief A timer operation
   */     
  void proxy::timer_function() {
    std::string state;
    publisher("state_pub")->send(state);
  }

  /**
   * @brief Function for receiving HiL sensor data
   */     
  void proxy::sensor_sub_function() {
    std::string receivedMessage = subscriber("sensor_sub")->message();
    E3SensorData sensorData;
    sensorData.ParseFromString(receivedMessage);
    std::cout << "Received sensor data from: " << sensorData.sensor_name() << std::endl;
    sensorMap[sensorData.sensor_name()] = sensorData.num_vehicles();
  }    

  /**
   * @brief Function for receiving HiL traffic light state data
   */     
  void proxy::state_sub_function() {
    std::string receivedMessage = subscriber("state_sub")->message();
    TrafficLightState stateData;
    stateData.ParseFromString(receivedMessage);
    std::cout << "Received state data from: " << stateData.traffic_light_name() << std::endl;
    stateMap[stateData.traffic_light_name()] = stateData.state();
  }    
}