#include "..\FileManager.h"

namespace File_Manager {
	FileManager::ReadBinaryFileHandle::ReadBinaryFileHandle(const std::filesystem::path& pathToFile) 
		: ReadFileHandle(pathToFile, std::ios::binary)
	{
	
	}
}