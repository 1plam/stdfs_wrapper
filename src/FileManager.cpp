#include <future>
#include <utility>

#include "FileManager.h"
#include "FileDoesNotExistException.h"
#include "NotAFileException.h"
#include "ThreadPool.h"

namespace File_Manager {
    size_t File_Manager::FileManager::pathHash::operator()(const std::filesystem::path &pathToFile) const noexcept {
        return std::hash<std::string>()(pathToFile.string());
    }

    File_Manager::FileManager::filePathState::filePathState()
        : readRequests(0), isWriteRequest(false)
    {
    }

    File_Manager::FileManager::RequestStruct::RequestStruct(fileCallBack&& callback, std::function<void()> onEndCallback, RequestHandleType handleType)
        : callback(std::move(callback)), onEndCallback(std::move(onEndCallback)), handleType(handleType)
    {
    }

    bool operator==(const File_Manager::FileManager::RequestStruct& request, File_Manager::FileManager::RequestType type) {
        return request.callback.index() == static_cast<size_t>(type);
    }

    FileManager::FileHandle* FileManager::createHandle(const std::filesystem::path &pathToFile, FileManager::RequestHandleType handleType) {
        switch (handleType) {
            case READFILE: return new ReadFileHandle(pathToFile);
            case WRITEFILE: return new WriteFileHandle(pathToFile);
            case READBINARY: return new ReadBinaryFileHandle(pathToFile);
            case WRITEBINARY: return new WriteBinaryFileHandle(pathToFile);
            case APPENDFILE: return new AppendFileHandle(pathToFile);
            case APPENDBINARY: return new AppendBinaryFileHandle(pathToFile);
        }

        return new FileHandle(pathToFile, static_cast<std::_Ios_Openmode>(NULL));
    }

    void FileManager::notify(std::filesystem::path &&pathToFile, std::ios::openmode mode) {
        std::lock_guard<std::mutex> lockGuard(filesMutex);
        if (std::ios::out & mode && !files[pathToFile].isWriteRequest) {
            threadPool->addTask([this, temporary = std::move(pathToFile)]() -> void {
                this->processQueue(temporary);
            });
        }
    }

    void FileManager::addRequest(const std::filesystem::path &pathToFile, fileCallBack &&callback, const std::function<void()> &onEndCallback, RequestHandleType handleType) {
        std::lock_guard<std::mutex> lockGuard(requestsMutex);
        requests[pathToFile].push(RequestStruct(std::move(callback), onEndCallback, handleType));
    }
}
