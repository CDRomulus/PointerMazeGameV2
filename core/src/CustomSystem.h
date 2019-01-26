#pragma once

#include <string>
#include <chrono>
#include <iostream>
#include <random>

#ifndef FALSE
#define FALSE               0
#endif

#ifndef TRUE
#define TRUE                1
#endif

namespace CustomSystem
{
	inline int rngIntGen(int l_thresh, int h_thresh)
	{
	std::random_device rd;     // only used once to initialise (seed) engine
	std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
	std::uniform_int_distribution<int> uni(l_thresh, h_thresh); // guaranteed unbiased
	auto random_integer = uni(rng);
	return random_integer;
	}

};
#if defined(_WIN32)
#include <windows.h>

namespace CustomSystem
{
	inline  void ClearScreen()
	{
		system("cls");
	}

	inline  std::string getExeDirectory()
	{
		char buffer[MAX_PATH];
		GetModuleFileName(NULL, buffer, MAX_PATH);
		return std::string(buffer);


	}
	inline  std::string GetDirectory()
	{
		return getExeDirectory().substr(0, getExeDirectory().find_last_of("\\/"));
	}
};

#elif defined(__linux__)
#include <unistd.h>
#include <limits.h>

namespace CustomSystem
{
	inline  void ClearScreen()
	{
		system("clear");
	}

		inline  std::string getExeDirectory()
		{
			char result[PATH_MAX];
			ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
			return std::string(result, (count > 0) ? count : 0);


		}
		inline  std::string GetDirectory()
		{


			return getExeDirectory().substr(0, getExeDirectory().find_last_of("\\/"));
		}
};
#endif



