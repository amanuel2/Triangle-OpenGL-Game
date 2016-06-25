#version 130
//The vertex shader operates on each vertex

//input data from the VBO. Each vertex is 2 floats
in vec2 V2_POSITION;
in vec4 V4_COLOR;

out vec4 fragment_interpolation_output;

void main() {
    //Set the x,y position on the screen
    gl_Position.xy = V2_POSITION;
    //the z position is zero since we are in 2D
    gl_Position.z = 1.0;
    
    //Indicate that the coordinates are normalized
    gl_Position.w = 1.0;

	fragment_interpolation_output = V4_COLOR;
}