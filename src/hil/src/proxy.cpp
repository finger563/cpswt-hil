/** @file    proxy.cpp 
 *  @author  William Emfinger
 *  @date    2016.07.20
 *  @brief   This file contains definitions of the proxy class
 */

#include "proxy.hpp"

#include "proto/hil.pb.h"
#include "proto/service_interface.pb.h"

namespace zcm {

  /**
   * @brief Function required to dynamically load proxy.so
   */     
  extern "C" {
    Component* create_component() {
      return new proxy();
    }
  }  

  /**
   * @brief Construct proxy
   * Register all operations exposed by this component
   */   
  proxy::proxy() {
    register_functionality("timer_function",
			   std::bind(&proxy::timer_function, this));
    register_functionality("sensor_sub_function",
			   std::bind(&proxy::sensor_sub_function, this));
    register_functionality("state_sub_function",
			   std::bind(&proxy::state_sub_function, this));
    register_functionality("interface_sub_function",
			   std::bind(&proxy::interface_sub_function, this));
  }

  /**
   * @brief A timer operation
   */     
  void proxy::timer_function() {
    std::string state;
    publisher("state_pub")->send(state);
  }

  /**
   * @brief Function for receiving interface data from the Federations
   */     
  void proxy::interface_sub_function() {
    std::string receivedMessage = subscriber("interface_sub")->message();

    Base baseData;
    baseData.ParseFromString(receivedMessage);

    std::string messageType = baseData.message_type();
    std::cout << "Received message of type: " << messageType << std::endl;

    if (!messageType.compare("Connect")) {
      // create a connection for the federation based on
      // resources/requirements and authentication data
      Connect connectData;
      connectData.ParseFromString(baseData.message_data());
      // get the connection info
      std::string fedName = connectData.federation_name();
      std::string authData = connectData.auth_data();
      std::string replyConnection = connectData.connection();
      // check the required streams and services
      Requirements reqData = connectData.requirements();
      for (int i = 0; i < reqData.services_size(); i++) {
	const Service& service = reqData.services(i);
	AbstractData data = service.command();
	std::string dataType = data.type();
	for (int j = 0; j < service.destinations_size(); j++) {
	  const Node& dest = service.destinations(j);
	  // make sure node 'dest' can accept data of type 'dataType'
	}
      }
      for (int i = 0; i < reqData.streams_size(); i++) {
	const Stream& stream = reqData.streams(i);
	AbstractData data = stream.data();
	std::string dataType = data.type();
	double interval = stream.interval().seconds();
	Node source = stream.source();
	// make sure that node 'source' can produce data of type
	// 'dataType'
      }
    }
    else if (!messageType.compare("Stream")) {
      // forward the data to the stream's defined nodes (defined
      // purely by the HiL)
      Stream streamData;
      streamData.ParseFromString(baseData.message_data());
    }
    else if (!messageType.compare("Service")) {
      // forward the data to the services defined destinations
      // (defined as part of service itself)
      Service serviceData;
      serviceData.ParseFromString(baseData.message_data());
    }
    else if (!messageType.compare("NetworkPacket")) {
      // encode the network packet and send it out on the wire to all
      // the destinations defined in the network packet structure
      // itself
      NetworkPacket networkData;
      networkData.ParseFromString(baseData.message_data());
      std::string data = networkData.data();
      for (int i = 0; i < networkData.destinations_size(); i++) {
	const Node& node = networkData.destinations(i);
	std::string address = node.address();
	// send data to address
      }
    }
    else if (!messageType.compare("AbstractData")) {
      // simply check type and select publisher by type?
      AbstractData abstractData;
      abstractData.ParseFromString(baseData.message_data());
    }
  }    

  /**
   * @brief Function for receiving HiL sensor data
   */     
  void proxy::sensor_sub_function() {
    std::string receivedMessage = subscriber("sensor_sub")->message();
    E3SensorData sensorData;
    sensorData.ParseFromString(receivedMessage);
    std::cout << "Received sensor data from: " << sensorData.sensor_name() << std::endl;
    sensorMap[sensorData.sensor_name()] = sensorData.num_vehicles();
  }    

  /**
   * @brief Function for receiving HiL traffic light state data
   */     
  void proxy::state_sub_function() {
    std::string receivedMessage = subscriber("state_sub")->message();
    TrafficLightState stateData;
    stateData.ParseFromString(receivedMessage);
    std::cout << "Received state data from: " << stateData.traffic_light_name() << std::endl;
    stateMap[stateData.traffic_light_name()] = stateData.state();
  }    
}
