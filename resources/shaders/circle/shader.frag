#version 460 core
out vec4 FragColor;

in vec4 fPos;
in vec4 fCenter;
in vec4 fColor;
in vec2 fOuterRadius;
in vec2 fInnerRadius;
in vec2 fAngleBounds;

void main()
{
    // Prevent division by zero
    if (fOuterRadius.x == 0 || fOuterRadius.y == 0) discard;
    float outerDist =
        pow(fPos.x - fCenter.x, 2) / (fOuterRadius.x * fOuterRadius.x) +
        pow(fPos.y - fCenter.y, 2) / (fOuterRadius.y * fOuterRadius.y);
    if (outerDist > 1) discard; // Ignore pixels that are outside the outer circle.

    // Prevent division by zero
    float innerDist;
    if (fInnerRadius.x == 0 || fInnerRadius.y == 0) {
        innerDist = 1;
    } else {
        innerDist =
            pow(fPos.x - fCenter.x, 2) / (fInnerRadius.x * fInnerRadius.x) +
            pow(fPos.y - fCenter.y, 2) / (fInnerRadius.y * fInnerRadius.y);
        if (innerDist < 1) discard; // Ignore pixels that are inside the inner circle.

    }

    /*
    -- TODO: Use fAngleBounds to only render partial circles
    if (fAngleBounds.x != 0.0f || fAngleBounds.y != 1.0f) {
        vec2 refAngle = vec2(1, 0);
        vec2 pixelDirection = vec2(fPos.x - fCenter.x, fPos.y - fCenter.y);
        float cosine = acos(pixelDirection.x / length(pixelDirection));// simplified dot product equation between refAngle and pixelDirection
    }
    */

    FragColor = fColor;
}