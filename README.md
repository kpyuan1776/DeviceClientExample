# DeviceClientExample
An examplified client software for example running on an embedded device

## stuff
* handling the message is implemented in ReST client on_read()


## install and run
* submodule init, submodule update
* run ```make``` to install dependencies, create build and run conan install
* in build ```cmake ..```
* ```make```
* to run program ```bin/./DeviceClientExample_Executable```
  * ```bin/./DeviceClientExample_Executable www.example.com 80 /```
* run unit tests ```bin/./DeviceClientExample_unit_tests```
* create doxygen documentation in docs/html ```make DeviceClientExample_docs```
* build benchmark executable ```cmake .. -D ENABLE_BENCHMARK=ON && make && bin/./DeviceClientExample_benchmarks```
* activate test coverage ```cmake .. -D ENABLE_COVERAGE=ON && make```


## references
* the example depends on two header-only client libraries
  * beast: https://github.com/boostorg/beast.git
  * certify: https://github.com/djarek/certify.git



## remarks
* not sure if ```sudo apt install libssl-dev``` is required?

