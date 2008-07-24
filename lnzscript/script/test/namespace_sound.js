print('Running tests for namespace Sound.')

// All of these seem to work, except maybe Sound.beep() with no arguments.
// Sound.changeVolume and Sound.setVolume seem to work.

registerTest('Sound.beep');
Sound.beep();

alert('You should not hear a ringing sound.');
Sound.mute(true);
Sound.playSound('..\\testfiles\\ringout.wav')
Sound.mute(false);
if(!confirm('Was it silent?')) assert(false);

alert('You should hear 4 sounds and then a ringing sound.')
Sound.playSound('Default')
Sound.playSound('Exclamation')
Sound.playSound('Question')
Sound.playSound('Asterisk')
Sound.playSound('..\\testfiles\\ringout.wav')
if(!confirm('Did you hear 4 sounds and then a ringing sound?')) assert(false);




methods_list_summary_namespace('Sound');