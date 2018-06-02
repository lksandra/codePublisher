#include <unordered_map>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <iostream>
#include <ctime>
#include "../Tokenizer/Tokenizer.h"
#include "../NoSqlDb/NoSqlDb.h"
#include "../TypeTable/TypeTable.h"
#include "../Utilities/Utilities.h"


using Key = std::string;
using Keys = std::vector<std::string>;
using File = std::string;
using Files = std::vector<File>;
using Pattern = std::string;
using Ext = std::string;
using FileMap = std::unordered_map<Pattern, Files>;
using Helper = Utilities::StringHelper;
using databasetable = std::unordered_map<std::string, std::vector<std::unordered_map<std::string, std::string>>>;

namespace CodeAnalysis
{
	//Class created for the purpose of finding dependencies
	class dowork
	{
	public:
		NoSqlDb  doTask(databasetable& db1, NoSqlDb  &db, Files allfiles);

	};

	//member function to find dependencies
	NoSqlDb  dowork::doTask(databasetable& db1, NoSqlDb & db, Files allfiles)
	{
		using databasetable = std::unordered_map<std::string, std::vector<std::unordered_map<std::string, std::string>>>;
		Keys keystype;
		std::unordered_map<Key, Key> temp;
		for (auto kv : db1)
		{
			keystype.push_back(kv.first);
			for (auto x : kv.second)
			{
				for (auto y : x)
				{
					temp[y.first] = y.second;
				}
			}
		}
		Element  elemitem;
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
							std::vector<std::unordered_map<std::string, std::string>> vec = db1[key];
							for (std::unordered_map<std::string, std::string> cv : vec)
							{
								for (auto g : cv)
								{
									if (g.first == "file") {
										elemitem.children.push_back(g.second);
										std::sort(elemitem.children.begin(), elemitem.children.end());
										elemitem.children.erase(std::unique(elemitem.children.begin(), elemitem.children.end()), elemitem.children.end());
										db.save(file, elemitem);
									}
								}
							}
						}
					}
				} while (in.good());
			}
			catch (std::logic_error& ex)
			{
				std::cout << "\n Exception caught in Dependency Analysis";
				std::cout << "\n  " << ex.what();
			}
		}
		return db;
	}
}
