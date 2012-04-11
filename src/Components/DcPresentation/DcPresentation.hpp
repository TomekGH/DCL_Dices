/*!
 * \file
 * \brief
 */

#ifndef DCPRESENTATION_HPP_
#define DCPRESENTATION_HPP_

#include "Component_Aux.hpp"
#include "Component.hpp"
#include "Panel_Empty.hpp"
#include "DataStream.hpp"

#include <cv.h>
#include <math.h>

#include "Types/Dices.hpp"

namespace Processors {
namespace DcPresentation {

using namespace cv;

/*!
 * \class DcPresentation
 * \brief DcPresentation processor class.
 */
class DcPresentation: public Base::Component
{
public:
	/*!
	 * Constructor.
	 */
	DcPresentation(const std::string & name = "");

	/*!
	 * Destructor
	 */
	virtual ~DcPresentation();


protected:

	// Input data stream
	Base::DataStreamIn <Mat> in_img;
	Base::DataStreamIn <Types::Dices> in_dices;

	// Output data stream
	Base::DataStreamOut <Mat> out_img;

	// Event handler function.	
	void onNewDices();

	// Event handler.
	Base::EventHandler <DcPresentation> h_onNewDices;

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

}//: namespace DcPresentation
}//: namespace Processors


/*
 * Register processor component.
 */
REGISTER_PROCESSOR_COMPONENT("DcPresentation", Processors::DcPresentation::DcPresentation, Common::Panel_Empty)

#endif /* DCPRESENTATION_HPP_ */
