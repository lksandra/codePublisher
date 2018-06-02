/////////////////////////////////////////////////////////////////////
//	Project#2:		Type-based Dependency Analysis				   //
//					To create a Type-based dependency analyzer	   //
//																   //
//	## Created by using Prof. Jim Fawcett's 'CodeAnalyzer'     ##  //
//  ## project and augmenting it with 'Type Analysis',         ##  //
//  ## 'Dependency Analysis' and 'Strong Components' features. ##  //
//																   //
//  Dep_Table.cpp:  Test-stub for Dependency Table				   //
//  *************************************************************  //
//	Version:		1.0											   //
//  Date:			03/15/2017									   //
//  Language:       Visual C++, Version 11.						   //
//  Platform:       Visual Studio Community Edition				   //
//					HP ENVY, Windows 10				               //
//  Application:    CSE687 - Object Oriented Design                //
//  Author:         Sachin Basavani Shivashankara				   //
//	SUID:			267871645									   //
//  Ph:, email:     (315)751-5895, sbasavan@syr.edu				   //
/////////////////////////////////////////////////////////////////////

#include "../Dependency_Analysis/Dep_Anal.h"
#include "Dep_Table.h"

using namespace CodeAnalysis;

using Rslt = Logging::StaticLogger<0>;
using Demo = Logging::StaticLogger<1>;
using Dbug = Logging::StaticLogger<2>;
using TypeTableMap = std::map<std::string, std::vector<CodeAnalysis::TypeInfo>>;

#ifdef DEP_TABLE

// Test-stub for Dependency Table
int main()
{
	return 0;
}

#endif