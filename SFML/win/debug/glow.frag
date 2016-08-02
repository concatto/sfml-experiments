uniform sampler2D texture;
uniform vec2 direction;
uniform vec2 step;

vec4 textureDisplaced(float dist) {
	return texture2D(texture, (gl_FragCoord.xy + (direction * dist)) / step);
}

vec4 makeBlur() {
	float blur = 2f;
	vec4 sum = vec4(0f, 0f, 0f, 0f);
	vec2 pos = gl_FragCoord.xy / step;
	
	float values[5];
	values[0] = 0.2270270270;
	values[1] = 0.1945945946;
	values[2] = 0.1216216216;
	values[3] = 0.0540540541;
	values[4] = 0.0162162162;
	
	for (float i = -4f; i <= 4f; i++) {
		sum += textureDisplaced(i * 1f) * values[int(abs(i))];
	}
	
	return sum;
}

void main()
{
    gl_FragColor = gl_Color * makeBlur();
}