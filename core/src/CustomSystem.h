#pragma once

#include <string>     
#include <chrono>
#include <iostream>

#if defined(_WIN32)
#include <windows.h>

namespace CustomSystem 
{
	extern void ClearScreen()
	{
		system("cls");
	}
	extern void WaitForInput()
	{
		system("PAUSE");
	}
	class Directory
	{
	private:
		std::string path;
		std::string exePath;
	public:
		Directory()
		{
			char buffer[MAX_PATH];
			GetModuleFileName(NULL, buffer, MAX_PATH);
			this->exePath = std::string(buffer);

			this->path = this->exePath.substr(0, this->exePath.find_last_of("\\/"));
		}
		std::string getDir()
		{
			return this->path;
		}
		std::string getExeDir()
		{
			return this->exePath;
		}
	};
};

#elif defined(__linux__)
#include <unistd.h>
#include <limits.h>
namespace CustomSystem 
{
	extern void ClearScreen()
	{
		system("clear");
	}
	extern void WaitForInput()
	{
		//std::cout << "Press Enter to Continue\n";
		
		//std::cin.get();
		//TODO: This doesnt work for somereason. >:(  
	}
	class Directory
	{
	private:
		std::string path;
		std::string exePath;
	public:
		Directory()
		{
			char result[PATH_MAX];
			ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
			this->exePath = std::string(result, (count > 0) ? count : 0);

			this->path = this->exePath.substr(0, this->exePath.find_last_of("\\/"));
		}
		std::string getDir()
		{
			return this->path;
		}
		std::string getExeDir()
		{
			return this->exePath;
		}
	};
};
#endif



