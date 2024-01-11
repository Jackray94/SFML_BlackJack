#include "imageFileHandle.h"

namespace bj{

int fileCount()
{
  int count = 0;

  const std::filesystem::path path{"./Media/Textures"};

  for(auto const & files : std::filesystem::directory_iterator(path)){
    count++;
  }

  return count;
}

std::vector<std::string> ListOfFilesInDirectory()
{
  auto vecStr = std::vector<std::string>();
  std::string str = " ";

  const std::filesystem::path path{"./Media/Textures"};

  for(auto const & files : std::filesystem::directory_iterator(path)){
    // str = files.path().string();
    str = files.path().stem();
    vecStr.push_back(str);
  }

  std::sort(vecStr.begin(), vecStr.end());

  return vecStr;
}

} // namespace bj
