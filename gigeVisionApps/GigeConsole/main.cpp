#include <iostream>
#include <iomanip>
#include "GigeManager.hpp"

void NoConfig(GigeManager& gige) 
{
	//выбираем динамическую библиотеку
	std::string lib = "bgapi2_gige.cti";
	//std::cout << "Lib: ";
	//std::cin >> lib;
	gige.UseLib(lib);

	//интерфейсы
	for (uint32_t i = 0; i < gige.GetIntefacesSize(); i++) {
		std::cout << i << ")" << gige.GetInterfaceName(i) << std::endl;
	}
	uint32_t interf;
	std::cout << "Interface: ";
	std::cin >> interf;
	gige.UseInterface(interf);

	//девайсы
	for (uint32_t i = 0; i < gige.GetDevicesSize(); i++) {
		std::cout << i << ")" << gige.GetDeviceName(i) << std::endl;
	}
	uint32_t device;
	std::cout << "Device: ";
	std::cin >> device;
	gige.UseDevice(device);

	//стримы
	for (uint32_t i = 0; i < gige.GetStreamsSize(); i++) {
		std::cout << i << ")" << gige.GetStreamName(i) << std::endl;
	}
	uint32_t stream;
	std::cout << "Stream: ";
	std::cin >> stream;
	gige.UseStream(stream);

	gige.CameraInit();

	int64_t height = 8;
	//std::cout << "Height: ";
	//std::cin >> height;
	//gige.SetIntNode("Height", height);
	
	int64_t width = 8;
	//std::cout << "Width: ";
	//std::cin >> width;
	//gige.SetIntNode("Width", width);
}
void UseConfig(GigeManager& gige)
{
	std::string config = "configH.txt";
	//std::cout << "Configurator: ";
	//std::cin >> config;
	gige.UseConfigurator(config);
}
void ShowNodes(GigeManager& gige)
{
	//узлы
	size_t nodesSize = gige.GetNodesSize();
	std::cout << std::setw(8) << std::right << "Name"
		<< std::setw(47) << std::right << "V"
		<< std::setw(5) << std::right << "AM"
		<< std::setw(5) << std::right << "T"
		<< std::setw(6) << std::right << "Val" << std::endl;

	for (uint32_t i = 0; i < nodesSize; i++)
	{
		const auto nodeType = gige.GetNodeType(i);

		//if (nodeType == 8 || nodeType == 10 || nodeType == 11)
		//	continue;

		std::cout << std::setw(3) << std::right << i << ")" << std::setw(50) << std::left << gige.GetNodeName(i)
			<< std::setw(5) << std::left << gige.GetNodeVisibility(i)
			<< std::setw(5) << std::left << gige.GetNodeAccess(i)
			<< std::setw(5) << std::left << gige.GetNodeType(i);

		if (nodeType == 2)
		{
			int64_t val;
			gige.GetIntNode(gige.GetNodeName(i), val);
			std::cout << val;
		}
		else if (nodeType == 3)
		{
			bool val;
			gige.GetBoolNode(gige.GetNodeName(i), val);
			std::cout << int(val ? 1 : 0);
		}
		else if (nodeType == 4)
		{
			bool val;
			gige.GetCommandNode(gige.GetNodeName(i), val);
			std::cout << int(val? 1:0);
		}
		else if (nodeType == 5)
		{
			double val;
			gige.GetFloatNode(gige.GetNodeName(i), val);
			std::cout << val;
		}
		else if (nodeType == 6)
		{
			std::string val;
			gige.GetStrNode(gige.GetNodeName(i), val);
			std::cout << val;
		}
		else if (nodeType == 9)
		{
			std::string val;
			gige.GetEnumStrNode(gige.GetNodeName(i), val);
			std::cout << val;
		}
		
		std::cout << std::endl;
	}
}
void TestShowConfig()
{
	Configurator conf;
	conf.ReadConfig("config.txt");
	conf.PrintConfig();
}
void GettingImage(GigeManager& gige)
{
	// захват изображения
	gige.AcquirerPreparing();
	gige.StartAcquisition();

	int64_t payloadSize = gige.ImageSize();
	std::cout << "PayloadSize: " << payloadSize << std::endl;

	Buffer img(payloadSize);
	unsigned char* image = img.Convert<unsigned char>();
	uint64_t timestamp = 0;

	int i = 0;
	while (i < 500)
	{
		size_t min, max;
		gige.GetBufferInfo(min, max);
		std::cout << "Min: " << min << " Max:" << max << std::endl;
		if (gige.GetImage(i, img.Convert<unsigned char>()))
		{
			gige.GetTimestamp(i, timestamp);
			std::cout << "Got image! Timestamp: " << timestamp << std::endl;

			i++;
		}
		std::cout << "i: " << i << std::endl;
	}

	gige.StopAcquisition();
}

int main()
{
	GigeManager gige;
	
	uint32_t iUseConfig;
	std::cout << "Use config: ";
	std::cin >> iUseConfig;

	iUseConfig ? UseConfig(gige) : NoConfig(gige);
	//ShowNodes(gige);

	gige.SaveConfig("config.txt");
	TestShowConfig();

	GettingImage(gige);
	system("pause");
	return 0;
} 
