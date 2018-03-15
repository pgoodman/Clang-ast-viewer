cmake_minimum_required(VERSION 2.8.9)
project(ClangAstViewer)

# Make sure we can find qt.
list(APPEND CMAKE_PREFIX_PATH /usr/local/opt/qt5/lib/cmake/)
#list(APPEND CMAKE_PREFIX_PATH /usr/local/opt/llvm/lib/cmake/llvm/)
#list(APPEND CMAKE_PREFIX_PATH /usr/local/opt/llvm/lib/cmake/clang/)

# enable the gnu extensions
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD 17)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
cmake_policy(SET CMP0071 NEW)
set(CMAKE_AUTOMOC ON)

# Find LLVM.
find_package(LLVM REQUIRED CONFIG)
add_definitions(${LLVM_DEFINITIONS})
include_directories(SYSTEM ${LLVM_INCLUDE_DIRS})
link_directories(${LLVM_LIBRARY_DIRS})
llvm_map_components_to_libnames(LLVM_LIBS support core object mc option profiledata)
set (CLANG_LIBS clangAST clangFrontend clangSerialization clangDriver
  clangParse clangSema clangAnalysis  clangBasic clangEdit
  clangLex clangTooling)

# Find the QtWidgets library
find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
set (QT5_LIBRARIES Qt5::Widgets Qt5::Core)

find_package(Boost REQUIRED)
include_directories(SYSTEM ${Boost_INCLUDE_DIRS})

add_definitions(-fvisibility=hidden)

add_subdirectory(ClangUtilities)

set(ClangAst_Forms MainWindow.ui)
set(ClangAst_Srcs 
	main.cpp 
	MainWindow.cpp 
	Highlighter.cpp
	AstReader.cpp
	AstModel.cpp
	CommandLineSplitter.cpp
	)

set(ClangAst_Hdrs 
	MainWindow.h 
	Highlighter.h
	AstReader.h
	AstModel.h
	CommandLineSplitter.h
	)

QT5_WRAP_UI(UIS_HDRS ${ClangAst_Forms})

# Tell CMake to create the helloworld executable
add_executable(ClangAstViewer ${ClangAst_Srcs} ${ClangAst_Hdrs} ${UIS_HDRS})


# Probably some can be removed...
target_link_libraries (ClangAstViewer 
	ClangUtilities
	clangAnalysis
	clangAST
	clangASTMatchers
	clangBasic
	clangDriver
	clangEdit
	clangFrontend
	clangLex
	clangParse
	clangStaticAnalyzerCore
	clangStaticAnalyzerCheckers
	clangStaticAnalyzerFrontend
	clangRewrite
	clangSema
	clangSerialization
	clangTooling
	LLVMBitReader
	LLVMMC
	LLVMMCParser
	LLVMOption
	LLVMSupport
	LLVMProfileData
	LLVMCore
	)

# Use the Widgets module from Qt 5.
qt5_use_modules(ClangAstViewer Widgets)


