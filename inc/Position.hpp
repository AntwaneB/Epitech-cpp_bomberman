#ifndef POSITION_HPP_
# define POSITION_HPP_

class Position
{
public:
	Position(double x, double y, double z);
	~Position();
	double getX() const;
	double getY() const;
	double getZ() const;

private:
	double _x;
	double _y;
	double _z;
	/* data */
};

#endif /* !POSITION_HPP_ */