uniform sampler2D heightTexture;
uniform float coef;

void main()
{	
	vec4 displacement = vec4(gl_Normal, 0.0) * texture2D(heightTexture, gl_MultiTexCoord0.xy).r * coef;
	gl_TexCoord[0].xy = gl_MultiTexCoord0.xy;
	gl_Position = gl_ModelViewProjectionMatrix * (gl_Vertex + displacement);
}