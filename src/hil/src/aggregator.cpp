/** @file    aggregator.cpp 
 *  @author  William Emfinger
 *  @date    2016.06.10
 *  @brief   This file contains definitions of the aggregator class
 */
#include "aggregator.hpp"

namespace zcm {

  /**
   * @brief Function required to dynamically load aggregator.so
   */     
  extern "C" {
    Component* create_component() {
      return new aggregator();
    }
  }  

  /**
   * @brief Construct aggregator
   * Register all operations exposed by this component
   */    
  aggregator::aggregator() {
    register_functionality("timer_function",
			     std::bind(&aggregator::timer_function, this));
    register_functionality("sensor_1_sub_operation",
			   std::bind(&aggregator::sensor_1_sub_operation, this));
    register_functionality("sensor_2_sub_operation",
			   std::bind(&aggregator::sensor_2_sub_operation, this));
  }

  /**
   * @brief A timer operation
   */     
  void aggregator::timer_function() {
    aggregate = sensor_1 + sensor_2;
    publisher("aggregated_pub")->send(std::to_string(aggregate));
  }

  /**
   * @brief Subscriber operation for sensor 1 data
   */     
  void aggregator::sensor_1_sub_operation() {
    std::string received_message = subscriber("")->message();
    sensor_1 = atoi(received_message.c_str());
  }    

  /**
   * @brief Subscriber operation for sensor 2 data
   */     
  void aggregator::sensor_2_sub_operation() {
    std::string received_message = subscriber("")->message();
    sensor_2 = atoi(received_message.c_str());
  }    
}
