#include <gtest/gtest.h>

#include <array>
#include <filesystem>
#include <fstream>
#include <memory>

#include <parent.hpp>

namespace fs = std::filesystem;

void RunTest(const std::vector<std::string>& input, const std::vector<std::string>& expectedOutput) {
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

    ParentProcess(inFile.get(), "/home/microhacker/Desktop/LabOS/build/lab2/child.out");


    auto outFile = std::ifstream(fileWithOutput);

    ASSERT_TRUE(outFile.good());
    
    std::string result;

    for(auto el: expectedOutput) {
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

TEST(SecondLabTests, NegativeSum) {

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

TEST(SecondLabTests, BigSum) {

    std::vector<std::string> input = {
            "1122.421 2.2 3123412.421",
            "1234124.412 12341.412",
            "11234.412 12341234.213"
    };

    std::vector<std::string> expectedOutput = {
            "16723472.000"
    };

    RunTest(input, expectedOutput);
    
}