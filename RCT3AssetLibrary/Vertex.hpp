// Vertex.h

#include "stdafx.hpp"

namespace RCT3Asset
{

	struct Vector3
	{
		float X;
		float Y;
		float Z;

		Vector3() : X(0.0f), Y(0.0f), Z(0.0f) { }
	};

	struct GameColor
	{
		unsigned int Color1, Color2, Color3;

		GameColor() : Color1(0), Color2(0), Color3(0) { }
	};

}