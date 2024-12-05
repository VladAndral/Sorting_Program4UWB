#ifndef SORTS_H_
#define SORTS_H_
#include <vector>

using std::vector;

// TODO: Implementation in .h file (here)

template <class T>
void BubbleSort(vector<T> &list, int lowerIndex, int upperIndex);

template <class T>
void InsertionSort(vector<T> &list, int lowerIndex, int upperIndex);

template <class T>
void MergeSort(vector<T> &list, int lowerIndex, int upperIndex);

template <class T>
void IterativeMergeSort(vector<T> &list, int lowerIndex, int upperIndex);

template <class T>
void QuickSort(vector<T> &list, int lowerIndex, int upperIndex);

template <class T>
void ShellSort(vector<T> &list, int lowerIndex, int upperIndex);

template <class T>
void swap(vector<T> &list, int index1, int index2);


#endif