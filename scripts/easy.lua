function move(height, width)
	searchActions = {["MOVE_UP"] = 1, ["MOVE_RIGHT"] = 2, ["MOVE_DOWN"] = 3, ["MOVE_LEFT"] = 4 }
	possibleDirections = {}
	searchX = {0, 1, 0, -1}
	searchY = {-1, 0, 1, 0}
	print (string.format("width : %d\nheight : %d", height, width))

	return 3
end

-- std::vector<Character::Action>  searchActions = { Character::MOVE_UP, Character::MOVE_RIGHT, Character::MOVE_DOWN, Character::MOVE_LEFT};
-- std::vector<Character::Action>  possibleDirections;
-- std::vector<int>                searchX = {0, 1, 0, -1};
-- std::vector<int>                searchY = {-1, 0, 1, 0};
-- int                             mapHeight = _level->map().height();
-- int                             mapWidth = _level->map().width();
-- int                             i = 0;

-- if (VERBOSE)
-- 	std::cout << "Starting MOVE(EASY)" << std::endl;
-- while (i < 4)
-- {
-- 	if ((_myX + searchX[i]) >= 0 && (_myX + searchX[i]) < mapWidth && (_myY + searchY[i]) >= 0 && (_myY + searchY[i]) < mapHeight)
-- 	{
-- 		if (_strategyMap[_myY + searchY[i]][_myX + searchX[i]].wall() == false
-- 			&& _strategyMap[_myY + searchY[i]][_myX + searchX[i]].destructible() == false)
-- 			possibleDirections.push_back(searchActions[i]);
-- 	}
-- 	i++;
-- }
-- if (VERBOSE)
-- 	std::cout << "[MOVE(EASY)] found : " << possibleDirections.size() << " possible directions" << std::endl;
-- if (possibleDirections.size() != 0)
-- {
-- 	if (VERBOSE)
-- 		std::cout << "MOVE(EASY) END" << std::endl;
-- 		return (possibleDirections[rand() % possibleDirections.size()]);
-- }
-- else
-- {
-- 	if (VERBOSE)
-- 		std::cout << "MOVE(EASY) END" << std::endl;
-- 		return (Character::WAIT);
-- }