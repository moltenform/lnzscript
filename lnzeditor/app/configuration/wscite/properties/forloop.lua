function GetCharAt(n)
	return editor:textrange(n,n+1)
end

function ForLoopExpand()
	local pos = editor.CurrentPos-1
	local firstpos = math.max(pos - 300, 0)

	local sinput = ''
	local found=false
	-- go backwards until hitting the first newline
	while pos > firstpos do
		local ch = GetCharAt(pos)
		if ch=="\n" then 
			found = true
			break 
		end
		sinput = ch .. sinput
		pos = pos-1
	end
	if found==false then return false end

	-- it looks like you are doing this on an already complete for loop, which doesn't do any good
	if string.find(sinput,';',1,true)~=nil or string.find(sinput,'++',1,true)~=nil then
	return false
	end
	
	-- Using [(] to represent the literal (
	local re = 'for%s*[(]([^)]+)[)]?'
	tstart,tend,captured = string.find(sinput,re)
	if captured==nil then return false end
	
	local result='for(var i=0; i<'..captured..';i++)'
	editor:remove(pos, editor.CurrentPos)
	editor:ReplaceSel(result)
	
	return true
end

local res = ForLoopExpand()
if res~= true then
	print('Expected use: for(23) => for(var i=0; i<23; i++)')
end

