uniform sampler2D texture;

void main()
{
    float factor = 1.0 / (1f + 0.001);
    vec2 pos = gl_TexCoord[0].xy / 600.0;
    gl_FragColor = texture2D(texture, pos) * gl_Color;
}