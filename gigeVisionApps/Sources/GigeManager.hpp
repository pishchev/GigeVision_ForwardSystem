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
#include "Configurator.hpp"
#include "Fifo.hpp"
#include "BayerConverter.hpp"

#include "GenTL.h"
#include "GenICam.h"


class GigeManager
{
public:

	enum NodeTypes 
	{
		Int = 2,
		Bool = 3,
		Float = 5,
		Command = 4,
		String = 6,
		Enumeration = 9
	};
	enum ConverterType 
	{ 
		RGBInt,
		RGBNoInt
	};

	GigeManager(){}

	~GigeManager()
	{
		//StopAcquisition();
		if (_stream) 
		{
			//std::cout << "~Stream" << std::endl;
			//elog(DSClose(_stream), "DSClose");
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
		{
			if (param->second.type == "int")
				SetIntNode(param->first, std::stoi(param->second.value));
			if (param->second.type == "float")
				SetFloatNode(param->first, std::stof(param->second.value));
			if (param->second.type == "bool")
				SetBoolNode(param->first, param->second.value == "1" ? true : false);
			if (param->second.type == "enum")
				SetEnumStrNode(param->first, param->second.value);
		}
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

	bool GetCommandNode(std::string iNode, bool& oValue)
	{
		return _camera.GetCommandNode(iNode, oValue);
	}
	bool ExecuteCommand(std::string iNode)
	{
		return _camera.ExecuteCommand(iNode);
	}
	bool GetIntNode(std::string iNode, int64_t& oValue)
	{
		return _camera.GetIntNode(iNode, oValue);
	}
	bool SetIntNode(std::string iNode, int64_t iValue)
	{
		_config._parameters[iNode] = Parameter("int", std::to_string(iValue));
		return _camera.SetIntNode(iNode, iValue);
	}
	bool GetFloatNode(std::string iNode, double& oValue)
	{
		return _camera.GetFloatNode(iNode, oValue);
	}
	bool SetFloatNode(std::string iNode, double iValue)
	{
		_config._parameters[iNode] = Parameter("float", std::to_string(iValue));
		return _camera.SetFloatNode(iNode, iValue);
	}
	bool GetBoolNode(std::string iNode, bool& oValue)
	{
		return _camera.GetBoolNode(iNode, oValue);
	}
	bool SetBoolNode(std::string iNode, bool iValue)
	{
		_config._parameters[iNode] = Parameter("bool", iValue? "1":"0");
		return _camera.SetBoolNode(iNode, iValue);
	}
	bool GetEnumStrNode(std::string iNode, std::string& oValue)
	{
		return _camera.GetEnumStrNode(iNode, oValue);
	}
	bool GetEnumNodeName(std::string iNode, std::string& oValue)
	{
		return _camera.GetEnumNodeName(iNode, oValue);
	}
	size_t GetEnumStrEntrySize(std::string iNode)
	{
		return _camera.GetEnumStrEntrySize(iNode);
	}
	std::string GetEnumStrEntryName(std::string iNode, size_t iIndex)
	{
		return _camera.GetEnumStrEntryName(iNode, iIndex);
	}
	bool SetEnumStrNode(std::string iNode, std::string iValue)
	{
		_config._parameters[iNode] = Parameter("enum", iValue);
		return _camera.SetEnumStrNode(iNode, iValue);
	}
	bool GetStrNode(std::string iNode, std::string& oValue)
	{
		return _camera.GetStrNode(iNode, oValue);
	}

	void SaveConfig(std::string iFileName)
	{
		_config.SaveConfig(iFileName);
	}

	int64_t PayloadSize()
	{
		GetIntNode("PayloadSize", _payloadSize);
		GetIntNode("Width", _width);
		GetIntNode("Height", _height);

		if (_width * _height == _payloadSize)
			return _payloadSize * 3;
		return _payloadSize;
	}

	void AcquirerPreparing()
	{
		GetIntNode("PayloadSize", _payloadSize);
		GetIntNode("Width", _width);
		GetIntNode("Height", _height);

		if (_width * _height == _payloadSize && !_converter)
			SetConverter(RGBNoInt);

		if (_converter) {
			_converter->_height = _height;
			_converter->_width = _width;
		}

		_fifoImage = new FIFO(_payloadSize, 50);
		_fifoTimestamps = new FIFO(sizeof(uint64_t), 50);
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

	bool GetImage(size_t iImageIndex, unsigned char* oBuffer)
	{
		if (!_isReady)
			return false;

		if (_converter) {
			const auto bayerBuffer = _fifoImage->GetBufferPtr(iImageIndex);
			if (!bayerBuffer)
				return false;

			_converter->_buffer = bayerBuffer;
			_converter->Convert(oBuffer);
			return true;
		}
		else
			return _fifoImage->GetBuffer(iImageIndex, oBuffer);
	}
	bool GetTimestamp(size_t iImageIndex, size_t& oTimestamp)
	{
		if (!_isReady)
			return false;

		return _fifoTimestamps->GetBuffer(iImageIndex, (unsigned char*)&oTimestamp);
	}
	void GetBufferInfo(size_t& oMin, size_t& oMax)
	{
		_fifoImage->GetInfo(oMin, oMax);
	}

	void SetConverter(ConverterType iType) {
		if (iType == RGBInt)
			_converter = RGBIntPtr(new BayerConverterRGBInterpolated);
		else if (iType == RGBNoInt)
			_converter = RGBNoIntPtr(new BayerConverterRGBNoInterpolated);
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
		Buffer imageBuffer(64);
		Buffer timestamp(64);
		Buffer dataBuffer(64);
		while (true)
		{
			if (iManager._stopAcquire) break;
			auto err = EventGetData(iManager._event, dataBuffer.Convert<void>(), dataBuffer.Size(), 10000);
			if (err == 0)
			{
				const auto dataBufferPtr = *dataBuffer.Convert<void**>();

				elog(DSGetBufferInfo(iManager._stream, dataBufferPtr, GenTL::BUFFER_INFO_BASE, &type, imageBuffer.Convert<void>(), imageBuffer.Size()), "IMAGEBUFER");
				iManager.AddImageToBuffer(*imageBuffer.Convert<unsigned char*>());

				const auto err = DSGetBufferInfo(iManager._stream, dataBufferPtr, GenTL::BUFFER_INFO_TIMESTAMP, &type, timestamp.Convert<void>(), timestamp.Size());
				if (err == 0) iManager.AddTimestampToBuffer(timestamp.Convert<unsigned char>());

				elog(DSQueueBuffer(iManager._stream, dataBufferPtr), "DSQueueBuffer");

				iManager._isReady = true;
			}
			else if (err != GenTL::GC_ERR_TIMEOUT)
			{
				elog(err, "ArqFunction");
			}
		}
	}

	void AddImageToBuffer(unsigned char* iImage) 
	{
		_fifoImage->PushBack(iImage);
	}
	void AddTimestampToBuffer(unsigned char* iTimestamp)
	{
		_fifoTimestamps->PushBack(iTimestamp);
	}

	Configurator _config;

	TransportLayer _transportLayer;
	Interface _interface;
	Device _device;
	Port _port;
	Camera _camera;
	ImageAcquirer _imageAcquirer;

	std::vector<GenTL::BUFFER_HANDLE> _buffers;

	bool _isReady = false;
	bool _stopAcquire = false;

	FIFO* _fifoImage;
	FIFO* _fifoTimestamps;

	GenTL::EVENT_HANDLE _event = nullptr;
	GenTL::DS_HANDLE _stream = nullptr;

	int64_t _width = 0;
	int64_t _height = 0;
	int64_t _payloadSize = 0;

	ConverterPtr _converter;
};
