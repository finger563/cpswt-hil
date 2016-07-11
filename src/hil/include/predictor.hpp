/** @file    predictor.hpp 
 *  @author  William Emfinger
 *  @date    2016.06.10
 *  @brief   This file declares the predictor class
 */

#ifndef PREDICTOR
#define PREDICTOR
#include "component.hpp"

namespace zcm {

  /**
   * @brief predictor class
   */    
  class predictor : public Component {
  public:

    /**
     * @brief Construct predictor & register all exposed functionality
     */     
    predictor();

    /**
     * @brief Function for receiving aggregated sensor data
     */         
    void subscriber_function(std::string received_message);

  private:
    int prediction;
  };
}

#endif
