#ifdef GL_ES
precision mediump float;
#endif

uniform vec2 pos1, pos2;
uniform vec4 color;
uniform vec2 u_resolution;
uniform float u_time;

float getAmplitude(vec2 pos, vec2 globalPos, float t){
    float c=0.05;
    float w=7.0, k=w/c;
    return sin(w*t- k*sqrt(pow(globalPos.x-pos.x,2.0)+ pow(globalPos.y-pos.y,2.0)));
}

void main(){
    float t=u_time;
    vec2 position= gl_FragCoord.xy/u_resolution-vec2(0.5,0.5);
   
    float f1= getAmplitude(pos1/u_resolution-vec2(0.5,0.5), position, u_time);
    float f2= getAmplitude(pos2/u_resolution-vec2(0.5,0.5), position, u_time);

    gl_FragColor= vec4(1.0, (f1+f2)/2.0, 1.0, 1.0)*color;
}