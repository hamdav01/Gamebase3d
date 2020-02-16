// globals
float4x4 g_World;
float4x4 g_ViewProj;

float3 g_LightDirection;
float4 g_LightColor;

Texture2D g_DiffuseTexture;

SamplerState diffuseSampler {
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = Wrap;
	AddressV = Wrap;
};

DepthStencilState DepthOn {
	DepthEnable = TRUE;
};

DepthStencilState DepthOff {
	DepthEnable = FALSE;
};

struct VS_OUT {
	float4 pos : SV_POSITION;
	float4 col : COLOR;
	float3 nor : NORMAL;
	float2 tex : TEXCOORD;
};

struct VS_ORTHO_OUT {
	float4 pos : SV_POSITION;
	float2 tex : TEXCOORD;
};

// main vertex and pixel shader code
VS_OUT vs_main( float4 Pos : POSITION, float4 Color : COLOR, 
				float3 Normal : NORMAL, float2 TexCoord : TEXCOORD ) {
	Pos=mul(Pos,g_World);
	Pos=mul(Pos,g_ViewProj);
	Normal=normalize(mul(Normal,(float3x3)g_World));

	VS_OUT OUT;
	OUT.pos=Pos;
	OUT.col=Color;
	OUT.nor=Normal;
	OUT.tex=TexCoord;
    return OUT;
}

float4 ps_main( VS_OUT IN ) : SV_Target {
	IN.nor=normalize(IN.nor);

	float light_factor=saturate(dot(-g_LightDirection,IN.nor));
	light_factor=clamp(light_factor,0.3f,1.0f);
	float4 color=g_DiffuseTexture.Sample(diffuseSampler,IN.tex);

	return color*light_factor*g_LightColor;
}

VS_ORTHO_OUT vs_skybox_main(float4 Pos : POSITION, float2 Tex : TEXCOORD) {
	Pos=mul(Pos,g_World);
	Pos=mul(Pos,g_ViewProj);

	VS_ORTHO_OUT OUT;
	OUT.pos=Pos;
	OUT.tex=Tex;
	return OUT;
}

float4 ps_skybox_main(VS_ORTHO_OUT IN) : SV_Target {
	return g_DiffuseTexture.Sample(diffuseSampler,IN.tex);
}

// ortho shaders
VS_ORTHO_OUT vs_ortho_main(float2 Pos : POSITION, float2 Tex : TEXCOORD) {
	VS_ORTHO_OUT OUT;
	OUT.pos=mul(float4(Pos,0,1),g_ViewProj);
	OUT.tex=Tex;
	return OUT;
}

float4 ps_ortho_main(VS_ORTHO_OUT IN) : SV_Target {
	return g_DiffuseTexture.Sample(diffuseSampler,IN.tex);
}


// tech
technique10 Basic {
    pass P0 {
        SetVertexShader(CompileShader(vs_4_0,vs_main()));
        SetGeometryShader(NULL);
        SetPixelShader(CompileShader(ps_4_0,ps_main()));
		SetDepthStencilState(DepthOn,0.0f);
    }
}
technique10 Skybox {
	pass P0 {
		SetGeometryShader(NULL);
		SetVertexShader(CompileShader(vs_4_0,vs_skybox_main()));
		SetPixelShader(CompileShader(ps_4_0,ps_skybox_main()));
		SetDepthStencilState(DepthOff,0.0f);
	}
}
technique10 BasicOrtho {
    pass P0 {
		SetGeometryShader(NULL);
        SetVertexShader(CompileShader(vs_4_0,vs_ortho_main()));
        SetPixelShader(CompileShader(ps_4_0,ps_ortho_main()));
		SetDepthStencilState(DepthOn,0.0f);
    }
}
