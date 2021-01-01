#include "Main/Application.h"
#include "Modules/ModuleRender.h"
#include "Modules/ModuleCamera.h"
#include "UI/Viewport.h"

#include "ImGui/imgui.h"

Viewport::Viewport() {
	visible = true;
	title = "Viewport";
}

Viewport::~Viewport() {}

void Viewport::Draw() {

	if (ImGui::Begin(title, &visible, ImGuiWindowFlags_NoCollapse)) {
		is_viewport_focused = ImGui::IsWindowFocused();

		static ImVec2 window_size = ImGui::GetWindowSize();

		App->render->RenderToViewport(static_cast<unsigned int>(window_size.x), static_cast<unsigned int>(window_size.y));

		ImGui::GetWindowDrawList()->AddImage(
			(void*)(intptr_t)App->render->texture,
			ImGui::GetCursorScreenPos(),
			ImVec2(ImGui::GetCursorScreenPos().x + window_size.x, ImGui::GetCursorScreenPos().y + window_size.y),
			ImVec2(0, 1), ImVec2(1, 0)
		);

		ImVec2 new_window_size = ImGui::GetWindowSize();
		if (window_size.x != new_window_size.x || window_size.y != new_window_size.y) {
			App->camera->SetAspectRatio(new_window_size.x / new_window_size.y);
			window_size = ImGui::GetWindowSize();
		}
	}
	ImGui::End();
}

bool Viewport::CleanUp() {
	return true;
}
