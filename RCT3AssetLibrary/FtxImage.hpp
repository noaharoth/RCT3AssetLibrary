// FtxImage.hpp

#pragma once

#include "stdafx.hpp"
#include "OvlImage.hpp"
#include "Vertex.hpp"

namespace RCT3Asset
{

	// FtxImage's use an indexed image format.
	class FtxImage final : public OvlImage
	{
	private:
		static BGRAColor _rgbPalette[256];
		static bool _rgbPaletteMade;

	public:

		FtxImage(RCT3Debugging::OutputLog& log);

		FtxImage(const std::string& imageFile, RCT3Debugging::OutputLog& log);

		inline unsigned int GetIndexedDataSize() const;

		inline unsigned int GetAlphaDataSize() const;

		inline unsigned int GetPaletteDataSize() const;

		void CopyDataTo(unsigned char* textureDest, unsigned char* paletteDest,
			unsigned char* alphaDest, bool makeRecolorable = false);

		static const BGRAColor* GetRGBPalette();

	};

}