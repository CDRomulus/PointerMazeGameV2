#pragma once

#include <string>     
#include <chrono>
#include <iostream>
#include <random>
namespace CustomSystem
{
	extern int rngIntGen(int l_thresh, int h_thresh)
{
	std::random_device rd;     // only used once to initialise (seed) engine
	std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
	std::uniform_int_distribution<int> uni(l_thresh, h_thresh); // guaranteed unbiased
	auto random_integer = uni(rng);
	return random_integer;
}
extern void WaitForInput()
	{
		std::cin.get();
	}
};
#if defined(_WIN32)
#include <windows.h>

namespace CustomSystem 
{
	extern void ClearScreen()
	{
		std::cout<<"\nPress enter to continue.";
		std::cin.get();
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



