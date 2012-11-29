#ifndef DICESMATRIX_HPP_
#define DICESMATRIX_HPP_

#include <boost/serialization/serialization.hpp>

namespace Types {

struct DicesMatrix 
{

	double matrix[5][4];

	DicesMatrix()
	{
	/*	for (int i=0; i<=5; ++i)
		{
			for (int j=0; j<=4; ++j)
			{
				matrix[i][j] = 0;
			}			
		}*/		
	}

	~DicesMatrix()
	{
	}	
	
	void toMatrix (Dices d)
	{
		for (int i=0; i<=4; ++i)
		{
			if (!(d.value.empty()))
			{
				matrix[i][0] = (double)(d.value[i]);
				matrix[i][1] = d.angle[i];
				matrix[i][2] = d.position[i].x;
				matrix[i][3] = d.position[i].y;
			}
			
		}
	}

private:
	friend class boost::serialization::access;
	template <class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & matrix;
	}
	
};

} //: namespace Types

#endif
