#shader vertex
#version 460 core

// Positions/Coordinates
layout (location = 0) in vec2 aPos;

void main()
{
    gl_Position = vec4(aPos, 0.0f, 1.0f);
}

#shader fragment
#version 460 core

layout (location = 0) out vec4 color;

void main()
{
    color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}
