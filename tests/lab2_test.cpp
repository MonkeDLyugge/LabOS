#include <gtest/gtest.h>

#include <array>
#include <filesystem>
#include <fstream>
#include <memory>
#include "../lab2/include/parent.hpp"

namespace fs = std::filesystem;

void RunTest(const std::vector<const char*>& input, const std::vector<const char*>& expectedOutput) {
    const char* fileWithInput = "input.txt";
    const char* fileWithOutput = "out.txt";
    {
        auto inFile = std::ofstream(fileWithInput);

        inFile << fileWithOutput << '\n';

        for(const auto& line : input) {
            inFile << line << '\n';
        }
    }

    auto deleter = [](FILE* file) {
        fclose(file);
    };

    std::unique_ptr<FILE, decltype(deleter)> inFile(fopen(fileWithInput, "r"), deleter);

    parentProcess(inFile.get());


    auto outFile = std::ifstream(fileWithOutput);

    ASSERT_TRUE(outFile.good());
    
    char* result;

    for(auto el : expectedOutput) {
        outFile >> result;
        EXPECT_EQ(result, el);
    }

     auto removeIfExists = [](const char* path) {
         if(fs::exists(path)) {
             fs::remove(path);
        }
    };
     
    removeIfExists(fileWithInput);
        removeIfExists(fileWithOutput);
    return;
}

TEST(SecondLabTests, PositiveSum) {

    std::vector<const char*> input = {
            "1 2 3",
            "0.5 0.7",
            "0.2"
    };

    std::vector<const char*> expectedOutput = {
            "7.400"
    };

    RunTest(input, expectedOutput);
    
}

TEST(SecondLabTests, NegativeSum) {

    std::vector<const char*> input = {
            "-1 -2 -3",
            "-0.5 -0.7",
            "-0.2"
    };

    std::vector<const char*> expectedOutput = {
            "-7.400"
    };

    RunTest(input, expectedOutput);
    
}

TEST(SecondLabTests, BigSum) {

    std::vector<const char*> input = {
            "1122.421 2.2 3123412.421",
            "1234124.412 12341.412",
            "11234.412 12341234.213"
    };

    std::vector<const char*> expectedOutput = {
            "16723471.491"
    };

    RunTest(input, expectedOutput);
    
}