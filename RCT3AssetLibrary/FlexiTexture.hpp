// FlexiTexture.h

#pragma once

#include "stdafx.hpp"
#include "FlexiTextureRaw.hpp"
#include "OvlFile.hpp"
#include "FtxImage.hpp"
#include "StructureCollection.hpp"

namespace RCT3Asset
{
	// * Recolorable texture options. AllColors makes all three recolorable, or you can mix and match them.
	struct RecolorOptions
	{
		enum
		{
			None = 0,
			FirstColor = 1,
			SecondColor = 2,
			ThirdColor = 4,
			AllColors = FirstColor | SecondColor | ThirdColor
		};
	};

	class FlexiTextureFrame
	{
	private:
		FtxImage& _image;
		unsigned int _recolor;

	public:

		FlexiTextureFrame(FtxImage& image);

		unsigned int Recolorability() const;

		void Recolorability(unsigned int recolor);

		FtxImage& GetImage();

		unsigned int Scale() const;

		unsigned int Dimension() const;

	};

	class FlexiTexture
	{
	private:
		std::string _name;
		unsigned int _recolor;
		unsigned int _fps;
		std::vector<unsigned int> _frameNumbers;
		std::vector<FlexiTextureFrame> _frames;

	public:
		
		FlexiTexture();

		std::string Name() const;

		void Name(std::string name);

		std::string GetNameID() const;

		unsigned int FramesPerSecond() const;

		void FramesPerSecond(unsigned int fps);

		void AddFrameNumber(unsigned int number);

		void AddFrame(const FlexiTextureFrame& frame);

		void MakeStillImage(); // DEPRECETATED

		void MakeStillImage(const FlexiTextureFrame& frame);

		unsigned int Recolorability() const;

		void Recolorability(unsigned int recolor);

		unsigned int GetDataSize(unsigned int file);

		void CopyDataTo(OvlFile& ovl, void* raw, unsigned int headerIndex);

		static StructureHeader GetHeader();

	};

	class FlexiTextureCollection final : public StructureCollection < FlexiTexture >
	{
	public:

		void AddTo(OvlFile& ovl);

	};

}