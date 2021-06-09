#include <iostream>
#include <vector>
#include <algorithm>

int getIndex(std::vector<float> v, float K)
{
    auto it = std::find(v.begin(), v.end(), K);

    // calculating the index
    // of K
    int index = it - v.begin();

    return index;
}

void subsetsUtil(std::vector<float>& A, std::vector<std::vector<std::pair<float, int>> >& res,
                 std::vector<std::pair<float,int>>& subset, int index)
{
    res.push_back(subset);
    for (int i = index; i < A.size(); i++) {

        // include the A[i] in subset.
        subset.push_back({A[i], index});

        // move onto the next element.
        subsetsUtil(A, res, subset, i + 1);

        // exclude the A[i] from subset and triggers
        // backtracking.
        subset.pop_back();
    }

    return;
}

// below function returns the subsets of vector A.
std::vector<std::vector<std::pair<float, int>> > subsets(std::vector<float>& A)
{
    std::vector<std::pair<float, int>> subset;
    std::vector<std::vector<std::pair<float, int>> > res;

    // keeps track of current element in vector A;
    int index = 0;
    subsetsUtil(A, res, subset, index);

    return res;
}

bool checkSum(std::vector<std::pair<float, int>>& inputs, float& target)
{
    float sum = 0;
    for (auto input : inputs) {
        sum += input.first;
    }
    return sum == target;
}

void run()
{
    std::vector<float> invoices;
    float input;
    float target;


    // Read invoices to vector
    std::cout << "Give invoices, end with f: ";
    while (std::cin >> input) {
        invoices.push_back(input);
    }

    std::cin.clear();
    std::cin.ignore(1000,'\n');
    std::cout << "Give target amount: ";
    std::cin >> target;

    std::vector<std::vector<std::pair<float, int>>> res = subsets(invoices);

    bool numbersFound = false;

    for (auto subset : res) {
        if (checkSum(subset, target)) {
            std::cout << "\n";
            for (auto result : subset) {
                std::cout << result.second + 1 << " " << result.first <<"\n";
            }
            numbersFound = true;
        }

    }

    if (not numbersFound) {
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

