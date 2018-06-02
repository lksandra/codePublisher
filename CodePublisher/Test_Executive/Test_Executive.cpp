/////////////////////////////////////////////////////////////////////
//	Project#2:		Type-based Dependency Analysis				   //
//					To create a Type-based dependency analyzer	   //
//																   //
//	## Created by using Prof. Jim Fawcett's 'CodeAnalyzer'     ##  //
//  ## project and augmenting it with 'Type Analysis',         ##  //
//  ## 'Dependency Analysis' and 'Strong Components' features. ##  //
//																   //
//  Test_Executive.cpp: Test-stub for Test Executive			   //
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

#include "Test_Executive.h"

using namespace CodeAnalysis;
using namespace GraphLib;

using Rslt = Logging::StaticLogger<0>;
using Demo = Logging::StaticLogger<1>;
using Dbug = Logging::StaticLogger<2>;
using TypeTableMap = std::map<std::string, std::vector<CodeAnalysis::TypeInfo>>;
using DepTableMap = std::map<std::string, DepInfo>;

typedef Graph<std::string, std::string> graph;
typedef Vertex<std::string, std::string> vertex;
typedef Display<std::string, std::string> display;

//#ifdef TEST_EXE

// Test stub to demonstrate requirements
int main(int argc, char* argv[])
{
	using namespace CodeAnalysis;

	CodeAnalysisExecutive exec;
	map<std::string, vertex> vrMap;
	graph g;

	try {
		bool succeeded = exec.ProcessCommandLine(argc, argv);
		if (!succeeded)
		{
			return 1;
		}
		exec.setDisplayModes();
		exec.startLogger(std::cout);

		std::ostringstream tOut("Dependency Analysis");
		Utils::sTitle(tOut.str(), 3, 92, tOut, '=');
		Rslt::write(tOut.str());

		//Rslt::write("\n     " + exec.getAnalysisPath());
		Rslt::write("\n     " + exec.systemTime());
		Rslt::flush();
		exec.showCommandLineArguments(argc, argv);
		Rslt::write("\n");

		exec.getSourceFiles();
		exec.processSourceCode(true);
		//exec.complexityAnalysis();
		exec.dispatchOptionalDisplays();
		exec.flushLogger();
		//exec.displayMetricSummary(50, 10);
		
		// Requirement 1
		std::cout << "\n" << "***********************************************";
		std::cout << "\n" << "Demonstrating Requirement #1: Using VS 2015 C++";
		std::cout << "\n" << "***********************************************";
		std::cout << "\n" << "Please examine code in VS to verify" << "\n\n\n";

		// Requirement 2
		std::cout << "\n" << "****************************************************************";
		std::cout << "\n" << "Demonstrating Requirement #2: To only use C++ standard libraries";
		std::cout << "\n" << "****************************************************************";
		std::cout << "\n" << "Please examine code in VS to verify" << "\n\n\n";

		// Requirement 3
		std::cout << "\n" << "*****************************************************************";
		std::cout << "\n" << "Demonstrating Requirement #3: To provide C++ package as described";
		std::cout << "\n" << "*****************************************************************";
		std::cout << "\n" << "Please examine code in VS to verify";
		std::cout << "\n" << "Created packages 'Type_Table', 'Type_Analysis' for Type Analysis";
		std::cout << "\n" << "Created packages 'Dependency_Table', 'Dependency_Analysis' for Dependency Analysis";
		std::cout << "\n" << "Imported package 'Graph' to find Strongly Connected Components";
		std::cout << "\n" << "Created package 'Test_Executive' for Requirements Demonstration" << "\n\n\n";
		
		// Requirement 4
		std::cout << "\n" << "*******************************************************************************************";
		std::cout << "\n" << "Demonstrating Requirement #4: To identify all the types defined in a file used in a project";
		std::cout << "\n" << "*******************************************************************************************";
		std::cout << "\n" << "--Displaying Type Table--";
		// Code related to Type Table 
		TypeAnalysis ta;
		ta.doTypeAnal();
		TypeTable tt = ta.getTypeTable();
		TypeTableMap dpt = tt.returnTT();
		std::cout << "\n\n\n";
		// Requirement 5
		std::cout << "\n" << "**********************************************************************************************";
		std::cout << "\n" << "Demonstrating Requirement #5: To identify all the dependencies between files used in a project";
		std::cout << "\n" << "**********************************************************************************************";
		std::cout << "\n" << "--Displaying Dependency Table--";
		// Code related to Dependency Table 
		set<std::string> f1 = ta.getAllFilenames();
		DepAnalysis dt;
		dt.doDepAnal(dpt, f1);
		DependencyTable dtObj = dt.getDepTable(); //st.returnDepTable();
		DepTableMap dtMap = dtObj.returnDepTable();

		exec.flushLogger();
		Rslt::write("\n");
		std::ostringstream out;
		//out << "\n  " << std::setw(10) << "searched" << std::setw(6) << exec.numDirs() << " dirs";
		//out << "\n  " << std::setw(10) << "processed" << std::setw(6) << exec.numFiles() << " files";
		//Rslt::write(out.str());
		Rslt::write("\n");
		exec.stopLogger();

		// Code related to Strongly Connected Components
		File forComp;
		for (std::string s : f1)
		{
			forComp = FileSystem::Path::getName(s);
			vertex v(forComp);
			g.addVertex(v);
			vrMap.insert_or_assign(forComp, v);

		}

		//DepTableMap::iterator it = dtMap.begin();
		//for (it; it != dtMap.end(); ++it)
		//{

		//	DepInfo val = it->second;
		//	for (std::string str : val.DepItem)
		//	{
		//		g.addEdge(str, vrMap.find(it->first)->second, vrMap.find(str)->second);
		//	}
		//}
		//std::cout << "\n\n";
		//// To display Dependency Analysis results using ouput machinery provided in 'Graph' package
		////display::show(g);

		//// Requirement 7 (Part 1)
		//std::cout << "\n" << "************************************************************************************";
		//std::cout << "\n" << "Demonstrating Requirement #7 (Part 1): To display Dependency Analysis results in XML";
		//std::cout << "\n" << "************************************************************************************";

		//// Displaying Dependency Analysis results into XML
		//std::cout << "\n" << "Displaying and storing Dependency Analysis results in XML";
		//std::string str = GraphToXmlString(g);
		//std::cout << str << "\n\n\n";

		// Commented Project2 code on 03/28/2017///////////////////////////////////////////////////////////////////////////////
		/*
		// Requirement 6
		std::cout << "\n" << "************************************************************************************************";
		std::cout << "\n" << "Demonstrating Requirement #6: To find Strongly Connected Components from the Dependency Analysis";
		std::cout << "\n" << "************************************************************************************************";
		std::cout << "\n" << "--Displaying Strongly Connected Components--" << "\n\n";
		// Code to display Strongly Connected Components results in XML
		g.SCC(g);
		std::vector<std::vector<std::string>> rs = g.getSCC();
		std::cout << "\n\n";

		// Requirement 7 (Part 2)
		std::cout << "\n" << "**************************************************************************************";
		std::cout << "\n" << "Demonstrating Requirement #7 (Part 2): To display Strongly Connected Components in XML";
		std::cout << "\n" << "**************************************************************************************";
		std::string sccStr = SCCToXmlString(rs);
		std::cout << sccStr << "\n";

		std::ofstream outToFile(exec.getXmlFilePath());
		outToFile << "<results>\n";
		outToFile << "<!-- Dependency Analysis Result -->\n";
		outToFile << str << "\n";
		outToFile << "<!-- Strongly Connected Components -->\n";
		outToFile << sccStr << "\n</results>\n";
		std::cout << "\n\n";
		*/
	}
	catch (std::exception& except)
	{
		exec.flushLogger();
		std::cout << "\n\n  caught exception in Executive::main: " + std::string(except.what()) + "\n\n";
		exec.stopLogger();
		return 1;
	}

	system("pause");
	return 0;
}
//#endif