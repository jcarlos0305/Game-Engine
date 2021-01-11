#ifndef _MODULE_DEBUGDRAW_H_
#define _MODULE_DEBUGDRAW_H_

#include "Modules/Module.h"
#include "Utils/Globals.h"
#include "Math/float4x4.h"

class DDRenderInterfaceCoreGL;
class Camera;

class ModuleDebugDraw : public Module
{

public:

    ModuleDebugDraw();
    ~ModuleDebugDraw();

	bool            Init();
	UpdateStatus    Update();
	bool            CleanUp();

    void            Draw(const float4x4& view, const float4x4& proj, unsigned width, unsigned height);
    void            DrawQuad(const float& max_x, const float& max_y, const float& max_z, const float& min_x, const float& min_y, const float& min_z);
    void            DrawFrustumCamera(const float4x4& viewProjMatrix);
private:

    static DDRenderInterfaceCoreGL* implementation;
};

#endif /* _MODULE_DEBUGDRAW_H_ */
