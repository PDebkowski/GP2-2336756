#version 330 core

in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D textureSampler;
uniform float glowStrength;
uniform float time;

void main()
{
    // Sample texture
    vec4 texColor = texture(textureSampler, TexCoord);

    // Calculate glow effect
    float glow = abs(sin(time * 5.0)) * glowStrength;
    vec3 glowColor = vec3(0.0, 1.0, 1.0); // Cyan glow color

    // Apply glow to fragment color
    vec3 finalColor = texColor.rgb + glowColor * glow;

    // Output final color with original alpha
    FragColor = vec4(finalColor, texColor.a);
}