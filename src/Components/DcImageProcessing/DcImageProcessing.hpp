/*!
 * \file
 * \brief
 */

#ifndef DCIMAGEPROCESSING_HPP_
#define DCIMAGEPROCESSING_HPP_

#include "Component_Aux.hpp"
#include "Component.hpp"
#include "Panel_Empty.hpp"
#include "DataStream.hpp"

#include <cv.h>

namespace Processors {
namespace DcImageProcessing {

using namespace cv;

/*!
 * \class DcImageProcessing
 * \brief DcImageProcessing processor class.
 */
class DcImageProcessing: public Base::Component
{
public:
	/*!
	 * Constructor.
	 */
	DcImageProcessing(const std::string & name = "");

	/*!
	 * Destructor
	 */
	virtual ~DcImageProcessing();


protected:

    // Input data stream
    Base::DataStreamIn <Mat> in_img;

    // Output data stream - processed image
    Base::DataStreamOut <Mat> out_img;

    // Event handler function.
    void onNewImage();

    // Event handler.
    Base::EventHandler <DcImageProcessing> h_onNewImage;

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

}//: namespace DcImageProcessing
}//: namespace Processors


/*
 * Register processor component.
 */
REGISTER_PROCESSOR_COMPONENT("DcImageProcessing", Processors::DcImageProcessing::DcImageProcessing, Common::Panel_Empty)

#endif /* DCIMAGEPROCESSING_HPP_ */
