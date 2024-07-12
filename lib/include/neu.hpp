#ifndef NEU_HPP
#define NEU_HPP

#include <iostream>
#include <string>
#include <filesystem>
#include <pybind11/pybind11.h>
#include <stdexcept>
//#include <opencv2/opencv.hpp>

namespace neu {

    namespace fs = std::filesystem;
    namespace py = pybind11;

//    void saveImageToDirectory(const cv::Mat& image, const fs::path& directory, const std::string& filename);

    class Neu {
        private:
            fs::path train_, val_, test_, model_path_;
            std::string model_name_;
            size_t epoch_count_;
            int status_{0};
    
            struct Net { // структура, указывающая на сеть, например, вид и имя файла xml или что там может быть
                // int kind;
                //std::string name;
                
                //Net(const int& akind = 0, const std::string& aname = ""):
                //    kind(akind), name(aname)
                //{};

                Net(fs::path entity, fs::path weights);
                fs::path entity_, weights_; // data.pkl and data folder with weights
            };

//            Net net();

        public:
           /**
            * @brief default constructor
            */
            Neu();

            /**
             * @brief set path for neural network to dataset
             * @param ec epoch count
             * @param ptd path to the whole dataset
             */
            //void setNeu(size_t ec, const fs::path& ptd, const std::string& mn = "yolov8n-cls.pt");

            /**
             * @brief set paths for neural network to training dataset and etc
             * @param ec epoch count
             * @param train path to training dataset
             * @param val path to validation dataset
             * @param test path to testing dataset
             */
            void setNeu( size_t ec, const fs::path& train = (fs::current_path() / "train")
                       , const fs::path& val = (fs::current_path() / "val")
                       , const fs::path& test = (fs::current_path() / "test")
                       , const std::string& mn = "yolov8n-cls.pt");

            /**
             * @brief
             * @param info
             * @param img
             * @return
             */
            int trainNeu(); // обучение, info - например 0 - нет, 1- да, img - имя файла, либо каталог с файлами, либо...
//            int trainNeu(int info, const cv::Mat& img);

        std::string checkNeu(const fs::path& path_to_pic);

            /**
             * @brief
             * @param info
             * @param img
             * @return
             */
//            int examNeu(int info, const fs::path& img); // проверка, info - не придумал зачем ))), img - имя файла, либо...

            /**
             * @brief destructor
             */
            ~Neu() = default;
    };
    
} // namespace neu

#endif