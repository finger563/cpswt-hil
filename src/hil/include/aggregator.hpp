/** @file    aggregator.hpp 
 *  @author  William Emfinger
 *  @date    2016.06.10
 *  @brief   This file declares the aggregator class
 */

#ifndef AGGREGATOR
#define AGGREGATOR
#include "component.hpp"

namespace zcm {

  /**
   * @brief aggregator class
   */    
  class aggregator : public Component {
  public:

    /**
     * @brief Construct aggregator & register all exposed functionality
     */     
    aggregator();

    /**
     * @brief A timer operation that can be triggered by some periodic timer
     */     
    void timer_function();

    /**
     * @brief Function for receiving sensor_1 data
     */         
    void sensor_1_sub_operation(std::string received_message);

    /**
     * @brief Function for receiving sensor_2 data
     */         
    void sensor_2_sub_operation(std::string received_message);

  private:
    int aggregate;
    int sensor_1;
    int sensor_2;
  };
}

#endif
