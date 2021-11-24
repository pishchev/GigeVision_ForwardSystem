#pragma once
#include <iostream>

#include "Port.hpp"
#include "GenTL.h"
#include "GenICam.h"
#include "Configurator.h"

using namespace GENAPI_NAMESPACE;
using namespace GENICAM_NAMESPACE;

class Camera
{
public:
	void LoadXML(gcstring xml_str)
	{
		cam._LoadXMLFromString(xml_str);
	}

	void Connect(IPort* port)
	{
		cam._Connect(port);
	}

	void StartAcquisition()
	{
		CCommandPtr ptrAcquisitionStart = cam._GetNode("AcquisitionStart");
		if (IsWritable(ptrAcquisitionStart))
		{
			ptrAcquisitionStart->Execute();
		}
	}

	void StopAcquisition()
	{
		CCommandPtr ptrAcquisitionStop = cam._GetNode("AcquisitionStop");
		if (IsWritable(ptrAcquisitionStop))
		{
			ptrAcquisitionStop->Execute();
		}
	}
	
	int64_t SetWidthMin()
	{
		CIntegerPtr ptrWidth = cam._GetNode("Width");
		if (IsWritable(ptrWidth))
		{
			*ptrWidth = ptrWidth->GetMin();
		}
		return ptrWidth->GetValue();
	}

	int64_t SetHeightMin()
	{
		CIntegerPtr ptrHeight = cam._GetNode("Height");
		if (IsWritable(ptrHeight))
		{
			*ptrHeight = ptrHeight->GetMin();
		}
		return ptrHeight->GetValue();
	}

	bool SetHeight(CameraConfigInt config)
	{
		if (!config._active) return false;
		CIntegerPtr ptrHeight = cam._GetNode("Height");
		if (IsWritable(ptrHeight))
		{
			*ptrHeight = config._value;
			return true;
		}
		return false;
	}

	bool SetWidth(CameraConfigInt config)
	{
		if (!config._active) return false;
		CIntegerPtr ptrWidth = cam._GetNode("Width");
		if (IsWritable(ptrWidth))
		{
			*ptrWidth = config._value;
			return true;
		}
		return false;
	}

	int64_t PayloadSize()
	{
		CIntegerPtr ptrPayloadSize = cam._GetNode("PayloadSize");
		if (IsReadable(ptrPayloadSize))
		{
			return ptrPayloadSize->GetValue();
		}
		return -1;
	}

	gcstring PixelFormat()
	{
		CEnumerationPtr ptrPixelFormat = cam._GetNode("PixelFormat");
		if (IsReadable(ptrPixelFormat))
		{
			return ptrPixelFormat->GetCurrentEntry()->GetSymbolic();
		}
		return "Not readable node:(";
	}

private:
	CNodeMapRef cam;
};