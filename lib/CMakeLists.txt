add_library(${PROJECT_NAME} SHARED neu.cpp include/neu.hpp)
#pybind11_add_module(${PROJECT_NAME} SHARED neu.cpp include/neu.hpp)

#target_link_libraries(${PROJECT_NAME} PRIVATE pybind11)
target_link_libraries(${PROJECT_NAME} PRIVATE pybind11::module pybind11::embed)

target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

install(
    TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION lib
)
