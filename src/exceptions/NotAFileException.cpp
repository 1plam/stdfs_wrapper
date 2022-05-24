#include "NotAFileException.h"

namespace File_Manager
{
	namespace Exceptions
	{
		NotAFileException::NotAFileException(const std::filesystem::path& path) :
			BaseException("The path " + path.string() + " doesn't represent a file!")
		{

		}
	}
}