#include "Console.h"
#include <string.h>

Console::Console() {
	title = "Console";
	visible = true;
	Clear();
}

Console::~Console() {}

void Console::Clear() {
	buffer.clear();
	line_offsets.clear();
	line_offsets.push_back(0);
}

void Console::AddLog(const char* fmt) {
	buffer.push_back(strdup(fmt));
}

void Console::Draw() {
	if (!ImGui::Begin(title, &visible)) {
		ImGui::End();
		return;
	}

	// Main window
	ImGui::BeginChild("scrolling", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);

	for (int i = 0; i < buffer.Size; ++i) {
		ImGui::TextUnformatted(buffer[i]);
	}

	if (auto_scroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
		ImGui::SetScrollHereY(1.0f);

	ImGui::EndChild();
	ImGui::End();
}