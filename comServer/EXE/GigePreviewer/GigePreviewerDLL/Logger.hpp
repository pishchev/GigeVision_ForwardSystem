#pragma once

#include <iostream>
#include <windows.h> 
#include <assert.h>

#include "GenTL.h"

#include "LibLoader.hpp"


static void log(GenTL::GC_ERROR err, std::string oper)
{
	Buffer buff(1000);
	size_t err_size = 1000;
	char* err_ch = new char[err_size];

	auto log_error = GCGetLastError(&err, buff.Convert<char>(), buff.Size());

	if (log_error != 0)
	{
		std::cout << "Logging error! Error descriptor: " << log_error << std::endl;
		return;
	}

	std::cout << "log -> Operation " << oper << ". Status: " << buff.Convert<char>() << std::endl;

	if (err != 0)
	{
		std::cout << "Error code: " << err << std::endl;
		system("pause");
		exit(-1);
	}
}

static void elog(GenTL::GC_ERROR err, std::string oper)
{
	if (err != 0)
		log(err, oper);
}


