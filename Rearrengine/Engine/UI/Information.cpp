#include "Information.h"

#include "ImGui/imgui.h"

#include <SDL.h>
#include "GL/glew.h"

#include <map>

Information::Information() {
	title = "Information";
	visible = false;
}

Information::~Information() {}

void Information::Draw() {
	ImGui::Begin(title);

	if (ImGui::CollapsingHeader("Software")) {
		SDL_version compiled;
		SDL_VERSION(&compiled);

		ImGui::Text("OpenGL version: %s", glGetString(GL_VERSION));
		ImGui::Text("GLSL version: %s", glGetString(GL_SHADING_LANGUAGE_VERSION));
		ImGui::Text("SDL version: %d.%d.%d", compiled.major, compiled.minor, compiled.patch);
	}

	if (ImGui::CollapsingHeader("Hardware")) {

		ImGui::Text("CPUs: %i", SDL_GetCPUCount());
		ImGui::SameLine();
		ImGui::Text("(Cache: %i Kb)", SDL_GetCPUCacheLineSize());
		ImGui::Text("System RAM: %.1f Gb", (SDL_GetSystemRAM() / 1024.0f));

		std::map<char*, SDL_bool> caps = { 
			{"3DNow", SDL_Has3DNow()},
			{"AVX", SDL_HasAVX()},
			{"AVX2", SDL_HasAVX2()},
			{"AltiVec", SDL_HasAltiVec()},
			{"MMX", SDL_HasMMX()},
			{"RDTSC", SDL_HasRDTSC()},
			{"SSE", SDL_HasSSE()},
			{"SSE2", SDL_HasSSE2()},
			{"SSE3", SDL_HasSSE3()},
			{"SSE41", SDL_HasSSE41()},
			{"SSE42", SDL_HasSSE42()}
		};

		ImGui::Text("Caps: ");
		ImGui::SameLine();
		for (auto cap : caps) {
			if (cap.second) {
				ImGui::Text(cap.first);
				ImGui::SameLine();
			}
		}
		ImGui::Text("");
		ImGui::Separator();

		ImGui::Text("Vendor: %s", glGetString(GL_VENDOR));
		ImGui::Text("Renderer: %s", glGetString(GL_RENDERER));

		GLint nTotalMemoryInKB = 0;
		glGetIntegerv(GL_GPU_MEMORY_INFO_TOTAL_AVAILABLE_MEMORY_NVX, &nTotalMemoryInKB);

		ImGui::Text("Total VRAM: %.2f Mb", nTotalMemoryInKB / 1024.0f);

		GLint nCurAvailMemoryInKB = 0;
		glGetIntegerv(GL_GPU_MEMORY_INFO_CURRENT_AVAILABLE_VIDMEM_NVX, &nCurAvailMemoryInKB);

		ImGui::Text("Available VRAM: %.2f Mb", nCurAvailMemoryInKB / 1024.0f);

		ImGui::Text("VRAM usage: %.2f Mb", (nTotalMemoryInKB - nCurAvailMemoryInKB) / 1024.0f);
	}

	ImGui::End();
}

bool Information::CleanUp() {
	return true;
}