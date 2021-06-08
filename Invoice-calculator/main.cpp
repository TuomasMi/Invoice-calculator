#include <iostream>
#include <vector>
#include <algorithm>

int getIndex(std::vector<float> v, float K)
{
    auto it = std::find(v.begin(), v.end(), K);

    // calculating the index
    // of K
    int index = it - v.begin();
    std::cout << index << std::endl;

    return index;
}

int main()
{
    std::vector<float> invoices;
    float input;
    float target;
    std::vector<float> results;

    // Read invoices to vector
    std::cout << "Give invoices, end with f: ";
    while (std::cin >> input) {
        invoices.push_back(input);
    }

    std::cout << "Give target amount: ";
    std::cin >> target;

    int numberOfInvoices = invoices.size();

    for (float invoice : invoices) {
        for (int i = 1 ; i <= numberOfInvoices ; i++) {
            if (invoice + invoices.at(invoice + i) == target) {
                results.push_back(invoice);
                results.push_back(invoices.at(invoice + i));
                break;
            }
        }
    }

    std::vector<int> indexes;
    for (auto result : results) {
        indexes.push_back(getIndex(invoices, result));
    }

    return EXIT_SUCCESS;
}


//

