#include <stdlib.h>
#include "Application.h"
#include "Modules/ModuleRender.h"
#include "Utils/Globals.h"

#include "Utils/LeakTest.h"
#include "Brofiler/Brofiler.h"

#include <SDL.h>

#pragma comment( lib, "External Libs/SDL/lib/x86/SDL2.lib" )
#pragma comment( lib, "External Libs/SDL/lib/x86/SDL2main.lib" )

Application* App = NULL;

void DumpLeaks(void) {
	_CrtDumpMemoryLeaks(); // show leaks with file and line where allocation was made
}

int main(int argc, char** argv) {
	atexit(DumpLeaks);
	int main_return = EXIT_FAILURE;
	MainStates state = MainStates::kMainCreation;

	while (state != MainStates::kMainExit) {
		BROFILER_FRAME(TITLE);
		switch (state) {
		case MainStates::kMainCreation:

			App = new Application();
			LOG("Application Creation --------------");
			state = MainStates::kMainStart;
			break;

		case MainStates::kMainStart:

			LOG("Application Init --------------");
			if (App->Init() == false) {
				LOG("Application Init exits with error -----");
				state = MainStates::kMainExit;
			}
			else {
				state = MainStates::kMainUpdate;
				LOG("Application Update --------------");
			}

			break;

		case MainStates::kMainUpdate:
		{
			UpdateStatus update_return = App->Update();

			if (update_return == UpdateStatus::kUpdateError) {
				LOG("Application Update exits with error -----");
				state = MainStates::kMainExit;
			}

			if (update_return == UpdateStatus::kUpdateStop)
				state = MainStates::kMainFinish;
		}
		break;

		case MainStates::kMainFinish:

			LOG("Application CleanUp --------------");
			if (App->CleanUp() == false) {
				LOG("Application CleanUp exits with error -----");
			}
			else
				main_return = EXIT_SUCCESS;

			state = MainStates::kMainExit;

			break;
		}
	}

	delete App;
	return main_return;
}