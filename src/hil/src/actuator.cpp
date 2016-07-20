/** @file    actuator.cpp 
 *  @author  William Emfinger
 *  @date    2016.07.20
 *  @brief   This file contains definitions of the actuator class
 */
#include "actuator.hpp"

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
   * @brief A timer operation
   */     
  void actuator::timer_function() {
    publisher("state_pub")->send(state);
  }

  /**
   * @brief Subscriber operation for sensor 1 data
   */     
  void actuator::state_sub_operation() {
    std::string received_message = subscriber("state_sub")->message();
    state = received_message;
  }    

}
