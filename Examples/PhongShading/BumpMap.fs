varying vec3 normal, lightDir, eyeDir;
varying vec3 _tangent, _bitangent;

uniform sampler2D colorTexture;
uniform sampler2D heightTexture;
uniform float textureWidth;
uniform float coef;

vec4 PhongShading(vec3 normal);
vec3 disturbNormal(vec3 normal);

void main (void)
{
	vec3 newNormal = disturbNormal(normal);
	gl_FragColor = PhongShading(newNormal);
}

vec3 disturbNormal(vec3 N) {
    float du = texture2D(heightTexture, gl_TexCoord[0].xy + vec2(1.0 / textureWidth, 0.0)).r - 
        texture2D(heightTexture, gl_TexCoord[0].xy).r;

    float dv = texture2D(heightTexture, gl_TexCoord[0].xy + vec2(0.0, 1.0 / textureWidth)).r - 
        texture2D(heightTexture, gl_TexCoord[0].xy).r;

    return N - (du * _tangent + dv * _bitangent) * coef;
}

vec4 PhongShading(vec3 normal) {
    vec4 final_color = 
	    (gl_FrontLightModelProduct.sceneColor * gl_FrontMaterial.ambient) + 
	    (gl_LightSource[0].ambient * gl_FrontMaterial.ambient);
							
	vec3 N = normalize(normal);
	vec3 L = normalize(lightDir);
	
	float lambertTerm = dot(N,L);
	
	if(lambertTerm > 0.0)
	{
		final_color += gl_LightSource[0].diffuse * 
		               texture2D(colorTexture, gl_TexCoord[0].xy) * 
					   lambertTerm;	
		
		vec3 E = normalize(eyeDir);
		vec3 R = reflect(-L, N);
		float specular = pow( max(dot(R, E), 0.0), 
		                 gl_FrontMaterial.shininess );
		final_color += gl_LightSource[0].specular * 
		               gl_FrontMaterial.specular * 
					   specular;	
	}

    return final_color;
}