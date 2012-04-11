/*!
 * \file
 * \brief
 */

#ifndef DCRECOGNITION_HPP_
#define DCRECOGNITION_HPP_

#include "Component_Aux.hpp"
#include "Component.hpp"
#include "Panel_Empty.hpp"
#include "DataStream.hpp"

#include <cv.h>
#include <math.h>

#include "Types/Dices.hpp"

namespace Processors {
namespace DcRecognition {

using namespace cv;

/*!
 * \class DcRecognition
 * \brief DcRecognition processor class.
 */
class DcRecognition: public Base::Component
{
public:
	/*!
	 * Constructor.
	 */
	DcRecognition(const std::string & name = "");

	/*!
	 * Destructor
	 */
	virtual ~DcRecognition();


protected:

	// Input data stream
	Base::DataStreamIn <vector<vector<Point> > > in_contours_big;
	Base::DataStreamIn <vector<vector<Point> > > in_contours_small;

	// Output data stream
	Base::DataStreamOut <Types::Dices> out_dices;

	// Event handler function.	
	void onNewContours();

	// Event handler.
	Base::EventHandler <DcRecognition> h_onNewContours;

	// Event emited after the image is processed.
	Base::Event * newDices;

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

}//: namespace DcRecognition
}//: namespace Processors


/*
 * Register processor component.
 */
REGISTER_PROCESSOR_COMPONENT("DcRecognition", Processors::DcRecognition::DcRecognition, Common::Panel_Empty)

#endif /* DCRECOGNITION_HPP_ */
