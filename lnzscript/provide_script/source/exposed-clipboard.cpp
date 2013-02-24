

///Function:Clipboard.getText
///Arguments:
///Returns:string strText
///Doc:Gets text from the clipboard. Returns false if clipboard is empty.
///Implementation:c++_au3
{
	//would use QtGui, but that requires QtGui.dll which we don't want.
	CHECK_ARGS
	char buf[LARGEBUFSIZE];
	
	AU3_ClipGet(buf, LARGEBUFSIZE);
	if (AU3_error()==1)
		return QScriptValue(eng, false);
	else
		return QScriptValue(eng, QString(buf));
}

///Function:Clipboard.setText
///Arguments:string strText
///Returns:
///Doc:Sets text of clipboard.
///Implementation:c++_au3
{
	CHECK_ARGS
	AU3_ClipPut(QStrToCStr(strText));
	// the documentation seems to refer to a return value, but the header says it returns void, so I guess not.
	return eng->nullValue();
}

//~ ///Function:nirdisabled_Clipboard.clear
//~ ///Arguments:
//~ ///Returns:bool bStatus
//~ ///Doc:Clear contents of the clipboard.
//~ ///Implementation:c++_nir-cmd


///Function:Clipboard.saveImage
///Arguments:string strImageFilename
///Returns:bool bStatus
///Doc:If there is an image in the clipboard, save image to a file. The following file formats are supported: .bmp, .gif, .jpg, .png, .tiff.
///Implementation:c++_qt
{
	CHECK_ARGS
	return R_WinCommonGdi("clipboard", strImageFilename);
}



