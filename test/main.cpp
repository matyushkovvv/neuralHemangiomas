#include <neu.hpp>

int main() {
    using namespace neu;

    const fs::path path_to_py = "/home/kolya/Desktop/code/2024-misis-practice/neuralHemangiomas/src";

    Neu& neuralNet = Neu::getInstance();

    neuralNet.setNeu(10, "/home/kolya/Desktop/code/2024-misis-practice/dataset/train"
                       , "/home/kolya/Desktop/code/2024-misis-practice/dataset/val/HM"
                       , "/home/kolya/Desktop/code/2024-misis-practice/dataset/val/No_HM");

    int train_res = neuralNet.trainNeu(1, path_to_py);
    if (train_res == 0) {
        std::cout << "Neural network uccessfully trained" << std::endl;
    } else {
        std::cout << "ERROR CODE: " << train_res << std::endl;
    }

//    std::string exam_result = neuralNet.checkNeu("/home/kolya/Desktop/code/2024-misis-practice/dataset/val/HM/download.jpg", path_to_py);
//    std::cout << exam_result << std::endl;

    return 0;
}