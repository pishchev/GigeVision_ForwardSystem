#include <iostream>
#include "GigeManager.hpp"

void PrintStrVec(const std::vector<std::string>& strVec)
{
	for (int i = 0; i < strVec.size(); i++) {
		std::cout << i << ") " << strVec[i] << std::endl;
	}
}

int main()
{
	GigeManager gige;

	std::cout << "CTI: ";
	std::string cti = "TLSimu.cti";
	//std::cin >> cti;
	gige.Init(cti);

	std::cout << "Interfaces: "<<std::endl;
	PrintStrVec(gige.Interfaces());

	std::cout << "Interface: ";
	int intfc = 0;
	//std::cin >> intfc;

	gige.useInterface(intfc);

	std::cout << "Devices: " << std::endl;
	PrintStrVec(gige.Devices());

	std::cout << "Devices: ";
	int dev = 1;
	//std::cin >> dev;

	gige.useDevice(dev);

	gige.cameraInit();

	gige.acquirerPreparing();

	gige.startAcquisition();

	size_t payloadSize = gige.imageSize();

	unsigned char* image = new unsigned char[payloadSize];

	while (true)
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
