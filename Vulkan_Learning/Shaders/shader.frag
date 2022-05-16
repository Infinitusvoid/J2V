#version 450            // Use GLSL 4.5

layout(location = 0) in vec3 fragColour; // Interpolated colour from vertex (location must match)

layout(location = 0) out vec4 outColor; // Final output colour (must also have location)

void main() {
    outColor = vec4(fragColour, 1.0);
}

