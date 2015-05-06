/*
 * File:   IA.hh
 * Author: buchse_a
 *
 * Created on May 7, 2015, 1:01 AM
 */

#ifndef IA_HH
#define	IA_HH

namespace IA
{

	enum Style { AGGRESSIVE, DEFENSIVE, MIXED };
	enum Difficulty { EASY, MEDIUM, HIGH };

	template <Style style = MIXED, Difficulty difficulty = EASY>
	class IA
	{
	public:

	public:
		IA();
		virtual ~IA();

	private:

	};

};


#endif	/* IA_HH */
