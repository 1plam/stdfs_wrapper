#include "..\FileManager.h"

namespace File_Manager {
	FileManager::AppendFileHandle::AppendFileHandle(const std::filesystem::path& pathToFile) 
		: WriteFileHandle(pathToFile, std::ios::app) 
	{

	}
}