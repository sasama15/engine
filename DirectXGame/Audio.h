#pragma once
#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <d3dx12.h>

#include <xaudio2.h>
#pragma comment(lib,"xaudio2.lib")



class Audio
{
public: // インナークラス
    // チャンクヘッダ
    struct ChunkHeader
    {
        char id[4]; // チャンク毎のID
        int32_t size;  // チャンクサイズ
    };

    // RIFFヘッダチャンク
    struct RiffHeader
    {
        ChunkHeader chunk;   // "RIFF"
        char type[4]; // "WAVE"
    };

    // FMTチャンク
    struct FormatChunk
    {
        ChunkHeader chunk; // "fmt "
        WAVEFORMATEX fmt; // 波形フォーマット
    };

    struct SoundData
    {
        // 波形フォーマット
        WAVEFORMATEX wfex;
        // バッファの先頭アドレス
        BYTE* pBuffer;
        // バッファのサイズ
        unsigned int bufferSize;
    };

    class XAudio2VoiceCallback : public IXAudio2VoiceCallback
    {
    public:
        // ボイス処理パスの開始時
        STDMETHOD_(void, OnVoiceProcessingPassStart) (THIS_ UINT32 BytesRequired) {};
        // ボイス処理パスの終了時
        STDMETHOD_(void, OnVoiceProcessingPassEnd) (THIS) {};
        // バッファストリームの再生が終了した時
        STDMETHOD_(void, OnStreamEnd) (THIS) {};
        // バッファの使用開始時
        STDMETHOD_(void, OnBufferStart) (THIS_ void* pBufferContext) {};
        // バッファの末尾に達した時
        STDMETHOD_(void, OnBufferEnd) (THIS_ void* pBufferContext) {};
        // 再生がループ位置に達した時
        STDMETHOD_(void, OnLoopEnd) (THIS_ void* pBufferContext) {};
        // ボイスの実行エラー時
        STDMETHOD_(void, OnVoiceError) (THIS_ void* pBufferContext, HRESULT Error) {};
    };

public:	// 静的メンバ関数
    static SoundData SoundLoadWave(const char* filename);

    // 音声再生
    static void SoundPlayWave(const SoundData& soundData);

    // 音声データ解放
    static void SoundUnload(SoundData* soundData);

    static void Initialize();

    static void Finalize();

private:
   

   

    

    static Microsoft::WRL::ComPtr<IXAudio2> xAudio2;
    static IXAudio2MasteringVoice* masterVoice;
    XAudio2VoiceCallback voiceCallback;
};



