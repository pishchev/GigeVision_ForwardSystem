#include <iostream>
#include "GigeManager.hpp"

int main()
{
	GigeManager gige;

	//выбираем динамическую библиотеку
	gige.init("TLSimu.cti");

	//интерфейсы
	for (uint32_t i = 0; i < gige.getIntefacesSize(); i++) {
		std::cout << i << ")" << gige.getInterfaceName(i) << std::endl;
	}
	uint32_t interf = 0;
	std::cin >> interf;
	gige.useInterface(interf);

	//девайсы
	for (uint32_t i = 0; i < gige.getDevicesSize(); i++) {
		std::cout << i << ")" << gige.getDeviceName(i) << std::endl;
	}
	uint32_t device = 0;
	std::cin >> device;
	gige.useDevice(device);

	//стримы
	for (uint32_t i = 0; i < gige.getStreamsSize(); i++) {
		std::cout << i << ")" << gige.getStreamName(i) << std::endl;
	}
	uint32_t stream = 0;
	std::cin >> stream;
	gige.useStream(stream);


	gige.cameraInit();

	gige.SetIntNode("Height", 8);
	gige.SetIntNode("Width", 8);

	std::string pixelFormat;
	gige.GetEnumStrNode("PixelFormat", pixelFormat);
	std::cout << "PixelFormat: " << pixelFormat << std::endl;

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
