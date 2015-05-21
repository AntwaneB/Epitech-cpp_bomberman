/*
 * File:   StdHelper.hh
 * Author: buchse_a
 *
 * Created on May 21, 2015, 12:01 PM
 */

#ifndef STDHELPER_HH
#define	STDHELPER_HH

#include <vector>
#include <map>
#include <list>

class StdHelper
{
public:
	virtual ~StdHelper();

	template <typename T, typename U>
	static std::vector<T>
	flatten(std::map<U, std::list<T> > map)
	{
		std::vector<T> result;

		for (auto it = map.begin(); it != map.end(); ++it)
		{
			for (auto yt = (*it).second.begin(); yt != (*it).second.end(); ++yt)
			{
				result.push_back(*yt);
			}
		}

		return (result);
	}

private:
	StdHelper();

};

#endif	/* STDHELPER_HH */
