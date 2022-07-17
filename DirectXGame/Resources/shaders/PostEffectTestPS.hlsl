#include "PostEffectTest.hlsli"

Texture2D<float4> tex : register(t0);   // 0番スロットに設定されたテクスチャ
SamplerState smp : register(s0);        // 0番スロットに設定されたサンプラー

float4 main(VSOutput input) : SV_TARGET
{
    // 緑
    /*float4 texcolor = tex.Sample(smp, input.uv);

    return float4(texcolor.rgb, 1);*/

    ////明るい緑
    //// UVしたピクセルの色をサンプリング
    //float4 texcolor = tex.Sample(smp, input.uv);
    //// RGBの数値を2倍して出力
    //return float4(texcolor.rgb * 2.0f, 1);

    ////紫
    //// UVしたピクセルの色をサンプリング
    //float4 texcolor = tex.Sample(smp, input.uv);
    //// RGBの数値を2倍して出力
    //return float4( 1.0f - texcolor.rgb, 1);

    //// UVずらし
    //// UVしたピクセルの色をサンプリング
    //float4 texcolor = tex.Sample(smp, input.uv + float2 (0.5f, 0.0f));
    //// RGBの数値を2倍して出力
    //return float4(1.0f - texcolor.rgb, 1);

    // ぼかし
    const float U = 1.0f / 1280.0f;
    const float V = 1.0f / 720.0f;
    float4 texcolor = { 0, 0, 0, 0 };

   /* texcolor += tex.Sample(smp, input.uv + float2(-U, -V));
    texcolor += tex.Sample(smp, input.uv + float2(0.0f, -V));
    texcolor += tex.Sample(smp, input.uv + float2(+U, -V));

    texcolor += tex.Sample(smp, input.uv + float2(-U, 0.0f));
    texcolor += tex.Sample(smp, input.uv + float2(0.0f, 0.0f));
    texcolor += tex.Sample(smp, input.uv + float2(+U, 0.0f));

    texcolor += tex.Sample(smp, input.uv + float2(-U, +V));
    texcolor += tex.Sample(smp, input.uv + float2(0.0f, +V));
    texcolor += tex.Sample(smp, input.uv + float2(+U, +V));

    return float4 (texcolor.rgb / 9.0f, 1);*/

    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 1; j++) {
            texcolor += tex.Sample(smp, input.uv + float2(i * U, j * V));
        }
    }
return  float4 (texcolor.rgb / 100.0f, 1);
}
