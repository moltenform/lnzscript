#ifndef PRINT_FUNCTION_H
#define PRINT_FUNCTION_H
#include <QtScript>

// all interfaces to LnzScript must implement the following:

void g_LnzScriptPrintCallback(QString * str);
// if you need access to a member variable, you might have to have a global void* to store context...

#endif

