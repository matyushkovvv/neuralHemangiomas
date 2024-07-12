add_library(${PROJECT_NAME} SHARED neu.cpp include/neu.hpp)

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})

target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

install(
    TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION lib
)

#add_executable(neuHem
#        neu.cpp
#        neu.hpp)
