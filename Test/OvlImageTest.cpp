// Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Image/OvlImage.hpp>
#include <Debugging/OutputLog.hpp>

int main()
{
	RCT3Debugging::OutputLog log;
	log.AssignStream(&std::cout);
	log.EnableDebugging();

	log.Info("Initializing...");

	{
		RCT3Asset::OvlImage image(log, "Test.png");

		std::cout << image.Width() << std::endl;
		std::cout << image.Height() << std::endl;
	}

	system("pause");
    return 0;
}

