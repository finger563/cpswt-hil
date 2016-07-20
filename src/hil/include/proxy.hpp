/** @file    proxy.hpp 
 *  @author  William Emfinger
 *  @date    2016.07.20
 *  @brief   This file declares the proxy class
 */

#ifndef PROXY
#define PROXY
#include "component.hpp"

namespace zcm {

  /**
   * @brief proxy class
   */    
  class proxy : public Component {
  public:

    /**
     * @brief Construct proxy & register all exposed functionality
     */     
    proxy();

    /**
     * @brief Function for handling HiL service interface
     */         
    void timer_function();

    /**
     * @brief Function for receiving traffic light state data
     */         
    void state_sub_function();

    /**
     * @brief Function for receiving sensor data
     */         
    void sensor_sub_function();

  private:
  };
}

#endif
