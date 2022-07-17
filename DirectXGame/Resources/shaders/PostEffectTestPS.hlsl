#include "PostEffectTest.hlsli"

Texture2D<float4> tex : register(t0);   // 0�ԃX���b�g�ɐݒ肳�ꂽ�e�N�X�`��
SamplerState smp : register(s0);        // 0�ԃX���b�g�ɐݒ肳�ꂽ�T���v���[

float4 main(VSOutput input) : SV_TARGET
{
    // ��
    /*float4 texcolor = tex.Sample(smp, input.uv);

    return float4(texcolor.rgb, 1);*/

    ////���邢��
    //// UV�����s�N�Z���̐F���T���v�����O
    //float4 texcolor = tex.Sample(smp, input.uv);
    //// RGB�̐��l��2�{���ďo��
    //return float4(texcolor.rgb * 2.0f, 1);

    ////��
    //// UV�����s�N�Z���̐F���T���v�����O
    //float4 texcolor = tex.Sample(smp, input.uv);
    //// RGB�̐��l��2�{���ďo��
    //return float4( 1.0f - texcolor.rgb, 1);

    //// UV���炵
    //// UV�����s�N�Z���̐F���T���v�����O
    //float4 texcolor = tex.Sample(smp, input.uv + float2 (0.5f, 0.0f));
    //// RGB�̐��l��2�{���ďo��
    //return float4(1.0f - texcolor.rgb, 1);

    // �ڂ���
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
