/*!
 * \file
 * \brief
 */

#include <memory>
#include <string>
#include <vector> 

#include "DcTest.hpp"
#include "Common/Logger.hpp"

namespace Processors {
namespace DcTest {

using namespace cv;

DcTest::DcTest(const std::string & name) : Base::Component(name)
{
	LOG(LTRACE) << "Hello DcTest\n";
}

DcTest::~DcTest()
{
	LOG(LTRACE) << "Good bye DcTest\n";
}

bool DcTest::onInit()
{
	LOG(LTRACE) << "DcTest::initialize\n";

    // Register handler.
    h_onNewImage.setup(this, &DcTest::onNewImage);
    registerHandler("onNewImage", &h_onNewImage);
    // Register event.
    newImage = registerEvent("newImage");
    // Register data streams.
    registerStream("in_img", &in_img);
    registerStream("out_img", &out_img);

	return true;
}

bool DcTest::onFinish()
{
	LOG(LTRACE) << "DcTest::finish\n";

	return true;
}

bool DcTest::onStep()
{
	LOG(LTRACE) << "DcTest::step\n";
	return true;
}

bool DcTest::onStop()
{
	return true;
}

bool DcTest::onStart()
{
	return true;
}

void DcTest::onNewImage()
{
    LOG(LTRACE) << "DcTest_Processor::onNewImage\n";
    try {
        // Read image from input data stream.
        Mat img = in_img.read();
	Mat img_1, img_2, img_3, img_4, img_5;
	Mat drawing = Mat::zeros(img.size(), CV_8UC3);
	
        // Convert to grayscale
	cvtColor(img, img_1, CV_RGB2GRAY);

	// Threshold, erode & dilate
	cv::threshold(img_1, img_2, 90, 255, CV_THRESH_BINARY);

	cv::Mat element_1(2,2,CV_8U,cv::Scalar(1));
		//cv::Mat element_2(2,2,CV_8U,cv::Scalar(1));

	cv::erode(img_2, img_3, element_1, cv::Point(-1,-1), 1);

	cv::dilate(img_3, img_4, element_1, cv::Point(-1,-1), 1);
		//cv::dilate(img_3, img_4, element_2, cv::Point(-1,-1), 1);

	cvtColor(img_3, img_5, CV_GRAY2BGR);        


	// ContoursDetection {
	std::vector<std::vector<cv::Point> > contours;
	vector<Vec4i> hierarchy;
	vector<Point> approx;
	Moments mm;
	string log;
	float maxx, maxy;
	vector<Point> center;
	vector<Point> anglePoint;
	vector<int> value(5);
	int j;
/*
	for (j=0; j<5; j++)
	{
		value[j] = 0;
	}
*/
	j=0;
	bool noticed = false;

	// Find Contours
	cv::findContours(img_3, contours, hierarchy, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);

	// Select big contours
  	for(int i = 0; i< contours.size(); i++)
     	{
		approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.08, true);
 		if (fabs(contourArea(Mat(approx))) > 800)
            	{
			drawContours(drawing, contours, i, cv::Scalar(255,0,0), 1, 8, hierarchy, 0, Point());			
			mm = moments(Mat(approx), true);
			noticed = false;
			for (int k = 0; k < center.size(); k++)
			{
				//Detect doubles
				if (mm.m10/mm.m00 < center[k].x + 5 && mm.m10/mm.m00 > center[k].x - 5 &&
				mm.m01/mm.m00 < center[k].y + 5 && mm.m01/mm.m00 > center[k].y - 5)
				{
					noticed = true;
				}
			}			
			if (noticed == false)
			{			
				maxx = 0;
				maxy = 0;
				center.push_back(Point(mm.m10/mm.m00, mm.m01/mm.m00));
				for (int k = 0; k < approx.size(); k++)
				{
					if (approx[k].x > maxx)
					{
						maxx = approx[k].x;
						maxy = approx[k].y;
					}
				}	
				anglePoint.push_back(Point(maxx,maxy));						
				value.push_back(0);
				//j++;
			}	
		}     	
	}



	//Select small contours
  	for(int i = 0; i< contours.size(); i++)
     	{
		approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.08, true); 		
		if (fabs(contourArea(Mat(approx))) < 800 && fabs(contourArea(Mat(approx))) > 4)
            	{			
			drawContours(drawing, contours, i, cv::Scalar(0,255,0), 1, 8, hierarchy, 0, Point());
			mm = moments(Mat(approx), true);
			for (int k = 0; k < center.size(); k++)
			{
				if (mm.m10/mm.m00 < center[k].x + 20 && mm.m10/mm.m00 > center[k].x - 20 &&
				mm.m01/mm.m00 < center[k].y + 20 && mm.m01/mm.m00 > center[k].y - 20)
				{
					value[k]++;
				}
			}
							
		}     	
	}

	// Draw circles
	for(int i = 0; i<center.size(); i++)
     	{
		circle(img, center[i], 20, cv::Scalar(0,0,255), 2, 8, 0);
	}
	
	// Draw values
	for (j=0; j<center.size(); j++)
	{
	string tmp;
	sprintf((char*)tmp.c_str(), "%d", (value[j]));
	string str = tmp.c_str();

	cv::putText(img, str, Point(center[j].x-8,center[j].y+8), FONT_HERSHEY_DUPLEX, 0.8, cv::Scalar(0,0,255));
	}

	//Draw lines
	for(int i = 0; i<center.size(); i++)
	{
		line(img, Point(center[i].x,center[i].y), Point(anglePoint[i].x,anglePoint[i].y), cv::Scalar(0,255,0), 1, 8, 0);		
	}

	//Print log
	log = "log: ";
	string tmp, str;

	sprintf((char*)tmp.c_str(), "%d", (contours.size()));
	log = log + "detected_contours: " + tmp.c_str() + "; ";

	sprintf((char*)tmp.c_str(), "%d", (center.size()));
	log = log + "detected_dices: " + tmp.c_str() + "; ";
/*		
	cv::putText(img, log, cv::Point(10,20), FONT_HERSHEY_SIMPLEX, 0.4, cv::Scalar(0,0,255));
	for (j=0; j<; j++)
	{
		log = "x:";		
		sprintf((char*)tmp.c_str(), "%d", (center[j].x));
		log = log + tmp.c_str() + " y:";
		sprintf((char*)tmp.c_str(), "%d", (center[j].y));
		log = log + tmp.c_str() + " value:";
		sprintf((char*)tmp.c_str(), "%d", (value[j]));
		log = log + tmp.c_str() + ";";
		cv::putText(img, log, cv::Point(10,(j+1)*20+20), FONT_HERSHEY_SIMPLEX, 0.4, cv::Scalar(0,0,255));
	}

*/
        // Write image to output data stream.
        out_img.write(img_2);
       
	// Raise event.
        newImage->raise();

    } catch (...) {
        LOG(LERROR) << "DcTest_Processor::onNewImage failed\n";
    }
}

}//: namespace DcTest
}//: namespace Processors
