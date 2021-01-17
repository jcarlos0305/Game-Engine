#version 460

in layout(location=0) vec3 position;
in layout(location=1) vec3 normal;
in layout(location=2) vec2 texture_uv;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;

out vec3 fragment_position;
out vec3 fragment_normal;

out vec2 uv;

void main() {
	gl_Position = proj*view*model*vec4(position, 1.0);
	fragment_position = (model*vec4(position, 1.0)).xyz;
	fragment_normal = transpose(inverse(mat3(model)))*normal;
	uv = texture_uv;
}