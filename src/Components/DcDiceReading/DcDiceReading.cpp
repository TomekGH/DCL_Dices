/*!
 * \file
 * \brief
 */

#include <memory>
#include <string>

#include "DcDiceReading.hpp"
#include "Common/Logger.hpp"

namespace Processors {
namespace DcDiceReading {

DcDiceReading::DcDiceReading(const std::string & name) : Base::Component(name)
{
	LOG(LTRACE) << "Hello DcDiceReading\n";
}

DcDiceReading::~DcDiceReading()
{
	LOG(LTRACE) << "Good bye DcDiceReading\n";
}

bool DcDiceReading::onInit()
{
	LOG(LTRACE) << "DcDiceReading::initialize\n";

	// Register data streams, events and event handlers HERE!
	h_onNewAngle.setup(this, &DcDiceReading::onNewAngle);
	registerHandler("onNewAngle", &h_onNewAngle);

	readingReady = registerEvent("readingReady");

	registerStream("in_angle", &in_angle);
	registerStream("in_dots", &in_dots);
	registerStream("out_reading", &out_reading);

	return true;
}

bool DcDiceReading::onFinish()
{
	LOG(LTRACE) << "DcDiceReading::finish\n";

	return true;
}

bool DcDiceReading::onStep()
{
	LOG(LTRACE) << "DcDiceReading::step\n";
	return true;
}

bool DcDiceReading::onStop()
{
	return true;
}

bool DcDiceReading::onStart()
{
	return true;
}

void DcDiceReading::onNewAngle()
{
	try {	
		double angle = in_angle.read();
		int dots = in_dots.read();
		//int dots = 0;

		Types::Mrrocpp_Proxy::DiceReading reading;
		reading.angle = angle;
		reading.dots = dots;

		LOG(LWARNING) << "ANGLE:" << angle << endl;
		LOG(LWARNING) << "DOTS:" << dots << endl;

		out_reading.write(reading);

		readingReady->raise();
	} catch (exception& ex) {
        	LOG(LERROR) << "DcDiceReading::onNewContours \n" << ex.what() << endl;
    	}
}

}//: namespace DcDiceReading
}//: namespace Processors
