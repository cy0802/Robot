#version 330 core
out vec4 FragColor;
in vec2 TexCoord;

uniform vec4 color;
// uniform sampler2D _texture;

void main(){
	FragColor = color;
	// FragColor = texture(_texture, TexCoord);
}