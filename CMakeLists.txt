cmake_minimum_required(VERSION 3.22)
project(fmstream)

set(CMAKE_CXX_STANDARD 17)

include_directories(dependencies)
include_directories(dependencies/include)
include_directories(src)
include_directories(src/exceptions)

add_executable(fmstream
        dependencies/include/SingletonThreadPool.h
        dependencies/include/ThreadPool.h
        src/exceptions/BaseException.cpp
        src/exceptions/BaseException.h
        src/exceptions/FileDoesNotExistException.cpp
        src/exceptions/FileDoesNotExistException.h
        src/exceptions/NotAFileException.cpp
        src/exceptions/NotAFileException.h
        src/handles/AppendBinaryFileHandle.cpp
        src/handles/AppendFileHandle.cpp
        src/handles/FileHandle.cpp
        src/handles/ReadBinaryFileHandle.cpp
        src/handles/ReadFileHandle.cpp
        src/handles/WriteBinaryFileHandle.cpp
        src/handles/WriteFileHandle.cpp
        src/FileManager.cpp
        src/FileManager.h
        src/ForwardDeclaration.h)
