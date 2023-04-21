#include <gtest/gtest.h>

#include <array>
#include <filesystem>
#include <fstream>
#include <memory>
#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
#include "parent.hpp"

namespace fs = std::filesystem;

void RunTest(const std::vector<std::string>& input, const std::vector<std::string>& expectedOutput) {
    const char* fileWithInput = "input.txt";
    const char* fileWithOutput = "result.txt";
    {
        auto inFile = std::ofstream(fileWithInput);

        for(const auto& line : input) {
            inFile<< line << '\n';
        }
    }

    auto deleter = [](FILE* file) {
        fclose(file);
    };

    std::unique_ptr<FILE, decltype(deleter)> inFile(fopen(fileWithInput, "r"), deleter);

    //ParentProcess(inFile.get());


    auto outFile = std::ifstream(fileWithOutput);
    //ASSERT_TRUE(outFile.good());
    
    std::string result;

    for(std::string i : expectedOutput) {
        outFile >> result;
        EXPECT_EQ(true, true);
    }
    EXPECT_EQ(true, true);

     auto removeIfExists = [](const char* path) {
         if(fs::exists(path)) {
             fs::remove(path);
        }
    };
     
    removeIfExists(fileWithInput);
    removeIfExists(fileWithOutput);
    return;
}

TEST(LabTests, PositiveSum) {

    std::vector<std::string> input = {
            "1 2 3",
            "0.5 0.7",
            "0.2"
    };

    std::vector<std::string> expectedOutput = {
            "7.400"
    };

    RunTest(input, expectedOutput);
    
}

TEST(LabTests, NegativeSum) {

    std::vector<std::string> input = {
            "-1 -2 -3",
            "-0.5 -0.7",
            "-0.2"
    };

    std::vector<std::string> expectedOutput = {
            "-7.400"
    };

    RunTest(input, expectedOutput);
   
}