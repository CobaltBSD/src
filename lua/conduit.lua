#!/usr/bin/env luajit

print("Not yet implemented")

local PATH = os.getenv("PATH")

local args = {...}

local function delim_split(str, delim)
	if delim == nil then
		delim = "%s"
	end

	local t = {}
	for substr in string.gmatch(str, "([^" .. delim .. "]+)") do
		table.insert(t, substr)
	end

	return t
end

local function file_exists(name)
	local f = io.open(name, "r")
	if f ~= nil then
		io.close(f)
		return true
	else
		return false
	end
end

local function find_executable(path, progname)
	for _, dir in next, delim_split(path, ":") do
		local absolute_path = dir .. "/" .. progname
		if file_exists(absolute_path) then
			return absolute_path
		end
	end
	return nil
end

print(find_executable(PATH, "cobalt-config"))

local nonopts = {}
local opts = {a = true, b = false}
local longopts = {test = true, ccc = false, ddd = true}

function is_long_opt(str)
	return string.sub(str, 1, 2) == "--"
end

function is_short_opt(str)
	return string.sub(str, 1, 1) == "-"
end

local i = 1
while i <= #args do
	if is_long_opt(args[i]) then
		local opt = string.sub(args[i], 3)
		split = delim_split(opt, "=")
		if longopts[split[1]] == nil then
			error("Received invalid option: '" .. opt .. "'")
		end

		if longopts[split[1]] ~= false then
			if opt ~= split[1] then
				local optarg = string.sub(opt, string.len(split[1]) + 2)
				longopts[split[1]] = optarg
			else
				if args[i + 1] == nil or is_short_opt(args[i + 1]) or is_long_opt(args[i + 1]) then
					error("Argument '" .. split[1] .. "' missing an argument")
				end

				longopts[split[1]] = args[i + 1]
				i = i + 1
			end
		end
	elseif is_short_opt(args[i]) then
		for j = 2, #args[i] do
			local optletter = string.sub(args[i], j, j)
			if opts[optletter] ~= nil then
				-- If the optletter requires an argument, then it first must be at the end of its string of short opts
				if opts[optletter] ~= false then
					if j ~= #args[i] then
						error("Argument '" .. optletter .. "' missing an argument")
					end

					-- Following argument must exist and not be an option itself
					if args[i + 1] == nil or is_short_opt(args[i + 1]) or is_long_opt(args[i + 1]) then
						error("Argument '" .. optletter .. "' missing an argument")
					end

					opts[optletter] = args[i + 1]
					i = i + 1
				end
			else
				error("Received invalid option: '" .. optletter .. "'")
			end
		end
	else
		table.insert(nonopts, args[i])
	end
	i = i + 1
end

--for i, v in next, longopts do
--	print(i .. ": " .. tostring(v))
--end
for _, v in next, nonopts do
	print(v)
end
