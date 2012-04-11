/*!
 * \file
 * \brief
 */

#include <memory>
#include <string>

#include "DcObjectRecognition.hpp"
#include "Common/Logger.hpp"

namespace Processors {
namespace DcObjectRecognition {

DcObjectRecognition::DcObjectRecognition(const std::string & name) : Base::Component(name)
{
	LOG(LTRACE) << "Hello DcObjectRecognition\n";
}

DcObjectRecognition::~DcObjectRecognition()
{
	LOG(LTRACE) << "Good bye DcObjectRecognition\n";
}

bool DcObjectRecognition::onInit()
{
	LOG(LTRACE) << "DcObjectRecognition::initialize\n";

    // Register handler.
    h_onNewImage.setup(this, &DcObjectRecognition::onNewImage);
    registerHandler("onNewImage", &h_onNewImage);
    // Register event.
    newImage = registerEvent("newImage");
    // Register data streams.
    registerStream("in_img", &in_img);
    registerStream("out_img", &out_img);

	return true;
}

bool DcObjectRecognition::onFinish()
{
	LOG(LTRACE) << "DcObjectRecognition::finish\n";

	return true;
}

bool DcObjectRecognition::onStep()
{
	LOG(LTRACE) << "DcObjectRecognition::step\n";
	return true;
}

bool DcObjectRecognition::onStop()
{
	return true;
}

bool DcObjectRecognition::onStart()
{
	return true;
}

void DcObjectRecognition::onNewImage()
{
    LOG(LTRACE) << "DcObjectRecognition_Processor::onNewImage\n";
    try {
        // Read image from input data stream.
        Mat img = in_img.read();

        // Write image to output data stream.
        out_img.write(img);
       
	// Raise event.
        newImage->raise();
    } catch (...) {
        LOG(LERROR) << "DcObjectRecognition_Processor::onNewImage failed\n";
    }
}

}//: namespace DcObjectRecognition
}//: namespace Processors
