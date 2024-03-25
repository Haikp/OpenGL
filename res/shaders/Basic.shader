#shader vertex
#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
uniform mat4 camMatrix;

out vec2 vertTexCoord;

void main()
{
	gl_Position = camMatrix * vec4(aPos, 1.0f);
    vertTexCoord = aTexCoord;
}

#shader tessellationctrl
#version 460 core

layout(vertices = 4) out;

in vec2 vertTexCoord[];

out vec2 ctrlTexCoord[];

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
    ctrlTexCoord[gl_InvocationID] = vertTexCoord[gl_InvocationID];
}

#shader tessellationeval
#version 460 core

layout(quads, equal_spacing, ccw) in;
uniform mat4 camMatrix;

in vec2 TexCoord[];

out float Height;

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

    // float u = gl_TessCoord.x;
    // float v = gl_TessCoord.y;

    // vec2 t00 = TexCoord[0];
    // vec2 t01 = TexCoord[1];
    // vec2 t10 = TexCoord[2];
    // vec2 t11 = TexCoord[3];

    // // bilinearly interpolate texture coordinate across patch
    // vec2 t0 = (t01 - t00) * u + t00;
    // vec2 t1 = (t11 - t10) * u + t10;
    // vec2 texCoord = (t1 - t0) * v + t0;

    // Height = texture(u_heightMap, TexCoord).y * 64.0 - 16.0;
}

#shader geometry
#version 460 core

layout (triangles) in;
layout (line_strip, max_vertices = 3) out;

in float Height[];

out float fragHeight;

void main()
{
    gl_Position = gl_in[0].gl_Position;
    EmitVertex();
    gl_Position = gl_in[1].gl_Position;
    EmitVertex();
    gl_Position = gl_in[2].gl_Position;
    EmitVertex();

    EndPrimitive();

    fragHeight = Height[0];
}

#shader fragment
#version 460 core

layout (location = 0) out vec4 fragColor;

// uniform sampler2D u_Texture;
uniform vec4 u_Color;

in float fragHeight;

// in fData
// {
//     vec3 color;
//     mat4 projection;
// }frag;

void main()
{
    // float h = (outHeight + 16) / 64.0f;
	fragColor = u_Color;
}
