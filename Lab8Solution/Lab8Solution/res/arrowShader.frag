#version 330 core

in vec2 TexCoord;
out vec4 FragColor;

uniform sampler2D texSampler;

void main()
{
    // Sample the texture
    vec4 texColor = texture(texSampler, TexCoord);

    // Adjust the intensity of the glow
    vec4 glowColor = texColor * 2.0;

    // Combine the glow with the original texture
    FragColor = texColor + glowColor;
}