#include "common_utils.h"

#include <algorithm>
#include <cctype>

#include <sys/types.h>
#include <sys/stat.h>

#ifdef _WIN32
#include <io.h>
#include <direct.h>
#include <windows.h>
#endif

bool check_path_exists(const std::string &path)
{
#ifdef _WIN32
	DWORD dwAttrib = GetFileAttributesA(path.c_str());
	return INVALID_FILE_ATTRIBUTES != dwAttrib && 0 == (dwAttrib & FILE_ATTRIBUTE_DIRECTORY);
#else
	struct stat st;
	if (stat(path.c_str(), &st) == 0)
	{
		return true;
	}

	return false;
#endif
}

bool create_directory_recursively(const std::string &directory)
{
	if (check_path_exists(directory))
	{
		return true;
	}
#ifdef _WIN32
	if (_access(directory.c_str(), 0) != -1 || directory.empty())
	{
		return false;
	}

	create_directory_recursively(directory.substr(0, directory.rfind('\\')));
	mkdir(directory.c_str());
	return true;
#else

	size_t pos = directory.rfind("/");
	if (pos != std::string::npos)
	{
		std::string parent = directory.substr(0, pos);
		bool ret = create_directory_recursively(parent);
		if (!ret)
		{
			return false;
		}
	}

	mode_t mode = S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
	if (mkdir(directory.c_str(), mode) != 0)
	{
		if (errno == EEXIST)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return true;
	}
#endif
}