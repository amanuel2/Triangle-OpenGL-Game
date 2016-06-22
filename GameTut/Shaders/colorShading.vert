#version 130

in vec2 vertexPosition;

void main(){
  //Set Positions
   gl_Position.xy = vertexPosition;
   //3D. Not in Need now..
   gl_Position.z = 0.0;
   //Not in Need Now..
   gl_Position.w = 0.0
}