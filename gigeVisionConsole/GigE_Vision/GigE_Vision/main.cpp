#include <iostream>
#include <iomanip>
#include "GigeManager.hpp"

int main()
{
	GigeManager gige;
	
	uint32_t useConfig;
	std::cout << "Use config: ";
	std::cin >> useConfig;

	if (!useConfig)
	{
		//выбираем динамическую библиотеку
		std::string lib = "TLSimu.cti";
		//std::cout << "Lib: ";
		//std::cin >> lib;
		gige.useLib(lib);

		//интерфейсы
		for (uint32_t i = 0; i < gige.getIntefacesSize(); i++) {
			std::cout << i << ")" << gige.getInterfaceName(i) << std::endl;
		}
		uint32_t interf;
		std::cout << "Interface: ";
		std::cin >> interf;
		gige.useInterface(interf);

		//девайсы
		for (uint32_t i = 0; i < gige.getDevicesSize(); i++) {
			std::cout << i << ")" << gige.getDeviceName(i) << std::endl;
		}
		uint32_t device;
		std::cout << "Device: ";
		std::cin >> device;
		gige.useDevice(device);

		//стримы
		for (uint32_t i = 0; i < gige.getStreamsSize(); i++) {
			std::cout << i << ")" << gige.getStreamName(i) << std::endl;
		}
		uint32_t stream;
		std::cout << "Stream: ";
		std::cin >> stream;
		gige.useStream(stream);

		gige.cameraInit();

		int64_t height = 8;
		std::cout << "Height: ";
		std::cin >> height;
		gige.SetIntNode("Height", height);

		int64_t width = 8;
		std::cout << "Width: ";
		std::cin >> width;
		gige.SetIntNode("Width", width);
	}
	else 
	{
		std::string config = "config.txt";
		//std::cout << "Configurator: ";
		//std::cin >> config;
		gige.useConfigurator(config);
	}

	//узлы
	size_t nodesSize = gige.getNodesSize();
	std::cout << std::setw(8) << std::right << "Name"
		<< std::setw(51) << std::right << "Visibility"
		<< std::setw(20) << std::right << "AccessMode"
		<< std::setw(18) << std::right << "Type" << std::endl;

	for (uint32_t i = 0; i < nodesSize; i++)
	{
		std::cout << std::setw(3) << std::right << i << ")" << std::setw(50) << std::left << gige.getNodeName(i)
			<< std::setw(20) << std::left << gige.getNodeVisibility(i)
			<< std::setw(20) << std::left << gige.getNodeAccess(i)
			<< std::setw(20) << std::left << gige.getNodeType(i) << std::endl;
	}

	gige.SaveConfig("config.txt");
	Configurator conf;
	conf.ReadConfig("config.txt");
	conf.PrintConfig();

	int64_t payloadSize;
	gige.GetIntNode("PayloadSize", payloadSize);
	std::cout << "\n\n\nPayloadSize: " << payloadSize << std::endl;

	std::string pixelFormat;
	gige.GetEnumStrNode("PixelFormat", pixelFormat);
	std::cout << "PixelFormat: " << pixelFormat << std::endl;

	std::string triggerSource;
	gige.GetEnumStrNode("TriggerSource", triggerSource);
	std::cout << "TriggerSource: " << triggerSource << std::endl;



	// захват изображения
	gige.acquirerPreparing();
	gige.startAcquisition();

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
