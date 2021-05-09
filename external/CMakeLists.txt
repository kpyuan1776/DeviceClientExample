set(LIBRARY_INCLUDES "beast/include")
add_library(beast INTERFACE) #interface because beast header only
target_include_directories(beast SYSTEM INTERFACE ${LIBRARY_INCLUDES})
