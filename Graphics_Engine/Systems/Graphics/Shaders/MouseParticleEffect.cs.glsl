#version 430

layout(std140, binding = 0) buffer Pos
{
   vec4 Positions[];
};

layout(std140, binding = 1) buffer Vel
{
    vec4 Velocities[];
};

layout(std140, binding = 2) buffer Acc
{
    vec4 Accelerations[];
};

layout (local_size_x = 16, local_size_y = 16) in;

uniform float dTime;
uniform vec3 destPos;
uniform float et;


// makes a pseudorandom number between 0 and 1
float hash(float n) {
  return fract(sin(n)*93942.234);
}

// smoothsteps a grid of random numbers at the integers
float noise(vec2 p) {
  vec2 w = floor(p);
  vec2 k = fract(p);
  k = k*k*(3.-2.*k); // smooth it
  
  float n = w.x + w.y*57.;
  
  float a = hash(n);
  float b = hash(n+1.);
  float c = hash(n+57.);
  float d = hash(n+58.);
  
  return mix(
    mix(a, b, k.x ),
    mix(c, d, k.x),
    k.y);
}
// rotation matrix
mat2 m = mat2(0.6,0.8,-0.8,0.6);


// fractional brownian motion (i.e. photoshop clouds)
float fbm(vec2 p) {
  float f = 0.;
  f += 0.5000*noise(p); p *= 2.02*m;
  f += 0.2500*noise(p); p *= 2.01*m;
  f += 0.1250*noise(p); p *= 2.03*m;
  f += 0.0625*noise(p);
  f /= 0.9375;
  return f;
}

void main()
{
  // Shader Buffer index
  uint index = gl_GlobalInvocationID.x;

  vec3 vPos = Positions[index].xyz;
  vec3 vVel = Velocities[index].xyz;
  vec3 vAcc = Accelerations[index].xyz;

  vAcc += normalize(destPos - vPos) * sin ((et));
  vVel += normalize(destPos - vPos) * sin (fbm (vAcc.xy * 0.00001 * et));

  vPos += vVel * dTime;

  Positions[index].xyz = vPos;
  Velocities[index].xyz = vVel;
  Accelerations [index].xyz = vAcc;
}