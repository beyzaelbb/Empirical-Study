#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>

void swapElements(int &a, int &b);
void printArray(const std::vector<int> &array);
void copyArray(const std::vector<int> &source, std::vector<int> &dest);
void bubbleSort(std::vector<int> &array);
void improvedBubbleSort(std::vector<int> &array);
void selectionSort(std::vector<int> &array);
void quickSort(std::vector<int> &array, int low, int high);
int partition(std::vector<int> &array, int low, int high);
void improvedQuickSort(std::vector<int> &array, int low, int high);
void mergeSort(std::vector<int> &array, int l, int r);
void merge(std::vector<int> &array, int l, int m, int r);
void radixSort(std::vector<int> &array);
double findAverage(const std::vector<double> &times);
void quickSortWrapper(std::vector<int> &array);
void improvedQuickSortWrapper(std::vector<int> &array);
void mergeSortWrapper(std::vector<int> &array);


const std::string RED = "\x1b[31m";
const std::string WHITE = "\x1b[37m";
const std::string DARK_BLUE = "\x1b[34m";
const std::string YELLOW = "\x1b[33m";
const std::string RESET = "\x1b[0m";


struct SortingArguments {
    std::vector<int> baseArray;
    void (*sortFunction)(std::vector<int> &);
    std::string sortName;
};

void swapElements(int &a, int &b) {
    std::swap(a, b);
}

void printArray(const std::vector<int> &array) {
    for (int num : array) {
        std::cout << num << " ";
    }
    std::cout << "\n";
}

void copyArray(const std::vector<int> &source, std::vector<int> &dest) {
    dest = source;
}


double findAverage(const std::vector<double> &times) {
    double sum = 0;
    for (size_t i = 1; i < times.size(); ++i) {
        sum += times[i];
    }
    return sum / (times.size() - 1);
}

void quickSortWrapper(std::vector<int> &array) {
    quickSort(array, 0, array.size() - 1);
}

void improvedQuickSortWrapper(std::vector<int> &array) {
    improvedQuickSort(array, 0, array.size() - 1);
}

void mergeSortWrapper(std::vector<int> &array) {
    mergeSort(array, 0, array.size() - 1);
}

void bubbleSort(std::vector<int> &array) {
    for (size_t i = 0; i < array.size() - 1; ++i) {
        for (size_t j = 0; j < array.size() - i - 1; ++j) {
            if (array[j] > array[j + 1]) {
                swapElements(array[j], array[j + 1]);
            }
        }
    }
}

void improvedBubbleSort(std::vector<int> &array) {
    for (size_t i = 0; i < array.size() - 1; ++i) {
        bool swapped = false;
        for (size_t j = 0; j < array.size() - i - 1; ++j) {
            if (array[j] > array[j + 1]) {
                swapElements(array[j], array[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

void selectionSort(std::vector<int> &array) {
    for (size_t i = 0; i < array.size() - 1; ++i) {
        size_t min_idx = i;
        for (size_t j = i + 1; j < array.size(); ++j) {
            if (array[j] < array[min_idx]) {
                min_idx = j;
            }
        }
        swapElements(array[min_idx], array[i]);
    }
}

void quickSort(std::vector<int> &array, int low, int high) {
    if (low < high) {
        int pi = partition(array, low, high);
        quickSort(array, low, pi - 1);
        quickSort(array, pi + 1, high);
    }
}

int partition(std::vector<int> &array, int low, int high) {
    int mid = low + (high - low) / 2;

    if (array[mid] < array[low])
        swapElements(array[low], array[mid]);
    if (array[high] < array[low])
        swapElements(array[low], array[high]);
    if (array[high] < array[mid])
        swapElements(array[mid], array[high]);

    int pivot = array[mid];
    swapElements(array[mid], array[high]);

    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (array[j] < pivot) {
            ++i;
            swapElements(array[i], array[j]);
        }
    }
    swapElements(array[i + 1], array[high]);
    return i + 1;
}


void improvedQuickSort(std::vector<int> &array, int low, int high) {
    const int THRESHOLD = 50;

    while (low < high) {
        if (high - low + 1 < THRESHOLD) {
            std::vector<int> subArray(array.begin() + low, array.begin() + high + 1);
            selectionSort(subArray);
            std::copy(subArray.begin(), subArray.end(), array.begin() + low);
            break;
        } else {
            int pi = partition(array, low, high);

            if (pi - low < high - pi) {
                improvedQuickSort(array, low, pi - 1);
                low = pi + 1;
            } else {
                improvedQuickSort(array, pi + 1, high);
                high = pi - 1;
            }
        }
    }
}

void mergeSort(std::vector<int> &array, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(array, l, m);
        mergeSort(array, m + 1, r);
        merge(array, l, m, r);
    }
}

void merge(std::vector<int> &array, int l, int m, int r) {
    std::vector<int> L(array.begin() + l, array.begin() + m + 1);
    std::vector<int> R(array.begin() + m + 1, array.begin() + r + 1);

    size_t i = 0, j = 0, k = l;
    while (i < L.size() && j < R.size()) {
        if (L[i] <= R[j]) {
            array[k++] = L[i++];
        } else {
            array[k++] = R[j++];
        }
    }

    while (i < L.size()) {
        array[k++] = L[i++];
    }
    while (j < R.size()) {
        array[k++] = R[j++];
    }
}


int getMax(const std::vector<int> &array) {
    return *std::max_element(array.begin(), array.end());
}

void countingSort(std::vector<int> &array, int exp) {
    std::vector<int> output(array.size());
    int count[10] = {0};

    for (int num : array) {
        count[(num / exp) % 10]++;
    }

    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    for (int i = array.size() - 1; i >= 0; i--) {
        output[count[(array[i] / exp) % 10] - 1] = array[i];
        count[(array[i] / exp) % 10]--;
    }

    array = output;
}

void radixSort(std::vector<int> &array) {
    int maxElement = getMax(array);
    for (int exp = 1; maxElement / exp > 0; exp *= 10) {
        countingSort(array, exp);
    }
}

void sortingTests(std::vector<int> &fullArray, const std::vector<int> &sizes) {
    for (int size : sizes) {
        std::cout << DARK_BLUE << "Running sorting tests for size: " << size << RESET << "\n";
        std::vector<int> baseArray(fullArray.begin(), fullArray.begin() + size);

        std::vector<SortingArguments> args = {
            {baseArray, bubbleSort, "Bubble Sort"},
            {baseArray, improvedBubbleSort, "Improved Bubble Sort"},
            {baseArray, selectionSort, "Selection Sort"},
            {baseArray, quickSortWrapper, "Quick Sort"},
            {baseArray, improvedQuickSortWrapper, "Improved Quick Sort"},
            {baseArray, mergeSortWrapper, "Merge Sort"},
            {baseArray, radixSort, "Radix Sort"}
        };

        for (const auto &arg : args) {
            std::vector<int> array = arg.baseArray;
            std::vector<double> times(5);

            for (int j = 0; j < 5; ++j) {
                array = arg.baseArray;
                clock_t start = clock();
                arg.sortFunction(array);
                clock_t end = clock();
                times[j] = static_cast<double>(end - start) / CLOCKS_PER_SEC;

                std::cout << WHITE << arg.sortName << " - Run " << j + 1 << ": "
                          << times[j] << " seconds" << RESET << "\n";
            }
            double avgTime = findAverage(times);

            std::cout << RED << "Average time for " << arg.sortName << ": "
                      << avgTime << " seconds" << RESET << "\n";
        }
    }
}

int largestProblemUnderTwoSecTest(void (*sortFunction)(std::vector<int> &), std::vector<int> &fullArray) {
    int left = 1, right = fullArray.size();
    int result = 0;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        std::vector<int> testArray(fullArray.begin(), fullArray.begin() + mid);

        auto start = std::chrono::high_resolution_clock::now();
        sortFunction(testArray);
        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> duration = end - start;

        if (duration.count() <= 2.0) {
            result = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return result;
}

int main() {
    const int max_size = 100000;
    std::vector<int> fullArray(max_size);
    std::srand(static_cast<unsigned>(std::time(nullptr)));


    for (int &num : fullArray) {
        num = (std::rand() % 65536) + 1;
    }

    std::cout << YELLOW << "\nFinding largest size sortable in under 2 seconds...\n" << RESET;

    std::vector<SortingArguments> args = {
        {fullArray, bubbleSort, "Bubble Sort"},
        // {fullArray, improvedBubbleSort, "Improved Bubble Sort"},
        // {fullArray, selectionSort, "Selection Sort"},
         //{fullArray, quickSortWrapper, "Quick Sort"},
        // {fullArray, improvedQuickSortWrapper, "Improved Quick Sort"},
        // {fullArray, mergeSortWrapper, "Merge Sort"},
        //{fullArray, radixSort, "Radix Sort"}
    };


    for (const auto &arg : args) {
        std::cout << "\nTesting " << DARK_BLUE << arg.sortName << RESET << "...\n";

        int largestSize = largestProblemUnderTwoSecTest(arg.sortFunction, fullArray);

        std::cout << WHITE << arg.sortName << " can sort up to size "
                  << largestSize << " in under 2 seconds.\n" << RESET;
    }


    //std::cout << YELLOW << "\nRunning full sorting tests...\n" << RESET;

    //std::vector<int> sizes = {100, 1000, 10000, 100000};
    //sortingTests(fullArray, sizes);

    return 0;
}



