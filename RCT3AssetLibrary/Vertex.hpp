// Vertex.hpp

/*
* (C) Copyright 2015 Noah Roth
*
* All rights reserved. This program and the accompanying materials
* are made available under the terms of the GNU Lesser General Public License
* (LGPL) version 2.1 which accompanies this distribution, and is available at
* http://www.gnu.org/licenses/lgpl-2.1.html
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
* Lesser General Public License for more details.
*
*/

#pragma once

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

	struct Vertex
	{
		Vector3 Position;
		Vector3 Normal;
		unsigned int Color;
		float U;
		float V;
	};

	struct Triangle
	{
		unsigned int A;
		unsigned int B;
		unsigned int C;
	};

	struct Matrix4x4
	{
		union
		{
			float M[4][4];

			struct
			{
				float A1, A2, A3, A4;
				float B1, B2, B3, B4;
				float C1, C2, C3, C4;
				float D1, D2, D3, D4;
			};
		};
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

	// For use with libsquish
	struct U8Color
	{
		squish::u8 R;
		squish::u8 G;
		squish::u8 B;
		squish::u8 A;

		U8Color() : R(0), G(0), B(0), A(0) { }
	};

}