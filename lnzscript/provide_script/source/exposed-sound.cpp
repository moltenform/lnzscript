///Function:Sound.beep
///Arguments:int nFrequency=-1, int nDurationMilliseconds=500
///Returns:bool bStatus
///Doc:Plays a beep. If no frequency is given, plays standard Windows beep sound.
///Implementation:c++_nircmd
{
	CHECK_ARGS
	if (nFrequency==-1)
		return util_nircmd_runCmd(ctx, eng, QString("stdbeep"));
	else
	{
		QString strNircmdCommand;
		strNircmdCommand.sprintf("beep %d %d", nFrequency, nDurationMilliseconds);
		return util_nircmd_runCmd(ctx, eng, strNircmdCommand);
	}
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
	
	QString strNircmdCommand;
	strNircmdCommand.sprintf("setsysvolume %d \"%s\"", nSoundLevel, QStrToCStrPointer(strComponent));
	return util_nircmd_runCmd(ctx, eng, strNircmdCommand);
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
	
	QString strNircmdCommand;
	strNircmdCommand.sprintf("changesysvolume %d \"%s\"", nSoundLevel, QStrToCStrPointer(strComponent));
	return util_nircmd_runCmd(ctx, eng, strNircmdCommand);
}

// consider: if called with no arguments, toggles setting? Would require special arg handling.
///Function:Sound.mute
///Arguments:bool bMuted, string strComponent="master"
///Returns:bool bStatus
///Doc:Mute or unmute the system volume. Defaults to setting master volume, also specify one of the following: master, waveout, synth, cd, microphone, phone, aux, line, headphones, wavein
///Implementation:c++_nircmd
{
	CHECK_ARGS
	int nParameter = (bMuted) ? 1 : 0;
	QString strNircmdCommand;
	strNircmdCommand.sprintf("mutesysvolume %d \"%s\"", nParameter, QStrToCStrPointer(strComponent));
	return util_nircmd_runCmd(ctx, eng, strNircmdCommand);
}