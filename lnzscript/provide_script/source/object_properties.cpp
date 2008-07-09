// set custom properties of the static objects.

objWindow.setProperty("HIDE", QScriptValue(eng, 0));
objWindow.setProperty("NORMAL", QScriptValue(eng, 1));
objWindow.setProperty("SHOWNORMAL", QScriptValue(eng, 1));
objWindow.setProperty("SHOWMINIMIZED", QScriptValue(eng, 2));
objWindow.setProperty("MAXIMIZE", QScriptValue(eng, 3));
objWindow.setProperty("SHOWMAXIMIZED", QScriptValue(eng, 3));
objWindow.setProperty("SHOWNOACTIVATE", QScriptValue(eng, 4));
objWindow.setProperty("SHOW", QScriptValue(eng, 5));
objWindow.setProperty("MINIMIZE", QScriptValue(eng, 6));
objWindow.setProperty("SHOWMINNOACTIVE", QScriptValue(eng, 7));
objWindow.setProperty("SHOWNA", QScriptValue(eng, 8));
objWindow.setProperty("RESTORE", QScriptValue(eng, 9));
objWindow.setProperty("SHOWDEFAULT", QScriptValue(eng, 10));
objWindow.setProperty("FORCEMINIMIZE", QScriptValue(eng, 11));
objWindow.setProperty("MAX", QScriptValue(eng, 11));

objDialog.setProperty("YES", QScriptValue(eng, 2));
objDialog.setProperty("OK", QScriptValue(eng, 2));
objDialog.setProperty("NO", QScriptValue(eng, 1));
objDialog.setProperty("CANCEL", QScriptValue(eng, 0));