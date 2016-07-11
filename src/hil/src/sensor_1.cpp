/** @file    sensor_1.cpp 
 *  @author  William Emfinger
 *  @date    2016.06.10
 *  @brief   This file contains definitions of the sensor_1 class
 */

#include "sensor_1.hpp"

using namespace utility;
using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace concurrency::streams;

namespace zcm {

  /**
   * @brief Function required to dynamically load sensor_1.so
   */   
  extern "C" {
    Component* create_component() {
      return new sensor_1();
    }
  }

  /**
   * @brief Construct sensor_1
   * Register all operations exposed by this component
   */    
  sensor_1::sensor_1() {
    register_timer_operation("timer_function",
			     std::bind(&sensor_1::timer_function, this));
  }

  /**
   * @brief A timer operation
   * This operation can be triggered by a periodic timer
   * Bind this operation to a periodic timer in the JSON configuration
   */     
  void sensor_1::timer_function() {
    int spaces = 0;

    http_client client(U("http://129.59.105.153:9000"));
    uri_builder builder(U("/api/devices/ch1/AvailableParkingSpaces"));
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
	std::cout << "Got ch1 parking spaces available: " << spaces << std::endl;
	publisher("sensor_1_pub")->send(std::to_string(spaces));
      }
    catch (const std::exception &e)
      {
	std::cout << "Error: " << e.what();
      }
  }
}

