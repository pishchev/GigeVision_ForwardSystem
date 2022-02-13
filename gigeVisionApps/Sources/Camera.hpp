#pragma once
#include <iostream>

#include "Port.hpp"
#include "GenTL.h"
#include "GenICam.h"
#include "Configurator.hpp"

using namespace GENAPI_NAMESPACE;
using namespace GENICAM_NAMESPACE;

class Camera
{
public:
	void LoadXML(Buffer iBuffer, bool iIsZipped)
	{
		if (iIsZipped)
			_camera._LoadXMLFromZIPData(iBuffer.Convert<void>(), *iBuffer.Size());
		else
			_camera._LoadXMLFromString(iBuffer.Convert<char>());
	}

	void Connect(IPort* iPort)
	{
		_camera._Connect(iPort);
	}

	void StartAcquisition()
	{
		CCommandPtr ptrAcquisitionStart = _camera._GetNode("AcquisitionStart");
		if (IsWritable(ptrAcquisitionStart))
			ptrAcquisitionStart->Execute();
	}

	void StopAcquisition()
	{
		CCommandPtr ptrAcquisitionStop = _camera._GetNode("AcquisitionStop");
		if (IsWritable(ptrAcquisitionStop))
			ptrAcquisitionStop->Execute();
	}

	void GetNodes()
	{
		_camera._GetNodes(_nodes);
		std::sort(_nodes.begin(), _nodes.end(), [](const INode* iNode1, const INode* iNode2)
		{
			if (iNode1->GetVisibility() != iNode2->GetVisibility())
				return iNode1->GetVisibility() < iNode2->GetVisibility();
			if (iNode1->GetAccessMode() != iNode2->GetAccessMode())
				return iNode1->GetAccessMode() > iNode2->GetAccessMode();
			if (iNode1->GetPrincipalInterfaceType() != iNode2->GetPrincipalInterfaceType())
				return iNode1->GetPrincipalInterfaceType() < iNode2->GetPrincipalInterfaceType();
			return false;
		});
	}

	size_t GetNodesSize()
	{
		return _nodes.size();
	}
	std::string GetNodeName(uint32_t iIndex)
	{
		return _nodes[iIndex]->GetName().c_str();
	}
	uint32_t GetNodeVisibility(uint32_t iIndex)
	{
		return _nodes[iIndex]->GetVisibility();
	}
	uint32_t GetNodeAccess(uint32_t iIndex)
	{
		return _nodes[iIndex]->GetAccessMode();
	}
	uint32_t GetNodeType(uint32_t iIndex)
	{
		return _nodes[iIndex]->GetPrincipalInterfaceType();
	}

	bool SetIntNode(std::string iNode, int64_t iValue)
	{
		CIntegerPtr ptrNode = _camera._GetNode(iNode.data());
		if (IsWritable(ptrNode))
		{
			*ptrNode = iValue;
			return true;
		}
		return false;
	}

	bool GetIntNode(std::string iNode, int64_t& oValue)
	{
		CIntegerPtr ptrNode = _camera._GetNode(iNode.data());
		if (IsReadable(ptrNode))
		{
			oValue = ptrNode->GetValue();
			return true;
		}
		return false;
	}

	bool GetEnumStrNode(std::string iNode, std::string& oValue)
	{
		CEnumerationPtr ptrNode = _camera._GetNode(iNode.data());
		if (IsReadable(ptrNode))
		{
			oValue = ptrNode->GetCurrentEntry()->GetSymbolic();
			return true;
		}
		return false;
	}

	bool GetStrNode(std::string iNode, std::string& oValue)
	{
		CStringPtr ptrNode = _camera._GetNode(iNode.data());
		if (IsReadable(ptrNode))
		{
			oValue = ptrNode->GetValue();
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

private:
	CNodeMapRef _camera;
	NodeList_t _nodes;
};