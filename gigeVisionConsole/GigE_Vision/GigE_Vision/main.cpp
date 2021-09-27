#include <iostream>
#include "GigeManager.hpp"

int main()
{
	GigeManager gige;
	Configurator config;

	gige.configuration(config);
	gige.acquirerPreparing();
	gige.startAcquisition();

	size_t payloadSize = gige.imageSize();
	Buffer img(payloadSize);
	unsigned char* image = img.Convert<unsigned char>();

	while(true)
	{
		gige.waitNext();
		if (gige.getImage(img.Convert<unsigned char>(), payloadSize))
		{
			for (int i = 0; i < payloadSize; i++)
			{
				std::cout << ' ' << (int)image[i];
			}
		}
		std::cout << std::endl;
		system("pause");	
	}
	gige.stopAcquisition();
	return 0;
} 
