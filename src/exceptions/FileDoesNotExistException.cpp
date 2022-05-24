#include "FileDoesNotExistException.h"

namespace File_Manager
{
	namespace Exceptions
	{
		FileDoesNotExistException::FileDoesNotExistException(const std::filesystem::path& pathToFile) :
			BaseException("The file " + pathToFile.string() + " doesn't exist!")
		{

		}
	}
}