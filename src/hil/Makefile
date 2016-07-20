ZCM_HEADERS=/usr/local/include/zcm
ZCM_LIBRARY=/usr/local/lib

TEST_PROTO_DIR=proto
TEST_INCLUDE_DIR=include
TEST_SOURCE_DIR=src
TEST_BUILD_DIR=build
TEST_CONFIG_DIR=config

all:
	mkdir -p $(TEST_BUILD_DIR)
	cp -r $(TEST_CONFIG_DIR)/* $(TEST_BUILD_DIR)/.

	protoc --cpp_out=. $(TEST_PROTO_DIR)/service_interface.proto
	protoc --cpp_out=. $(TEST_PROTO_DIR)/hil.proto

	g++ -fPIC -shared $(TEST_SOURCE_DIR)/sensor.cpp $(TEST_PROTO_DIR)/hil.pb.cc -o $(TEST_BUILD_DIR)/sensor.so -I$(TEST_INCLUDE_DIR) -I. -std=c++11 -pthread -I$(ZCM_HEADERS) -L$(ZCM_LIBRARY) -lzcm -lzmq -lboost_filesystem -lprotobuf

	g++ -fPIC -shared $(TEST_SOURCE_DIR)/actuator.cpp $(TEST_PROTO_DIR)/hil.pb.cc -o $(TEST_BUILD_DIR)/actuator.so -I$(TEST_INCLUDE_DIR) -I. -std=c++11 -pthread -I$(ZCM_HEADERS) -L$(ZCM_LIBRARY) -lzcm -lzmq -lboost_filesystem -lprotobuf

	g++ -fPIC -shared $(TEST_SOURCE_DIR)/proxy.cpp $(TEST_PROTO_DIR)/hil.pb.cc $(TEST_PROTO_DIR)/service_interface.pb.cc -o $(TEST_BUILD_DIR)/proxy.so -I$(TEST_INCLUDE_DIR) -I. -std=c++11 -pthread -I$(ZCM_HEADERS) -L$(ZCM_LIBRARY) -lzcm -lzmq -lboost_filesystem -lprotobuf

	g++ $(TEST_SOURCE_DIR)/main.cpp -o $(TEST_BUILD_DIR)/actor -I$(TEST_INCLUDE_DIR) -std=c++11 -ldl -pthread -I$(ZCM_HEADERS) -L$(ZCM_LIBRARY) -lzcm -lzmq

run:
	cd $(TEST_BUILD_DIR) && export LD_LIBRARY_PATH=$(PWD):$(LD_LIBRARY_PATH) && ./actor

clean:
	rm -rf $(TEST_BUILD_DIR)
