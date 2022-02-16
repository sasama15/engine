#include "Input.h"
//#include <wrl.h>

//using namespace Microsoft::WRL;

//#define DIRECTINPUT_VERSION	0x0800	// DirectInput�̃o�[�W�����w��
//#include <dinput.h>

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

void Input::Initialize(WinApp* winApp){
	HRESULT result;

	// �؂�Ă���winApp�̃C���X�^���X���L�^
	this->winApp = winApp;

	// DirectInput�̃C���X�^���X����
	//ComPtr<IDirectInput8> dinput = nullptr;
	result = DirectInput8Create(winApp->GetHInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&dinput, nullptr);
	
	// �L�[�{�[�h�f�o�C�X����
	//ComPtr<IDirectInputDevice8> devkeyboard;
	result = dinput->CreateDevice(GUID_SysKeyboard, &devkeyboard, NULL);
	
	// ���̓f�[�^�`���̃Z�b�g
	result = devkeyboard->SetDataFormat(&c_dfDIKeyboard);
	
	// �r�����䃌�x���̃Z�b�g
	result = devkeyboard->SetCooperativeLevel(winApp->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
}

void Input::Update(){
	HRESULT result;

	// �O��̃L�[���͂�ۑ�
	memcpy(keyPre, key, sizeof(key));

	// �L�[�{�[�h���̎擾�J�n
	result = devkeyboard->Acquire();

	// �S�L�[�̓��͏����擾����
	//BYTE key[256] = {};
	result = devkeyboard->GetDeviceState(sizeof(key), key);
}

bool Input::PushKey(BYTE keyNumber){
	// �w��L�[�������Ă����true��Ԃ�
	if (key[keyNumber]) {
		return true;
	}
	// �����łȂ����false��Ԃ�
	return false;
}

bool Input::TriggerKey(BYTE keyNumber)
{
	if (!keyPre[keyNumber] && key[keyNumber]) {
		return true;
	}
	// �����łȂ����false��Ԃ�
	return false;
}
