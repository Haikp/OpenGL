#shader vertex
#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
uniform mat4 camMatrix;

void main()
{
	gl_Position = camMatrix * vec4(aPos, 1.0f);
}

#shader tessellationctrl
#version 460 core

layout(vertices = 3) out;

void main()
{
    gl_TessLevelOuter[0] = 8.0;
    gl_TessLevelOuter[1] = 8.0;
    gl_TessLevelOuter[2] = 8.0;

    gl_TessLevelInner[0] = 8.0;

    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
}

#shader tessellationeval
#version 460 core

layout(triangles, equal_spacing, ccw) in;

vec4 interpolate(vec4 v0, vec4 v1, vec4 v2, vec4 v3)
{
    vec4 a = mix(v0, v1, gl_TessCoord.x);
    vec4 b = mix(v2, v3, gl_TessCoord.x);
    return mix(a, b, gl_TessCoord.y);
}

vec4 interpolate2D(vec4 v0, vec4 v1, vec4 v2)
{
    return vec4(gl_TessCoord.x) * v0 + vec4(gl_TessCoord.y) * v1 + vec4(gl_TessCoord.z) * v2;
}

void main()
{
    gl_Position = interpolate2D(gl_in[0].gl_Position,
                                gl_in[1].gl_Position,
                                gl_in[2].gl_Position);
}

#shader geometry
#version 460 core

layout (triangles) in;
layout (line_strip, max_vertices = 20) out;

void main()
{
    gl_Position = gl_in[0].gl_Position;
    EmitVertex();
    gl_Position = gl_in[1].gl_Position;
    EmitVertex();
    gl_Position = gl_in[2].gl_Position;
    EmitVertex();

    EndPrimitive();
}

#shader fragment
#version 460 core

layout (location = 0) out vec4 fragColor;

in fData
{
    vec3 color;
    mat4 projection;
}frag;

void main()
{
	fragColor = vec4(.5,.5,.5, 1.0);
}
