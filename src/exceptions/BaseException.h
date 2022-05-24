#include <stdexcept>
#include <filesystem>
#ifdef FILE_MANAGER_DLL
#define FILE_MANAGER_API __declspec(dllexport)

#pragma warning(disable: 4251)
#pragma warning(disable: 4275)
#else
#define FILE_MANAGER_API
#endif

namespace File_Manager {
	namespace Exceptions {
		class FILE_MANAGER_API BaseException : std::runtime_error {
		public:
			BaseException(const std::string& message);
			virtual ~BaseException() = default;
		};
	}
}