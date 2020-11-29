#pragma once
#include "Globals.h"
#include "Application.h"
#include "ModuleEditor.h"
#include "Console.h"

#include <string.h>

void log(const char file[], int line, const char* format, ...) {
	static char tmp_string[4096];
	static va_list  ap;

	// Construct the string from variable arguments
	va_start(ap, format);
	vsprintf_s(tmp_string, 4096, format, ap);
	va_end(ap);

	App->editor->console->AddLog(tmp_string);
}