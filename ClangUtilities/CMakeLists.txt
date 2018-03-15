cmake_minimum_required(VERSION 2.8.9)

set(ClangUtilities_Srcs 
	TemplateUtilities.cpp 
	StringLiteralExtractor.cpp
	)
	
set(ClangUtilities_Hdrs 
	TemplateUtilities.h 
	StringLiteralExtractor.h
	)

add_library(ClangUtilities STATIC ${ClangUtilities_Srcs} ${ClangUtilities_Hdrs})



# Probably some can be removed...
target_link_libraries (ClangUtilities 
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


