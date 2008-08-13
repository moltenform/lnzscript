function GetCharAt(n)
	return editor:textrange(n,n+1)
end

function ForLoopExpand()
	local linetext,linepos = (editor:GetCurLine())

	-- it looks like you are doing this on an already complete for loop, which doesn't do any good
	if string.find(linetext,';',1,true)~=nil or string.find(linetext,'++',1,true)~=nil then
	return false
	end

	-- [(] in regexp to represent the literal (
	local re = 'for%s*[(]([^)]+)[)]?'
	local tstart,tend,captured = string.find(linetext,re)
	if captured==nil then return false end

	local result='for(var i=0; i<'..captured..';i++)'
	editor:DelLineLeft() --clear line
	editor:ReplaceSel(result) -- add output

	return true
end

-- previous version used Lua string manip, and had a bug. It would delete preceding line, except on the first time run on that line.
-- This might have had to do with CurrentPos / inconsistencies in treating \r\n as a single character

local res = ForLoopExpand()
if res~= true then
	print('Expected use: for(23) => for(var i=0; i<23; i++)')
end

