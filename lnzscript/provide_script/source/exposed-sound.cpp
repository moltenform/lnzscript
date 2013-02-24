///Function:Sound.beep
///Arguments:int nFrequency=300, int nDurationMilliseconds=250
///Returns:bool bStatus
///Doc:Plays a beep. If no frequency is given, plays standard Windows beep sound.
///Implementation:c++_qt
{
	CHECK_ARGS
	BOOL ret = ::Beep(nFrequency, nDurationMilliseconds);
	return util_LongToBool(ret);
}

///Function:Sound.playSound
///Arguments:string strSoundFile="Default"
///Returns:
///Doc:Play a wave file or standard Windows sound. Pass in the filepath of a WAV file, or one of the following:[[br]]"Asterisk"[[br]]"Default"[[br]]"Exclamation"[[br]]"Question"[[br]]
///Example: Sound.playSound('c:/this/mysound.wav'); Sound.playSound('Welcome')
///Implementation:c++_winext
{
	CHECK_ARGS
	return R_WinCommonDialog("sound", strSoundFile);
}

//~ ///Function:nirdisabled_Sound.setVolume
//~ ///Arguments:int nPercentageVolume, string strComponent="master"
//~ ///Returns:bool bStatus
//~ ///Doc:Set system volume. Pass a percentage, where 0 is silent and 100 is maximum volume. Defaults to setting master volume, also specify one of the following: master, waveout, synth, cd, microphone, phone, aux, line, headphones, wavein
//~ ///Implementation:c++_nir-cmd


//~ ///Function:nirdisabled_Sound.changeVolume
//~ ///Arguments:int nVolumeUnits, string strComponent="master"
//~ ///Returns:bool bStatus
//~ ///Doc:Increase or decrease system volume. Units are in 1/100ths of maximum volume. Defaults to setting master volume, also specify one of the following: master, waveout, synth, cd, microphone, phone, aux, line, headphones, wavein
//~ ///Example: Sound.changeVolume(-10); //get quieter[[br]]Sound.changeVolume(10); //get louder
//~ ///Implementation:c++_nir-cmd


// consider: if called with no arguments, toggles setting? Would require special arg handling.
//~ ///Function:nirdisabled_Sound.mute
//~ ///Arguments:bool bMuted, string strComponent="master"
//~ ///Returns:bool bStatus
//~ ///Doc:Mute or unmute the system volume. Defaults to setting master volume, also specify one of the following: master, waveout, synth, cd, microphone, phone, aux, line, headphones, wavein
//~ ///Implementation:c++_nir-cmd

