#ifndef _H_COMMON_UTILS_H_
#define _H_COMMON_UTILS_H_

#include <string>
#include <vector>

/**
* @brief check if the path exists
* @param path -- the path
* @return true if the path exists, otherwise return false
*/
bool check_path_exists(const std::string &path);

/**
* @brief create directory recursively
* @param directory -- the directory path
* @return true if create successfully, otherwise return false
*/
bool create_directory_recursively(const std::string &directory);

#endif