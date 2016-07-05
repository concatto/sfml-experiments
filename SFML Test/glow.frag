uniform sampler2D texture;
uniform vec2 step;

int bright() {
	//for (float i = -1f; i <= 1f; i++) {
    	//for (float j = -1f; j <= 1f; j++) {
    		vec4 tr = texture2D(texture, gl_TexCoord[0].xy + (step * vec2(1, 0)));
    		vec4 tl = texture2D(texture, gl_TexCoord[0].xy + (step * vec2(-1, 0)));
    		if ((tr.r >= 0.9 && tr.a >= 0.9) || (tl.r >= 0.9 || tl.a >= 0.9)) {
    			return 1;
    		}
    	//}
    //}
    
    return 0;
}

void main()
{
    if (bright() == 1) {
    	gl_FragColor = vec4(0.9, 0.9, 0.9, 1);
    } else {
    	gl_FragColor = vec4(0.9, 0.9, 0.9, 0);
    }
}