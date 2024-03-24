#shader vertex
#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
uniform mat4 camMatrix;

// out vec2 vertTexCoord;
// out mat4 cam;

void main()
{
	gl_Position = camMatrix * vec4(aPos, 1.0f);
    // vertTexCoord = aTexCoord;
    // cam = camMatrix;
}

#shader tessellationctrl
#version 460 core

layout(vertices = 4) out;

// in vec2 vertTexCoord[];
// flat in mat4 cam[];

// out vec2 ctrlTexCoord[];
// flat out mat4 camMatrix[];

void main()
{
    if (gl_InvocationID == 0)
    {
        gl_TessLevelOuter[0] = 16.0;
        gl_TessLevelOuter[1] = 16.0;
        gl_TessLevelOuter[2] = 16.0;
        gl_TessLevelOuter[3] = 16.0;

        gl_TessLevelInner[0] = 16.0;
        gl_TessLevelInner[1] = 16.0;

    }

    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
    // ctrlTexCoord[gl_InvocationID] = vertTexCoord[gl_InvocationID];
    // camMatrix[gl_InvocationID] = cam[0];
}

#shader tessellationeval
#version 460 core

layout(quads, equal_spacing, ccw) in;
// uniform sampler2D heightMap;

// in vec2 TexCoord[];
// in camMatrix[];

// out float Height;

vec4 interpolate(vec4 v0, vec4 v1, vec4 v2, vec4 v3)
{
    vec4 a = mix(v3, v2, gl_TessCoord.x);
    vec4 b = mix(v0, v1, gl_TessCoord.x);
    return mix(a, b, gl_TessCoord.y);
}

vec4 interpolate2D(vec4 v0, vec4 v1, vec4 v2)
{
    return vec4(gl_TessCoord.x) * v0 + vec4(gl_TessCoord.y) * v1 + vec4(gl_TessCoord.z) * v2;
}

void main()
{
    gl_Position = interpolate(gl_in[0].gl_Position,
                              gl_in[1].gl_Position,
                              gl_in[2].gl_Position,
                              gl_in[3].gl_Position);
}

#shader geometry
#version 460 core

layout (triangles) in;
layout (line_strip, max_vertices = 3) out;

// in float Height[];

// out float outHeight;

void main()
{
    gl_Position = gl_in[0].gl_Position;
    EmitVertex();
    gl_Position = gl_in[1].gl_Position;
    EmitVertex();
    gl_Position = gl_in[2].gl_Position;
    EmitVertex();

    EndPrimitive();

    // outHeight = Height[0];
}

#shader fragment
#version 460 core

layout (location = 0) out vec4 fragColor;

// in outHeight;

in fData
{
    vec3 color;
    mat4 projection;
}frag;

void main()
{
    // float h = (outHeight + 16) / 64.0f;
	fragColor = vec4(1, 1, 1, 1.0);
}
