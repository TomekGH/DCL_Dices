/*!
 * \file
 * \brief
 */

#include <memory>
#include <string>

#include "DcPresentation.hpp"
#include "Common/Logger.hpp"

namespace Processors {
namespace DcPresentation {

DcPresentation::DcPresentation(const std::string & name) : Base::Component(name)
{
	LOG(LTRACE) << "Hello DcPresentation\n";
}

DcPresentation::~DcPresentation()
{
	LOG(LTRACE) << "Good bye DcPresentation\n";
}

bool DcPresentation::onInit()
{
	LOG(LTRACE) << "DcPresentation::initialize\n";

	// Register handler.
	h_onNewDices.setup(this, &DcPresentation::onNewDices);
	registerHandler("onNewDices", &h_onNewDices);
	// Register event.
	newImage = registerEvent("newImage");
	// Register data streams.
	registerStream("in_img", &in_img);
	registerStream("in_dices", &in_dices);
	registerStream("out_img", &out_img);

	return true;
}

bool DcPresentation::onFinish()
{
	LOG(LTRACE) << "DcPresentation::finish\n";

	return true;
}

bool DcPresentation::onStep()
{
	LOG(LTRACE) << "DcPresentation::step\n";
	return true;
}

bool DcPresentation::onStop()
{
	return true;
}

bool DcPresentation::onStart()
{
	return true;
}

void DcPresentation::onNewDices()
{
	// Read image from input data stream.
        Mat img = in_img.read();
	Mat out = img.clone();
	
	Types::Dices dices = in_dices.read();

	string tmp, str;
	double x, y;

	// Draw circles
	for(int i = 0; i<dices.position.size(); i++)
     	{
		circle(out, dices.position[i], 25, cv::Scalar(0,255,0), 2, 8, 0);
	}
	
	// Draw angles
	for (int i = 0; i<dices.angle.size(); i++)
	{


	sprintf((char*)tmp.c_str(), "%f", (dices.angle[i]));
	str = tmp.c_str();

	line(out, Point(dices.position[i].x,dices.position[i].y), Point(dices.position[i].x+(25*cos(dices.angle[i])),dices.position[i].y+(25*sin(dices.angle[i]))), cv::Scalar(0,255,0), 1, 8, 0);
	}


	// Draw values
	for (int i = 0; i<dices.value.size(); i++)
	{
	sprintf((char*)tmp.c_str(), "%d", (dices.value[i]));
	str = tmp.c_str();

	cv::putText(out, str, Point(dices.position[i].x-8,dices.position[i].y+8), FONT_HERSHEY_DUPLEX, 0.8, cv::Scalar(0,0,255));
	}



	sprintf((char*)tmp.c_str(), "%d", (dices.position.size()));
	str = tmp.c_str();
	cv::putText(out, str, Point(50,50), FONT_HERSHEY_DUPLEX, 0.4, cv::Scalar(0,0,255));

	// Write image to output data stream.
	out_img.write(out); 

	// Raise event.
	newImage->raise();
}
}//: namespace DcPresentation
}//: namespace Processors
