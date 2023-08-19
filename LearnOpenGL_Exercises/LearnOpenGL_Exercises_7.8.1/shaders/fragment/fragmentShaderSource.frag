#version 330 core

out vec4 FragColor;

in vec2 texCoords;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    FragColor = mix(texture(texture1, texCoords),
                    texture(texture2, vec2(texCoords.s, 1.0 - texCoords.t)), 0.2);
}