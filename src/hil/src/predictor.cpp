/** @file    predictor.cpp 
 *  @author  William Emfinger
 *  @date    2016.06.10
 *  @brief   This file contains definitions of the predictor class
 */

#include "predictor.hpp"

namespace zcm {

  /**
   * @brief Function required to dynamically load predictor.so
   */     
  extern "C" {
    Component* create_component() {
      return new predictor();
    }
  }  

  /**
   * @brief Construct predictor
   * Register all operations exposed by this component
   */   
  predictor::predictor() {
    register_subscriber_operation("subscriber_function",
				  std::bind(&predictor::subscriber_function, 
					    this,
					    std::placeholders::_1));
  }

  /**
   * @brief A subscriber operation
   */     
  void predictor::subscriber_function(std::string received_message) {
    prediction = atoi(received_message.c_str());
    std::cout << "There will be " << prediction << " spaces." << std::endl;
  }    
}
