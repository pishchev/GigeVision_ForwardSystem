#pragma once

#include "LibLoader.hpp"
#include "GenICam.h"
#include "Buffer.hpp"

GENICAM_INTERFACE GENAPI_DECL_ABSTRACT Port : public GENAPI_NAMESPACE::IPort
{
	GenTL::PORT_HANDLE hPort = nullptr;

	void UsePort(GenTL::PORT_HANDLE port)
	{
		hPort = port;
	}

	//! Reads a chunk of bytes from the port
	virtual void Read(void* pBuffer, int64_t Address, int64_t Length)
	{
		size_t len = Length;
		elog(GCReadPort(hPort , Address, pBuffer , &len), "GCReadPort");
	}

	//! Writes a chunk of bytes to the port
	virtual void Write(const void* pBuffer, int64_t Address, int64_t Length)
	{
		size_t len = Length;
		elog(GCWritePort(hPort, Address, pBuffer, &len),"GCWritePort");
	}

	//! Get the access mode of the node
	virtual GENAPI_NAMESPACE::EAccessMode GetAccessMode() const
	{
		int type = 1;

		Buffer read(10);
		auto err = GCGetPortInfo(hPort, GenTL::PORT_INFO_ACCESS_READ, &type, read.Convert<void>(), read.Size());
		elog(err, "GetAccessMode");

		Buffer write(10);
		err = GCGetPortInfo(hPort, GenTL::PORT_INFO_ACCESS_WRITE, &type, write.Convert<void>(), write.Size());
		elog(err, "GetAccessMode");

		Buffer na(10);
		err = GCGetPortInfo(hPort, GenTL::PORT_INFO_ACCESS_NA, &type, na.Convert<void>(), na.Size());
		elog(err, "GetAccessMode");

		Buffer ni(10);
		err = GCGetPortInfo(hPort, GenTL::PORT_INFO_ACCESS_NI, &type, ni.Convert<void>(), ni.Size());
		elog(err, "GetAccessMode");

		if (*read.Convert<bool8_t>() && *write.Convert<bool8_t>())	return GENAPI_NAMESPACE::EAccessMode::RW;
		if (*read.Convert<bool8_t>())																return GENAPI_NAMESPACE::EAccessMode::RO;
		if (*write.Convert<bool8_t>())															return GENAPI_NAMESPACE::EAccessMode::WO;
		if (*na.Convert<bool8_t>())																	return GENAPI_NAMESPACE::EAccessMode::NA;
		if (*ni.Convert<bool8_t>())																	return GENAPI_NAMESPACE::EAccessMode::NI;
	}

	static GENICAM_NAMESPACE::gcstring GetXML(GenTL::PORT_HANDLE port)
	{
		uint32_t num_urls = -1;

		elog(GCGetNumPortURLs(port, &num_urls), "GCGetNumPortURLs");

		Buffer info(40);
		int32_t iInfoCmd = GenTL::INFO_DATATYPE_STRING;
		elog(GCGetPortURLInfo(port, 0, GenTL::URL_INFO_FILE_REGISTER_ADDRESS, &iInfoCmd, info.Convert<void>(), info.Size()), "GCGetPortURLInfo");

		uint64_t addres = *info.Convert<uint64_t>();

		Buffer info2(40);
		int32_t iInfoCmd2 = GenTL::INFO_DATATYPE_STRING;
		elog(GCGetPortURLInfo(port, 0, GenTL::URL_INFO_FILE_SIZE, &iInfoCmd2, info2.Convert<void>(), info2.Size()), "GCGetPortURLInfo");

		Buffer read_port_buffer(*info2.Convert<uint64_t>());
		elog(GCReadPort(port, addres, read_port_buffer.Convert<void>(), read_port_buffer.Size()), "GCReadPort");
		//print_as<char>(read_port_buffer); //вывод XML

		return GENICAM_NAMESPACE::gcstring(read_port_buffer.Convert<char>());
	}
};
