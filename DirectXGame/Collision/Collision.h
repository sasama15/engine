#pragma once
#include <DirectXMath.h>

using namespace DirectX;

struct Sphere{
	XMVECTOR center = { 0, 0, 0, 1 };
	float radius = 1.0f;
};

bool OnCollisionCircle(Object3d* circle1, Object3d* circle2, float r1, float r2)
{
    float x = circle1->GetPosition().x - circle2->GetPosition().x;
    float y = circle1->GetPosition().y - circle2->GetPosition().y;
    float z = circle1->GetPosition().z - circle2->GetPosition().z;

    float c = sqrt(x * x + y * y + z * z);
    float sum_radius = r1 + r2;

    if (c <= sum_radius)
    {
        return true;
    }
    return false;
}