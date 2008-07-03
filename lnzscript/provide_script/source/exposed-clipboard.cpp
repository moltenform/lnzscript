

///Function:Clipboard.getText
///Arguments:
///Returns:string strText
///Doc:Gets text from the clipboard. Returns false if clipboard is empty.
{
	CHECK_ARGS
	char buf[BUFSIZE];
	
	AU3_ClipGet(buf, BUFSIZE);
	if (AU3_error()==1)
		return QScriptValue(eng, false);
	else
		return QScriptValue(eng, QString(buf));
}

///Function:Clipboard.setText
///Arguments:string strText
///Returns:
///Doc:Sets text of clipboard.
{
	CHECK_ARGS
	AU3_ClipPut(QStrToCStr(strText));
	// the documentation seems to refer to a return value, but the header says it returns void, so I guess not.
	return eng->nullValue();
}

///Function:Clipboard.clear
///Arguments:
///Returns:bool bStatus
///Doc:Clear contents of the clipboard.
///Implementation:c++_nircmd
{
	CHECK_ARGS
	return util_nircmd_runCmd(ctx, eng, QString("clipboard clear"));
}

///Function:Clipboard.saveImage
///Arguments:string strImageFilename
///Returns:bool bStatus
///Doc:If there is an image in the clipboard, save image to a file. The following file formats are supported: .bmp, .gif, .jpg, .png, .tiff.
///Implementation:c++_nircmd
{
	CHECK_ARGS
	QString strNircmdCommand = "clipboard saveimage \""+strImageFilename+"\"";
	return util_nircmd_runCmd(ctx, eng, strNircmdCommand);
}


