#pragma once
#ifndef TEST_EXE
#define TEST_EXE

/////////////////////////////////////////////////////////////////////
//	Project#2:		Type-based Dependency Analysis				   //
//					To create a Type-based dependency analyzer	   //
//																   //
//	## Created by using Prof. Jim Fawcett's 'CodeAnalyzer'     ##  //
//  ## project and augmenting it with 'Type Analysis',         ##  //
//  ## 'Dependency Analysis' and 'Strong Components' features. ##  //
//																   //
//  Test_Executive.h: Header file for Test Executive			   //
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

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <functional>
#include <algorithm>
#include <exception>
#include <iomanip>
#include <chrono>
#include <ctime>

#include "../Parser/Parser.h"
#include "../FileSystem/FileSystem.h"
#include "../FileMgr/FileMgr.h"
#include "../Parser/ActionsAndRules.h"
#include "../Parser/ConfigureParser.h"
#include "../AbstractSyntaxTree/AbstrSynTree.h"
#include "../Logger/Logger.h"
#include "../Utilities/Utilities.h"
#include "../Graph/Graph.h"
#include "../Analyzer/Executive.h"
#include "../Type_Table/Type_Table.h"
#include "../Type_Analysis/Type_Analysis.h"
#include "../Dependency_Analysis/Dep_Anal.h"
#include "../Dependency_Table/Dep_Table.h"
#include "../Graph/XmlReader.h"
#include "../Graph/XmlWriter.h"

#endif