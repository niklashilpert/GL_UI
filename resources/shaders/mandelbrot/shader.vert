#version 460 core
layout (location = 0) in vec3 inPos;

layout(std140, binding = 0) uniform ScreenSize {
    vec2 viewportSize;
};

uniform vec3 uOffset;

const mat2 TRANSFORM = mat2(2, 0, 0, -2);

// Transforms absolute pixel coords into relative coords.
vec2 toRelativeCoords(vec2 coords) {
    return vec2(coords.x / viewportSize.x, coords.y / viewportSize.y);
}

// Transforms top-left relative coords into GL-coords.
vec2 toGLCoords(vec2 coords) {
    return (TRANSFORM * coords) + vec2(-1, 1);
}

void main()
{
    vec2 transformedPos = toGLCoords(toRelativeCoords(vec2(inPos.x, inPos.y)));
    gl_Position = vec4(transformedPos, inPos.z, 1) + vec4(uOffset, 0);
}