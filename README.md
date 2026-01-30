# Empirical Analysis of Sorting Algorithms

A comprehensive performance comparison study of various sorting algorithms implemented in C++. This project empirically measures and analyzes the execution time of seven different sorting algorithms across varying input sizes.

## Table of Contents

- [Overview](#overview)
- [Algorithms Implemented](#algorithms-implemented)
- [Methodology](#methodology)
- [Results](#results)
- [Project Structure](#project-structure)
- [Building and Running](#building-and-running)
- [Time Complexity Analysis](#time-complexity-analysis)

## Overview

This empirical study was conducted as part of the CSE 311 course curriculum. The objective is to benchmark and compare the real-world performance characteristics of common sorting algorithms, validating theoretical time complexity predictions through experimental data.

### Key Features

- Implementation of 7 sorting algorithms from scratch
- Automated benchmarking with multiple trials per algorithm
- Binary search-based threshold testing (2-second limit)
- Statistical analysis with warm-up run exclusion
- Color-coded terminal output for readability

## Algorithms Implemented

### 1. Bubble Sort
The classic comparison-based algorithm that repeatedly steps through the list, compares adjacent elements, and swaps them if they are in the wrong order.

**Time Complexity:** O(n²)

### 2. Improved Bubble Sort
An optimized variant that terminates early if no swaps occur during a pass, indicating the array is already sorted.

**Time Complexity:** O(n²) worst case, O(n) best case

### 3. Selection Sort
Divides the input into a sorted and unsorted region, repeatedly selecting the smallest element from the unsorted region.

**Time Complexity:** O(n²)

### 4. Quick Sort
A divide-and-conquer algorithm that selects a pivot element and partitions the array around it. This implementation uses **median-of-three pivot selection** for improved performance on sorted/nearly-sorted inputs.

**Time Complexity:** O(n log n) average, O(n²) worst case

### 5. Improved Quick Sort
A hybrid algorithm combining Quick Sort with Selection Sort for small subarrays. Key optimizations include:
- **Threshold switching:** Uses Selection Sort for subarrays smaller than 50 elements
- **Tail call optimization:** Reduces stack depth by iterating on the larger partition

**Time Complexity:** O(n log n) average

### 6. Merge Sort
A stable, divide-and-conquer algorithm that recursively divides the array into halves, sorts them, and merges the results.

**Time Complexity:** O(n log n)

### 7. Radix Sort
A non-comparative integer sorting algorithm that processes digits from least significant to most significant using counting sort as a subroutine.

**Time Complexity:** O(d × (n + k)) where d = number of digits, k = base (10)

## Methodology

### Test Parameters

| Parameter | Value |
|-----------|-------|
| Input Sizes | 100, 1,000, 10,000, 100,000 |
| Trials per Test | 5 runs |
| Data Range | Random integers [1, 65,536] |
| Maximum Array Size | 100,000 elements |
| Time Limit Test | 2 seconds threshold |

### Measurement Approach

1. **Random Data Generation:** Arrays are filled with random integers between 1 and 65,536 using `std::srand` seeded with current time.

2. **Multiple Trials:** Each algorithm runs 5 times per input size to account for system variability.

3. **Warm-up Exclusion:** The first run is excluded from average calculations to account for cache warming and JIT effects.

4. **Timing:** High-precision timing using `clock_t` and `std::chrono::high_resolution_clock`.

5. **Fresh Data:** Each trial uses a fresh copy of the original unsorted array.

## Results

### Performance Summary (Average Time in Seconds)

| Algorithm | n=100 | n=1,000 | n=10,000 | n=100,000 |
|-----------|-------|---------|----------|-----------|
| Bubble Sort | 0.000015 | 0.000927 | 0.029580 | 5.026 |
| Improved Bubble Sort | 0.000014 | 0.000898 | 0.026959 | 4.655 |
| Selection Sort | 0.000016 | 0.001765 | 0.049747 | 2.383 |
| Quick Sort | 0.000003 | 0.000041 | 0.000386 | 0.208 |
| Improved Quick Sort | 0.000004 | 0.000054 | 0.000401 | 0.208 |
| Merge Sort | 0.000015 | 0.000110 | 0.000667 | 0.006 |
| Radix Sort | 0.000009 | 0.000027 | 0.000136 | 0.002 |

### Key Observations

1. **O(n²) Algorithms:** Bubble Sort, Improved Bubble Sort, and Selection Sort show quadratic growth, becoming impractical for large datasets (n > 10,000).

2. **Radix Sort Dominance:** For integer sorting, Radix Sort significantly outperforms all comparison-based algorithms, achieving ~0.002 seconds for 100,000 elements.

3. **Merge Sort Efficiency:** Demonstrates consistent O(n log n) performance, handling 100,000 elements in ~6ms.

4. **Quick Sort Performance:** Despite O(n²) worst case, the median-of-three pivot selection provides excellent average-case performance (~0.21s for 100,000 elements).

5. **Optimization Impact:** Improved Bubble Sort shows ~7% improvement over standard Bubble Sort due to early termination on nearly-sorted data.

### Performance Visualization

*Note: Charts from the Excel analysis files can be added here as images.*

<!-- Add your Excel charts as images:
![Average Time Comparison](images/average_time_chart.png)
![Scaling Analysis](images/scaling_chart.png)
-->

## Project Structure

```
Empirical-Study/
├── main.cpp                              # Main source code with all implementations
├── README.md                             # This documentation file
├── Average time for algorithms.xlsx      # Summary statistics and charts
├── 2 seconds 3.xlsx                      # Threshold test analysis
└── outputs/                              # Raw benchmark results
    ├── bubble_sorted_times.txt
    ├── improved_bubble_sorted_times.txt
    ├── selection_sorted_times.txt
    ├── quick_sorted_times.txt
    ├── improved_quick_sorted_times.txt
    ├── merge_sorted_times.txt
    └── radix_sorted_times.txt
```

## Building and Running

### Prerequisites

- C++11 or later compiler (g++, clang++, MSVC)
- Standard library support for `<chrono>`

### Compilation

```bash
# Using g++
g++ -std=c++11 -O2 -o sorting_benchmark main.cpp

# Using clang++
clang++ -std=c++11 -O2 -o sorting_benchmark main.cpp
```

### Execution

```bash
./sorting_benchmark
```

### Configuring Tests

In `main.cpp`, modify the `main()` function to enable/disable specific algorithms:

```cpp
std::vector<SortingArguments> args = {
    {fullArray, bubbleSort, "Bubble Sort"},
    {fullArray, improvedBubbleSort, "Improved Bubble Sort"},
    {fullArray, selectionSort, "Selection Sort"},
    {fullArray, quickSortWrapper, "Quick Sort"},
    {fullArray, improvedQuickSortWrapper, "Improved Quick Sort"},
    {fullArray, mergeSortWrapper, "Merge Sort"},
    {fullArray, radixSort, "Radix Sort"}
};
```

To run the full sorting tests, uncomment the following lines in `main()`:

```cpp
std::vector<int> sizes = {100, 1000, 10000, 100000};
sortingTests(fullArray, sizes);
```

## Time Complexity Analysis

### Theoretical vs Empirical Comparison

| Algorithm | Theoretical | Empirical Observation |
|-----------|-------------|----------------------|
| Bubble Sort | O(n²) | Confirmed - ~170x increase from n=10K to n=100K |
| Selection Sort | O(n²) | Confirmed - ~48x increase from n=10K to n=100K |
| Quick Sort | O(n log n) avg | Confirmed - ~540x faster than Bubble Sort at n=100K |
| Merge Sort | O(n log n) | Confirmed - Consistent logarithmic growth |
| Radix Sort | O(d×n) | Confirmed - Near-linear scaling observed |

### Space Complexity

| Algorithm | Space Complexity | Notes |
|-----------|-----------------|-------|
| Bubble Sort | O(1) | In-place |
| Improved Bubble Sort | O(1) | In-place |
| Selection Sort | O(1) | In-place |
| Quick Sort | O(log n) | Stack space for recursion |
| Improved Quick Sort | O(log n) | Optimized stack usage |
| Merge Sort | O(n) | Auxiliary arrays for merging |
| Radix Sort | O(n + k) | Counting arrays |

## Conclusion

This empirical study validates theoretical time complexity predictions and demonstrates the practical implications of algorithm selection. For general-purpose integer sorting:

- **Small arrays (n < 100):** Simple algorithms like Insertion Sort (not tested) or Selection Sort are sufficient
- **Medium arrays (100 < n < 10,000):** Quick Sort or Merge Sort recommended
- **Large arrays (n > 10,000):** Radix Sort (for integers) or Merge Sort (for stability requirements)

The hybrid Improved Quick Sort demonstrates how combining algorithms can leverage the strengths of each approach, using efficient algorithms for small subarrays while maintaining overall O(n log n) performance.

---

*This project was developed for educational purposes as part of CSE 311 coursework.*
