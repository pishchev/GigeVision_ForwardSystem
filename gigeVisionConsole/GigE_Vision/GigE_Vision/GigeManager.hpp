#pragma once

#include <fstream>
#include <assert.h>
#include <windows.h> 
#include <stdio.h> 
#include <string>
#include <vector>
#include <thread>
#include <queue>
#include <memory>

#include "Buffer.hpp"
#include "Logger.hpp"
#include "LibLoader.hpp"
#include "Port.hpp"
#include "ImageAcquirer.hpp"
#include "TransportLayer.hpp"
#include "Interface.hpp"
#include "Device.hpp"
#include "Camera.hpp"
#include "Configurator.h"

#include "GenTL.h"
#include "GenICam.h"


class GigeManager
{
public:

	GigeManager(){}
	~GigeManager()
	{
		stopAcquisition();
	}

	void configuration(const Configurator& config)
	{
		Init(config.ctiFile);
		useInterface(config.interfaceIndex);
		useDevice(config.deviceIndex);
		useStream(config.streamIndex);
		cameraInit();

		camera.SetHeight(config.height);
		camera.SetWidth(config.width);
	}

	void Init(std::string cti)
	{
		Init_Lib(cti);
		GCInitLib();

		tl_handler.Open();
		tl_handler.UpdateInterfaceList();
	}

	std::vector<std::string> Interfaces()
	{
		return tl_handler.ShowInterfaces();
	}
	void useInterface(int int_num)
	{
		if_handler.setInterfaces(tl_handler.GetInterface(int_num));
		if_handler.UpdateDeviceList();
	}

	std::vector<std::string> Devices()
	{
		return if_handler.ShowDevices();
	}
	void useDevice(uint32_t dev_num)
	{
		dev_handler.setDevice(if_handler.GetDevice(dev_num));
	}

	std::vector<std::string> Streams()
	{
		return dev_handler.ShowStreams();
	}
	void useStream(uint32_t stream_num)
	{
		hDS = dev_handler.GetStream(stream_num);
		p.UsePort(dev_handler.GetPort());
	}

	void cameraInit()
	{
		camera.LoadXML(Port::GetXML(dev_handler.GetPort()));
		camera.Connect(static_cast<IPort*>(&p));
	}

	void acquirerPreparing()
	{
		payloadSize = camera.PayloadSize();
		image = Buffer(payloadSize);
		imageAcq.AnnounceBuffers(hDS, payloadSize);
		imageAcq.StartAcquisition(hDS);
		ds_buffers = imageAcq.GetBuffers();
	}

	void startAcquisition()
	{
		camera.StartAcquisition();
		elog(GCRegisterEvent(hDS, GenTL::EVENT_NEW_BUFFER, &hEvent), "GCRegisterEvent");
		asyncAcquisition();
	}

	size_t imageSize()
	{
		return payloadSize;
	}
	
	bool getImage(unsigned char* buffer , size_t size)
	{
		if (!(payloadSize>=static_cast<int64_t>(size)) || !is_ready)
		{
			return false;
		}
		memcpy(buffer, image.Convert<void>(), sizeof(unsigned char) * size);
		return true;
	}

	void waitNext()
	{
		next = true;
	}

	void stopAcquisition()
	{
		stopAcq = true;
		camera.StopAcquisition();
	}

private:

	void asyncAcquisition()
	{
		std::thread thr(asyncCapture, std::ref(*this));
		thr.detach();
	}

	static void asyncCapture(GigeManager& manager)
	{
		int type = GenTL::INFO_DATATYPE_STRING;
		Buffer buffer_info(20);
		Buffer data_buffer(64);
		while (true)
		{
			if (manager.stopAcq) break;
			if (!manager.next) continue;
			auto err = EventGetData(manager.hEvent, data_buffer.Convert<void>(), data_buffer.Size(), 10000);
			if (err == 0)
			{
				DSGetBufferInfo(manager.hDS, *data_buffer.Convert<void**>(), GenTL::BUFFER_INFO_BASE, &type, buffer_info.Convert<void>(), buffer_info.Size());
				unsigned char* buf = *buffer_info.Convert<unsigned char*>();
				memcpy(manager.image.Convert<void>(), buf, sizeof(unsigned char) * manager.payloadSize);
				manager.is_ready = true;
				elog(DSQueueBuffer(manager.hDS, *data_buffer.Convert<void**>()), "DSQueueBuffer");
				manager.next = false;
			}
			else if (err != GenTL::GC_ERR_TIMEOUT)
			{
				elog(err, "ArqFunction");
			}
		}
	}

	TransportLayer tl_handler;
	Interface if_handler;
	Device dev_handler;
	Port p;
	Camera camera;
	ImageAcquirer imageAcq;

	std::vector<GenTL::BUFFER_HANDLE> ds_buffers;

	bool next = false;
	bool is_ready = false;
	bool stopAcq = false;
	Buffer image;

	GenTL::EVENT_HANDLE hEvent = nullptr;
	GenTL::DS_HANDLE hDS = nullptr;

	int64_t payloadSize = 0;
};
