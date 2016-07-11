/** @file    sensor_1.hpp 
 *  @author  William Emfinger
 *  @date    2016.06.10
 *  @brief   This file declares the sensor_1 class
 */

#ifndef SENSOR_1
#define SENSOR_1
#include "component.hpp"

#include "json.hpp"

#include "cpprest/http_client.h"

namespace zcm {

  /**
   * @brief sensor_1 class
   */    
  class sensor_1 : public Component {
  public:

    /**
     * @brief Construct sensor_1 & register all exposed functionality
     */     
    sensor_1();

    /**
     * @brief A timer operation that can be triggered by some periodic timer
     */     
    void timer_function();
  };

}

#endif
