#include <gtest/gtest.h>
#include <chrono>

#include <t_handler.hpp>

TEST(ThirdLabTest, PerfomanceTest) { // проверка среднего времени работы одного и нескольких потоков
    auto getAvgTime = [](int threadCount) {
        NewDeck();

        constexpr int runsCount = 10;

        double avg = 0;

        for(int i = 0; i < runsCount; ++i) {
            srand(time(nullptr));
            auto begin = std::chrono::high_resolution_clock::now();
            ThreadExperiment(2, threadCount);
            auto end = std::chrono::high_resolution_clock::now();
            avg += std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
        }

        return avg / runsCount;
    };

    auto singleThread = getAvgTime(1);
    auto tenThread = getAvgTime(10);
    auto hundredThread = getAvgTime(100);

    std::cout << "Avg time for 1 thread: " << singleThread << '\n';
    std::cout << "Avg time for 10 threads: " << tenThread << '\n';
    std::cout << "Avg time for 100 threads: " << hundredThread << '\n';

    EXPECT_GE(tenThread, singleThread);
    EXPECT_GE(hundredThread, tenThread);
}
