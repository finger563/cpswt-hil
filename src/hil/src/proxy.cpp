/** @file    proxy.cpp 
 *  @author  William Emfinger
 *  @date    2016.07.20
 *  @brief   This file contains definitions of the proxy class
 */

#include "proxy.hpp"

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
    std::string received_message = subscriber("sensor_sub")->message();
  }    

  /**
   * @brief Function for receiving HiL traffic light state data
   */     
  void proxy::state_sub_function() {
    std::string received_message = subscriber("state_sub")->message();
  }    
}
