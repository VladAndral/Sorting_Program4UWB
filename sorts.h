#ifndef SORTS_H_
#define SORTS_H_
#include <vector>

using std::vector;

template <class T>
void BubbleSort(vector<T> &list, T lowestValueItem, T highestValueItem);

template <class T>
void InsertionSort(vector<T> &list, T lowestValueItem, T highestValueItem);

template <class T>
void MergeSort(vector<T> &list, T lowestValueItem, T highestValueItem);

template <class T>
void IterativeMergeSort(vector<T> &list, T lowestValueItem, T highestValueItem);

template <class T>
void QuickSort(vector<T> &list, T lowestValueItem, T highestValueItem);

template <class T>
void ShellSort(vector<T> &list, T lowestValueItem, T highestValueItem);


#endif