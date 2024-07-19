#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <chrono>
#include <random>
#include <algorithm>
#include <thread>

using namespace std;

bool antradalis = true, pivotswitch = false;

int partition(std::vector<int>& array, int low, int high) {
    int mid = low + (high - low) / 2;
    int pivot;
    if (!pivotswitch) {
        pivot = array[mid];
     }
        if ((array[low] <= array[mid] && array[mid] <= array[high]) || (array[high] <= array[mid] && array[mid] <= array[low]))
        {
            pivot = array[mid];
        }
        else if ((array[mid] <= array[low] && array[low] <= array[high]) || (array[high] <= array[low]) && (array[low] <= array[mid]))
        {
            swap(array[low], array[mid]);
                pivot = array[mid];
        }
        else {
            swap(array[high], array[mid]);
                pivot = array[mid];
        }

        int i = low - 1;
        int j = high + 1;
        while (true) {
            do {
                i++;
            } while (array[i] < pivot);

            do {
                j--;
            } while (array[j] > pivot);

            if (i >= j) {
                return j;
            }

            std::swap(array[i], array[j]);
        }
}

void quickSort(std::vector<int>& data, int low, int high) {
    while (low < high) {
        int pivotIndex = partition(data, low, high);
        if ((pivotIndex - low) <= (high - pivotIndex)) {
            quickSort(data, low, pivotIndex);
            low = pivotIndex + 1;
        }
        else {
            quickSort(data, pivotIndex + 1, high);
            high = pivotIndex;
        }
    }
}

int main() {
    const int dataSize = 5062500;
    int averageQuicksortMedian = 0;
    int averageQuicksortMiddle = 0;
    int LastIndex = dataSize - 1;
    int RandomIndex = rand() % LastIndex;
    unsigned int seed = chrono::steady_clock::now().time_since_epoch().count();
    std::default_random_engine randomNumberGenerator(seed);
    std::uniform_int_distribution<int> distribution(1, 9999999);
    for (int i = 0; i < 3; ++i) {
        vector<int> temp;
        for (int i = 0; i < 1000000; i++) {
            temp.push_back(distribution(randomNumberGenerator));
        }

        quickSort(temp, 0, temp.size() - 1);
    }
    for (int j = 0; j < 5; ++j) {
        vector<int> data;
        cout << j + 1 << " Aibe\n\n";
        for (int i = 0; i < dataSize; i++) {
            data.push_back(distribution(randomNumberGenerator));
        }
        if (antradalis) {
            std::sort(data.begin(), data.end());
            std::swap(data[RandomIndex], data[LastIndex]);
        }

        for (int attempt = 0; attempt < 6; attempt++) {
            vector<int> temp = data;
            auto start = chrono::high_resolution_clock::now();
            quickSort(temp, 0, temp.size() - 1);
            auto stop = chrono::high_resolution_clock::now();
            auto durationQuicksortMiddle = chrono::duration_cast<chrono::milliseconds>(stop - start);
            averageQuicksortMiddle += durationQuicksortMiddle.count();
            cout << "Middle rusiavimo laikas su bandymu numeris " << attempt + 1 << ": " << durationQuicksortMiddle.count() << " ms\n";
        }
        pivotswitch = true;
        for (int attempt = 0; attempt < 6; attempt++){
            vector<int> temp = data;

            auto start = chrono::high_resolution_clock::now();
            quickSort(temp, 0, temp.size() - 1);
            auto stop = chrono::high_resolution_clock::now();
            auto durationQuicksortMedian = chrono::duration_cast<chrono::milliseconds>(stop - start);
            averageQuicksortMedian += durationQuicksortMedian.count();

            cout << "Median rusiavimo laikas su bandymu numeris " << attempt + 1 << ": " << durationQuicksortMedian.count() << " ms\n";
        }
        std::cout << "Quicksorto laiko vidurkis kai pivot yra middle: " << averageQuicksortMiddle / 6 << " ms\n";
        std::cout << "Quicksorto laiko vidurkis kai pivot yra median: " << averageQuicksortMedian / 6 << " ms\n\n";
        averageQuicksortMedian = 0;
        averageQuicksortMiddle = 0;
    }
    pivotswitch = false;
    return 0;
}