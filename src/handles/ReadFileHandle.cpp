#include "..\FileManager.h"

namespace File_Manager {
	FileManager::ReadFileHandle::ReadFileHandle(const std::filesystem::path& pathToFile, std::ios::openmode mode)
		: FileHandle(pathToFile, mode | std::ios::in) 
	{

	}

	std::string FileManager::ReadFileHandle::readAllData() 
	{
		return (std::ostringstream() << file.rdbuf()).str();
	}

	std::streamsize FileManager::ReadFileHandle::readSome(std::string& outData, std::streamsize count, bool resizeData) {
		if (resizeData && outData.size() != count) 
		{
			outData.resize(count);
		}

		std::streamsize temporary = file.readsome(outData.data(), count);

		if (resizeData && outData.size() != temporary) 
		{
			outData.resize(temporary);
		}
			
		return temporary;
	}

	std::istream& FileManager::ReadFileHandle::getStream() 
	{
		return file.read(nullptr, 0);
	}

	FileManager::ReadFileHandle::~ReadFileHandle() 
	{
		if (isOnDestruction) 
		{
			FileManager::getInstance().decreaseReadRequests(pathToFile);
		}
	}
}