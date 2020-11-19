#include <stdlib.h>
#include "Application.h"
#include "ModuleRender.h"
#include "Globals.h"

#include "SDL/include/SDL.h"
#pragma comment( lib, "SDL/lib/x86/SDL2.lib" )
#pragma comment( lib, "SDL/lib/x86/SDL2main.lib" )

Application* App = NULL;

int main(int argc, char** argv) {
	int main_return = EXIT_FAILURE;
	MainStates state = MainStates::kMainCreation;

	while (state != MainStates::kMainExit) {
		switch (state) {
		case MainStates::kMainCreation:

			LOG("Application Creation --------------");
			App = new Application();
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
	LOG("Bye :)\n");
	return main_return;
}