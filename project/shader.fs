#version 450
out vec4 FragColor;
in vec4 Color;

uniform vec2 _iResolution;
uniform float _gridSize = 10.0;
uniform float _iTime;

vec2 fragCoord = gl_FragCoord.xy;
vec2 uv = fragCoord.xy / _iResolution.xy;

float hash(vec2 xy)
{
    return 1.5* fract(sin(
                 dot(xy.xy, 
                    (vec2(12.9898,78.233))))*43758.5453123)-0.5;
}

float noise(vec2 xy)
{
    vec2 i = floor(xy);
    vec2 f = xy - floor(xy);

    //corners
    float a = hash(i);
    float b = hash(i+vec2(1.0, 0.0));
    float c = hash(i+vec2(0.0, 1.0));
    float d = hash(i+vec2(1.0, 1.0));

    //interpolation
    vec2 u = smoothstep(0.0, 1.0, f);

    return mix(a,b,u.x)+(c-a)*u.y * (1.0 - u.x) + (d-b) * u.x * u.y;
}

void main()
{
    uv = uv * 2.0 - 1.0;
    //uv.x *= _iResolution.x / _iResolution.y; 

    vec2 pos = vec2(uv*_gridSize);
    pos.x += _iTime;
    float n = noise(pos);

    //FragColor = Color;
    FragColor = vec4(vec3(n), 1.0);
}

//SOURCES:
//https://thebookofshaders.com/11/
//https://rtouti.github.io/graphics/perlin-noise-algorithm
//https://mrl.cs.nyu.edu/~perlin/paper445.pdf
//https://www.shadertoy.com/view/4dS3Wd

