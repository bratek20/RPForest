#version 330 core

in vec3 Position_modelspace;
in vec3 Position_worldspace;
in vec3 Normal_cameraspace;
in vec2 UV;
in vec3 EyeDirection_cameraspace;
in vec3 LightPosition_worldspace;
in vec3 LightDirection_cameraspace;

uniform vec3 AmbientColor;
uniform vec3 DiffuseColor;
uniform vec3 SpecularColor;

out vec3 color;

void main(){
	vec3 MaterialDiffuseColor = DiffuseColor;
	vec3 MaterialAmbientColor = AmbientColor * MaterialDiffuseColor;
	vec3 MaterialSpecularColor = SpecularColor;

	color = MaterialAmbientColor / 10;
	// Distance to the light
	float distance = length( LightPosition_worldspace - Position_worldspace );

	// Normal of the computed fragment, in camera space
	vec3 n = normalize( Normal_cameraspace );
	// Direction of the light (from the fragment to the light)
	vec3 l = normalize( LightDirection_cameraspace);
	// Cosine of the angle between the normal and the light direction, 
	// clamped above 0
	//  - light is at the vertical of the triangle -> 1
	//  - light is perpendicular to the triangle -> 0
	//  - light is behind the triangle -> 0
	float cosTheta = clamp( dot( n,l ), 0,1 );
	
	// Eye vector (towards the camera)
	vec3 E = normalize(EyeDirection_cameraspace);
	// Direction in which the triangle reflects the light
	vec3 R = reflect(-l,n);
	// Cosine of the angle between the Eye vector and the Reflect vector,
	// clamped to 0
	//  - Looking into the reflection -> 1
	//  - Looking elsewhere -> < 1
	float cosAlpha = clamp( dot( E,R ), 0,1 ); 

	float distanceLoss = 
		//distance * distance * LightDistanceCoefficients[i].x +
		//distance * LightDistanceCoefficients[i].y +
		//LightDistanceCoefficients[i].z;  
		distance;
	float invDistLoss = 1 / distanceLoss;

	float lightPower = 100;
	color += 
		// Diffuse : "color" of the object  
		+ MaterialDiffuseColor * invDistLoss * lightPower * cosTheta
		// Specular : reflective highlight, like a mirror
		+ MaterialSpecularColor * invDistLoss * lightPower * pow(cosAlpha, 10);

	if(length(Normal_cameraspace) < 0.1){
		color = MaterialAmbientColor;
	}
	
}