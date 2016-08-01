uniform sampler2D texture;
uniform vec2 direction;
uniform vec2 step;

vec2 calcPos(float dist) {
	return (gl_FragCoord.xy + (direction * dist)) / step;
}

vec4 makeBlur() {
	float blur = 2f;
	float sum = 0f;
	vec2 pos = gl_FragCoord.xy / step;
	
    sum += texture2D(texture, calcPos(-4f)).a * 0.1162162162;
    sum += texture2D(texture, calcPos(-3f)).a * 0.1540540541;
    sum += texture2D(texture, calcPos(-2f)).a * 0.2216216216;
    sum += texture2D(texture, calcPos(-1f)).a * 0.2945945946;
    
    sum += texture2D(texture, calcPos(0)).a * 0.1270270270;
    
    sum += texture2D(texture, calcPos(1f)).a * 0.2945945946;
    sum += texture2D(texture, calcPos(2f)).a * 0.2216216216;
    sum += texture2D(texture, calcPos(3f)).a * 0.1540540541;
    sum += texture2D(texture, calcPos(4f)).a * 0.162162162;    
    
	sum = 0;
	for (float i = -50; i < 50; i++) {
		sum += (texture2D(texture, calcPos(i)).r / 100f);
	}
	
	return vec4(sum, 1f, 1f, 1f);
}

void main()
{
    gl_FragColor = gl_Color * makeBlur();
}