/////////////////////////////////////////////////////////////////////
//	Project#2:		Type-based Dependency Analysis				   //
//					To create a Type-based dependency analyzer	   //
//																   //
//	## Created by using Prof. Jim Fawcett's 'CodeAnalyzer'     ##  //
//  ## project and augmenting it with 'Type Analysis',         ##  //
//  ## 'Dependency Analysis' and 'Strong Components' features. ##  //
//																   //
//  Type_Table.cpp: Test-stub for Type Table					   //
//  *************************************************************  //
//	Version:		1.0											   //
//  Date:			03/14/2017									   //
//  Language:       Visual C++, Version 11.						   //
//  Platform:       Visual Studio Community Edition				   //
//					HP ENVY, Windows 10				               //
//  Application:    CSE687 - Object Oriented Design                //
//  Author:         Sachin Basavani Shivashankara				   //
//	SUID:			267871645									   //
//  Ph:, email:     (315)751-5895, sbasavan@syr.edu				   //
/////////////////////////////////////////////////////////////////////

#include "Type_Table.h"
#include "../Type_Analysis/Type_Analysis.h"

using namespace CodeAnalysis;

using Rslt = Logging::StaticLogger<0>;
using Demo = Logging::StaticLogger<1>;
using Dbug = Logging::StaticLogger<2>;

#ifdef TEST_TYPETABLE

// Test-stub for Type Table
int main()
{
	std::cout << "Testing Type Table";

	TypeAnalysis ta;

	ta.doTypeAnal();

	TypeTable tt = ta.getTypeTable();

	tt.displayHeader();
	tt.display();

	return 0;
}
#endif
