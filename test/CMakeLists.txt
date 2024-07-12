#pybind11_add_module(neu_example main.cpp)
#target_link_libraries(neu_example PRIVATE ${PROJECT_NAME} pybind11)

add_executable(neu_example main.cpp)
target_link_libraries(neu_example PRIVATE ${PROJECT_NAME} pybind11::module pybind11::embed)
target_include_directories(neu_example PRIVATE ${pybind11_INCLUDE_DIRS})