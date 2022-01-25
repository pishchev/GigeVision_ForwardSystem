#include <iostream>
#include <iomanip>
#include "GigeManager.hpp"

void noConfig(GigeManager& gige) 
{
	//выбираем динамическую библиотеку
	std::string lib = "mvGenTLProducer.cti";
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
void useConfig(GigeManager& gige)
{
	std::string config = "config.txt";
	//std::cout << "Configurator: ";
	//std::cin >> config;
	gige.useConfigurator(config);
}
void showNodes(GigeManager& gige)
{
	//узлы
	size_t nodesSize = gige.getNodesSize();
	std::cout << std::setw(8) << std::right << "Name"
		<< std::setw(47) << std::right << "V"
		<< std::setw(5) << std::right << "AM"
		<< std::setw(5) << std::right << "T"
		<< std::setw(6) << std::right << "Val" << std::endl;

	for (uint32_t i = 0; i < nodesSize; i++)
	{
		std::cout << std::setw(3) << std::right << i << ")" << std::setw(50) << std::left << gige.getNodeName(i)
			<< std::setw(5) << std::left << gige.getNodeVisibility(i)
			<< std::setw(5) << std::left << gige.getNodeAccess(i)
			<< std::setw(5) << std::left << gige.getNodeType(i);

		if (gige.getNodeType(i) == 2)
		{
			int64_t val;
			gige.GetIntNode(gige.getNodeName(i), val);
			std::cout << val;
		}
		else if (gige.getNodeType(i) == 9)
		{
			std::string val;
			gige.GetEnumStrNode(gige.getNodeName(i), val);
			std::cout << val;
		}
		else if (gige.getNodeType(i) == 6)
		{
			std::string val;
			gige.GetStrNode(gige.getNodeName(i), val);
			std::cout << val;
		}

		std::cout << std::endl;
	}
}
void testShowConfig()
{
	Configurator conf;
	conf.ReadConfig("config.txt");
	conf.PrintConfig();
}
void gettingImage(GigeManager& gige)
{
	// захват изображения
	gige.acquirerPreparing();
	gige.startAcquisition();

	int64_t payloadSize;
	gige.GetIntNode("PayloadSize", payloadSize);
	Buffer img(payloadSize);
	unsigned char* image = img.Convert<unsigned char>();

	while (true)
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
}

int main()
{
	GigeManager gige;
	
	uint32_t iUseConfig;
	std::cout << "Use config: ";
	std::cin >> iUseConfig;

	iUseConfig ? useConfig(gige) : noConfig(gige);
	showNodes(gige);

	gige.SaveConfig("config.txt");
	testShowConfig();

	gettingImage(gige);
	return 0;
} 
