# Sources and Headers
set(LIBRARY_SOURCES "my_lib.cpp" "httprestclient.cpp" "utils.cpp" "devicestate.cpp" "messagehandling.cpp")
set(LIBRARY_HEADERS "${PROJECT_SOURCE_DIR}/include/my_lib.h" "${PROJECT_SOURCE_DIR}/include/httprestclient.h" "${PROJECT_SOURCE_DIR}/include/utils.h" "${PROJECT_SOURCE_DIR}/include/devicestate.h" "${PROJECT_SOURCE_DIR}/include/messagehandling.h")
set(LIBRARY_INCLUDES "${PROJECT_SOURCE_DIR}/include/")

# MyLib Library
add_library(${LIBRARY_NAME} ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
target_include_directories(${LIBRARY_NAME} PUBLIC ${LIBRARY_INCLUDES})
target_link_libraries(${LIBRARY_NAME} PUBLIC ${Boost_LIBRARIES})
target_link_libraries(${LIBRARY_NAME} PUBLIC beast)
target_link_libraries(${LIBRARY_NAME} PUBLIC certify)
target_link_libraries(${LIBRARY_NAME} PUBLIC simpleJSON)
target_compile_features(${LIBRARY_NAME} PUBLIC cxx_std_17)
