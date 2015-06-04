-- move = {"MOVE_UP", "MOVE_DOWN", "MOVE_LEFT", "MOVE_RIGHT", "WAIT" }
searchX = {0, 1, 0, -1}
searchY = {-1, 0, 1, 0}

function move(width, height, x, y)
	i = 1
	j = 1
	searchActions = {0, 1, 2, 3, 5 }
	possibleDirections = {}
	obj = getObjects()
	while i < 5 do
		if (x + searchX[i]) >= 0 and (x + searchX[i]) < width and (y + searchY[i] >= 0) and (y + searchY[i]) < height then
			if obj:getWall(y + searchY[i], x + searchX[i]) ~= 1 and obj:getDestructible(y + searchY[i], x + searchX[i]) ~= 1 then
				table.insert(possibleDirections, searchActions[i])
				j = j + 1
			end
		end
		i = i + 1
	end
	if #possibleDirections ~= 0 then
		action = possibleDirections[math.random(1, #possibleDirections)]
		-- print(move[possibleDirections[action] + 1])
	else
		action = searchActions[5]
	end
	return action
end

function BombDetection(width, height, x, y)
	return false
end

function BombOpportunity(width, height, x, y)
	-- body
	local i = 1
	action = false
	obj = getObjects()
	while i < 5 do
		if (x + searchX[i]) >= 0 and (x + searchX[i]) < width and (y + searchY[i] >= 0) and (y + searchY[i]) < height then
			local enemy = obj:getEnemy(y + searchY[i], x + searchX[i])
			if enemy > 0 and enemy <= 10 then
				action = true
			end
		end
		i = i + 1
	end
	return action
end