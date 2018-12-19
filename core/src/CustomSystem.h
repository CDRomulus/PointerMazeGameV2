#pragma once

#include <string>
#include <thread>        
#include <chrono>
#include <iostream>

#if defined(_WIN32)
#define PLATFORM_NAME "windows" // Windows
#include <windows.h>
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
	std::string getPath()
	{
		return this->path;
	}
	std::string getExePath()
	{
		return this->exePath;
	}
};
class System
{
public:
	void ClearScreen()
	{
		system("cls");
	}
	void WaitForInput()
	{
		std::cout << "Press Enter to Continue\n";
		system("PAUSE");
	}
};
#elif defined(__linux__)
#define PLATFORM_NAME "linux"
#include <unistd.h>
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
		this->exePath= std::string(result, (count > 0) ? count : 0);		

		this->path = this->exePath.substr(0, this->exePath.find_last_of("\\/"));
	}
	std::string getPath()
	{
		return this->path;
	}
	std::string getExePath()
	{
		return this->exePath;
	}
};
class System
{
public:
	void ClearScreen()
	{
		system("clear");
	}
	void WaitForInput()
	{
		std::cout << "Press Enter to Continue\n";
		pause();
	}
};
#endif



