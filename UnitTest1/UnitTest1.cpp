#include "pch.h"
#include <string>
#include <fstream>
#include <iostream>
#include "CppUnitTest.h"
#include "../Test_Intellistart/Test_intellistart.cpp"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

string open_file(string path)
{
	string arr;
	string Text;
	ifstream FileRead(path);
	while (getline(FileRead, Text))
	{
		arr += Text;
	}
	FileRead.close();
	return arr;
}

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			/*
			Name;Month;Total hours
			John Doe; October; 13
			Jane Doe; October; 4
			*/


			Work_with_File work("../UnitTest1/Test_input/Test1/Test.csv", "../UnitTest1/Test_output/Output.csv");
			work.MAIN_LOOP();
			string output_file, file_test;
			output_file = open_file("../UnitTest1/Test_output/Output.csv");
			file_test = open_file("../UnitTest1/Test_input/Test1/Output_file.csv");
			
			Assert::AreEqual(output_file, file_test);
		}
		TEST_METHOD(TestMethod2)
		{
			/*
			Name;Month;Total hours
			John Doe;October;13
			Jane Doe;October;18
			Voloday;October;23
			Test name;September;15
			Jane Doe;September;9
			*/


			Work_with_File work("../UnitTest1/Test_input/Test2/Test.csv", "../UnitTest1/Test_output/Output_test2.csv");
			string output_file, file_test;
			work.MAIN_LOOP();
			output_file = open_file("../UnitTest1/Test_output/Output_test2.csv");
			file_test = open_file("../UnitTest1/Test_input/Test2/Output_file.csv");
			Assert::AreEqual(output_file, file_test);
		}
		TEST_METHOD(TestMethod3)
		{
			/*
			Name;Month;Total hours
			John Doe;October;26
			Jane Doe;October;29
			Voloday;October;23
			Test name;September;30
			Jane Doe;September;9
			Bill;October;23
			Jane Doest;October;7
			Jane Doest;September;9
			*/


			Work_with_File work("../UnitTest1/Test_input/Test3/Test.csv", "../UnitTest1/Test_output/Output_test3.csv");
			string output_file, file_test;
			work.MAIN_LOOP();
			output_file = open_file("../UnitTest1/Test_output/Output_test3.csv");
			file_test = open_file("../UnitTest1/Test_input/Test3/Output_file.csv");
			Assert::AreEqual(output_file, file_test);
		}
	};
}
