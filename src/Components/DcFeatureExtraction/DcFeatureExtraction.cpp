/*!
 * \file
 * \brief
 */

#include <memory>
#include <string>

#include "DcFeatureExtraction.hpp"
#include "Common/Logger.hpp"

namespace Processors {
namespace DcFeatureExtraction {

DcFeatureExtraction::DcFeatureExtraction(const std::string & name) : Base::Component(name)
{
	LOG(LTRACE) << "Hello DcFeatureExtraction\n";
}

DcFeatureExtraction::~DcFeatureExtraction()
{
	LOG(LTRACE) << "Good bye DcFeatureExtraction\n";
}

bool DcFeatureExtraction::onInit()
{
	LOG(LTRACE) << "DcFeatureExtraction::initialize\n";

    // Register handler.
    h_onNewImage.setup(this, &DcFeatureExtraction::onNewImage);
    registerHandler("onNewImage", &h_onNewImage);
    // Register event.
    newImage = registerEvent("newImage");
    // Register data streams.
    registerStream("in_img", &in_img);
    registerStream("out_img", &out_img);

	return true;
}

bool DcFeatureExtraction::onFinish()
{
	LOG(LTRACE) << "DcFeatureExtraction::finish\n";

	return true;
}

bool DcFeatureExtraction::onStep()
{
	LOG(LTRACE) << "DcFeatureExtraction::step\n";
	return true;
}

bool DcFeatureExtraction::onStop()
{
	return true;
}

bool DcFeatureExtraction::onStart()
{
	return true;
}

void DcFeatureExtraction::onNewImage()
{
    LOG(LTRACE) << "DcFeatureExtraction_Processor::onNewImage\n";
    try {
        // Read image from input data stream.
        Mat img = in_img.read();

        // Write image to output data stream.
        out_img.write(img);
       
	// Raise event.
        newImage->raise();
    } catch (...) {
        LOG(LERROR) << "DcFeatureExtraction_Processor::onNewImage failed\n";
    }
}

}//: namespace DcFeatureExtraction
}//: namespace Processors
