#include "pch.h"
#include "CppUnitTest.h"
#include <vector>
#include <fstream>
#include <sstream>
#include "../PDS_LAB_7/PDS_LAB_7.cpp" 

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    TEST_CLASS(UnitTest1)
    {
    public:

        TEST_METHOD(TestReadGraph)
        {
            const std::string testFilename = "test_graph.txt";

            
            {
                std::ofstream file(testFilename);
                file << "0 1 0\n";
                file << "1 0 1\n";
                file << "0 1 0\n";
                file.close();
            }

            
            std::vector<std::vector<int>> expectedGraph = {
                {0, 1, 0},
                {1, 0, 1},
                {0, 1, 0}
            };

            
            auto graph = readGraph(testFilename);

           
            Assert::AreEqual(expectedGraph.size(), graph.size());
            for (size_t i = 0; i < expectedGraph.size(); ++i) {
                Assert::AreEqual(expectedGraph[i].size(), graph[i].size());
                for (size_t j = 0; j < expectedGraph[i].size(); ++j) {
                    Assert::AreEqual(expectedGraph[i][j], graph[i][j]);
                }
            }
        }

        TEST_METHOD(TestCalculateDegrees)
        {
            
            std::vector<std::vector<int>> graph = {
                {0, 1, 0},
                {1, 0, 1},
                {0, 1, 0}
            };

            std::stringstream buffer;
            std::streambuf* prevcoutbuf = std::cout.rdbuf(buffer.rdbuf());

            calculateDegrees(graph);

            std::cout.rdbuf(prevcoutbuf); 

            std::string output = buffer.str();
            std::string expectedOutput =
                "Степені вершин графу (виходу/заходу):\n"
                "Вершина 1: Вихідний степінь = 1, Вхідний степінь = 1\n"
                "Вершина 2: Вихідний степінь = 2, Вхідний степінь = 2\n"
                "Вершина 3: Вихідний степінь = 1, Вхідний степінь = 1\n"
                "Граф не є однорідним.\n";

            Assert::AreEqual(expectedOutput, output);
        }

        TEST_METHOD(TestFindPendantAndIsolatedVertices)
        {
            
            std::vector<std::vector<int>> graph = {
                {0, 1, 0},
                {1, 0, 1},
                {0, 1, 0}
            };

            std::stringstream buffer;
            std::streambuf* prevcoutbuf = std::cout.rdbuf(buffer.rdbuf());

            findPendantAndIsolatedVertices(graph);

            std::cout.rdbuf(prevcoutbuf); 

            std::string output = buffer.str();
            std::string expectedOutput =
                "Висячі вершини: 1 3 \n"
                "Ізольовані вершини: Немає\n";

            Assert::AreEqual(expectedOutput, output);
        }
    };
}
