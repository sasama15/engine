#include "LightGroup.h"
#include <assert.h>

using namespace DirectX;

void LigthGroup::TransferConstBuffer() {
	HRESULT result;
	// �萔�o�b�t�@�փf�[�^�]��
	ConstBufferData* constMap = nullptr;
	result = constBuff->Map(0, nullptr, (void**)&constMap);
	if (SUCCEEDED(result)) {
		constMap->ambientColor = ambientColor;

		// ���s����
		for (int i = 0; i < DirLightNum; i++) {
			// ���C�g���L���Ȃ�ݒ��]��
			if (dirLights[i].IsActive()) {
				constMap->dirLights[i].active = 1;
				constMap->dirLights[i].lightv = -dirLights[i].GetLightDir();
				constMap->dirLights[i].lightcolor = dirLights[i].GetLightColor();
			}
			// ���C�g�������Ȃ烉�C�g�F��0��
			else {
				constMap->dirLights[i].active = 0;
			}
		}

		// �_����
		for (int i = 0; i < PointLightNum; i++) {
			// ���C�g���L���Ȃ�ݒ��]��
			if (pointLights[i].IsActive()){
				constMap->pointLights[i].active = 1;
				constMap->pointLights[i].lightpos = pointLights[i].GetLightPos();
				constMap->pointLights[i].lightcolor = pointLights[i].GetLightColor();
				constMap->pointLights[i].lightatten = pointLights[i].GetLightAtten();
			}
			// ���C�g�������Ȃ烉�C�g�F��0��
			else {
				constMap->pointLights[i].active = 0;
			}
		}
		constBuff->Unmap(0, nullptr);
	}
}

void LigthGroup::SetPointLightActive(int index, bool active)
{
	assert(0 <= index && index < PointLightNum);

	pointLights[index].SetActive(active);
}

void LigthGroup::SetPointLightPos(int index, const XMFLOAT3& lightpos)
{
	assert(0 <= index && index < PointLightNum);

	pointLights[index].SetLightPos(lightpos);
	dirty = true;
}

void LigthGroup::SetPointLightColor(int index, const XMFLOAT3& lightcolor)
{
	assert(0 <= index && index < PointLightNum);

	pointLights[index].SetLightColor(lightcolor);
	dirty = true;
}

void LigthGroup::SetPointLightAtten(int index, const XMFLOAT3& lightAtten)
{
	assert(0 <= index && index < PointLightNum);

	pointLights[index].SetLightAtten(lightAtten);
	dirty = true;
}
