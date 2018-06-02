#pragma once
#ifndef DEP_ANAL
#define DEP_ANAL

/////////////////////////////////////////////////////////////////////
//	Project#2:		Type-based Dependency Analysis				   //
//					To create a Type-based dependency analyzer	   //
//																   //
//	## Created by using Prof. Jim Fawcett's 'CodeAnalyzer'     ##  //
//  ## project and augmenting it with 'Type Analysis',         ##  //
//  ## 'Dependency Analysis' and 'Strong Components' features. ##  //
//																   //
//  Dep_Anal.h:     Header file for analyzing dependencies between //
//					all the files used in the project.			   //
//					Uses Type Table as the input and generates	   //
//					a dependency table.							   //
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
// Contains Class (DepAnalysis) which performs Dependency Analysis and
// displays the Dependency Table
// It finds dependencies between various files used in a project.
// Uses Type Table which has info on Type, Type Name, Namespace, File.
// Uses 'Tokenizer' to get tokens from every file and compares it
// with every Type Name in the Type Table.
// 
// Public Interface:
// ==================
//		void performAnal(TypeTableMap& db1, DependencyTable  &db, Files allfiles);		// To perform Dependency Analysis
//		void doDepAnal(TypeTableMap& dpt, Files allfiles);								// To perform Dependency Analysis and displays Dependency Table
//		DependencyTable& getDepTable();													// Returns Dependency Table
// 
// Required Files:
// ===============
// Type_Table.h, Type_Table.cpp, Dep_Table.h

#include <unordered_map>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <iostream>
#include <ctime>
#include "../Tokenizer/Tokenizer.h"
#include "../Type_Table/Type_Table.h"
#include"../Type_Analysis/Type_Analysis.h"
#include "../Utilities/Utilities.h"
#include"../Dependency_Table/Dep_Table.h"

using Key = std::string;
using Keys = std::vector<std::string>;
using File = std::string;
using Files = std::set<File>;
using Helper = Utilities::StringHelper;
using TypeTableMap= std::map<std::string, std::vector<CodeAnalysis::TypeInfo>>;

namespace CodeAnalysis
{
	//Class created to find dependencies
	class DepAnalysis
	{
	public:
		void performAnal(TypeTableMap& db1, DependencyTable  &db, Files allfiles);		// To perform Dependency Analysis
		void doDepAnal(TypeTableMap& dpt, Files allfiles);								// To perform Dependency Analysis and displays Dependency Table
		DependencyTable& getDepTable();													// Returns Dependency Table
	private:
		DependencyTable db;

	};

	// Performs Dependency Analysis and displays Dependency Table
	inline void DepAnalysis::doDepAnal(TypeTableMap& dpt, Files allfiles)
	{
		performAnal(dpt,db,allfiles);
		db.display();
	}

	// Returns Dependency Table
	inline DependencyTable& DepAnalysis::getDepTable()
	{
		return db;
	}
	// Performs Dependency Analysis
	inline void DepAnalysis::performAnal(TypeTableMap& db1, DependencyTable & db, Files allfiles)
	{
		using TypeTableMap = std::map<std::string, std::vector<CodeAnalysis::TypeInfo>>;
		Keys keystype;
		std::map<Key, Key> temp;
		for (auto kv : db1)
		{
			keystype.push_back(kv.first);

		}
		File forComp;
		DepInfo elemitem;
		for (File f : allfiles)
		{
			try {
				std::string file = FileSystem::Path::getName(f);
				std::ifstream in(f);
				if (!in.good())
				{
					std::cout << "\n  can't open " << file << "\n\n";
				}
				Scanner::Toker toker;
				toker.returnComments(false);
				toker.attach(&in);
				do {
					std::string tok = toker.getTok();
					for (std::string key : keystype)
					{
						if (key == tok)
						{
							std::vector<CodeAnalysis::TypeInfo> vec = db1[key];
							for (CodeAnalysis::TypeInfo cv : vec)
							{
								forComp = FileSystem::Path::getName(cv.getFilename());
								if (file.compare(forComp) != 0)
								{

									elemitem.DepItem.push_back(forComp);

								}
							}
						}
					}
				} while (in.good());
				std::sort(elemitem.DepItem.begin(), elemitem.DepItem.end());
				elemitem.DepItem.erase(std::unique(elemitem.DepItem.begin(), elemitem.DepItem.end()), elemitem.DepItem.end());
				db.save(f, elemitem);
				elemitem.DepItem.clear();
			}
			catch (std::logic_error& ex)
			{
				std::cout << "\n Exception caught in Dependency Analysis";
				std::cout << "\n  " << ex.what();
			}
		}
	}
}
#endif