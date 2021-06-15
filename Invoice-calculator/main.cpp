#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <locale>
#include <math.h>



void subsetsUtil(std::vector<int>& A, std::vector<std::vector<std::pair<int, int>> >& res,
                 std::vector<std::pair<int,int>>& subset, int index)
{
    res.push_back(subset);
    for (int i = index; i < A.size(); i++) {

        // include the A[i] in subset.
        subset.push_back({A[i], i});

        // move onto the next element.
        subsetsUtil(A, res, subset, i + 1);

        // exclude the A[i] from subset and triggers
        // backtracking.
        subset.pop_back();
    }

    return;
}

// below function returns the subsets of vector A.
std::vector<std::vector<std::pair<int, int>> > subsets(std::vector<int>& A)
{
    std::vector<std::pair<int, int>> subset;
    std::vector<std::vector<std::pair<int, int>> > res;

    // keeps track of current element in vector A;
    int index = 0;
    subsetsUtil(A, res, subset, index);

    return res;
}

bool checkSum(std::vector<std::pair<int, int>>& inputs, int& target)
{
    int sum = 0;
    for (auto input : inputs) {
        sum += input.first;
    }
    return sum == target;
}

int closeEnough(std::vector<std::pair<int, int>>& inputs, int& target)
{
    int sum = 0;
    for (auto input : inputs) {
        sum += input.first;
    }

    if (sum <= target + 100 and sum > target) {
        return sum - target;
    }

    else if (sum >= target - 100 and sum < target) {
        return sum - target;
    }

    else {
        return 0;
    }

}

void run()
{
    std::vector<int> invoices;
    float target;

    std::ifstream inputFile;
    inputFile.open("input.csv");


    // Read invoices manually to vector
    /*float input;
     std::cout << "Give invoices, end with f: ";
    while (std::cin >> input) {
        invoices.push_back(input);
    }*/

    // read .csv file to vector
    while (inputFile.good()) {
        std::string line;
        std::getline(inputFile, line);
        if (line != "") {
            for (char& c : line) {
                if (c == ',') {
                    c = '.';
                }
            }
            float value = std::stof(line);
            value = ceil(value * 100);
            int ivalue = static_cast<int>(value);
            invoices.push_back(ivalue);
        }

    }

    inputFile.close();

    //std::cin.clear();
    //std::cin.ignore(1000,'\n');
    std::cout << "Give target amount: ";
    std::cin >> target;
    target = ceil(target * 100);
    int itarget = static_cast<int>(target);

    std::vector<std::vector<std::pair<int, int>>> res = subsets(invoices);

    bool numbersFound = false;

    for (auto subset : res) {
        if (checkSum(subset, itarget)) {
            std::cout << "\n";
            for (auto result : subset) {
                std::cout << result.second + 1 << " " << static_cast<float>(result.first) / 100 <<"\n";
            }
            numbersFound = true;
        }

    }

    bool closeFound = false;

    if (!numbersFound) {

        for (auto subset : res) {
            int result = closeEnough(subset, itarget);
            if (result != 0) {
                std::cout << "\nNot exact, but almost: \n";
                for (auto r : subset) {
                    std::cout << r.second + 1 << " " << static_cast<float>(r.first) / 100 << "\n";
                }
                std::cout << "Separated by: " << static_cast<float>(result) / 100 << "\n";
                closeFound = true;
            }
        }

    }

    if (!numbersFound && !closeFound){
        std::cout << "No possible solutions \n";
    }

}

int main()
{

    while (true) {
        run();
        std::cout << "\n";
    }

    return EXIT_SUCCESS;
}




//

