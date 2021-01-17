#version 460
/*
	Phong
*/
out vec4 color;

uniform vec3 light_dir;
uniform vec3 light_color;
uniform vec3 ambient_color;

uniform vec3 view_pos;

uniform float Ks;
uniform float Kd;
uniform float shininess;

in vec3 fragment_position;
in vec3 fragment_normal;

in vec2 uv;

layout(binding = 0) uniform sampler2D diffuse_texture;

/*
	PBR Phong
*/
uniform float refractive_index;
layout(binding = 1) uniform sampler2D specular_texture;

/*
	Phong
*/
vec4 Phong() {
	vec3 L = normalize(light_dir);
	vec3 N = normalize(fragment_normal);
	float nDotL = max(dot(N, -L), 0.0);
	
	vec3 diffuse_color = texture(diffuse_texture, uv).rgb;
	vec3 diffuse = Kd*diffuse_color*light_color*nDotL;
	
	vec3 R = reflect(L, N);
	vec3 V = normalize(view_pos-fragment_position);
	float vDotR = max(dot(V, R), 0.0);
	
	vec3 specular = Ks*light_color*pow(vDotR, shininess);
	
	return vec4(ambient_color * diffuse_color +  diffuse + specular, 1.0);
}

/*
	PBR Phong
*/

// Schlick's approximation Rf(0^0)
float MinimalReflection() {
	return pow((refractive_index - 1)/(refractive_index + 1), 2.0);
}

// Schlick's approximation Rf(Angle)
float AngleReflection(float angle) {
	return MinimalReflection() + (1 - MinimalReflection()) * pow((1 - cos(angle)), 5.0);
}

vec4 PbrPhong() {
	vec3 L = normalize(-light_dir);
	vec3 N = normalize(fragment_normal);
	float nDotL = max(dot(N, -L), 0.0);
	
	// Getting the diffuse color
	vec3 diffuse_color = pow(texture(diffuse_texture, uv).rgb, vec3(2.2));
	vec3 diffuse = Kd*diffuse_color;
	
	vec3 V = normalize(view_pos - fragment_position);
	vec3 R = reflect(L, N);
	float vDotR = max(dot(V, R), 0.0);
	
	// Getting the specular color
	vec3 specular_color = pow(texture(specular_texture, uv).rgb, vec3(2.2));
	vec3 specular = Ks*specular_color;
	
	vec3 minimal_reflection = specular * MinimalReflection();
	vec3 angle_reflection = specular *  AngleReflection(nDotL);
	
	vec3 BRDF = (
			diffuse * (1 - minimal_reflection) +
			(shininess + 2) / 2 *
			angle_reflection *
			pow(vDotR, shininess)
		);
	
	return vec4(BRDF * (2 * light_color * ambient_color) * nDotL, 1.0);
}

void main() {
//	color = Phong();
	color = pow(PbrPhong(), vec4(1/2.2));
}