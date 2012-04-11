/*!
 * \file
 * \brief
 */

#ifndef DCTEST_HPP_
#define DCTEST_HPP_

#include "Component_Aux.hpp"
#include "Component.hpp"
#include "Panel_Empty.hpp"
#include "DataStream.hpp"

#include <cv.h>
#include <math.h>

namespace Processors {
namespace DcTest {

using namespace cv;

/*!
 * \class DcTest
 * \brief DcTest processor class.
 */
class DcTest: public Base::Component
{
public:
	/*!
	 * Constructor.
	 */
	DcTest(const std::string & name = "");

	/*!
	 * Destructor
	 */
	virtual ~DcTest();


protected:

    // Input data stream
    Base::DataStreamIn <Mat> in_img;

    // Output data stream - processed image
    Base::DataStreamOut <Mat> out_img;

    // Event handler function.
    void onNewImage();

    // Event handler.
    Base::EventHandler <DcTest> h_onNewImage;

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

}//: namespace DcTest
}//: namespace Processors


/*
 * Register processor component.
 */
REGISTER_PROCESSOR_COMPONENT("DcTest", Processors::DcTest::DcTest, Common::Panel_Empty)

#endif /* DCTEST_HPP_ */
