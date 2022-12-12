#pragma once

#include <DirectXMath.h>

class Camera
{
protected:
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;

	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	Camera(int winWidth, int winHeight);
	virtual ~Camera() = default;
	virtual void Update();
	void UpdateViewMatrix();
	void UpdateProjectionMatrix();

	const XMMATRIX& GetViewMatrix() { return matView; }
	const XMMATRIX& GetProjectionMatrix() { return matProjection; }
	const XMMATRIX& GetViewProjectionMatrix() { return matViewProjection; }
	const XMMATRIX& GetBillboardMatrix() { return matBillboard; }
	const XMFLOAT3& GetEye() { return eye; }

	void SetEye(XMFLOAT3 eye) { this->eye = eye; viewDirty = true; }

	const XMFLOAT3& GetTarget() { return target; }

	void SetTarget(XMFLOAT3 target) { this->target = target; viewDirty = true; }

	const XMFLOAT3& GetUp() { return up; }

	void SetUp(XMFLOAT3 up) { this->up = up; viewDirty = true;}
	void MoveEyeVector(const XMFLOAT3& move);
	void MoveEyeVector(const XMVECTOR& move);
	void MoveVector(const XMFLOAT3& move);
	void MoveVector(const XMVECTOR& move);

protected:
	XMMATRIX matView = DirectX::XMMatrixIdentity();
	XMMATRIX matProjection = DirectX::XMMatrixIdentity();
	XMMATRIX matViewProjection = DirectX::XMMatrixIdentity();
	XMMATRIX matBillboard = DirectX::XMMatrixIdentity();
	XMMATRIX matBillboardY = DirectX::XMMatrixIdentity();

	bool viewDirty = false;
	bool projectionDirty = false;

	XMFLOAT3 eye = { 0, -30, 0 };
	XMFLOAT3 target = { 0, 0, 0 };
	XMFLOAT3 up = { 0, 1, 0 };

	float aspectRatio = 1.0f;
};

