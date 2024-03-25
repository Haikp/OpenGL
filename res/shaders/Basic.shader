#shader vertex
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
uniform mat4 camMatrix;

out vec2 vertTexCoord;

void main()
{
	gl_Position = camMatrix * vec4(aPos, 1.0f);
    vertTexCoord = aTexCoord;
}

#shader fragment
#version 330 core

layout (location = 0) out vec4 fragColor;

in vec2 vertTexCoord;

uniform sampler2D u_Texture;
uniform vec4 u_Color;

void main()
{
    // float h = (outHeight + 16) / 64.0f
    vec4 texColor = texture(u_Texture, vertTexCoord);
    color = texColor;
}
