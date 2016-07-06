uniform sampler2D texture;
uniform vec2 direction;
uniform vec2 step;

vec4 makeBlur() {
	float blur = 1f;
	float sum = 0f;
    sum += texture2D(texture, gl_TexCoord[0].xy + (step * -4.0 * direction * blur)).a * 0.0162162162;
    sum += texture2D(texture, gl_TexCoord[0].xy + (step * -3.0 * direction * blur)).a * 0.0540540541;
    sum += texture2D(texture, gl_TexCoord[0].xy + (step * -2.0 * direction * blur)).a * 0.1216216216;
    sum += texture2D(texture, gl_TexCoord[0].xy + (step * -1.0 * direction * blur)).a * 0.1945945946;
    
    sum += texture2D(texture, gl_TexCoord[0].xy + step).a * 0.2270270270;
    
    sum += texture2D(texture, gl_TexCoord[0].xy + (step * 1.0 * direction * blur)).a * 0.1945945946;
    sum += texture2D(texture, gl_TexCoord[0].xy + (step * 2.0 * direction * blur)).a * 0.1216216216;
    sum += texture2D(texture, gl_TexCoord[0].xy + (step * 3.0 * direction * blur)).a * 0.0540540541;
    sum += texture2D(texture, gl_TexCoord[0].xy + (step * 4.0 * direction * blur)).a  * 0.062162162;
    
    
    
    return vec4(1f, 0.95f, 0.85f, sum * 2.1);
}

void main()
{
    gl_FragColor = gl_Color * makeBlur();
}