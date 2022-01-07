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

	void GetNodes()
	{
		cam._GetNodes(nodes);

		std::sort(nodes.begin(), nodes.end(), [](const INode* node1, const INode* node2)
		{
			if (node1->GetVisibility() != node2->GetVisibility())
				return node1->GetVisibility() < node2->GetVisibility();
			if (node1->GetAccessMode() != node2->GetAccessMode())
				return node1->GetAccessMode() > node2->GetAccessMode();
			if (node1->GetPrincipalInterfaceType() != node2->GetPrincipalInterfaceType())
				return node1->GetPrincipalInterfaceType() < node2->GetPrincipalInterfaceType();
			return false;
		});

		/*
		for (auto node = nodes.begin(); node != nodes.end(); ++node)
		{
			const auto nd = *node;
			std::cout << "Name: " << std::setw(50) << std::left << nd->GetName() 
				<< "Visibility: " << std::setw(2) << std::left << nd->GetVisibility()
				<< "AccessMode: " << std::setw(2) << std::left << nd->GetAccessMode()
				<< "InterfaceType: " << std::setw(2) << std::left << nd->GetPrincipalInterfaceType()
				<< std::endl;
		}*/
	}

	size_t GetNodesSize()
	{
		return nodes.size();
	}
	std::string getNodeName(uint32_t index)
	{
		return nodes[index]->GetName().c_str();
	}
	uint32_t getNodeVisibility(uint32_t index)
	{
		return nodes[index]->GetVisibility();
	}
	uint32_t getNodeAccess(uint32_t index)
	{
		return nodes[index]->GetAccessMode();
	}
	uint32_t getNodeType(uint32_t index)
	{
		return nodes[index]->GetPrincipalInterfaceType();
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
		CEnumerationPtr ptrNode = cam._GetNode(node.data());
		if (IsReadable(ptrNode))
		{
			value = ptrNode->GetCurrentEntry()->GetSymbolic();
			return true;
		}
		return false;
	}

	bool GetStrNode(std::string node, std::string& value)
	{
		CStringPtr ptrNode = cam._GetNode(node.data());
		if (IsReadable(ptrNode))
		{
			value = ptrNode->GetValue();
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
	CNodeMapRef cam;
	NodeList_t nodes;
};