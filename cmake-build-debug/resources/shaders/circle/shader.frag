#version 460 core
out vec4 FragColor;

in vec4 fPos;
in vec4 fCenter;
in float xRadius;
in float yRadius;
in vec4 fColor;

void main()
{
    float scaledDist =
        pow(fPos.x - fCenter.x, 2) / (xRadius * xRadius) +
        pow(fPos.y - fCenter.y, 2) / (yRadius * yRadius);
    if (scaledDist > 1) discard;
    FragColor = fColor;
}