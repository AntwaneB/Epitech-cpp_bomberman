searchX = {0, 0, -1, 1, 0, 0, -2, 2}
searchY = {-1, 1, 0, 0, -2, 2, 0, 0}
movement = 0
mmove = 0

-- function move(width, height, x, y, last_move)
-- 	local i = 1
-- 	local searchActions = {0, 1, 2, 3, 6 }
-- 	local possibleDirections = {}
-- 	local obj = getObjects()
-- 	local move = {"MOVE_UP", "MOVE_DOWN", "MOVE_LEFT", "MOVE_RIGHT", "end_move", "DROP_BOMB", "WAIT" }

-- 	while i < 5 do
-- 		if (x + searchX[i]) >= 0 and (x + searchX[i]) < width and (y + searchY[i] >= 0) and (y + searchY[i]) < height then
-- 			if obj:getWall(y + searchY[i], x + searchX[i]) ~= 1 and obj:getDestructible(y + searchY[i], x + searchX[i]) ~= 1 then
-- 				table.insert(possibleDirections, searchActions[i])
-- 				wall =  obj:getWall(y + searchY[i], x + searchX[i])
-- 				getDestructible = obj:getDestructible(y + searchY[i], x + searchX[i])
-- 				print(string.format("(%d/%d) Possible way detected : %s (%d/%d) wall : %s Dest : %s", x, y, move[searchActions[i] + 1], x + searchX[i], y + searchY[i] , wall, destructible))
-- 			end
-- 		end
-- 		i = i + 1
-- 	end
-- 	if #possibleDirections ~= 0 then
-- 		if #possibleDirections > 2 then
-- 			repeat
-- 				action = possibleDirections[math.random(1, #possibleDirections)]
-- 			until action ~= last_move
-- 		else
-- 			action = possibleDirections[math.random(1, #possibleDirections)]
-- 		end
-- 		print(string.format("my last action was %s now its %s", move[last_move + 1], move[action + 1]))
-- 	else
-- 		action = searchActions[5]
-- 	end
-- 	return action
-- end

function move(width, height, x, y, last_move)
	local move = {"MOVE_UP", "MOVE_DOWN", "MOVE_LEFT", "MOVE_RIGHT", "end_move", "DROP_BOMB", "WAIT" }
	local action = 1
	if movement > 0 then
		movement = movement - 1
		-- print (string.format("Continue to move on : %s", move[mmove + 1]))
		return mmove
	else
		local i = 1
		local searchActions = {0, 1, 2, 3, 6 }
		local possibleDirections = {}
		local obj = getObjects()
		local history = {}
		-- print (string.format("history of current position(%d/%d) : %d", x, y, obj:getHistory(y, x)))
		while i < 5 do
			if (x + searchX[i]) >= 0 and (x + searchX[i]) < width and (y + searchY[i] >= 0) and (y + searchY[i]) < height then
				if obj:getWall(y + searchY[i], x + searchX[i]) ~= 1 and obj:getDestructible(y + searchY[i], x + searchX[i]) ~= 1 then
					table.insert(possibleDirections, searchActions[i])
					table.insert(history, obj:getHistory(y + searchY[i], x + searchX[i]))
					-- print(string.format("Possible way detected : %s (%d/%d) history : %d", move[searchActions[i] + 1],
					-- 	x + searchX[i], y + searchY[i], obj:getHistory(y + searchY[i], x + searchX[i])))
				end
			end
			i = i + 1
		end
		local j = 5000
		local i = 1
		while i <= #history do
			-- print (string.format("j = %d ; history[i] = %d ; action = %s", j, history[i], move[possibleDirections[i] + 1]))
			if history[i] < j then
				action = possibleDirections[i]
				j = history[i]
			end
			i = i + 1
		end
		-- print (string.format("Move where I was the less : %s", move[action + 1]))
		mmove = action
		movement = 4
		return action
	end
end

function BombDetection(width, height, x, y)
	obj = getObjects()
	explosion = obj:getExplosion(y, x)
	bomb = obj:getBomb(y, x)
	action = false
	if explosion == true or bomb == true then
		action = true
	end
	return action
end

function BombOpportunity(width, height, x, y)
	local i = 1
	local action = false
	obj = getObjects()
	while i < 9 do
		if (x + searchX[i]) >= 0 and (x + searchX[i]) < width and (y + searchY[i]) >= 0 and (y + searchY[i]) < height then
			local enemy = obj:getEnemy(y + searchY[i], x + searchX[i])
			if enemy > 0 and enemy <= 10 then
				action = true
			end
		end
		i = i + 1
	end
	return action
end
