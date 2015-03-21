// TexImage.cpp

#include "stdafx.hpp"
#include "TexImage.hpp"

using namespace RCT3Asset;

TexImage::TexImage(RCT3Debugging::OutputLog& log)
	: OvlImage(log), _format(TexImageFormat::Default)
{

}

TexImage::TexImage(const std::string& imageFile, unsigned int format, RCT3Debugging::OutputLog& log)
	: OvlImage(imageFile, log), _format(format)
{

}

TexImage::TexImage(const std::string& imageFile, RCT3Debugging::OutputLog& log)
	: OvlImage(imageFile, log), _format(TexImageFormat::Default)
{

}

unsigned int TexImage::GetFlicFormat() const
{
	switch (_format)
	{
	case TexImageFormat::ARGB8:
		return 0x02;
	case TexImageFormat::DDS::DXT1:
		return 0x12;
	case TexImageFormat::DDS::DXT3:
		return 0x13;
	case TexImageFormat::DDS::DXT5:
		return 0x14;
	default:
	{
		_log.Error("TexImage::GetFlicFormat(..): Unknown format " +
			std::to_string(_format));
		return 0;
	}
	}
}

unsigned int TexImage::Blocks() const
{
	if (_format == TexImageFormat::ARGB8)
		return Dimension();

	return Dimension() / 4;
}

unsigned int TexImage::Pitch() const
{
	if (_format == TexImageFormat::ARGB8)
		return (Dimension() * 64) / 16;

	unsigned int blockSize = 0;

	if (_format == TexImageFormat::DDS::DXT1)
		blockSize = 8;
	else blockSize = 16;

	return Dimension() * blockSize / 4;
}

unsigned int TexImage::Format() const
{
	return _format;
}

void TexImage::Format(unsigned int format)
{
	_format = format;
}

unsigned int TexImage::GetDataSize() const
{
	if (_format == TexImageFormat::ARGB8)
	{
		return Width() * Height() * sizeof(U8Color);
	}

	return squish::GetStorageRequirements(Width(), Height(), (int)_format);
}

void TexImage::CopyDataTo(void* buffer)
{
	if (!_isValid)
	{
		_log.Error("TexImage::CopyDataTo(...): Tried to access invalid image");
		return;
	}

	if (_format == TexImageFormat::ARGB8)
	{
		try
		{
			Magick::Image temp = _image;

			temp.flip();
			temp.matte(true);
			temp.write(0, 0, temp.columns(), temp.rows(), "ARGB", Magick::CharPixel, buffer);
		}
		catch (Magick::Exception& e)
		{
			_log.Error("GraphicsMagick threw an exception: " + std::string(e.what()));
			return;
		}
	}
	else
	{
		int datasize = 4 * _image.rows() * _image.columns();
		squish::u8* data = new squish::u8[datasize]();
		Magick::Image temp = _image;

		try
		{
			temp.flip();
			temp.matte(true);
			temp.write(0, 0, temp.columns(), temp.rows(), "RGBA", Magick::CharPixel, data);
		}
		catch (Magick::Exception& e)
		{
			_log.Error("GraphicsMagick threw an exception: " + std::string(e.what()));
			return;
		}

		squish::CompressImage(data, temp.columns(), temp.rows(), buffer, ((int)_format) | squish::kColourIterativeClusterFit | squish::kWeightColourByAlpha);

		delete[] data;
	}
}