
///Function:Registry.openRegedit
///Arguments:string strKeyname, string strValuename
///Returns:
///Doc:Open regedit to the specified key and value.
///Implementation:c++_nircmd
{
	CHECK_ARGS
	QString strNircmdCommand = "regedit \""+strKeyname+"\" \""+strValuename+"\"";
	return util_nircmd_runCmd(ctx, eng, strNircmdCommand);
}

///Function:Registry.deleteKey
///Arguments:string strKeyname
///Returns:int nResult
///Doc:Deletes a key from the registry. Returns 1 upon success, 0 if key doesn't exist, -1 if error deleting key. Deleting from the registry is potentially dangerous--please exercise caution! A registry key must start with "HKEY_LOCAL_MACHINE" ("HKLM") or "HKEY_USERS" ("HKU") or "HKEY_CURRENT_USER" ("HKCU") or "HKEY_CLASSES_ROOT" ("HKCR") or "HKEY_CURRENT_CONFIG" ("HKCC").
///Example: Registry.deleteKey("HKEY_LOCAL_MACHINE\\SOFTWARE\\MyKey")
{
	CHECK_ARGS
	long res = AU3_RegDeleteKey(QStrToCStr(strKeyname));
	if (res==1)
		return QScriptValue(eng, 1);
	else if (res==2)
		return QScriptValue(eng, -1); // error deleting key
	else
		return QScriptValue(eng, 0);  //key does not exist
}

///Function:Registry.deleteVal
///Arguments:string strKeyname, string strValuename
///Returns:int nResult
///Doc:Deletes a value from the registry. Returns 1 upon success, 0 if key doesn't exist, -1 if error deleting key. To access the (Default) value use "" (a blank string) for the valuename. Deleting from the registry is potentially dangerous--please exercise caution! A registry key must start with "HKEY_LOCAL_MACHINE" ("HKLM") or "HKEY_USERS" ("HKU") or "HKEY_CURRENT_USER" ("HKCU") or "HKEY_CLASSES_ROOT" ("HKCR") or "HKEY_CURRENT_CONFIG" ("HKCC").
///Example: Registry.deleteKey("HKEY_LOCAL_MACHINE\\SOFTWARE", "TestValue")
{
	CHECK_ARGS
	long res = AU3_RegDeleteVal(QStrToCStr(strKeyname), QStrToCStr(strValuename));
	if (res==1) return QScriptValue(eng, 1);
	else if (res==2)	return QScriptValue(eng, -1); // error deleting key
	else return QScriptValue(eng, 0);  //key does not exist
}

///Function:Registry.readVal
///Arguments:string strKeyname, string strValuename
///Returns:string strValue
///Doc:Read value from the registry. Returns string value upon success, and boolean false on failure. To access the (Default) value use "" (a blank string) for the valuename.  Supports registry keys of type REG_BINARY (returns hex string), REG_SZ, REG_MULTI_SZ (returns \\n delimited string), REG_EXPAND_SZ, and REG_DWORD. Cannot return more than 1024 bytes. A registry key must start with "HKEY_LOCAL_MACHINE" ("HKLM") or "HKEY_USERS" ("HKU") or "HKEY_CURRENT_USER" ("HKCU") or "HKEY_CLASSES_ROOT" ("HKCR") or "HKEY_CURRENT_CONFIG" ("HKCC").
///Example: var strProgFiles = Registry.readVal("HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion", "ProgramFilesDir")
{
	CHECK_ARGS
	char buf[BUFSIZE];
	AU3_RegRead(QStrToCStr(strKeyname), QStrToCStr(strValuename), buf, BUFSIZE);
	
	long ner = AU3_error();
	if (ner==0) return QScriptValue(eng, QString(buf));
	else return QScriptValue(eng, false);
}

///Function:Registry.writeVal
///Arguments:string strKeyname, string strValuename, string strValue, string strType="REG_SZ"
///Returns:bool bSuccess
///Doc:Write value to registry. Returns false on failure. To access the (Default) value use "" (a blank string) for the valuename.  Supports registry keys of type REG_BINARY (use hex string such as "01A9FF77"), REG_SZ, REG_MULTI_SZ (provide \\n delimited string - with no blank entries), REG_EXPAND_SZ, and REG_DWORD. A registry key must start with "HKEY_LOCAL_MACHINE" ("HKLM") or "HKEY_USERS" ("HKU") or "HKEY_CURRENT_USER" ("HKCU") or "HKEY_CLASSES_ROOT" ("HKCR") or "HKEY_CURRENT_CONFIG" ("HKCC").
///Example: Registry.writeVal(""HKEY_LOCAL_MACHINE\\SOFTWARE", "TestKey", "Hello this is a test"); Registry.writeVal(""HKEY_LOCAL_MACHINE\\SOFTWARE", "TestKeyArray", "Hello\\n this\\n is\\n a\\n test", "REG_MULTI_SZ"); 
{
	CHECK_ARGS
	
	long nRes = AU3_RegWrite(QStrToCStr(strKeyname), QStrToCStr(strValuename), QStrToCStr(strType), QStrToCStr(strValue));
	return util_LongToBool(nRes);
}

///Function:Registry.listKeys
///Arguments:string strKeyname
///Returns:array astrSubkeys
///Doc:Reads the names of subkeys of the given key. Returns an array of strings, or null if the key cannot be found.
{
	CHECK_ARGS
	char buf[BUFSIZE];
	
	int nIndex = 1; //1-based index
	long ner;
	QList<QString> results;
	while (true)
	{
		AU3_RegEnumKey(QStrToCStr(strKeyname), nIndex, buf, BUFSIZE);
		ner = AU3_error();
		if (ner == 0)
		{
			results << QString(buf);
			nIndex++;
			continue;
		}
		else break;
	}
	if (ner == -1) // we've reached the end of the range, so it worked
		return util_QListToScriptArray(eng, results);
	else //some type of error occurred.
		return eng->nullValue();
}

///Function:Registry.listVal
///Arguments:string strKeyname
///Returns:array astrValueNames
///Doc:Reads the names of values under the given key. Returns an array of strings, or null if the key cannot be found.
{
	CHECK_ARGS
	char buf[BUFSIZE];
	
	int nIndex = 1; //1-based index
	long ner;
	QList<QString> results;
	while (true)
	{
		AU3_RegEnumVal(QStrToCStr(strKeyname), nIndex, buf, BUFSIZE);
		ner = AU3_error();
		if (ner == 0)
		{
			results << QString(buf);
			nIndex++;
			continue;
		}
		else break;
	}
	if (ner == -1) // we've reached the end of the range, so it worked
		return util_QListToScriptArray(eng, results);
	else //some type of error occurred.
		return eng->nullValue();
}
