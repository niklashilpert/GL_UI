#version 460 core
layout (location = 0) in vec3 inPos;
layout (location = 1) in vec4 inColor;
layout (location = 2) in float inOuterRadius;
layout (location = 3) in float inInnerRadius;
layout (location = 4) in vec2 inAngleBounds;

layout(std140, binding = 0) uniform ScreenSize {
    vec2 viewportSize;
};

uniform vec2 offset;

out vec4 vColor;
out vec2 vOuterRadius;
out vec2 vInnerRadius;
out vec2 vAngleBounds;

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
    vec2 transformedPos = toGLCoords(toRelativeCoords(vec2(inPos.x, inPos.y) + offset));
    gl_Position = vec4(transformedPos, inPos.z, 1);
    vOuterRadius = vec2(inOuterRadius / viewportSize.x, inOuterRadius / viewportSize.y);
    vInnerRadius = vec2(inInnerRadius / viewportSize.x, inInnerRadius / viewportSize.y);
    vColor = inColor;
    vAngleBounds = inAngleBounds;
}