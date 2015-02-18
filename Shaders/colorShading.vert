#version 120

varying vec2 vertexPosition;
uniform float array[8];

void main() {
/*
   vec4 v = vec4(gl_Vertex);
      // v.z = sin(5.0*v.z)*0.25;
      v.z = array[i];*/

      //gl_Position = gl_ModelViewProjectionMatrix * v;

   for (int i = 0;i < 8;i++)
   {
      vec4 v = vec4(gl_Vertex);
      v.y = array[i];
      gl_Position = gl_ModelViewProjectionMatrix * v;
   }
}
