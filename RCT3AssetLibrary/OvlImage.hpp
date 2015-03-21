// OvlImage.h

#pragma once

#include "stdafx.hpp"
#include "OutputLog.hpp"

namespace RCT3Asset
{

	class OvlImage
	{
	protected:
		Magick::Image _image;
		bool _isValid;
		RCT3Debugging::OutputLog& _log;

	public:

		OvlImage(RCT3Debugging::OutputLog& log);

		OvlImage(const std::string& imageFile, RCT3Debugging::OutputLog& log);

		bool FromFile(const std::string& imageFile);

		bool Check(std::string& out_msg);

		inline bool HasAlpha() const;

		inline unsigned int Width() const;

		inline unsigned int Height() const;

		inline unsigned int Dimension() const;

	protected:

		static inline bool _isPowerOf2(unsigned int x);

	};

}