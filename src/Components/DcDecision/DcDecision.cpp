/*!
 * \file
 * \brief
 */

#include <memory>
#include <string>

#include "DcDecision.hpp"
#include "Common/Logger.hpp"

#include "Types/Dices.hpp"

namespace Processors {
namespace DcDecision {

DcDecision::DcDecision(const std::string & name) : Base::Component(name)
{
	LOG(LTRACE) << "Hello DcDecision\n";
}

DcDecision::~DcDecision()
{
	LOG(LTRACE) << "Good bye DcDecision\n";
}

bool DcDecision::onInit()
{
	LOG(LTRACE) << "DcDecision::initialize\n";

	    // Register handler.
	    h_onNewContours.setup(this, &DcDecision::onNewContours);
	    registerHandler("onNewContours", &h_onNewContours);
	    // Register event.
	    newHomogMatrix = registerEvent("newHomogMatrix");
            newImage = registerEvent("newImage");
            newAngle = registerEvent("newAngle");
	    // Register data streams.
	    registerStream("in_img", &in_img);
	    registerStream("in_contours", &in_contours);
	    registerStream("out_img", &out_img);
	    registerStream("out_homogMatrix", &out_homogMatrix);
	    registerStream("out_angle", &out_angle);	

	return true;
}

bool DcDecision::onFinish()
{
	LOG(LTRACE) << "DcDecision::finish\n";

	return true;
}

bool DcDecision::onStep()
{
	LOG(LTRACE) << "DcDecision::step\n";
	return true;
}

bool DcDecision::onStop()
{
	return true;
}

bool DcDecision::onStart()
{
	return true;
}

void DcDecision::onNewContours()
{
LOG(LTRACE) << "DcDecision::onNewContours\n";
	   
	int err = 0;
	try {

	// Read image from input data stream.
        Mat img = in_img.read();

	Mat drawing = Mat::zeros(img.size(), CV_8UC3);

	vector<vector<Point> > contours = in_contours.read();

	Types::Dices dices;
	
	vector<Point> approx;
	vector<Vec4i> hierarchy;
	Moments mm;
	float maxx, maxy;
	bool noticed = false;
	
	err++;

	//Find dices
	for(int i = 0; i< contours.size(); i++)
	{
		approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.08, true);
		mm = moments(Mat(approx), true);
		noticed = false;
		for (int k = 0; k < dices.position.size(); k++)
		{
			//Detect doubles
			if (mm.m10/mm.m00 < dices.position[k].x + 10 && mm.m10/mm.m00 > dices.position[k].x - 10 &&
			mm.m01/mm.m00 < dices.position[k].y + 10 && mm.m01/mm.m00 > dices.position[k].y - 10)
			{
				noticed = true;
			}
		}			
		if (noticed == false)
		{			
			//Add position
			dices.position.push_back(Point(mm.m10/mm.m00, mm.m01/mm.m00));
			//Calculate angle				
			maxx = 0;
			maxy = 0;
			for (int k = 0; k < approx.size(); k++)
			{
				if (approx[k].x > maxx)
				{
					maxx = approx[k].x;
					maxy = approx[k].y;
				}
			}

			//Add angle
			dices.angle.push_back( atan((maxy-(mm.m01/mm.m00))/(maxx-(mm.m10/mm.m00))));
			
		}
	}
	
	err++;

	//Draw potential map
	for(int i = 0; i< contours.size(); i++)
     	{
		drawContours(drawing, contours, i, cv::Scalar(0.0,0.0,255.0), -1, 8, hierarchy, 0, Point());			
	}
	
	Mat cpy = Mat::zeros(img.size(), CV_8UC3);
	cpy = drawing.clone();
	Mat result = Mat::zeros(img.size(), CV_8UC3);
	Mat layer;

	double dilation_size = 3.0;
	Mat element = getStructuringElement( MORPH_ELLIPSE, Size(2*dilation_size +1, 2*dilation_size+1), Point (dilation_size, dilation_size) );

	for(int i=0; i<6; i++)
	{
		dilate(drawing, layer, element, Point(-1,-1), i*2, BORDER_CONSTANT, morphologyDefaultBorderValue() );
		double alpha = 0.5/(i+1.0);
		double beta = 1.0;
		addWeighted(layer, alpha, cpy, beta, 0.0, cpy);
	}
	
	err++;

	//Select object
	bool found = false;
	cv::Point s_position;
	double min_val = 0.0;
	s_position.x = 321.0001;
	s_position.y = 241.0001;
	int s_value = 0;
	double s_angle = -3.14159265/4.0;

	for(int i = 0; i< dices.position.size(); i++)
     	{
		if (dices.position[i].y + dices.position[i].x/10.0 >= min_val)
		{
			min_val = dices.position[i].y + dices.position[i].x/10.0;
			s_position.x = dices.position[i].x;
			s_position.y = dices.position[i].y;
			s_angle = dices.angle[i];
			found = true;
		}
	}
	
	err++;

	//Calculate angle

	int gripper = 50;
	double map_value = 500000.0;
	double new_value = 0.0;

	double perfect_angle = s_angle + 3.14159265/4.0; 

	//LOG(LWARNING) << "S_ANGLE: " << s_angle << endl;	
	//LOG(LWARNING) << "P_ANGLE: " << perfect_angle << endl;
	double a = perfect_angle;

	map_value = 
		cpy.at<cv::Vec3b>(Point(s_position.x+(gripper*cos(a)), s_position.y+(gripper*sin(a))))[2]+
		cpy.at<cv::Vec3b>(Point(s_position.x+(gripper*cos(a+0.3)), s_position.y+(gripper*sin(a+0.3))))[2]+
		cpy.at<cv::Vec3b>(Point(s_position.x+(gripper*cos(a-0.3)), s_position.y+(gripper*sin(a-0.3))))[2]+
		cpy.at<cv::Vec3b>(Point(s_position.x+(gripper*cos(3.14+a)), s_position.y+(gripper*sin(3.14+a))))[2]+
		cpy.at<cv::Vec3b>(Point(s_position.x+(gripper*cos(3.14+a+0.3)), s_position.y+(gripper*sin(3.14+a+0.3))))[2]+
		cpy.at<cv::Vec3b>(Point(s_position.x+(gripper*cos(3.14+a-0.3)), s_position.y+(gripper*sin(3.14+a-0.3))))[2];		
		
	map_value = map_value - 50;
	a = perfect_angle + 3.14159265/2.0;

	//LOG(LWARNING) << "A_ANGLE: " << a << endl;
	new_value = 
		cpy.at<cv::Vec3b>(Point(s_position.x+(gripper*cos(a)), s_position.y+(gripper*sin(a))))[2]+
		cpy.at<cv::Vec3b>(Point(s_position.x+(gripper*cos(a+0.3)), s_position.y+(gripper*sin(a+0.3))))[2]+
		cpy.at<cv::Vec3b>(Point(s_position.x+(gripper*cos(a-0.3)), s_position.y+(gripper*sin(a-0.3))))[2]+
		cpy.at<cv::Vec3b>(Point(s_position.x+(gripper*cos(3.14+a)), s_position.y+(gripper*sin(3.14+a))))[2]+
		cpy.at<cv::Vec3b>(Point(s_position.x+(gripper*cos(3.14+a+0.3)), s_position.y+(gripper*sin(3.14+a+0.3))))[2]+
		cpy.at<cv::Vec3b>(Point(s_position.x+(gripper*cos(3.14+a-0.3)), s_position.y+(gripper*sin(3.14+a-0.3))))[2];		
		
	new_value = new_value - 50;
	if (new_value < map_value)
	{
		map_value = new_value;
		perfect_angle = a;
	}

	if (map_value > 0) {
		for (a=0.0; a<3.28; a=a+0.02)
		{
			new_value = 
				cpy.at<cv::Vec3b>(Point(s_position.x+(gripper*cos(a)), s_position.y+(gripper*sin(a))))[2]+
				cpy.at<cv::Vec3b>(Point(s_position.x+(gripper*cos(a+0.3)), s_position.y+(gripper*sin(a+0.3))))[2]+
				cpy.at<cv::Vec3b>(Point(s_position.x+(gripper*cos(a-0.3)), s_position.y+(gripper*sin(a-0.3))))[2]+
				cpy.at<cv::Vec3b>(Point(s_position.x+(gripper*cos(3.14+a)), s_position.y+(gripper*sin(3.14+a))))[2]+
				cpy.at<cv::Vec3b>(Point(s_position.x+(gripper*cos(3.14+a+0.3)), s_position.y+(gripper*sin(3.14+a+0.3))))[2]+
				cpy.at<cv::Vec3b>(Point(s_position.x+(gripper*cos(3.14+a-0.3)), s_position.y+(gripper*sin(3.14+a-0.3))))[2];		
		
			if (new_value < map_value)
			{
				map_value = new_value;
				perfect_angle = a;
			}
		}
	}

	LOG(LWARNING) << "MAP: " << map_value << endl;

	//Draw lines
	for(int i = 0; i< dices.position.size(); i++)
     	{
		circle(cpy, dices.position[i], gripper, cv::Scalar(255,255,255), 1, 8, 0);
	}

	

	circle(cpy, Point(s_position.x+(gripper*cos(perfect_angle)), s_position.y+(gripper*sin(perfect_angle))), 2, cv::Scalar(255,255,255), 1, 8, 0);
	circle(cpy, Point(s_position.x+(gripper*cos(perfect_angle+0.3)), s_position.y+(gripper*sin(perfect_angle+0.3))), 2, cv::Scalar(255,255,255), 1, 8, 0);
	circle(cpy, Point(s_position.x+(gripper*cos(perfect_angle-0.3)), s_position.y+(gripper*sin(perfect_angle-0.3))), 2, cv::Scalar(255,255,255), 1, 8, 0);
	
	circle(cpy, Point(s_position.x+(gripper*cos(3.14+perfect_angle)), s_position.y+(gripper*sin(3.14+perfect_angle))), 2, cv::Scalar(255,255,255), 1, 8, 0);
	circle(cpy, Point(s_position.x+(gripper*cos(3.14+perfect_angle+0.3)), s_position.y+(gripper*sin(3.14+perfect_angle+0.3))), 2, cv::Scalar(255,255,255), 1, 8, 0);
	circle(cpy, Point(s_position.x+(gripper*cos(3.14+perfect_angle-0.3)), s_position.y+(gripper*sin(3.14+perfect_angle-0.3))), 2, cv::Scalar(255,255,255), 1, 8, 0);

	//Prepare Matrix
	Types::HomogMatrix hm;

	if (found) {
		if (s_position.x == 320.0) 
			s_position.x = s_position.x + 0.001;
		if (s_position.y == 240.0) 
			s_position.y = s_position.y + 0.001;
		hm.elements[0][3] = -(s_position.x-320.0)/640.0;
		hm.elements[1][3] = -(s_position.y-240.0)/480.0;
		hm.elements[2][3] = 0.0;
	}
	else {
		hm.elements[0][3] = 0.0;
		hm.elements[1][3] = 0.0;
		hm.elements[2][3] = 0.0;
	}

	LOG(LWARNING) << "POS_X: " << hm.elements[0][3] << endl;	
	LOG(LWARNING) << "POS_Y: " << hm.elements[1][3] << endl;

	err++;

	//Write outputs
	out_img.write(cpy);       
	out_homogMatrix.write(hm);
	out_angle.write(perfect_angle);

	err++;

	// Raise event.
	newImage->raise();
	newAngle->raise();
	newHomogMatrix->raise();
	err++;


    } catch (exception& ex) {
        LOG(LERROR) << "DcDecision::onNewContours \n" << err << " - " << ex.what() << endl;
    }
}

}//: namespace DcDecision
}//: namespace Processors
