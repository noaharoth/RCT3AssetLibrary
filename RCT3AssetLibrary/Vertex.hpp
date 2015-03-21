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
		unsigned int Color1;
		unsigned int Color2;
		unsigned int Color3;;

		GameColor() : Color1(0), Color2(0), Color3(0) { }
	};

	struct BGRAColor
	{
		unsigned char B;
		unsigned char G;
		unsigned char R;
		unsigned char A;

		BGRAColor() : B(0), G(0), R(0), A(0) { }
	};

	struct U8Color
	{
		squish::u8 R;
		squish::u8 G;
		squish::u8 B;
		squish::u8 A;
	};

}