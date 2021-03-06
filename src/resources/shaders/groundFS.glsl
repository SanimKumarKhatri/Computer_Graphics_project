#version 330 core
in vec2 TexCord;

uniform sampler2D g_texture;
uniform bool isDark;

out vec4 FragColor;
void main()
{
    if(isDark)
    FragColor = texture(g_texture, TexCord) * 0.0;
    else
    FragColor = texture(g_texture, TexCord) * 0.5;
};