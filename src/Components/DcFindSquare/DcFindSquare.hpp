/*!
 * \file
 * \brief
 */

#ifndef DCFINDSQUARE_HPP_
#define DCFINDSQUARE_HPP_

#include "Component_Aux.hpp"
#include "Component.hpp"
#include "Panel_Empty.hpp"
#include "DataStream.hpp"

#include <cv.h>
#include <math.h>

namespace Processors {
namespace DcFindSquare {

using namespace cv;

/*!
 * \brief CvFindContours properties
 */
struct FindSquareProps: public Base::Props
{
	
	int min, max;

	/*!
	 * \copydoc Base::Props::load
	 */
	void load(const ptree & pt)
	{
		min = pt.get("min", 0);
		max = pt.get("max", 10000);
	}

	/*!
	 * \copydoc Base::Props::save
	 */
	void save(ptree & pt)
	{
		pt.put("min", min);
		pt.put("max", max);
	}

};

/*!
 * \class DcFindSquare
 * \brief DcFindSquare processor class.
 */
class DcFindSquare: public Base::Component
{
public:
	/*!
	 * Constructor.
	 */
	DcFindSquare(const std::string & name = "");

	/*!
	 * Destructor
	 */
	virtual ~DcFindSquare();

	Base::Props * getProperties()
	{
		return &props;
	}


protected:

	// Input data stream
	Base::DataStreamIn <Mat> in_img;

	// Output data stream - processed image
	Base::DataStreamOut<vector<vector<Point> > > out_contours;
	Base::DataStreamOut <Mat> out_img;

	// Event handler function.
	void onNewImage();

	// Event handler.
	Base::EventHandler <DcFindSquare> h_onNewImage;

	// Event emited after the image is processed.
	Base::Event * newContours;
	Base::Event * newImage;

	/// FindSquare properties
	FindSquareProps props;

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

}//: namespace DcFindSquare
}//: namespace Processors


/*
 * Register processor component.
 */
REGISTER_PROCESSOR_COMPONENT("DcFindSquare", Processors::DcFindSquare::DcFindSquare, Common::Panel_Empty)

#endif /* DCFINDSQUARE_HPP_ */
