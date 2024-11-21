#include "sorts.h"
#include <vector>
#include <chrono>
#include <iostream>

using std::vector;
using std::cout;
using std::cin;
using std::endl;
// using std::chrono;
using std::srand;

/* 
    1. Develop, compile, and test locally
    2. Push to git
    3. Pull on LinuxLabs and run
*/

template <class T>
void BubbleSort(vector<T> &list, T lowestValueItem, T highestValueItem) {

    int size = list.size();
    int start = 0;
    int end = size-2;
    bool swapWasMade;

    while (end >= start) {
        int currPos = start;
        swapWasMade = false;
        while (currPos <= end) {
            T currentItem = list[currPos];
            T nextItem = list[currPos+1];
            // cout << currentItem << " " << nextItem << endl;
            if (currentItem > nextItem) {
                swapWasMade = true;
                T temp;
                temp = currentItem;
                list[currPos] = nextItem;
                list[currPos+1] = temp;
            }
            // cout << swapWasMade << endl;
            currPos++;
        }
        if (!swapWasMade) {
            break;
        }
        end--;
    }
}

template <class T>
void InsertionSort(vector<T> &list, T lowestValueItem, T highestValueItem) {

}

template <class T>
void MergeSort(vector<T> &list, T lowestValueItem, T highestValueItem) {

}

template <class T>
void IterativeMergeSort(vector<T> &list, T lowestValueItem, T highestValueItem) {

}

template <class T>
void QuickSort(vector<T> &list, T lowestValueItem, T highestValueItem) {

}

template <class T>
void ShellSort(vector<T> &list, T lowestValueItem, T highestValueItem) {

}

int main(int argc, char *argv[]) {

    srand(time(0));
    int size = 7;
    vector<int> testList;
    for (int i = 0; i < size; i++) {
        int toAdd = rand()%20;
        testList.push_back(toAdd);
    }

    BubbleSort(testList, 0, 19);

    for (int item : testList) {
        cout << item << "  ";
    }

}