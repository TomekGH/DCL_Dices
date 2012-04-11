#ifndef DICES_HPP_
#define DICES_HPP_

#include <vector>
#include <cv.h>

namespace Types {

using namespace cv;

struct Dices {

	vector<Point> position;
	vector<int> value;
	vector<double> angle;
};

} //: namespace Types

#endif
