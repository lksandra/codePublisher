#pragma once
#ifndef TYPETABLE_H
#define TYPETABLE_H

/////////////////////////////////////////////////////////////////////
//	Project#2:		Type-based Dependency Analysis				   //
//					To create a Type-based dependency analyzer	   //
//																   //
//	## Created by using Prof. Jim Fawcett's 'CodeAnalyzer'     ##  //
//  ## project and augmenting it with 'Type Analysis',         ##  //
//  ## 'Dependency Analysis' and 'Strong Components' features. ##  //
//																   //
//  Type_Table.h:   Header file to save and display Type Table     //
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

// Module Operations:
// ==================
// Contains a class (TypeInfo) that stores type information (Type, Type name, Namespace,
// and path) necessary for dependency analysis.
// Contains a class (TypeTable) that saves and displays Type Table.
// 
// Public Interface:
// ==================
// 		bool save(std::string typeName, TypeInfo val);		// To Save into TypeTable
// 		void display();										// To Display TypeTable
// 		void displayHeader();								// To display TypeTable header
// 		map<std::string, vector<TypeInfo>>& returnTT();		// To return TypeTable
// 
// Required Files:
// ===============
// Type_Table.h, Type_Table.cpp

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iomanip> 
#include <sstream>
#include <unordered_map>
#include <functional>
#include <algorithm>
#include <exception>
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
#include "../Analyzer/Executive.h"

namespace CodeAnalysis
{
	// Class to store Type Information
	class TypeInfo                     
	{
	private:
		std::string typeName;							// Name of the Type		
		std::string typeValue;							// Type of the name
		std::string typeNamespace;						// Namespace where Type is defined
		std::string typeFileName;						// Filepath where Type if defined

	public:
		void setTypeName(std::string typeNam)			// Sets Typename
		{
			typeName = typeNam;
		}
		std::string getTypeName()						// Gets Typename
		{
			return typeName;
		}
		void setType(std::string typeVal)				// Sets Type 
		{
			typeValue = typeVal;
		}
		std::string getType()							// Gets Type 
		{
			return typeValue;
		}
		void setNamespace(std::string typeNamesp)		// Sets Namespace 
		{
			typeNamespace = typeNamesp;
		}
		std::string getNamespace()						// Gets Namespace 
		{
			return typeNamespace;
		}
		void setFilename(std::string typeFilenam)		// Sets Filename
		{
			typeFileName = typeFilenam;
		}
		std::string getFilename()						// Gets Filename 
		{
			return typeFileName;
		}
	};

	// Class to save and display Type Table
	class TypeTable
	{
	private:
		std::map<std::string, std::vector<TypeInfo>> TTmap;			// TypeTable map
	public:
		bool save(std::string typeName, TypeInfo val);				// Save into TypeTable
		void display();												// Display TypeTable
		void displayHeader();										// Display TypeTable Header
		std::map<std::string, std::vector<TypeInfo>>& returnTT();	// returns TypeTable
	};

	// Returns TypeTable
	inline std::map<std::string, std::vector<TypeInfo>>& TypeTable::returnTT()
	{
		return TTmap;
	}

	// Saves into TypeTable
	inline bool TypeTable::save(std::string typeName, TypeInfo val)
	{
		TTmap[typeName].push_back(val);

		return true;
	}

	// Displays TypeTable Header
	inline void TypeTable::displayHeader()
	{
		std::cout << "\n";
		std::cout << std::right;
		std::cout << "\n" << "##########################################################################################";
		std::cout << "\n" << "                                 --TYPE TABLE--									   ";
		std::cout << "\n" << "##########################################################################################";
		std::cout << "\n ";
		std::cout << std::setw(25) << "Type name";
		std::cout << std::setw(25) << "Type";
		std::cout << std::setw(25) << "Namespace";
		std::cout << std::setw(25) << "Filename";
		std::cout << std::right;
		std::cout << "\n  ";
		std::cout << std::setw(25) << "-------------------";
		std::cout << std::setw(25) << "-------------------";
		std::cout << std::setw(25) << "-------------------";
		std::cout << std::setw(25) << "-------------------";
	}
	// Displays TypeTable
	inline void TypeTable::display()
	{
		TypeTable::displayHeader();
		std::cout << "\n ";
		std::map<std::string, std::vector<TypeInfo>>::iterator it = TTmap.begin();
		for (it; it != TTmap.end(); ++it)
		{
			std::cout << std::right;
			for (TypeInfo val : it->second)
			{
				std::cout << std::setw(25) << it->first;
				std::cout << std::setw(25) << val.getType();
				std::cout << std::setw(25) << val.getNamespace();
				std::cout << "\t\t" << std::setw(50) << val.getFilename();
				std::cout << "\n ";
			}
		}
	}
}
#endif