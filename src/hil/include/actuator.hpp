/** @file    actuator.hpp 
 *  @author  William Emfinger
 *  @date    2016.07.20
 *  @brief   This file declares the actuator class
 *           for controlling the state of the traffic light
 */

#ifndef ACTUATOR
#define ACTUATOR
#include "component.hpp"

namespace zcm {

  /**
   * @brief actuator class
   */    
  class actuator : public Component {
  public:

    /**
     * @brief Construct actuator & register all exposed functionality
     */     
    actuator();

    /**
     * @brief A timer operation for periodically publishing the state of the traffic light
     */     
    void timer_function();

    /**
     * @brief Function for receiving state data to set the state
     */         
    void state_sub_operation();

  private:
    std::string name;
    std::string state;
  };
}

#endif
