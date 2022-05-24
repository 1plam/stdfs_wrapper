#include "..\FileManager.h"

namespace File_Manager {
	FileManager::AppendBinaryFileHandle::AppendBinaryFileHandle(const std::filesystem::path& pathToFile)
		: WriteBinaryFileHandle(pathToFile, std::ios::app)
	{

	}
}