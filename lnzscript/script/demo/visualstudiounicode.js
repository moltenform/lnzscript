
//This is specific to a certain setup.

Window.waitUntilActive('%Microsoft Visual%')
// wait for a window with "microsoft visual" in the title

// assumes that focus is on the panel, on the first one.
for(var i=0; i<7; i++)
{
	//open context menu
	Keyboard.send('<Shift>{F10}'); Time.sleep(100);
	
	// arrow keys to choose Properties from menu
	Keyboard.send('{UP}{UP}{ENTER}')
	
	Time.sleep(500);// wait for dialog to open
	
	for(var j=0; j<9;j++)
		Keyboard.send('{DOWN}');
	
	Keyboard.send('{TAB}'); //tab over to Character set
	Keyboard.send('{UP}'); //choose Unicode
	Keyboard.send('{ENTER}');
	
	Keyboard.send('{ENTER}'); //save and close dialog
	Time.sleep(1500);
	
	Keyboard.send('{DOWN}');
	Time.sleep(1500);
}

