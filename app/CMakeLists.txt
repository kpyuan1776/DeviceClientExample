# Sources
set (APP_SOURCES "maintwo.cpp")

# Executable
add_executable(${MAIN} ${APP_SOURCES} mainwindow.cpp mainwindow.ui resources.qrc)

# Main Executable
#target_link_libraries(${MAIN} PUBLIC ${LIBRARY_NAME} beast ${Boost_LIBRARIES} Qt5::Widgets ${OPENSSL_LIBRARIES})
target_link_libraries(${MAIN} PUBLIC ${LIBRARY_NAME} beast certify ${Boost_LIBRARIES} Qt5::Widgets ${OPENSSL_LIBRARIES})
target_include_directories(${MAIN} PUBLIC ${PROJECT_BINARY_DIR})
target_compile_features(${LIBRARY_NAME} PUBLIC cxx_std_17)
