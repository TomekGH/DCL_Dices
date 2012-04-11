/*!
 * \file
 * \brief
 */

#include <memory>
#include <string>

#include "DcImageProcessing.hpp"
#include "Common/Logger.hpp"

namespace Processors {
namespace DcImageProcessing {

DcImageProcessing::DcImageProcessing(const std::string & name) : Base::Component(name)
{
	LOG(LTRACE) << "Hello DcImageProcessing\n";
}

DcImageProcessing::~DcImageProcessing()
{
	LOG(LTRACE) << "Good bye DcImageProcessing\n";
}

bool DcImageProcessing::onInit()
{
	LOG(LTRACE) << "DcImageProcessing::initialize\n";

    // Register handler.
    h_onNewImage.setup(this, &DcImageProcessing::onNewImage);
    registerHandler("onNewImage", &h_onNewImage);
    // Register event.
    newImage = registerEvent("newImage");
    // Register data streams.
    registerStream("in_img", &in_img);
    registerStream("out_img", &out_img);

	return true;
}

bool DcImageProcessing::onFinish()
{
	LOG(LTRACE) << "DcImageProcessing::finish\n";

	return true;
}

bool DcImageProcessing::onStep()
{
	LOG(LTRACE) << "DcImageProcessing::step\n";
	return true;
}

bool DcImageProcessing::onStop()
{
	return true;
}

bool DcImageProcessing::onStart()
{
	return true;
}

void DcImageProcessing::onNewImage()
{
    LOG(LTRACE) << "DcImageProcessing_Processor::onNewImage\n";
    try {
        // Read image from input data stream.
        Mat img = in_img.read();

	Mat img_1, img_2, img_3, img_4, img_5;
	Mat drawing = Mat::zeros(img.size(), CV_8UC3);
	
        // Convert to grayscale
	//cvtColor(img, img_1, CV_RGB2GRAY);

	// Threshold, erode & dilate
	cv::threshold(img, img_2, 90, 255, CV_THRESH_BINARY);

	cv::Mat element_1(2,2,CV_8U,cv::Scalar(1));
		//cv::Mat element_2(2,2,CV_8U,cv::Scalar(1));

	cv::erode(img_2, img_3, element_1, cv::Point(-1,-1), 1);

	//cv::dilate(img_3, img_4, element_1, cv::Point(-1,-1), 1);
		//cv::dilate(img_3, img_4, element_2, cv::Point(-1,-1), 1);

	//cvtColor(img_3, img_5, CV_GRAY2BGR);  


        // Write image to output data stream.
        out_img.write(img_3);
       
	// Raise event.
        newImage->raise();
    } catch (...) {
        LOG(LERROR) << "DcImageProcessing_Processor::onNewImage failed\n";
    }
}

}//: namespace DcImageProcessing
}//: namespace Processors
