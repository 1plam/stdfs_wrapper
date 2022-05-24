#include "BaseException.h"

namespace File_Manager {
	namespace Exceptions {
		BaseException::BaseException(const std::string& message) 
			: std::runtime_error(message)
		{
		
		}
	}
}