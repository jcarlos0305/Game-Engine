#pragma once

#include "UiComponent.h"

class Information : public UiComponent {
public:
	Information();
	~Information();

	void Draw();

	bool CleanUp();
};