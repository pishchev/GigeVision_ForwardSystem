#pragma once
#include "GenTL.h"
#include "LibLoader.hpp"
#include "Logger.hpp"

class Device
{
public:

	Device(GenTL::DEV_HANDLE hDevice) : hDevice(hDevice) {}

	Device() {}

	void setDevice(GenTL::DEV_HANDLE dev)
	{
		hDevice = dev;
	}

	uint32_t GetNumStreams()
	{
		uint32_t num_streams;
		auto err = DevGetNumDataStreams(hDevice, &num_streams);
		elog(err, "DEV_Handler::GetNumStreams");
		return num_streams;
	}

	void ShowStreams()
	{
		std::cout << "Streams: " << std::endl;
		for (uint32_t i = 0; i < GetNumStreams(); i++)
		{
			Buffer dDSID(20);
			auto err = DevGetDataStreamID(hDevice, i, dDSID.Convert<char>(), dDSID.Size());
			std::cout << i << ") " << dDSID.Convert<char>();
			elog(err, "DEV_Handler::ShowStreams");
		}
	}

	GenTL::DS_HANDLE GetStream(uint32_t num)
	{
		Buffer dDSID(20);
		auto err = DevGetDataStreamID(hDevice, num, dDSID.Convert<char>(), dDSID.Size());
		elog(err, "DEV_Handler::GetStream");
		GenTL::DS_HANDLE hDS = nullptr;
		err = DevOpenDataStream(hDevice, dDSID.Convert<char>(), &hDS);
		elog(err, "DEV_Handler::GetStream");
		return hDS;
	}

	GenTL::PORT_HANDLE GetPort()
	{
		GenTL::PORT_HANDLE port = nullptr;

		auto err = DevGetPort(hDevice, &port);
		elog(err, "DEV_Handler::GetPort");
		return port;
	}

	GenTL::DEV_HANDLE GetDevice()
	{
		return hDevice;
	}


private:
	GenTL::DEV_HANDLE hDevice = nullptr;
};