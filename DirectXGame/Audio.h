#pragma once
#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <d3dx12.h>

#include <xaudio2.h>
#pragma comment(lib,"xaudio2.lib")



class Audio
{
public: // �C���i�[�N���X
    // �`�����N�w�b�_
    struct ChunkHeader
    {
        char id[4]; // �`�����N����ID
        int32_t size;  // �`�����N�T�C�Y
    };

    // RIFF�w�b�_�`�����N
    struct RiffHeader
    {
        ChunkHeader chunk;   // "RIFF"
        char type[4]; // "WAVE"
    };

    // FMT�`�����N
    struct FormatChunk
    {
        ChunkHeader chunk; // "fmt "
        WAVEFORMATEX fmt; // �g�`�t�H�[�}�b�g
    };

    struct SoundData
    {
        // �g�`�t�H�[�}�b�g
        WAVEFORMATEX wfex;
        // �o�b�t�@�̐擪�A�h���X
        BYTE* pBuffer;
        // �o�b�t�@�̃T�C�Y
        unsigned int bufferSize;
    };

    class XAudio2VoiceCallback : public IXAudio2VoiceCallback
    {
    public:
        // �{�C�X�����p�X�̊J�n��
        STDMETHOD_(void, OnVoiceProcessingPassStart) (THIS_ UINT32 BytesRequired) {};
        // �{�C�X�����p�X�̏I����
        STDMETHOD_(void, OnVoiceProcessingPassEnd) (THIS) {};
        // �o�b�t�@�X�g���[���̍Đ����I��������
        STDMETHOD_(void, OnStreamEnd) (THIS) {};
        // �o�b�t�@�̎g�p�J�n��
        STDMETHOD_(void, OnBufferStart) (THIS_ void* pBufferContext) {};
        // �o�b�t�@�̖����ɒB������
        STDMETHOD_(void, OnBufferEnd) (THIS_ void* pBufferContext) {};
        // �Đ������[�v�ʒu�ɒB������
        STDMETHOD_(void, OnLoopEnd) (THIS_ void* pBufferContext) {};
        // �{�C�X�̎��s�G���[��
        STDMETHOD_(void, OnVoiceError) (THIS_ void* pBufferContext, HRESULT Error) {};
    };

public:	// �ÓI�����o�֐�
    static SoundData SoundLoadWave(const char* filename);

    // �����Đ�
    static void SoundPlayWave(const SoundData& soundData);

    // �����f�[�^���
    static void SoundUnload(SoundData* soundData);

    static void Initialize();

    static void Finalize();

private:
   

   

    

    static Microsoft::WRL::ComPtr<IXAudio2> xAudio2;
    static IXAudio2MasteringVoice* masterVoice;
    XAudio2VoiceCallback voiceCallback;
};



