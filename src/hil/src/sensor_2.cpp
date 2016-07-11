/** @file    sensor_1.cpp 
 *  @author  William Emfinger
 *  @date    2016.06.10
 *  @brief   This file contains definitions of the sensor_2 class
 */

#include "sensor_2.hpp"

using namespace utility;
using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace concurrency::streams;

namespace zcm {

  /**
   * @brief Function required to dynamically load sensor_2.so
   */   
  extern "C" {
    Component* create_component() {
      return new sensor_2();
    }
  }

  /**
   * @brief Construct sensor_2
   * Register all operations exposed by this component
   */    
  sensor_2::sensor_2() {
    register_timer_operation("timer_function",
			     std::bind(&sensor_2::timer_function, this));
  }

  /**
   * @brief A timer operation
   * This operation can be triggered by a periodic timer
   * Bind this operation to a periodic timer in the JSON configuration
   */     
  void sensor_2::timer_function() {
    int spaces = 0;

    http_client client(U("http://129.59.105.153:9000"));
    uri_builder builder(U("/api/devices/ch2/AvailableParkingSpaces"));
    pplx::task<int> requestTask = client.request(methods::GET, builder.to_string())
      .then([=](http_response response)
	    {
	      //std::cout << "Received response status code: " << response.status_code() << std::endl;
	      return response.extract_string();
	    })
      .then([=](std::string body)
	    {
	      //std::cout << "Received response body: " << body << std::endl;
	      Json::Value root;
	      Json::Reader jsonReader;
	      if (jsonReader.parse(body, root)) {
		//std::cout << root << std::endl;
		return root["value"].asInt();
	      }
	    });
    try 
      {
	requestTask.wait();
	spaces = requestTask.get();
	std::cout << "Got ch2 parking spaces available: " << spaces << std::endl;
	publisher("sensor_2_pub")->send(std::to_string(spaces));
      }
    catch (const std::exception &e)
      {
	std::cout << "Error: " << e.what();
      }
  }
}

