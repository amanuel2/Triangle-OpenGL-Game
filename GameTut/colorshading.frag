#version 130
//The fragment shader operates on each pixel in a given polygon

//This is the 3 component float vector that gets outputted to the screen
//for each pixel.
out vec4 color;

in vec4 fragment_interpolation_output;

void main() {
    //Just hardcode the color to red
    color = fragment_interpolation_output;

}