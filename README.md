# neuralHemangiomas
This project is designed to detect and classify hemangiomas on a child's body.

## Prerequisites

Before you start, make sure you have the following installed:

- Python 3.7 or higher
- PyTorch
- OpenCV
- CMake
- A C++ compiler (e.g., g++)

## Installation

1. **Clone the repository**

    ```sh
    git clone https://github.com/yourusername/neuralHemangiomas.git
    cd neuralHemangiomas
    ```

2. **Set up Python environment**
    ```sh
    python3 -m venv venv
    source venv/bin/activate
    ```

3. **Requirements**
    a. Install vcpkg from https://github.com/microsoft/vcpkg and Cmake https://cmake.org/download/.
    b. Install pybind11, ultralytics and opencv packages via ```sh ./vcpkg install <package-name> ```.

4. **Building the project**
    ```sh
    cmake -S . -B  build -DCMAKE_TOOLCHAIN_FILE=/path/to/vcpkg.cmake
    cmake --build build
    ```

5. **Using neu library**
    a. Include neu library ```c++ #include <neu.hpp>```
    b. Init namespace ```c++ using namespace neu;```
    c. Init object ```c++ Neu& neuralNet = Neu::getInstance();```
    d. Set up path to dataset with training, validation and test data ```c++ neuralNet.setNeu(10, "/path/to/train", "/path/to/val", "/path/to/test");```
    e. Use `trainNeu` and `checkNeu` functions to train neural network and send images for classification.

6. **Running executable file**
    ```sh
    ./neuralHemangiomas
    ```
