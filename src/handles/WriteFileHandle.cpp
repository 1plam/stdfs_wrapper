#include "..\FileManager.h"

namespace File_Manager {
	FileManager::WriteFileHandle::WriteFileHandle(const std::filesystem::path& pathToFile, std::ios::openmode mode)
		: FileHandle(pathToFile, mode | std::ios::out) 
	{
	
	}

	void FileManager::WriteFileHandle::write(const std::string& data)
	{
		file.write(data.data(), data.size());
	}

	std::ostream& FileManager::WriteFileHandle::getStream() 
	{
		return file.write(nullptr, 0);
	}

	FileManager::WriteFileHandle::~WriteFileHandle() 
	{
		if (isOnDestruction) 
		{
			FileManager::getInstance().completeWriteRequest(pathToFile);
		}
	}
}