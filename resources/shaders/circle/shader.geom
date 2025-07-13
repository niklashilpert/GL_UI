#version 460 core
layout (points) in;
layout (triangle_strip, max_vertices=6) out;

in vec4 vColor[];
in vec2 vOuterRadius[];
in vec2 vInnerRadius[];
in vec2 vAngleBounds[];

out vec4 fPos;
out vec4 fCenter;
out vec4 fColor;
out vec2 fOuterRadius;
out vec2 fInnerRadius;
out vec2 fAngleBounds;

void main() {
    fCenter = gl_in[0].gl_Position;
    fColor = vColor[0];
    fOuterRadius = vOuterRadius[0];
    fInnerRadius = vInnerRadius[0];
    fAngleBounds = vAngleBounds[0];

    gl_Position = gl_in[0].gl_Position + vec4(fOuterRadius.x, fOuterRadius.y, 0, 0);
    fPos = gl_Position;
    EmitVertex();
    gl_Position = gl_in[0].gl_Position + vec4(-fOuterRadius.x, fOuterRadius.y, 0, 0);
    fPos = gl_Position;
    EmitVertex();
    gl_Position = gl_in[0].gl_Position + vec4(-fOuterRadius.x, -fOuterRadius.y, 0, 0);
    fPos = gl_Position;
    EmitVertex();
    gl_Position = gl_in[0].gl_Position + vec4(fOuterRadius.x, fOuterRadius.y, 0, 0);
    fPos = gl_Position;
    EmitVertex();
    gl_Position = gl_in[0].gl_Position + vec4(fOuterRadius.x, -fOuterRadius.y, 0, 0);
    fPos = gl_Position;
    EmitVertex();
    gl_Position = gl_in[0].gl_Position + vec4(-fOuterRadius.x, -fOuterRadius.y, 0, 0);
    fPos = gl_Position;
    EmitVertex();

    EndPrimitive();
}