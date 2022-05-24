#include "..\FileManager.h"
namespace File_Manager {
	FileManager::FileHandle::FileHandle(const std::filesystem::path& pathToFile, std::ios::openmode mode) 
		: pathToFile(pathToFile), file(pathToFile, mode), mode(mode), isOnDestruction(true) 
	{
	}

	FileManager::FileHandle::FileHandle(FileHandle&& obj) noexcept 
	{
		*this = std::move(obj);
	}

	FileManager::FileHandle& FileManager::FileHandle::operator=(FileHandle&& obj) noexcept 
	{
		pathToFile = std::move(obj.pathToFile);
		file = std::move(obj.file);
		mode = obj.mode;
		isOnDestruction = true;
		obj.isOnDestruction = false;
		return *this;
	}

	uint64_t File_Manager::FileManager::FileHandle::getFileSize() const
	{
		return std::filesystem::file_size(pathToFile);
	}

	FileManager::FileHandle::~FileHandle() 
	{
		if (isOnDestruction) 
		{
			file.close();
			FileManager::getInstance().notify(std::move(pathToFile), mode);
		}
	}

}