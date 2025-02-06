#version 400

in vec3 Position;
in vec3 Normal;
in vec2 TexCoord;
in vec4 ShadowCoord;

uniform sampler2D BaseTex;
uniform sampler2DShadow ShadowMap;
uniform mat4 ViewMatrix;

uniform sampler3D OffsetTex;
uniform vec3 OffsetTexSize; // (width, height, depth)
uniform float Radius;

struct LightInfo {
  vec3 Ldir;
  vec3 La;
  vec3 Ld;
  vec3 Ls;
};
uniform LightInfo Light;

struct MaterialInfo{
  vec3 Ka;
  vec3 Kd;
  vec3 Ks;
  float Shininess;
};
uniform MaterialInfo Material;

out vec4 FragColor;

vec3 ads(vec3 TexColor)
{
  vec4 s4 = ViewMatrix*vec4(Light.Ldir, 0.0);
  vec3 n = normalize(Normal);
  vec3 v = normalize(-Position);
  vec3 s = normalize(-vec3(s4));
  vec3 r = reflect(-s, n);
  float dRate = max(dot(s, n), 0.0);
  float sRate = pow(max(dot(r, v), 0.0), Material.Shininess);
  vec3 difusse = Light.Ld * Material.Kd * dRate;
  vec3 specular = Light.Ls * Material.Ks * sRate;
  return difusse*TexColor + specular;
}

void main()
{
  vec3 TexColor = vec3( texture(BaseTex,TexCoord) );
  vec3 ambient = Light.La * Material.Ka * TexColor;
  vec3 diffAndSpec = ads(TexColor);
  vec4 ShadowTexCoord = (ShadowCoord/ShadowCoord.w)*0.5 + vec4(0.5, 0.5, 0.5, 0.5);

  ivec3 offsetCoord;
  offsetCoord.xy = ivec2( mod( gl_FragCoord.xy, OffsetTexSize.xy ) );
  float sum = 0.0;
  int samplesDiv2 = int(OffsetTexSize.z);
  vec4 sc = ShadowTexCoord;
  for( int i = 0 ; i< 4; i++ )
  {
    offsetCoord.z = i;
    vec4 offsets = texelFetch(OffsetTex,offsetCoord,0) *Radius * ShadowTexCoord.w;
    sc.xy = ShadowTexCoord.xy + offsets.xy;
    sum += textureProj(ShadowMap, sc);
    sc.xy = ShadowTexCoord.xy + offsets.zw;
    sum += textureProj(ShadowMap, sc);
  }
  float shadow = sum / 8.0;

  if( shadow != 1.0 && shadow != 0.0 )
  {
    for( int i = 4; i< samplesDiv2; i++ )
    {
      offsetCoord.z = i;
      vec4 offsets = texelFetch(OffsetTex, offsetCoord,0)*Radius*ShadowTexCoord.w;
      sc.xy = ShadowTexCoord.xy + offsets.xy;
      sum += textureProj(ShadowMap, sc);
      sc.xy = ShadowTexCoord.xy + offsets.zw;
      sum += textureProj(ShadowMap, sc);
    }
    shadow = sum / float(samplesDiv2 * 2.0);
  }

  FragColor = vec4(diffAndSpec * shadow + ambient, 1.0);
}