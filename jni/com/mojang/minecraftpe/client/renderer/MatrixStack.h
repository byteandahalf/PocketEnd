#pragma once

struct Vec3;

struct Matrix
{
	float matrices[16];

	Matrix();

	void translate(const Vec3&);
	void scale(const Vec3&);
	void rotate(float, const Vec3&);
	void setPerspective(float, float, float, float);
};

struct MatrixStack
{
	char filler[12];
	bool bool12;

	struct Ref
	{
		MatrixStack& stack;
		Matrix& matrix;

		MatrixStack::Ref* release();
		MatrixStack::Ref& operator=(const Matrix&);
	};

	static MatrixStack View;
	static MatrixStack Projection;
	static MatrixStack World;

	MatrixStack::Ref push();
	MatrixStack::Ref pushIdentity();
	void pop();
};
