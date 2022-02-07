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
		StopAcquisition();
		if (_stream) 
		{
			std::cout << "~Stream" << std::endl;
			elog(DSClose(_stream), "DSClose");
		}
	}

	void UseConfigurator(std::string iConfigFile)
	{
		_config.ReadConfig(iConfigFile);
		UseLib(_config._lib);
		UseInterface(_config._interface);
		UseDevice(_config._device);
		UseStream(_config._stream);

		CameraInit();

		for (auto param = _config._parameters.begin(); param != _config._parameters.end(); ++param)
			SetIntNode(param->first, param->second);
	}


	void UseLib(std::string iCti)
	{
		_config._lib = iCti;

		Init_Lib(iCti);
		GCInitLib();

		_transportLayer.Open();
		_transportLayer.UpdateInterfaceList();
	}

	//работа с интерфейсами
	uint32_t GetIntefacesSize()
	{
		return _transportLayer.GetNumInterfaces();
	}
	std::string GetInterfaceName(uint32_t iIndex)
	{
		return _transportLayer.GetInterfaceName(iIndex);
	}
	void UseInterface(uint32_t iIndex)
	{
		_config._interface = GetInterfaceName(iIndex);

		_interface.SetInterfaces(_transportLayer.GetInterface(iIndex));
		_interface.UpdateDeviceList();
	}
	void UseInterface(std::string iInterface)
	{
		for (uint32_t i = 0; i < GetIntefacesSize(); i++)
			if (iInterface == GetInterfaceName(i)) {
				_config._interface = iInterface;
				_interface.SetInterfaces(_transportLayer.GetInterface(i));
				_interface.UpdateDeviceList();
				break;
			}
	}

	//работа с девайсами
	uint32_t GetDevicesSize()
	{
		return _interface.GetNumDevices();
	}
	std::string GetDeviceName(uint32_t iIndex)
	{
		return _interface.GetDeviceName(iIndex);
	}
	void UseDevice(uint32_t iIndex)
	{
		_config._device = GetDeviceName(iIndex);
		_device.SetDevice(_interface.GetDevice(iIndex));
	}
	void UseDevice(std::string device)
	{
		for (uint32_t i = 0; i < GetDevicesSize(); i++)
			if (device == GetDeviceName(i)) {
				_config._device = device;
				_device.SetDevice(_interface.GetDevice(i));
			}
	}

	//работа со стримами
	uint32_t GetStreamsSize()
	{
		return _device.GetNumStreams();
	}
	std::string GetStreamName(uint32_t iIndex)
	{
		return _device.GetStreamName(iIndex);
	}
	void UseStream(uint32_t iIndex)
	{
		_config._stream = GetStreamName(iIndex);
		_stream = _device.GetStream(iIndex);
		_port.UsePort(_device.GetPort());
	}
	void UseStream(std::string iStream) {
		for (uint32_t i = 0; i < GetStreamsSize(); i++)
			if (iStream == GetStreamName(i)) {
				_config._stream = iStream;
				_stream = _device.GetStream(i);
				_port.UsePort(_device.GetPort());
			}
	}

	void CameraInit()
	{
		bool isZipped = false;
		Buffer xmlData = Port::GetXML(_device.GetPort(), isZipped);

		_camera.LoadXML(xmlData, isZipped);
		_camera.Connect(static_cast<IPort*>(&_port));
		_camera.GetNodes();
	}

	//парсинг узлов
	size_t GetNodesSize()
	{
		return _camera.GetNodesSize();
	}
	std::string GetNodeName(uint32_t iIndex)
	{
		return _camera.GetNodeName(iIndex);
	}
	uint32_t GetNodeVisibility(uint32_t iIndex)
	{
		return _camera.GetNodeVisibility(iIndex);
	}
	uint32_t GetNodeAccess(uint32_t iIndex)
	{
		return _camera.GetNodeAccess(iIndex);
	}
	uint32_t GetNodeType(uint32_t iIndex)
	{
		return _camera.GetNodeType(iIndex);
	}

	bool GetIntNode(std::string iNode, int64_t& oValue)
	{
		return _camera.GetIntNode(iNode, oValue);
	}
	bool SetIntNode(std::string iNode, int64_t iValue)
	{
		_config._parameters[iNode] = iValue;
		return _camera.SetIntNode(iNode, iValue);
	}
	bool GetEnumStrNode(std::string iNode, std::string& oValue)
	{
		return _camera.GetEnumStrNode(iNode, oValue);
	}
	bool GetStrNode(std::string iNode, std::string& oValue)
	{
		return _camera.GetStrNode(iNode, oValue);
	}

	void SaveConfig(std::string iFileName)
	{
		_config.SaveConfig(iFileName);
	}

	void AcquirerPreparing()
	{
		_payloadSize = _camera.PayloadSize();
		_image = Buffer(_payloadSize);
		_imageAcquirer.AnnounceBuffers(_stream, _payloadSize);
		_imageAcquirer.StartAcquisition(_stream);
		_buffers = _imageAcquirer.GetBuffers();
	}
	void StartAcquisition()
	{
		_camera.StartAcquisition();
		elog(GCRegisterEvent(_stream, GenTL::EVENT_NEW_BUFFER, &_event), "GCRegisterEvent");
		AsyncAcquisition();
	}
	void StopAcquisition()
	{
		_stopAcquire = true;
		_camera.StopAcquisition();
	}

	size_t ImageSize()
	{
		return _payloadSize;
	}
	bool GetImage(unsigned char* oBuffer , size_t iSize)
	{
		if (!(_payloadSize >=static_cast<int64_t>(iSize)) || !_isReady)
			return false;

		memcpy(oBuffer, _image.Convert<void>(), sizeof(unsigned char) * iSize);
		return true;
	}
	void WaitNext()
	{
		_next = true;
	}

private:
	//захват изображений
	void AsyncAcquisition()
	{
		std::thread thr(AsyncCapture, std::ref(*this));
		thr.detach();
	}
	static void AsyncCapture(GigeManager& iManager)
	{
		int type = GenTL::INFO_DATATYPE_STRING;
		Buffer bufferInfo(20);
		Buffer dataBuffer(64);
		while (true)
		{
			if (iManager._stopAcquire) break;
			if (!iManager._next) continue;
			auto err = EventGetData(iManager._event, dataBuffer.Convert<void>(), dataBuffer.Size(), 10000);
			if (err == 0)
			{
				DSGetBufferInfo(iManager._stream, *dataBuffer.Convert<void**>(), GenTL::BUFFER_INFO_BASE, &type, bufferInfo.Convert<void>(), bufferInfo.Size());
				unsigned char* buf = *bufferInfo.Convert<unsigned char*>();
				memcpy(iManager._image.Convert<void>(), buf, sizeof(unsigned char) * iManager._payloadSize);
				elog(DSQueueBuffer(iManager._stream, *dataBuffer.Convert<void**>()), "DSQueueBuffer");

				iManager._isReady = true;
				iManager._next = false;
			}
			else if (err != GenTL::GC_ERR_TIMEOUT)
			{
				elog(err, "ArqFunction");
			}
		}
	}

	Configurator _config;

	TransportLayer _transportLayer;
	Interface _interface;
	Device _device;
	Port _port;
	Camera _camera;
	ImageAcquirer _imageAcquirer;

	std::vector<GenTL::BUFFER_HANDLE> _buffers;

	bool _next = false;
	bool _isReady = false;
	bool _stopAcquire = false;
	Buffer _image;

	GenTL::EVENT_HANDLE _event = nullptr;
	GenTL::DS_HANDLE _stream = nullptr;

	int64_t _payloadSize = 0;
};
