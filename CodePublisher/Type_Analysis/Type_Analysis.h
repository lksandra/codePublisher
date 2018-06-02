#pragma once
#ifndef TYPEANAL_H
#define TYPEANAL_H

/////////////////////////////////////////////////////////////////////
//	Project#2:			Type-based Dependency Analysis			   //
//					    To create a Type-based dependency analyzer //
//																   //
//	## Created by using Prof. Jim Fawcett's 'CodeAnalyzer'     ##  //
//  ## project and augmenting it with 'Type Analysis',         ##  //
//  ## 'Dependency Analysis' and 'Strong Components' features. ##  //
//																   //
//  Type_Analysis.h:   Header file to create Type Table			   //
//  *************************************************************  //
//	Version:		   1.0										   //
//  Date:			   03/14/2017								   //
//  Language:          Visual C++, Version 11.					   //
//  Platform:          Visual Studio Community Edition			   //
//					   HP ENVY, Windows 10				           //
//  Application:       CSE687 - Object Oriented Design             //
//  Author:            Sachin Basavani Shivashankara			   //
//	SUID:			   267871645								   //
//  Ph:, email:        (315)751-5895, sbasavan@syr.edu			   //
/////////////////////////////////////////////////////////////////////

// Module Operations:
// ==================
// Contains Class (TypeAnalysis) to find all the types and global functions defined
// in a project.
// 
// Public Interface:
// ==================
//		void doTypeAnal();						// Performs Type Analysis
//		void storeToTypeTable(ASTNode* pNode);	// Stores information into TypeTable
//		TypeTable& getTypeTable();				// Provides acces to TypeTable
//		Scanner::Toker& getToker();				// Provides access to Toker
//		void storeAllFilenames(ASTNode* pNode);	// Stores all filenames in the project
//		std::set<std::string> getAllFilenames();			// Retrieves set of filenames in the project
// 
// Required Files:
// ===============
// Type_Analysis.h, Type_Analysis.cpp

#include "../Parser/ActionsAndRules.h"
#include "../Type_Table/Type_Table.h"

#include <iostream>
#include <string>
#include <set>

namespace CodeAnalysis
{
	// Class TypeAnalysis to create Type Table
	class TypeAnalysis
	{
	public:
		using SPtr = std::shared_ptr<ASTNode*>;

		TypeAnalysis();
		void doTypeAnal();									// To perform Type Analysis
		void storeToTypeTable(ASTNode* pNode);				// To store information into TypeTable
		TypeTable& getTypeTable();							// To return TypeTable
		Scanner::Toker& getToker();							// To provide access to Toker
		void storeAllFilenames(ASTNode* pNode);				// To store all filenames in the project
		std::set<std::string> getAllFilenames();			// To retrieve the set of filenames in the project

	private:
		void DFS(ASTNode* pNode);							// To perform Depth First Search over the AST
		AbstrSynTree& ASTref_;								// AST's instance
		ScopeStack<ASTNode*> scopeStack_;					// ScopeStacks's instance
		Scanner::Toker& toker_;								// Toker's instance
		TypeTable tt;										// TypeTable's instance
		std::set<std::string> allFilenames;					// Set of all filenames in the project
	};

	// Retrieves set of filenames in the project
	inline std::set<std::string> TypeAnalysis::getAllFilenames()
	{
		return allFilenames;
	}

	// Returns Type Table
	inline TypeTable& TypeAnalysis::getTypeTable()
	{
		return tt;
	}

	// Provides access to Toker
	inline Scanner::Toker& TypeAnalysis::getToker()
	{
		return toker_;
	}

	// Retrieves set of filenames in the project
	inline TypeAnalysis::TypeAnalysis() :
		ASTref_(Repository::getInstance()->AST()),
		scopeStack_(Repository::getInstance()->scopeStack()),
		toker_(*(Repository::getInstance()->Toker()))
	{
	}

	// Performs Type Analysis
	inline void TypeAnalysis::doTypeAnal()
	{
		ASTNode* pRoot = ASTref_.root();
		storeToTypeTable(pRoot);
		storeAllFilenames(pRoot);
		tt.display();
	}

	// Performs Depth First Search over the AST
	inline void TypeAnalysis::DFS(ASTNode* pNode)
	{
		static std::string path = "";
		if (pNode->path_ != path)
		{
			std::cout << "\n    -- " << pNode->path_;

			std::cout << "\n    -- " << pNode->package_;
			path = pNode->path_;
		}
		std::cout << "\n      " << pNode->name_;
		std::cout << ", " << pNode->type_;
		for (auto pChild : pNode->children_)
			DFS(pChild);
	}

	// Stores all filenames in the project
	inline void TypeAnalysis::storeAllFilenames(ASTNode* pNode)
	{
		static std::string path = "";

		if (pNode->path_ != path)
		{
			allFilenames.insert(pNode->path_);
		}
		for (auto pChild : pNode->children_)
			storeAllFilenames(pChild);
	}

	// Stores information into TypeTable
	inline void TypeAnalysis::storeToTypeTable(ASTNode* pNode)
	{
		static std::string path = "";

		std::string which_type = pNode->type_;

		if (which_type == "namespace")
			scopeStack_.push(pNode);

		if (pNode->path_ != path)
		{
			TypeInfo val;

			if (which_type == "class" || which_type == "struct" || which_type == "namespace" || which_type == "function")
			{
				val.setTypeName(pNode->name_);

				val.setType(pNode->type_);

				val.setNamespace(scopeStack_.top()->name_);

				val.setFilename(pNode->path_);

				if (which_type == "function" && val.getNamespace() != "Global Namespace")
				{   
					// Dont add member functions and main functions to TypeTable 		
				}
				else if (which_type == "function" && val.getNamespace() == "Global Namespace" && val.getTypeName() == "main")
				{
					// Dont add main functions to TypeTable 
				}
				else
				{
					tt.save(val.getTypeName(), val);
				}
			}
		}
		for (auto pChild : pNode->children_)
			storeToTypeTable(pChild);
		if (pNode->type_ == "namespace")
			scopeStack_.pop();
	}
}

#endif