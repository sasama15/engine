#include "MultiTexture.hlsli"

Texture2D<float4> tex0 : register(t0);   // 0番スロットに設定されたテクスチャ
Texture2D<float4> tex1 : register(t1);   // 0番スロットに設定されたテクスチャ
SamplerState smp : register(s0);        // 0番スロットに設定されたサンプラー

float4 main(VSOutput input) : SV_TARGET
{
	float4 colortex0 = tex0.Sample(smp, input.uv);
	float4 colortex1 = tex1.Sample(smp, input.uv);

	//紫
	// UVしたピクセルの色をサンプリング
	float4 color = float4(1.0f - colortex0.rgb, 1);

	if (fmod(input.uv.y, 0.1f) < 0.05f) {
		// ぼかし
		const float U = 1.0f / 1280.0f;
		const float V = 1.0f / 720.0f;
		float4 texcolor = { 0, 0, 0, 0 };

		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				colortex1 += tex0.Sample(smp, input.uv + float2(i * U, j * V));
			}
		}

		color = float4 (colortex1.rgb / 100.0f, 1);
	}
	return float4(color.rgb, 1);
}
