#pragma once
#include <filesystem>
#include <unordered_map>
#include <thread>
#include <mutex>
#include <fstream>
#include <sstream>
#include <functional>
#include <future>
#include <variant>
#include <queue>

#include "ForwardDeclaration.h"

#ifdef FILE_MANAGER_DLL
#define FILE_MANAGER_API __declspec(dllexport)
#else
#define FILE_MANAGER_API
#endif

namespace File_Manager {
	class FILE_MANAGER_API FileManager {
	private:
		struct pathHash {
			size_t operator()(const std::filesystem::path& pathToFile) const noexcept;
		};

		struct filePathState {
			size_t readRequests;
			bool isWriteRequest;
			filePathState();
		};

		class FileHandle {
		protected:
			std::filesystem::path pathToFile;
			std::fstream file;
			std::ios::openmode mode;
			bool isOnDestruction;
		public:
			FileHandle(const std::filesystem::path& pathToFile, std::ios::openmode mode);
			FileHandle(FileHandle&& obj) noexcept;
			FileHandle& operator=(FileHandle&& obj) noexcept;
			uint64_t getFileSize() const;
			virtual ~FileHandle();
		};

		FileManager(uint32_t threadsCount);
		FileManager(const FileManager& obj) = delete;
		~FileManager();

		FileManager& operator=(const FileManager& obj) = delete;
		FileManager& operator=(FileManager&& obj) noexcept = delete;
	public:
		class FILE_MANAGER_API ReadFileHandle : public FileHandle {
		private:
			ReadFileHandle(const std::filesystem::path& pathToFile, std::ios::openmode mode = 0);
		public:
			std::string readAllData();
			std::streamsize readSome(std::string& outData, std::streamsize count, bool resizeOutData = true);
			std::istream& getStream();
			virtual ~ReadFileHandle();

			friend class FileManager;
		};

		class FILE_MANAGER_API WriteFileHandle : public FileHandle {
		private:
			WriteFileHandle(const std::filesystem::path& pathToFile, std::ios::openmode mode = 0);
		public:
			void write(const std::string& data);
			std::ostream& getStream();
			virtual ~WriteFileHandle();
			friend class FileManager;
		};
	private:
		class ReadBinaryFileHandle : public ReadFileHandle {
		public:
			ReadBinaryFileHandle(const std::filesystem::path& pathToFile);
			~ReadBinaryFileHandle() = default;
		};

		class WriteBinaryFileHandle : public WriteFileHandle {
		public:
			WriteBinaryFileHandle(const std::filesystem::path& pathToFile, std::ios::openmode mode = 0);
			virtual ~WriteBinaryFileHandle() = default;
		};
		
		class AppendFileHandle : public WriteFileHandle {
		public:
			AppendFileHandle(const std::filesystem::path& pathToFile);
			~AppendFileHandle() = default;
		};

		class AppendBinaryFileHandle : public WriteBinaryFileHandle {
		public:
			AppendBinaryFileHandle(const std::filesystem::path& pathToFile);
			~AppendBinaryFileHandle() = default;
		};
    protected:
		enum RequestType {
			READ,
			WRITE
		};

		enum RequestHandleType {
			READFILE,
			WRITEFILE,
			APPENDFILE,
			READBINARY,
			WRITEBINARY,
			APPENDBINARY
		};

		using readFileCallback = std::function<void(std::unique_ptr<ReadFileHandle>&&)>;
		using writeFileCallback = std::function<void(std::unique_ptr<WriteFileHandle>&&)>;
		using fileCallBack = std::variant<readFileCallback, writeFileCallback>;

		struct RequestStruct {
			fileCallBack callback;
			RequestHandleType handleType;
			std::function<void()> onEndCallback;

            RequestStruct(fileCallBack&& callback, std::function<void()> onEndCallback, RequestHandleType handleType);
		};

		friend bool operator==(const RequestStruct& request, RequestType type);
	private:
		Threading::ThreadPool* threadPool;
		std::unordered_map<std::filesystem::path, filePathState, pathHash> files;
		std::unordered_map<std::filesystem::path, std::queue<RequestStruct>, pathHash> requests;
		std::mutex filesMutex, requestsMutex;
	private:
		FileHandle* createHandle(const std::filesystem::path& pathToFile, RequestHandleType handleType);
		void notify(std::filesystem::path&& pathToFile, std::ios::openmode mode);
		void addRequest(const std::filesystem::path& pathToFile, fileCallBack&& callback, const std::function<void()>& onEndCallback, RequestHandleType handleType);
		void addReadRequest(const std::filesystem::path& pathToFile, const readFileCallback& callback, RequestHandleType handletype, bool isWait);
		void addWriteRequest(const std::filesystem::path& pathToFile, const readFileCallback& callback, RequestHandleType handletype, bool isWait);
		void processQueue(const std::filesystem::path& pathToFile);
		void decreaseReadRequests(const std::filesystem::path& pathToFile);
		void completeWriteRequest(const std::filesystem::path& pathToFile);
	public:
		static FileManager& getInstance(uint32_t threadsCount = std::thread::hardware_concurrency());
		void addFile(const std::filesystem::path& pathToFile, bool isFileAlreadyExist = true);
		void readFile(const std::filesystem::path& pathToFile, const readFileCallback& callback, bool isWait = true);
		void writeFile(const std::filesystem::path& pathToFile, const readFileCallback& callback, bool isWait = true);
		void appendFile(const std::filesystem::path& pathToFile, const readFileCallback& callback, bool isWait = true);
		void readBinaryFile(const std::filesystem::path& pathToFile, const readFileCallback& callback, bool isWait = true);
		void writeBinaryFile(const std::filesystem::path& pathToFile, const readFileCallback& callback, bool isWait = true);
		void appendBinaryFile(const std::filesystem::path& pathToFile, const readFileCallback& callback, bool isWait = true);
	};
}
