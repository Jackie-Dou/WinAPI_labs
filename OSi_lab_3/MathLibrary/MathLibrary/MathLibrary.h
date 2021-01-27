// MathLibrary.h - Contains declarations of math functions
#pragma once
#include <windows.h>
#include <tlhelp32.h>

#define MAX_READ 128

#ifdef MATHLIBRARY_EXPORTS
#define MATHLIBRARY_API __declspec(dllexport)
#else
#define MATHLIBRARY_API __declspec(dllimport)
#endif

extern "C" MATHLIBRARY_API void ReplaceString(char* lpOrigStr, char* lpReplStr);
