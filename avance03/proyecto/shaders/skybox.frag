/*
#version 330
in vec3 TexCoords;
out vec4 color;
uniform samplerCube skybox;
void main()
{
color=texture(skybox,TexCoords);
}
*/
#version 330

in vec3 TexCoords;
out vec4 color;

uniform samplerCube dayCubemap;
uniform samplerCube nightCubemap;
uniform float blendFactor;

void main()
{
    vec4 dayColor = texture(dayCubemap, TexCoords);
    vec4 nightColor = texture(nightCubemap, TexCoords);
    color = mix(nightColor, dayColor, blendFactor);
}
