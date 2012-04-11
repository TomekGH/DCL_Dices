/*!
 * \file
 * \brief
 */

#include <memory>
#include <string>

#include "DcRecognition.hpp"
#include "Common/Logger.hpp"

namespace Processors {
namespace DcRecognition {

DcRecognition::DcRecognition(const std::string & name) : Base::Component(name)
{
	LOG(LTRACE) << "Hello DcRecognition\n";
}

DcRecognition::~DcRecognition()
{
	LOG(LTRACE) << "Good bye DcRecognition\n";
}

bool DcRecognition::onInit()
{
	LOG(LTRACE) << "DcRecognition::initialize\n";

	// Register handler.
	h_onNewContours.setup(this, &DcRecognition::onNewContours);
	registerHandler("onNewContours", &h_onNewContours);
	// Register event.
	newDices = registerEvent("newDices");
	// Register data streams.
	registerStream("in_contours_big", &in_contours_big);
	registerStream("in_contours_small", &in_contours_small);
	registerStream("out_dices", &out_dices);

	return true;
}

bool DcRecognition::onFinish()
{
	LOG(LTRACE) << "DcRecognition::finish\n";

	return true;
}

bool DcRecognition::onStep()
{
	LOG(LTRACE) << "DcRecognition::step\n";
	return true;
}

bool DcRecognition::onStop()
{
	return true;
}

bool DcRecognition::onStart()
{
	return true;
}

void DcRecognition::onNewContours()
{
    LOG(LTRACE) << "DcRecognition_Processor::onNewContours\n";
    try {
        // Read from input data stream.
        vector<vector<Point> > bigContours = in_contours_big.read();
	vector<vector<Point> > smallContours = in_contours_small.read();

	Types::Dices dices;
	
	vector<Point> approx;
	Moments mm;
	float maxx, maxy;
	bool noticed = false;

	//Find dices
	for(int i = 0; i< bigContours.size(); i++)
	{
		approxPolyDP(Mat(bigContours[i]), approx, arcLength(Mat(bigContours[i]), true)*0.08, true);
		mm = moments(Mat(approx), true);
		noticed = false;
		for (int k = 0; k < dices.position.size(); k++)
			{
				//Detect doubles
				if (mm.m10/mm.m00 < dices.position[k].x + 5 && mm.m10/mm.m00 > dices.position[k].x - 5 &&
				mm.m01/mm.m00 < dices.position[k].y + 5 && mm.m01/mm.m00 > dices.position[k].y - 5)
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
				//dices.angle.push_back(atan((mm.m01/mm.m00)-maxy/(mm.m10/mm.m00)-maxx) * 180/3.14159265);
				dices.angle.push_back( atan((maxy-(mm.m01/mm.m00))/(maxx-(mm.m10/mm.m00))));
				//Initiate value
				dices.value.push_back(0);
				//j++;
			}
	}

	//Count dots
	for(int i = 0; i< smallContours.size(); i++)
	{
		approxPolyDP(Mat(smallContours[i]), approx, arcLength(Mat(smallContours[i]), true)*0.08, true);
		mm = moments(Mat(approx), true);
		for (int k = 0; k < dices.position.size(); k++)
		{
			if (mm.m10/mm.m00 < dices.position[k].x + 20 && mm.m10/mm.m00 > dices.position[k].x - 20 &&
			mm.m01/mm.m00 < dices.position[k].y + 20 && mm.m01/mm.m00 > dices.position[k].y - 20)
			{
				dices.value[k]++;
			}
		}
	}
	


        // Write to output data stream.
        out_dices.write(dices);      
	
	// Raise event.
        newDices->raise();

    } catch (...) {
        LOG(LERROR) << "CvFindContours_Processor::onNewContours failed\n";
    }	
}

}//: namespace DcRecognition
}//: namespace Processors
