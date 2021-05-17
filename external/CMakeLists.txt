set(LIBRARY_INCLUDES "beast/include" "certify/include")
add_library(beast INTERFACE) #interface because beast header only
target_include_directories(beast SYSTEM INTERFACE ${LIBRARY_INCLUDES})
add_library(certify INTERFACE)
target_include_directories(certify SYSTEM INTERFACE ${LIBRARY_INCLUDES})
