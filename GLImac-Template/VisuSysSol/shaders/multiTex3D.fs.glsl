#version 330 core

in vec3 vFragPositionVS;
in vec3 vFragNormalVS;
in vec2 vFragTex;

out vec3 fFragNormalVS;

uniform sampler2D uTexture;
uniform sampler2D uTexture2;

void main(){
    vec4 tmp = texture(uTexture, vFragTex);
    vec4 tmp2 = texture(uTexture2, vFragTex);
    fFragNormalVS = tmp.xyz + tmp2.xyz;
}
