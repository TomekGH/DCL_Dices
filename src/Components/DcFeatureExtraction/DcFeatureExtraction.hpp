/*!
 * \file
 * \brief
 */

#ifndef DCFEATUREEXTRACTION_HPP_
#define DCFEATUREEXTRACTION_HPP_

#include "Component_Aux.hpp"
#include "Component.hpp"
#include "Panel_Empty.hpp"
#include "DataStream.hpp"

#include <cv.h>

namespace Processors {
namespace DcFeatureExtraction {

using namespace cv;

/*!
 * \class DcFeatureExtraction
 * \brief DcFeatureExtraction processor class.
 */
class DcFeatureExtraction: public Base::Component
{
public:
	/*!
	 * Constructor.
	 */
	DcFeatureExtraction(const std::string & name = "");

	/*!
	 * Destructor
	 */
	virtual ~DcFeatureExtraction();


protected:

    // Input data stream
    Base::DataStreamIn <Mat> in_img;

    // Output data stream - processed image
    Base::DataStreamOut <Mat> out_img;

    // Event handler function.
    void onNewImage();

    // Event handler.
    Base::EventHandler <DcFeatureExtraction> h_onNewImage;

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

}//: namespace DcFeatureExtraction
}//: namespace Processors


/*
 * Register processor component.
 */
REGISTER_PROCESSOR_COMPONENT("DcFeatureExtraction", Processors::DcFeatureExtraction::DcFeatureExtraction, Common::Panel_Empty)

#endif /* DCFEATUREEXTRACTION_HPP_ */
