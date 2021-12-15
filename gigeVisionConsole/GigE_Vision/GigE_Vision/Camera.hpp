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

	bool SetIntNode(std::string node, int64_t value)
	{
		CIntegerPtr ptrNode = cam._GetNode(node.data());
		if (IsWritable(ptrNode))
		{
			*ptrNode = value;
			return true;
		}
		return false;
	}

	bool GetIntNode(std::string node, int64_t& value)
	{
		CIntegerPtr ptrNode = cam._GetNode(node.data());
		if (IsReadable(ptrNode))
		{
			value = ptrNode->GetValue();
			return true;
		}
		return false;
	}

	bool GetEnumStrNode(std::string node, std::string& value)
	{
		CEnumerationPtr ptrNode = cam._GetNode("PixelFormat");
		if (IsReadable(ptrNode))
		{
			value = ptrNode->GetCurrentEntry()->GetSymbolic();
			return true;
		}
		return false;
	}

	int64_t PayloadSize()
	{
		int64_t payloadSize = 0;
		GetIntNode("PayloadSize", payloadSize);
		return payloadSize;
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