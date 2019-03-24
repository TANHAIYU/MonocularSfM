﻿#include <iostream>
#include <opencv2/opencv.hpp>

#include "Common/Timer.h"
#include "Database/Database.h"
#include "Feature/FeatureExtraction.h"
using namespace std;
using namespace cv;
using namespace MonocularSfM;

int main(int argc, char** argv)
{
    // step1 : 提取特征, 并存储到数据库

    if(argc != 2)
    {
        std::cout << "You need specify the YAML file path!" << std::endl;
        exit(-1);
    }


    cv::FileStorage fs(argv[1], FileStorage::READ);

    if(!fs.isOpened())
    {
        std::cout << "YAML file : " << argv[1] << " can't not open!" << std::endl;
        exit(-1);
    }

    // 图片所在的文件夹
    string images_path;
    string database_path;

    int max_image_size = 3200;
    int num_features = 8024;

    fs["images_path"] >> images_path;
    fs["database_path"] >> database_path;
    fs["SIFTextractor.max_image_size"] >> max_image_size;
    fs["SIFTextractor.num_features"] >> num_features;



    Timer timer;
    timer.Start();

    cv::Ptr<FeatureExtractor> extractor =
            cv::Ptr<FeatureExtractorCPU>(new FeatureExtractorCPU(database_path, images_path, max_image_size, num_features));
    extractor->RunExtraction();

    timer.PrintMinutes();



    return 0;
}
