// TextureStyle.hpp

#pragma once

#include "stdafx.hpp"
#include "OvlFile.hpp"

namespace RCT3Asset
{

	class TextureStyle
	{
	private:
		std::string _style;

	public:
		TextureStyle();

		TextureStyle(std::string style);

		std::string GetStyle() const;

		std::string GetNameID() const;

		TextureStyle& operator=(const std::string& value);

		void AddTo(OvlFile& ovl);

		// --- Texture Style Constants --- //

		static const TextureStyle PathGround;
		static const TextureStyle GUIIcon;
	};

}