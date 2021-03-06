#version 330 core
out vec4 FragColor;

in vec3 TexCoords;

uniform samplerCube skybox;
uniform bool isDark;

void main()
{   if (isDark)
    FragColor = texture(skybox, TexCoords) * 0.0 ;
    else
    FragColor = texture(skybox, TexCoords) * 0.5 ;
}