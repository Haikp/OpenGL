#shader vertex
#version 460 core

// Positions/Coordinates
layout (location = 0) in vec3 aPos;
// Colors
layout (location = 1) in vec3 aColor;
// Texture Coordinates
layout (location = 2) in vec2 aTex;


// Outputs the color for the Fragment Shader
out vec3 color;
// Outputs the texture coordinates to the fragment shader
out vec2 texCoord;

// Imports the camera matrix from the main function
uniform mat4 camMatrix;


void main()
{
    // Outputs the positions/coordinates of all vertices
    gl_Position = camMatrix * vec4(aPos, 1.0);
    // Assigns the colors from the Vertex Data to "color"
    color = aColor;
    // Assigns the texture coordinates from the Vertex Data to "texCoord"
    texCoord = aTex;
}

#shader fragment
#version 460 core

// Outputs colors in RGBA
layout (location = 0) out vec4 fragColor;

in vec3 color;
in vec3 texCoord;

void main()
{
    fragColor = vec4(color, 1.0f);
}