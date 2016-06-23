#include "MatrixStack.h"

Matrix::Matrix()
{
	for(int i = 0; i < 16; i++)
	{
		matrices[i] = 0.0F;
	}
}
