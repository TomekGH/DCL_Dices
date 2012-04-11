/*!
 * \file
 * \brief
 */

#ifndef CVFINDCONTOURS_HPP_
#define CVFINDCONTOURS_HPP_

#include "Component_Aux.hpp"
#include "Component.hpp"
#include "Panel_Empty.hpp"
#include "DataStream.hpp"

#include <cv.h>
#include <math.h>

namespace Processors {
namespace CvFindContours {

using namespace cv;

/*!
 * \brief CvFindContours properties
 */
struct FindContoursProps: public Base::Props
{
	
	int min, max, colorR, colorG, colorB;

	/*!
	 * \copydoc Base::Props::load
	 */
	void load(const ptree & pt)
	{
		min = pt.get("min", 0);
		max = pt.get("max", 10000);
		colorR = pt.get("colorR", 255);
		colorG = pt.get("colorG", 255);
		colorB = pt.get("colorB", 255);
	}

	/*!
	 * \copydoc Base::Props::save
	 */
	void save(ptree & pt)
	{
		pt.put("min", min);
		pt.put("max", max);
		pt.put("colorR", colorR);
		pt.put("colorG", colorG);
		pt.put("colorB", colorB);
	}

};

/*!
 * \class CvFindContours
 * \brief CvFindContours processor class.
 */
class CvFindContours: public Base::Component
{
public:
	/*!
	 * Constructor.
	 */
	CvFindContours(const std::string & name = "");

	/*!
	 * Destructor
	 */
	virtual ~CvFindContours();

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
	Base::EventHandler <CvFindContours> h_onNewImage;

	// Event emited after the image is processed.
	Base::Event * newContours;
	Base::Event * newImage;

	/// FindContours properties
	FindContoursProps props;

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

}//: namespace CvFindContours
}//: namespace Processors


/*
 * Register processor component.
 */
REGISTER_PROCESSOR_COMPONENT("CvFindContours", Processors::CvFindContours::CvFindContours, Common::Panel_Empty)

#endif /* CVFINDCONTOURS_HPP_ */
