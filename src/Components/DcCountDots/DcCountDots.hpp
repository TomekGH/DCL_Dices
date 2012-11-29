/*!
 * \file
 * \brief
 */

#ifndef DCCOUNTDOTS_HPP_
#define DCCOUNTDOTS_HPP_

#include "Component_Aux.hpp"
#include "Component.hpp"
#include "Panel_Empty.hpp"
#include "DataStream.hpp"

#include <cv.h>
#include <math.h>

namespace Processors {
namespace DcCountDots {

/*!
 * \class DcCountDots
 * \brief DcCountDots processor class.
 */

using namespace cv;

class DcCountDots: public Base::Component
{
public:
	/*!
	 * Constructor.
	 */
	DcCountDots(const std::string & name = "");

	/*!
	 * Destructor
	 */
	virtual ~DcCountDots();


protected:

	// Input data stream
	Base::DataStreamIn <Mat> in_img;

	// Output data stream
	Base::DataStreamOut <int> out_dots;
	Base::DataStreamOut <Mat> out_img;

	// Event handler function.	
	void onNewImage();

	// Event handler.
	Base::EventHandler <DcCountDots> h_onNewImage;

	// Event emited after the image is processed.
	Base::Event * newDots;
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

}//: namespace DcCountDots
}//: namespace Processors


/*
 * Register processor component.
 */
REGISTER_PROCESSOR_COMPONENT("DcCountDots", Processors::DcCountDots::DcCountDots, Common::Panel_Empty)

#endif /* DCCOUNTDOTS_HPP_ */
