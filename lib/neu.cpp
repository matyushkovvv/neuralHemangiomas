#include <neu.hpp>

namespace neu {

    Neu::Neu(): train_(fs::current_path() / "train")
              , val_(fs::current_path() / "val")
              , test_(fs::current_path() / "test")
              , model_name_("yolov8n-cls.pt"), epoch_count_(10)
    {}

    Neu::Net::Net(fs::path entity, fs::path weights):
        entity_(std::move(entity)), weights_(std::move(weights))
    {}

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
        } else if (!fs::exists(val) || !fs::is_directory(val)) {
            throw std::invalid_argument("Provided path to val directory is incorrect");
        } else if (!fs::exists(test) || !fs::is_directory(test)) {
            throw std::invalid_argument("Provided path to test directory is incorrect");
        }

        epoch_count_ = ec;
        train_ = train;
        val_ = val;
        test_ = test;
        model_name_ = mn;
    }

    int Neu::trainNeu() {
        try {
            py::module train_module = py::module::import("neu");
            py::object train_model = train_module.attr("train_model");
            model_path_ = train_model(train_.string(), model_name_, epoch_count_).cast<fs::path>();

            //std::cout << "Model trained and saved at: " << model_path << std::endl;
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

    std::string Neu::checkNeu(const fs::path& path_to_pic) {
        try {
            py::module classify_module = py::module::import("neu");
            py::object classify_image = classify_module.attr("classify_image");
            py::object result = classify_image(model_path_.string(), path_to_pic.string());

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
