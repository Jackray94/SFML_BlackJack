#include "imageFileHandle.h"

int fileCount()
{
  int count = 0;

  const std::filesystem::path path{"./Media/Textures"};

  for(auto const & files : std::filesystem::directory_iterator(path)){
    count++;
  }

  return count;
}

std::vector<std::string> filesInDirectory()
{
  auto vecStr = std::vector<std::string>();
  std::string str = " ";

  const std::filesystem::path path{"./Media/Textures"};

  for(auto const & files : std::filesystem::directory_iterator(path)){
    str = files.path().string();
    vecStr.push_back(str);
  }

  std::sort(vecStr.begin(), vecStr.end()); // is this redundent? Haven't I changed this? Meaning, before my recent changes there was a need to sort because the source we copied this vector from would have been randomized. ???????
  // ??????????????????
  // Or, has this sort not been needed this whole time? shoudln't they be in order due to the file system being alphabetically ordered already????

  return vecStr;
}
