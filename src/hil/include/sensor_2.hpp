/** @file    sensor_2.hpp 
 *  @author  William Emfinger
 *  @date    2016.06.10
 *  @brief   This file declares the sensor_2 class
 */

#ifndef SENSOR_2
#define SENSOR_2
#include "component.hpp"

#include "json.hpp"

#include "cpprest/http_client.h"


namespace zcm {

  /**
   * @brief sensor_2 class
   */    
  class sensor_2 : public Component {
  public:

    /**
     * @brief Construct sensor_2 & register all exposed functionality
     */     
    sensor_2();

    /**
     * @brief A timer operation that can be triggered by some periodic timer
     */     
    void timer_function();
  };

}

#endif
