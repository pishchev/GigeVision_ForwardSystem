#pragma once
#include "GenTL.h"
#include "LibLoader.hpp"
#include "Logger.hpp"

class Interface
{
public:
	Interface(GenTL::IF_HANDLE hIF) : hIF(hIF) {}

	Interface(){}

	void setInterfaces(GenTL::IF_HANDLE itf)
	{
		hIF = itf;
	}

	void UpdateDeviceList()
	{
		bool8_t pbChanged = false;
		auto err = IFUpdateDeviceList(hIF, &pbChanged, 5);
		elog(err, "IF_Handler::UpdateInterfaceList");
	}

	uint32_t GetNumDevices()
	{
		uint32_t num_devices;
		auto err = IFGetNumDevices(hIF, &num_devices);
		elog(err, "IF_Handler::GetNumDevices");
		return num_devices;
	}

	std::vector<std::string> ShowDevices()
	{
		std::vector<std::string> devices;
		for (uint32_t i = 0; i < GetNumDevices(); i++)
		{
			Buffer buffer(20);
			auto err = IFGetDeviceID(hIF, i, buffer.Convert<char>(), buffer.Size());
			devices.push_back(buffer.Convert<char>());
			elog(err, "IF_Handler::ShowDevices");
		}
		return devices;
	}

	GenTL::DEV_HANDLE GetDevice(uint32_t num)
	{
		Buffer buffer(20);
		auto err = IFGetDeviceID(hIF, num, buffer.Convert<char>(), buffer.Size());
		elog(err, "IF_Handler::GetDevice");
		GenTL::DEV_HANDLE hDevice = nullptr;
		err = IFOpenDevice(hIF, buffer.Convert<char>(), GenTL::DEVICE_ACCESS_EXCLUSIVE, &hDevice);
		elog(err, "IF_Handler::GetDevice");
		return hDevice;
	}

	GenTL::IF_HANDLE GetInterface()
	{
		return hIF;
	}

private:
	GenTL::IF_HANDLE hIF = nullptr;
};