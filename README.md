# DeviceClientExample
An examplified client software for example running on an embedded device

## install and run
* submodule init, submodule update
* run ```make``` to install dependencies, create build and run conan install
* ```cmake ..```
* ```make```
* to run program ```bin/./DeviceClientExample_Executable```
* run unit tests ```bin/./DeviceClientExample_unit_tests```
* create doxygen documentation in docs/html ```make DeviceClientExample_docs```
* build benchmark executable ```cmake .. -D ENABLE_BENCHMARK=ON && make && bin/./DeviceClientExample_benchmarks```
* activate test coverage ```cmake .. -D ENABLE_COVERAGE=ON && make```
