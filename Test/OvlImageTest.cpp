// Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Image/OvlImage.hpp>
#include <Debugging/OutputLog.hpp>
#include <Image/FtxImage.hpp>

RCT3Asset::BGRAColor test[] = { {56, 2, 4, 5}, };

int main()
{
	RCT3Debugging::OutputLog log;
	log.AssignStream(&std::cout);
	log.EnableDebugging();

	log.Info("Initializing...");

	{
		RCT3Asset::FtxImage image(log, "C:\\Users\\noaha\\Documents\\Visual Studio 2015\\Projects\\RCT3AssetLibrary\\Release\\Test.png", false);

		unsigned char* texture = new unsigned char[image.GetIndexedDataSize()]();
		unsigned char* palette = new unsigned char[image.GetPaletteDataSize()]();

		unsigned char* alpha;

		//if (image.HasAlpha())
			//alpha = new unsigned char[image.GetAlphaDataSize()]();

		image.CopyDataTo(texture, palette, nullptr);

		FILE* t_f, *p_f, *a_f;

		t_f = fopen("texture.dat", "wb");
		p_f = fopen("palette.dat", "wb");

		//if (image.HasAlpha())
			//a_f = fopen("alpha.dat", "wb");

		fwrite(texture, image.GetIndexedDataSize(), 1, t_f);
		fwrite(palette, image.GetPaletteDataSize(), 1, p_f);

		//if (image.HasAlpha())
			//fwrite(alpha, image.GetAlphaDataSize(), 1, a_f);

		fclose(t_f);
		fclose(p_f);

		//if (image.HasAlpha())
		//{
			//fclose(a_f);
			//delete[] a_f;
		//}

		delete[] t_f;
		delete[] p_f;
	}
	system("pause");
    return 0;
}

