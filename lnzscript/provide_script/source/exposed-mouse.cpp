
///Function:Mouse.click
///Arguments:int x=INTDEFAULT, int y=INTDEFAULT, bool bRelativeCds=false, string strBtn="left", int nSpeed=-1
///Returns:
///Doc:Moves cursor to x, y and sends simulated mouse click. If x and y are not specified sends mouseclick at current mouse position. If you specify bRelativeCds to be true, moves the cursor relative to window. You can pass the speed to move the mouse in the range 1 (fastest) to 100 (slowest). A speed of 0 will move the mouse instantly. Default speed is 10.
///Implementation:c++_au3
{
	CHECK_ARGS
	util_SetAU3MouseRelativeCoords(bRelativeCds);
	AU3_MouseClick(QStrToCStr(strBtn),x,y,1,nSpeed);
	return eng->nullValue();
}

///Function:Mouse.doubleClick
///Arguments:int x=INTDEFAULT, int y=INTDEFAULT, bool bRelativeCds=false, string strBtn="left", int nSpeed=-1
///Returns:
///Doc:Moves cursor to x, y and sends simulated mouse double-click. If x and y are not specified sends clicks at current mouse position. If you specify bRelativeCds to be true, moves the cursor relative to window. You can pass the speed to move the mouse in the range 1 (fastest) to 100 (slowest). A speed of 0 will move the mouse instantly. Default speed is 10.
///Implementation:c++_au3
{
	CHECK_ARGS
	util_SetAU3MouseRelativeCoords(bRelativeCds);
	AU3_MouseClick(QStrToCStr(strBtn),x,y,2,nSpeed);
	return eng->nullValue();
}

///Function:Mouse.drag
///Arguments:int x1, int y1, int x2, int y2, bool bRelativeCds=false, string strBtn="left", int nSpeed=-1
///Returns:
///Doc:Perform a mouse click and drag operation. If x and y are not specified sends mouseclick at current mouse position. If you specify bRelativeCds to be true, moves the cursor relative to window. You can pass the speed to move the mouse in the range 1 (fastest) to 100 (slowest). A speed of 0 will move the mouse instantly. Default speed is 10.
///Implementation:c++_au3
{
	CHECK_ARGS
	util_SetAU3MouseRelativeCoords(bRelativeCds);
	AU3_MouseClickDrag(QStrToCStr(strBtn),x1,y1,x2,y2,nSpeed);
	return eng->nullValue();
}

///Function:Mouse.getCursor
///Arguments:
///Returns:int nCursorId
///Doc: Returns a cursor ID Number:[[br]]    0 = UNKNOWN (this includes pointing and grabbing hand icons)[[br]]    1 = APPSTARTING[[br]]    2 = ARROW[[br]]    3 = CROSS[[br]]    4 = HELP[[br]]    5 = IBEAM[[br]]    6 = ICON[[br]]    7 = NO[[br]]    8 = SIZE[[br]]    9 = SIZEALL[[br]]  10 = SIZENESW[[br]]  11 = SIZENS[[br]]  12 = SIZENWSE[[br]]  13 = SIZEWE[[br]]  14 = UPARROW[[br]]  15 = WAIT
///Implementation:c++_au3
{
	CHECK_ARGS
	return QScriptValue(eng, (int)AU3_MouseGetCursor());
}

///Function:Mouse.getPosition
///Arguments:
///Returns:[int x, int y]
///Doc:Returns array of the current X and Y position of the mouse.
///Implementation:c++_au3
{
	CHECK_ARGS
	QScriptValue arCoords = eng->newArray(2);
	arCoords.setProperty(0, QScriptValue(eng,(int)AU3_MouseGetPosX()));
	arCoords.setProperty(1, QScriptValue(eng,(int)AU3_MouseGetPosY()));
	return arCoords;
}

///Function:Mouse.move
///Arguments:int x, int y, bool bRelativeCds=false, int nSpeed=10
///Returns:
///Doc:Moves the cursor. If you specify bRelativeCds to be true, moves the cursor relative to its current position. You can pass the speed to move the mouse in the range 1 (fastest) to 100 (slowest). A speed of 0 will move the mouse instantly. Default speed is 10.
///Implementation:c++_au3
{
	CHECK_ARGS
	util_SetAU3MouseRelativeCoords(bRelativeCds);
	AU3_MouseMove(x,y,nSpeed);
	return eng->nullValue();
}

///Function:Mouse.mouseDown
///Arguments:string strBtn="left"
///Returns:
///Doc:Simulate mouseDown. For every mouseDown there should eventually be a corresponding mouseUp.
///Implementation:c++_au3
{
	CHECK_ARGS
	AU3_MouseDown(QStrToCStr(strBtn));
	return eng->nullValue();
}

///Function:Mouse.mouseUp
///Arguments:string strBtn="left"
///Returns:
///Doc:Simulate mouseUp. For every mouseDown there should eventually be a corresponding mouseUp.
///Implementation:c++_au3
{
	CHECK_ARGS
	AU3_MouseUp(QStrToCStr(strBtn));
	return eng->nullValue();
}

///Function:Mouse.wheel
///Arguments:int nDisplacement
///Returns:
///Doc:Moves mouse wheel up or down. Pass 2 to scroll up two, pass -2 to scroll down two, and so on.
///Implementation:c++_au3
{
	CHECK_ARGS
	if (nDisplacement==0) return eng->nullValue();
	else if (nDisplacement > 0)
		AU3_MouseWheel("up", nDisplacement);
	else if (nDisplacement < 0)
		AU3_MouseWheel("down", nDisplacement * -1);
	return eng->nullValue();
}

///Function:Mouse.setClickDelay
///Arguments:int nMilliseconds
///Returns:
///Doc:For simulated mouse clicks, alters the length of the brief pause in between mouse clicks. Time in milliseconds to pause (default=10).
///Implementation:c++_au3
{
	CHECK_ARGS
	AU3_AutoItSetOption("MouseClickDelay",nMilliseconds);
	return eng->nullValue();
}

///Function:Mouse.setClickDownDelay
///Arguments:int nMilliseconds
///Returns:
///Doc:For simulated mouse clicks,Alters the length a click is held down before release. Time in milliseconds to pause (default=10).
///Implementation:c++_au3
{
	CHECK_ARGS
	AU3_AutoItSetOption("MouseClickDownDelay",nMilliseconds);
	return eng->nullValue();
}

///Function:Mouse.setClickDragDelay
///Arguments:int nMilliseconds
///Returns:
///Doc:Alters the length of the brief pause at the start and end of a mouse drag operation. Time in milliseconds to pause (default=250).
///Implementation:c++_au3
{
	CHECK_ARGS
	AU3_AutoItSetOption("MouseClickDragDelay",nMilliseconds);
	return eng->nullValue();
}

