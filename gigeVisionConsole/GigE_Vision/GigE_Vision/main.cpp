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
	unsigned char* image = new unsigned char[payloadSize];

	while(true)
	{
		gige.waitNext();
		if (gige.getImage(image, payloadSize))
		{
			for (int i = 0; i < payloadSize; i++)
			{
				std::cout << ' ' << (int)image[i];
			}
		}
		std::cout << std::endl;
		system("pause");
		
	}
	return 0;
} 
