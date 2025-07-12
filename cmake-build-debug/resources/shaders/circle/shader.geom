#version 460 core
layout (points) in;
layout (triangle_strip, max_vertices=6) out;

in vec4 vColor[];
in vec2 vRadius[];

out vec4 fCenter;
out vec4 fColor;
out float xRadius;
out float yRadius;
out vec4 fPos;


void main() {
    fCenter = gl_in[0].gl_Position;
    fColor = vColor[0];

    xRadius = vRadius[0].x;
    yRadius = vRadius[0].y;

    gl_Position = gl_in[0].gl_Position + vec4(xRadius, yRadius, 0, 0);
    fPos = gl_Position;
    EmitVertex();
    gl_Position = gl_in[0].gl_Position + vec4(-xRadius, yRadius, 0, 0);
    fPos = gl_Position;
    EmitVertex();
    gl_Position = gl_in[0].gl_Position + vec4(-xRadius, -yRadius, 0, 0);
    fPos = gl_Position;
    EmitVertex();
    gl_Position = gl_in[0].gl_Position + vec4(xRadius, yRadius, 0, 0);
    fPos = gl_Position;
    EmitVertex();
    gl_Position = gl_in[0].gl_Position + vec4(xRadius, -yRadius, 0, 0);
    fPos = gl_Position;
    EmitVertex();
    gl_Position = gl_in[0].gl_Position + vec4(-xRadius, -yRadius, 0, 0);
    fPos = gl_Position;
    EmitVertex();

    EndPrimitive();
}