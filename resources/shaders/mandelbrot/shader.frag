#version 460 core
out vec4 FragColor;

layout(std140, binding = 0) uniform ScreenSize {
    vec2 viewportSize;
};

uniform vec2 uCenter;
uniform float uZoom;
uniform int uIterationCount;

void main()
{

    vec2 uv = (2 * (gl_FragCoord.xy / viewportSize.xy)) + vec2(-1, -1);

    vec2 c = uCenter + uv / uZoom * 2;

    vec2 z = c;

    FragColor = vec4(1, 1, 1, 1);

    for (int i = 0; i < uIterationCount; i++) {
        if (length(z) <= 2) {
            z = vec2((z.x * z.x) - (z.y * z.y), 2 * z.x * z.y) + c; // Represents f(z) = z² + c
        } else {
            FragColor = vec4(float(i) / uIterationCount, float(i) / uIterationCount, float(i) / uIterationCount, 1);
            break;
        }
    }
}