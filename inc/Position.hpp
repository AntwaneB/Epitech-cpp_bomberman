#ifndef POSITION_HPP_
# define POSITION_HPP_

class Position
{
public:
	Position(int x, int y, int z);
	~Position();
	int getX() const;
	int getY() const;
	int getZ() const;

private:
	int _x;
	int _y;
	int _z;
	/* data */
};

#endif /* !POSITION_HPP_ */