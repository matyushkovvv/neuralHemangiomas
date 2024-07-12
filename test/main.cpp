#include <neu.hpp>

int main() {
    using namespace neu;

    neu::Neu neuralNet;
    neuralNet.setNeu(10, "/home/kolya/Desktop/code/2024-misis-practice/dataset/train/HM");

    int train_res = neuralNet.trainNeu();
    if (train_res == 0) {
        std::cout << "Neural network uccessfully trained" << std::endl;
    } else {
        std::cout << "ERROR CODE: " << train_res << std::endl;
    }

    std::string exam_result = neuralNet.checkNeu("/home/kolya/Desktop/code/2024-misis-practice/dataset/val/HM/download.jpg");
    std::cout << exam_result << std::endl;

    return 0;
}