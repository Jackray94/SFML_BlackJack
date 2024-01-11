#ifndef IMAGEFILEHANDLE_H
#define IMAGEFILEHANDLE_H

#include <filesystem>
#include <vector>
#include <string>
#include <algorithm>

namespace bj{

[[nodiscard]] std::vector<std::string> ListOfFilesInDirectory();

[[nodiscard]] int fileCount();

} // namespace bj

#endif
