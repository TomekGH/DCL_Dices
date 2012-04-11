/*!
 * \file
 * \brief
 */

#include <memory>
#include <string>
#include <vector> 

#include "CvFindContours.hpp"
#include "Common/Logger.hpp"

namespace Processors {
namespace CvFindContours {

using namespace cv;

CvFindContours::CvFindContours(const std::string & name) : Base::Component(name)
{
	LOG(LTRACE) << "Hello CvFindContours\n";
}

CvFindContours::~CvFindContours()
{
	LOG(LTRACE) << "Good bye CvFindContours\n";
}

bool CvFindContours::onInit()
{
	LOG(LTRACE) << "CvFindContours::initialize\n";

    // Register handler.
    h_onNewImage.setup(this, &CvFindContours::onNewImage);
    registerHandler("onNewImage", &h_onNewImage);
    // Register event.
    newContours = registerEvent("newContours");
    newImage = registerEvent("newImage");
    // Register data streams.
    registerStream("in_img", &in_img);
    registerStream("out_contours", &out_contours);
    registerStream("out_img", &out_img);

	return true;
}

bool CvFindContours::onFinish()
{
	LOG(LTRACE) << "CvFindContours::finish\n";

	return true;
}

bool CvFindContours::onStep()
{
	LOG(LTRACE) << "CvFindContours::step\n";
	return true;
}

bool CvFindContours::onStop()
{
	return true;
}

bool CvFindContours::onStart()
{
	return true;
}

void CvFindContours::onNewImage()
{
    LOG(LTRACE) << "CvFindContours_Processor::onNewImage\n";
    try {
        // Read image from input data stream.
        Mat img = in_img.read();
	Mat cpy = img.clone();
	Mat drawing = Mat::zeros(img.size(), CV_8UC3);

	// ContoursDetection {
	vector<vector<Point> > contours;
	vector<vector<Point> > out;
	vector<Vec4i> hierarchy;
	vector<Point> approx;

	// Find Contours
	cv::findContours(cpy, contours, hierarchy, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);

	// Select contours
  	for(int i = 0; i< contours.size(); i++)
     	{
		approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.08, true);
 		if (fabs(contourArea(Mat(approx))) > props.min && fabs(contourArea(Mat(approx))) < props.max)
            	{
			drawContours(drawing, contours, i, cv::Scalar(props.colorR,props.colorG,props.colorB), 1, 8, hierarchy, 0, Point());			
			out.push_back(contours[i]);
		}     	
	}



        // Write image to output data stream.
        out_contours.write(out);
	out_img.write(drawing);       
	
	// Raise event.
        newContours->raise();
	newImage->raise();

    } catch (...) {
        LOG(LERROR) << "CvFindContours_Processor::onNewImage failed\n";
    }
}


}//: namespace CvFindContours
}//: namespace Processors
