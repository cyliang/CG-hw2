varying vec3 normal, lightDir, eyeDir;

attribute vec3 tangent, bitangent;
varying vec3 _tangent, _bitangent;

void main()
{	
	normal = gl_NormalMatrix * gl_Normal;

	vec3 vVertex = vec3(gl_ModelViewMatrix * gl_Vertex);

	lightDir = vec3(gl_LightSource[0].position.xyz - vVertex);
	eyeDir = -vVertex;
	
	gl_TexCoord[0].xy = gl_MultiTexCoord0.xy;
	_tangent = tangent;
	_bitangent = bitangent;

	gl_Position = ftransform();		
}