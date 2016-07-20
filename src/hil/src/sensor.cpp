/** @file    sensor.cpp 
 *  @author  William Emfinger
 *  @date    2016.07.20
 *  @brief   This file contains definitions of the sensor class
 */

#include "sensor.hpp"

#include "proto/hil.pb.h"

namespace zcm {

  /**
   * @brief Function required to dynamically load sensor.so
   */   
  extern "C" {
    Component* create_component() {
      return new sensor();
    }
  }

  /**
   * @brief Construct sensor
   * Register all operations exposed by this component
   */    
  sensor::sensor() {
    register_functionality("timer_function",
			   std::bind(&sensor::timer_function, this));
  }

  /**
   * @brief A timer operation
   * This operation can be triggered by a periodic timer
   * Bind this operation to a periodic timer in the JSON configuration
   */     
  void sensor::timer_function() {
    try 
      {
	E3SensorData sensorData;
	sensorData.set_sensor_name(name);
	sensorData.set_num_vehicles(numCars);
	std::string sensorString;
	sensorData.SerializeToString(&sensorString);
	publisher("sensor_pub")->send(sensorString);
      }
    catch (const std::exception &e)
      {
	std::cout << "Error: " << e.what();
      }
  }
}

