/*!
 * \file
 * \brief
 */

#ifndef DCOBJECTRECOGNITION_HPP_
#define DCOBJECTRECOGNITION_HPP_

#include "Component_Aux.hpp"
#include "Component.hpp"
#include "Panel_Empty.hpp"
#include "DataStream.hpp"

#include <cv.h>

namespace Processors {
namespace DcObjectRecognition {

using namespace cv;

/*!
 * \class DcObjectRecognition
 * \brief DcObjectRecognition processor class.
 */
class DcObjectRecognition: public Base::Component
{
public:
	/*!
	 * Constructor.
	 */
	DcObjectRecognition(const std::string & name = "");

	/*!
	 * Destructor
	 */
	virtual ~DcObjectRecognition();


protected:

    // Input data stream
    Base::DataStreamIn <Mat> in_img;

    // Output data stream - processed image
    Base::DataStreamOut <Mat> out_img;

    // Event handler function.
    void onNewImage();

    // Event handler.
    Base::EventHandler <DcObjectRecognition> h_onNewImage;

    // Event emited after the image is processed.
    Base::Event * newImage;

	/*!
	 * Connects source to given device.
	 */
	bool onInit();

	/*!
	 * Disconnect source from device, closes streams, etc.
	 */
	bool onFinish();

	/*!
	 * Retrieves data from device.
	 */
	bool onStep();

	/*!
	 * Start component
	 */
	bool onStart();

	/*!
	 * Stop component
	 */
	bool onStop();

};

}//: namespace DcObjectRecognition
}//: namespace Processors


/*
 * Register processor component.
 */
REGISTER_PROCESSOR_COMPONENT("DcObjectRecognition", Processors::DcObjectRecognition::DcObjectRecognition, Common::Panel_Empty)

#endif /* DCOBJECTRECOGNITION_HPP_ */
