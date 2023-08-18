#version 330 core

out vec4 FragColor;

in vec3 ourColor;
in vec2 texCoords;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    FragColor = mix(texture(texture1, texCoords),
                    texture(texture2, texCoords), 0.2);
}