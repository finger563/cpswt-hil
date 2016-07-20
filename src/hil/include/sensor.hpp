/** @file    sensor.hpp 
 *  @author  William Emfinger
 *  @date    2016.07.20
 *  @brief   This file declares the sensor class for getting 
 *           getting the number of cars in a queue
 */

#ifndef SENSOR
#define SENSOR
#include "component.hpp"

#include "json.hpp"

namespace zcm {

  /**
   * @brief sensor class
   */    
  class sensor : public Component {
  public:

    /**
     * @brief Construct sensor & register all exposed functionality
     */     
    sensor();

    /**
     * @brief A timer operation that can be triggered by some periodic timer
     */     
    void timer_function();
  private:
    int numCars;
    std::string name;
  };

}

#endif
