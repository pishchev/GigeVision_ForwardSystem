#pragma once
#include "GenTL.h"
#include "LibLoader.hpp"
#include "Logger.hpp"

class TransportLayer
{
public:

	void Open()
	{
		auto err = TLOpen(&hTL);
		elog(err, "TL_Handler::Open");
	}

	~TransportLayer()
	{
		auto err = TLClose(hTL);
		elog(err, "TL_Handler::Close");
	}

	void UpdateInterfaceList()
	{
		bool8_t pbChanged = false;
		auto err = TLUpdateInterfaceList(hTL, &pbChanged, GENTL_INFINITE);
		elog(err, "TL_Handler::UpdateInterfaceList");
	}

	uint32_t GetNumInterfaces()
	{
		uint32_t num_interfaces = 0;
		auto err = TLGetNumInterfaces(hTL, &num_interfaces);
		elog(err, "TL_Handler::GetNumInterfaces");
		return num_interfaces;
	}

	std::vector<std::string> ShowInterfaces()
	{
		std::vector<std::string> interfaces;
		uint32_t num_interfaces = GetNumInterfaces();
		for (uint32_t i = 0; i < num_interfaces; i++)
		{
			Buffer buffer(20);
			auto err = TLGetInterfaceID(hTL, i, buffer.Convert<char>(), buffer.Size());
			interfaces.push_back(buffer.Convert<char>());
			elog(err, "TL_Handler::ShowInterfaces");
		}
		return interfaces;
	}

	GenTL::IF_HANDLE GetInterface(uint32_t num)
	{
		Buffer buffer(20);
		auto err = TLGetInterfaceID(hTL, num, buffer.Convert<char>(), buffer.Size());
		elog(err, "TL_Handler::GetInterface");
		GenTL::IF_HANDLE hIF = nullptr;
		err = TLOpenInterface(hTL, buffer.Convert<char>(), &hIF);
		elog(err, "TL_Handler::GetInterface");
		return hIF;
	}

	GenTL::TL_HANDLE GetTL()
	{
		return hTL;
	}

private:
	GenTL::TL_HANDLE hTL = nullptr;
};