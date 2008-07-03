
///Function:Screen.getColor
///Arguments:int x, int y, bool bRelativeCoords=false
///Returns:[int r, int g, int b]
///Doc:Finds color of screen at coordinates. Returns array of r,g,b values (from 0 to 255), or null upon failure.
{
	CHECK_ARGS
	util_SetAU3PixelRelativeCoords(bRelativeCoords);
	long nColor = AU3_PixelGetColor(x,y);
	if (nColor==-1)
		return eng->nullValue();
	
	QScriptValue arColors = eng->newArray(3);
	arColors.setProperty(0, QScriptValue(eng, (int) GetRValue(nColor)));
	arColors.setProperty(1, QScriptValue(eng, (int) GetGValue(nColor)));
	arColors.setProperty(2, QScriptValue(eng, (int) GetBValue(nColor)));
	return arColors;
}

///Function:Screen.copyScreenshot
///Arguments:bool bFullScreen=false
///Returns:
///Doc:Copy screenshot to the clipboard. Defaults to screenshot of the active window, specify true to take screenshot of full screen.
{
	CHECK_ARGS
	if (bFullScreen) AU3_Send("{PRINTSCREEN}",0);
	else
	{
		//apparently has to be sent a slower way. than //AU3_Send("!{PRINTSCREEN}",0);
		
		AU3_Send("{ALTDOWN}",0);
		AU3_Sleep(100);
		AU3_Send("{PRINTSCREEN}",0);
		AU3_Sleep(100);
		AU3_Send("{ALTUP}",0);
	}
	return eng->nullValue();
}

///Function:Screen.saveScreenshot
///Arguments:string strImageFilename, bool bFullScreen=false
///Returns:bool bStatus
///Doc:Save screenshot to an image file. Defaults to screenshot of the active window, specify true to take screenshot of full screen. Image formats: .bmp, .gif, .png, .jpg, .tiff
///Implementation:c++_nircmd
{
	CHECK_ARGS
	QString strNircmdCommand;
	if (bFullScreen)
		strNircmdCommand = "savescreenshot \""+strImageFilename+"\"";
	else
		strNircmdCommand = "savescreenshotwin \""+strImageFilename+"\"";
	return util_nircmd_runCmd(ctx, eng, strNircmdCommand);
}

///Function:Screen.convertImage
///Arguments:string strImageFilename, string strNewImageName
///Returns:bool bStatus
///Doc:Convert image file from one format from another. Image formats: .bmp, .gif, .png, .jpg, .tiff
///Implementation:c++_nircmd
{
	CHECK_ARGS
	QString strNircmdCommand = "convertimage \""+strImageFilename+"\" \""+strNewImageName+"\"";
	return util_nircmd_runCmd(ctx, eng, strNircmdCommand);
}
///Function:Screen.convertImages
///Arguments:string strImagePattern, string strOutputPattern
///Returns:bool bStatus
///Doc:Convert image files from one format from another. See example. strImagePattern is pattern like "*.bmp" or "a*.bmp". strOutputpattern is pattern like ".png". Image formats: .bmp, .gif, .png, .jpg, .tiff
///Example:Screen.convertImages('c:\\myfolder\\*.bmp','.png') //converts all .bmp images in the folder to .png.
///Implementation:c++_nircmd
{
	CHECK_ARGS
	QString strNircmdCommand = "convertimages \""+strImagePattern+"\" \""+strOutputPattern+"\"";
	return util_nircmd_runCmd(ctx, eng, strNircmdCommand);
}

///Function:Screen.setDisplayMode
///Arguments:int nWidth, int nHeight, int nColorBits
///Returns:bool bStatus
///Doc:Changes display settings. nColorBits is the number of colors, for example 16-bit color or 24-bit color.
///Example:Screen.displayMode(800,600,24); //set display to 800x600
///Implementation:c++_nircmd
{
	CHECK_ARGS
	QString strNircmdCommand;
	strNircmdCommand.sprintf("setdisplay %d %d %d", nWidth, nHeight, nColorBits);
	return util_nircmd_runCmd(ctx, eng, strNircmdCommand);
}

