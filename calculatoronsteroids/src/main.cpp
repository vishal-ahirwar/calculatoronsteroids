#include <barkeep/barkeep.h>
#include <calculatoronsteroidsconfig.h>

#include <boost/multiprecision/cpp_int.hpp>
#include <chrono>
#include <fstream>
#include <future>
#include <iostream>
#include <thread>
#include <vector>

using boost::multiprecision::cpp_int;

cpp_int factorialRange(int start, int end)
{
    cpp_int result = 1;
    for (int i = start; i <= end; ++i) result *= i;
    return result;
}

cpp_int parallelFactorial(int n, int numThreads = std::thread::hardware_concurrency())
{
    if (n < 2)
        return 1;

    std::vector<std::future<cpp_int>> futures;
    int                               chunkSize = n / numThreads;
    int                               start     = 1;

    for (int t = 0; t < numThreads; ++t)
    {
        int end = (t == numThreads - 1) ? n : (start + chunkSize - 1);
        futures.emplace_back(std::async(std::launch::async, factorialRange, start, end));
        start = end + 1;
    }
    cpp_int result = 1;
    for (auto& f : futures) result *= f.get();

    return result;
}

int main()
{
    using namespace std::chrono_literals;
    namespace bk = barkeep;

    std::cout << Project::PROJECT_NAME << " v" << Project::VERSION_STRING << " by "
              << Project::COMPANY_NAME << std::endl;
    int n;
    std::cout << "Enter value you want to find factorial of? ";
    std::cin >> n;
    
    auto anim = bk::Animation({.message = "Calculating just wait and watch ;)"});
    auto    start  = std::chrono::high_resolution_clock::now();
    cpp_int result = parallelFactorial(n);
    auto    end    = std::chrono::high_resolution_clock::now();
    anim->done();
    std::cout << "Factorial computed!\n";
    anim=bk::Animation({.message = "Counting Total Digits in resultent factorial"});
    auto digits= result.str().size();
    anim->done();
    std::cout << "Digits: " <<digits << "\n";
    
    std::ofstream out("result.txt");
    out << result.str();
    out.close();
    std::cout << "Result has been saved to file\n";
    std::cout << "Time taken: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms\n";
    return 0;
}
