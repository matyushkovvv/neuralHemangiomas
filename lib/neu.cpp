#include <neu.hpp>

namespace neu {

    using namespace py::literals;

    PYBIND11_EMBEDDED_MODULE(neu, m) {
        m.def("train_model", [](const std::string& data_path, const std::string& model_name = "yolov8n-cls.pt", int epochs = 10) {
            py::module_ ultralytics = py::module_::import("ultralytics");
            py::object YOLO = ultralytics.attr("YOLO");
            py::object model = YOLO(model_name);

            py::object result = model.attr("train")(
                    "data"_a = data_path,
                    "epochs"_a = epochs
            );

            py::print(result);

            std::string model_path = "yolov8n-cls-training.pt";
            model.attr("save")(model_path);

            return model_path;
        });

        m.def("classify_image", [](const std::string& model_path, const std::string& image_path) {
            py::module_ ultralytics = py::module_::import("ultralytics");
            py::object YOLO = ultralytics.attr("YOLO");
            py::object model = YOLO(model_path);

            cv::Mat image = cv::imread(image_path);
            if (image.empty()) {
                throw std::runtime_error("Image not found: " + image_path);
            }

            py::object results = model(image);

            return results;
        });
    }

    Neu::Neu(): train_(fs::current_path() / "train")
              , val_(fs::current_path() / "val")
              , test_(fs::current_path() / "test")
              , model_name_("yolov8n-cls.pt")
              , epoch_count_(10), guard_()
    {
//        py::exec(R"(
//            import sys
//            import os
//            pyhome = os.path.join(os.getcwd(), 'pyhome', 'venv', 'lib', 'python3.11', 'site-packages')
//            print(pyhome)
//            if pyhome not in sys.path:
//                sys.path.append(pyhome)
//            #import math  # Ensure 'math' module is loaded
//        )");
    }

    Neu::Net::Net(fs::path entity, fs::path weights):
        entity_(std::move(entity)), weights_(std::move(weights))
    {}

    Neu& Neu::getInstance() {
        static Neu instance;
        return instance;
    }

    /*void Neu::setNeu(size_t ec, const fs::path& ptd, const std::string& mn) {
        if (!fs::exists(ptd) || !fs::is_directory(ptd)) {
            throw std::invalid_argument("Provided path is incorrect");
        }

        epoch_count_ = ec;
        model_name_ = mn;
        train_ = ptd / "train";
        val_ = ptd / "val";
        test_ = ptd / "test";
    }*/

    void Neu::setNeu( size_t ec, const fs::path& train
                    , const fs::path& val
                    , const fs::path& test
                    , const std::string& mn) {
        if (!fs::exists(train) || !fs::is_directory(train)) {
            throw std::invalid_argument("Provided path to train directory is incorrect");
//            std::cerr << "Provided path to train directory is incorrect\n";
        } if (!fs::exists(val) || !fs::is_directory(val)) {
            throw std::invalid_argument("Provided path to val directory is incorrect");
//            std::cerr << "Provided path to val directory is incorrect\n";
        } if (!fs::exists(test) || !fs::is_directory(test)) {
            throw std::invalid_argument("Provided path to test directory is incorrect");
//            std::cerr << "Provided path to test directory is incorrect\n";
        }

        epoch_count_ = ec;
        train_ = train;
        val_ = val;
        test_ = test;
        model_name_ = mn;
    }

    int Neu::trainNeu(int info, const fs::path& path_to_neunet_module) {
        try {
            py::module neu = py::module::import("neu");
            model_path_ = neu.attr("train_model")((train_ / (info ? "HM" : "No_HM")).string(), "yolov8n-cls.pt", 10).cast<std::string>();


            //std::cout << "Model trained and saved at: " << model_path_ << std::endl;
            return 0;
        } catch (const py::error_already_set& e) {
            std::cerr << "Python error: " << e.what() << std::endl;
            return -1;
        } catch (const std::exception& ex) {
            std::cerr << ex.what() << std::endl;
            return 59;
        } catch (...) {
            return -100;
        }
    }

    std::string Neu::checkNeu(const fs::path& path_to_pic, const fs::path& path_to_neunet_module) {
        try {

            py::module neu = py::module::import("neu");
            py::object result = neu.attr("classify_image")(
                    path_to_neunet_module.string(),
                    path_to_pic.string()
            );

            py::print(result);
            return py::str(result);
        } catch (const py::error_already_set& e) {
            return "Python error: " + static_cast<std::string>(e.what());
        }
    }

//    int Neu::trainNeu(int info, const cv::Mat& img) {
//
//    }

    /*int Neu::examNeu(int info, const fs::path& img) {
        int res = 0;
        if (info) {
            // ... основная часть
            res = 1; // здесь результат основной части
        }
    
    
        // вывод именно такой, чтобы его взял backend
        std::cout << "results:exam:" << res << std::endl;

        std::cout << "Neu: info - " << info << ", image - " << img << std::endl;
    
        return 0;
    }*/

    /*void saveImageToDirectory(const cv::Mat& image, const fs::path& directory, const std::string& filename) {
        if (!fs::exists(directory)) {
            throw std::invalid_argument("Directory does not exist");
        }

        std::filesystem::path filePath = directory / filename;

        if (cv::imwrite(filePath.string(), image)) {
            std::cout << "Image saved successfully at: " << filePath << std::endl;
        } else {
            std::cerr << "Failed to save the image at: " << filePath << std::endl;
        }

    }*/

} // namespace neu
