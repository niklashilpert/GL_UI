#version 460 core
layout (location = 0) in vec3 inPos1;
layout (location = 1) in vec3 inPos2;
layout (location = 2) in vec4 inColor;
layout (location = 3) in float inWidth;

layout(std140, binding = 0) uniform ScreenSize {
    vec2 viewportSize;
};

out vec3 vPos1;
out vec3 vPos2;
out vec3 vOrthogonal;
out vec4 vColor;

const mat3 TRANSFORM = mat3(2, 0, 0, 0, -2, 0, 0, 0, 1);

// Transforms absolute pixel coords into relative coords.
vec3 toRelativeCoords(vec3 coords) {
    return vec3(coords.x / viewportSize.x, coords.y / viewportSize.y, coords.z);
}

// Transforms top-left relative coords into GL-coords.
vec3 toGLCoords(vec3 coords) {
    return (TRANSFORM * coords) + vec3(-1, 1, 0);
}

void main()
{
    vColor = inColor;
    vPos1 = toGLCoords(toRelativeCoords(inPos1));
    vPos2 = toGLCoords(toRelativeCoords(inPos2));

    vec3 orthDirection = cross(vec3(0, 0, 1), vPos2 - vPos1);
    vec3 orthPixel = normalize(orthDirection) * (inWidth / 2);
    vOrthogonal = orthPixel / vec3(viewportSize.x, viewportSize.y, 1);
}