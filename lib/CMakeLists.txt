add_library(${PROJECT_NAME} SHARED neu.cpp include/neu.hpp) # ${CMAKE_SOURCE_DIR}/src/neu.py)

#Python_add_library(${PROJECT_NAME} SHARED neu.cpp include/neu.hpp)
#pybind11_add_module(${PROJECT_NAME} SHARED neu.cpp include/neu.hpp)

target_link_libraries(${PROJECT_NAME} PRIVATE pybind11::headers pybind11::module pybind11::embed ${OpenCV_LIBS})
#set_target_properties(${PROJECT_NAME} PROPERTIES
#        INTERPROCEDURAL_OPTIMIZATION ON
#        CXX_VISIBILITY_PRESET default
#        VISIBILITY_INLINES_HIDDEN ON
#)

target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

install(
    TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION lib
)
