#pragma once
#include "BaseException.h"

namespace File_Manager
{
	namespace Exceptions
	{
		/// @brief Thrown if file does not exist
		class FILE_MANAGER_API FileDoesNotExistException : public BaseException
		{
		public:
			FileDoesNotExistException(const std::filesystem::path& pathToFile);
			~FileDoesNotExistException() = default;
		};
	}
}