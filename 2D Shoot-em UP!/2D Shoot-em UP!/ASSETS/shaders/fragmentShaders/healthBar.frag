// Lightning
// By: Brandon Fogerty
// bfogerty at gmail dot com 
// xdpixel.com


// MORE MODS BY 27

// And then by some guy called Hugh.


#ifdef GL_ES
precision lowp float;
#endif

uniform float hp;
uniform float time;
uniform vec2 resolution;
uniform float r;
uniform float g;

float Hash( vec2 p)
{
	vec3 p2 = vec3(p.xy,1.);
	return fract(sin(dot(p2,vec3(37.1,61.7, 12.4)))*3758.5453123);
}

float noise(in vec2 p)
{
	vec2 i = floor(p);
	vec2 f = fract(p);
	f *= f * (3.-2.*f);

	return mix(mix(Hash(i + vec2(0.,0.)), Hash(i + vec2(1.,0.)),f.x),
               mix(Hash(i + vec2(0.,1.)), Hash(i + vec2(1.,1.)),f.x),
               f.y);
}

float fbm(vec2 p)
{
	float v = 0.;	
	float n = 3.;
	for(float f = 1.; f<=1.; f++) v += noise(p*f)*(n-f)/(n*n);
	return v;
}

void main( void ) 
{

	vec2 uv = ( gl_FragCoord.xy / resolution.xy ) * 1.1 - 1.0;
	uv.x *= resolution.x/resolution.y;
		
	vec3 finalColor = vec3( 0.0 );
	float i = hp;
	float hh = .1;
	
	
	
	
	float v = abs(1. / ((uv.y +  - fbm( uv + (time*2.)/i))*75.));
	finalColor +=  v * vec3( r, g, 0.0 );
	
	
	gl_FragColor = vec4( finalColor, 2.0 );

}