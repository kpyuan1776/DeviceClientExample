# DeviceClientExample
An examplified client software for example running on an embedded device

## stuff
* handling the message is implemented in ReST client on_read()

### API calls
* getLatestClientVersion GET Auth required HOST_NAME/api/clientVersion
  * response: ```{'version': 1.0.001}```
* getUpdateDownload GET Auth required HOST_NAME/api/downloadUpdate
  * response:
    * filecontent
    * header: Content-Type: application/tar+gzip
    * header: Content-Disposition: attachment, filename

## install and run
* submodule init, submodule update
* run ```make``` to install dependencies, create build and run conan install
* in build ```cmake ..```
* ```make```
* to run program ```bin/./DeviceClientExample_Executable```
  * ```bin/./DeviceClientExample_Executable```
* run unit tests ```bin/./DeviceClientExample_unit_tests```
* create doxygen documentation in docs/html ```make DeviceClientExample_docs```
* build benchmark executable ```cmake .. -D ENABLE_BENCHMARK=ON && make && bin/./DeviceClientExample_benchmarks```
* activate test coverage ```cmake .. -D ENABLE_COVERAGE=ON && make```


## references
* the example depends on two header-only client libraries
  * beast: https://github.com/boostorg/beast.git
  * certify: https://github.com/djarek/certify.git
  * SimpleJSON: https://github.com/nbsdx/SimpleJSON.git
* www.boost.org



## remarks
* install conan with python3 ```pip3 install conan``` (python2 is deprecated)
* not sure if ```sudo apt install libssl-dev``` is required?

