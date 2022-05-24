#pragma once
#include "BaseException.h"

namespace File_Manager
{
	namespace Exceptions
	{
		/// @brief Thrown if path represents not a regular file
		class FILE_MANAGER_API NotAFileException : public BaseException
		{
		public:
			NotAFileException(const std::filesystem::path& path);
			~NotAFileException() = default;
		};
	}
}