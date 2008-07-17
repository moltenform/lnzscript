///Function:Sound.beep
///Arguments:int nFrequency=-1, int nDurationMilliseconds=500
///Returns:bool bStatus
///Doc:Plays a beep. If no frequency is given, plays standard Windows beep sound.
///Implementation:c++_nircmd
{
	CHECK_ARGS
	if (nFrequency==-1)
		return R_Nircmd("stdbeep");
	else
	{
		QString strNircmdCommand;
		strNircmdCommand.sprintf("beep %d %d", nFrequency, nDurationMilliseconds);
		return R_NircmdPreformatted(strNircmdCommand);
	}
}

///Function:Sound.playSound
///Arguments:string strSoundFile="Default"
///Returns:
///Doc:Play a wave file or standard Windows sound. Pass in the filepath of a WAV file, or one of the following:[[br]]"Asterisk"[[br]]"Default"[[br]]"Exclamation"[[br]]"Question"[[br]]
///Example: Sound.playSound('c:/this/mysound.wav'); Sound.playSound('Welcome')
///Implementation:c++_winext
{
	CHECK_ARGS
	// this was moved to another program, which worked out great. Less messing with headers / libraries / unicode-ascii
	// note this needs 2nd version of WinCommonDialog.exe
	return R_WinCommonDialog("sound", strSoundFile);
}

///Function:Sound.setVolume
///Arguments:int nPercentageVolume, string strComponent="master"
///Returns:bool bStatus
///Doc:Set system volume. Pass a percentage, where 0 is silent and 100 is maximum volume. Defaults to setting master volume, also specify one of the following: master, waveout, synth, cd, microphone, phone, aux, line, headphones, wavein
///Implementation:c++_nircmd
{
	CHECK_ARGS
	if (nPercentageVolume <0 || nPercentageVolume>100)
		return ctx->throwError("Volume must be given as a percentage from 0 to 100.");
	int nSoundLevel = (int) ((nPercentageVolume / 100.0) * 65535.0);
	
	QString strLevel; strLevel.sprintf("%d", nSoundLevel);
	return R_Nircmd("setsysvolume", strLevel, strComponent);
}

///Function:Sound.changeVolume
///Arguments:int nVolumeUnits, string strComponent="master"
///Returns:bool bStatus
///Doc:Increase or decrease system volume. Units are in 1/100ths of maximum volume. Defaults to setting master volume, also specify one of the following: master, waveout, synth, cd, microphone, phone, aux, line, headphones, wavein
///Example: Sound.changeVolume(-10); //get quieter Sound.changeVolume(10); //get louder
///Implementation:c++_nircmd
{
	CHECK_ARGS
	if (nVolumeUnits <-100 || nVolumeUnits>100)
		return ctx->throwError("Units are in 1/100ths of maximum volume; must be in range -100 to 100");
	int nSoundLevel = (int) ((nVolumeUnits / 100.0) * 65535.0);
	
	QString strLevel; strLevel.sprintf("%d", nSoundLevel);
	return R_Nircmd("changesysvolume", strLevel, strComponent);
}

// consider: if called with no arguments, toggles setting? Would require special arg handling.
///Function:Sound.mute
///Arguments:bool bMuted, string strComponent="master"
///Returns:bool bStatus
///Doc:Mute or unmute the system volume. Defaults to setting master volume, also specify one of the following: master, waveout, synth, cd, microphone, phone, aux, line, headphones, wavein
///Implementation:c++_nircmd
{
	CHECK_ARGS
	if (bMuted)
		return R_Nircmd("mutesysvolume", "1", strComponent);
	else
		return R_Nircmd("mutesysvolume", "0", strComponent);
}