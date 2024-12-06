#include "sorts.h"
#include <vector>
#include <chrono>
#include <iostream>

using std::vector;
using std::cout;
using std::cin;
using std::endl;
using std::srand;
using std::string;

/* 
    1. Develop, compile, and test locally
    2. Push to git
    3. Pull on LinuxLabs and run
*/

template <class T>
void BubbleSort(vector<T> &list, const int lowerIndex, const int upperIndex) {

    int size = list.size();
    int start = lowerIndex;
    int end = upperIndex;
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
        if (!swapWasMade) { // No matter what has already been sorted, if we go through and no swaps were made, the list is necessarily sorted
            break;
        }
        end--;
    }
}

template <class T>
void InsertionSort(vector<T> &list, const int lowerIndex, const int upperIndex) {
    int sortedPortion = lowerIndex;
    while (sortedPortion < upperIndex) {
        
        int posOfItemToInsert = sortedPortion + 1;
        int toCheck = sortedPortion;
        bool insertNeeded = false;
        
        while (toCheck >= 0) {
            if (list[posOfItemToInsert] < list[toCheck]) { // if the top sorted item is less than this item, no need to check rest
                while ((toCheck >= 0) && (list[posOfItemToInsert] < list[toCheck])) {
                    toCheck--;
                }
                toCheck++; // insert after the item that is smaller than toInsert (deals with back insertion as well)

                T temp;
                temp = list[posOfItemToInsert];
                int posShift = posOfItemToInsert-1;
                while (posShift >= toCheck) {
                    list[posShift+1] = list[posShift];
                    posShift--;
                }
                posShift++;
                list[posShift] = temp;
                break;
            } else break;
        }
        sortedPortion++;
    }
}

template <class T>
void MergeSort(vector<T> &list, const int lowerIndex, const int upperIndex) {

    vector<T> list1;
    vector<T> list2;


    if (list.size() == 1) {
        return;
    }

    int mid = ((upperIndex+1)-lowerIndex)/2; // integer division, +1 because of zero indexing
    int pos = lowerIndex;
    while (pos <= upperIndex) {
        if (pos < mid) {
            list1.push_back(list[pos]);
        } else {
            list2.push_back(list[pos]);
        }
        pos++;
    }

    MergeSort(list1, 0, list1.size()-1);
    MergeSort(list2, lowerIndex, list2.size()-1);

    int list1Pos = 0;
    int list2Pos = 0;
    int mainListPos = lowerIndex;
    while ((list1Pos < list1.size()) && (list2Pos < list2.size())) {
        if (list1[list1Pos] <= list2[list2Pos]) {
            list[mainListPos] = list1[list1Pos];
            list1Pos++;
        } else {
            list[mainListPos] = list2[list2Pos];
            list2Pos++;
        }
        mainListPos++;
    }

    if (list1Pos < list1.size()) {
        while (list1Pos < list1.size()) {
            list[mainListPos] = list1[list1Pos];
            list1Pos++;
            mainListPos++;
        }
    } else if (list2Pos < list2.size()){
        while (list2Pos < list2.size()) {
            list[mainListPos] = list2[list2Pos];
            list2Pos++;
            mainListPos++;
        }
    }
}

template <class T>
void compareSort(const vector<T> &list, vector<T> &listToCopyTo, const int listToCopyTo_copyStartIndex, const int bottomSubList_lowerBound, const int bottomSubList_upperBound, const int topSubList_lowerBound, const int topSubList_upperBound) {

    int bottomSubList_iterator = bottomSubList_lowerBound;
    int topSubList_iterator = topSubList_lowerBound;
    int listToCopyTo_iterator = listToCopyTo_copyStartIndex;

    while ((bottomSubList_iterator < bottomSubList_upperBound) && ((topSubList_iterator < topSubList_upperBound) && topSubList_iterator < list.size())) {
        if (list[bottomSubList_iterator] < list[topSubList_iterator]) {
            listToCopyTo[listToCopyTo_iterator] = list[bottomSubList_iterator];
            bottomSubList_iterator++;
        } else {
            listToCopyTo[listToCopyTo_iterator] = list[topSubList_iterator];
            topSubList_iterator++;
        }
        listToCopyTo_iterator++;
    }

    if (bottomSubList_iterator == bottomSubList_upperBound) {
        while (topSubList_iterator < topSubList_upperBound) {
            listToCopyTo[listToCopyTo_iterator] = list[topSubList_iterator];
            topSubList_iterator++;
            listToCopyTo_iterator++;
        }
    } else {
        while (bottomSubList_iterator < bottomSubList_upperBound) {
            listToCopyTo[listToCopyTo_iterator] = list[bottomSubList_iterator];
            bottomSubList_iterator++;
            listToCopyTo_iterator++;
        }
    }

}

template <class T>
void IterativeMergeSort(vector<T> &list, const int lowerIndex, const int upperIndex) {

    vector<T> tempList = list; // Copy Constructor
    int subArray_size = 1;
    int listSize = list.size();
    bool onTempList = false;

    while (subArray_size < list.size()) {

        int bottomSubArray_Index = lowerIndex;
        int topSubArray_Index = bottomSubArray_Index+subArray_size;

        while (topSubArray_Index < listSize) {
            if (onTempList) {
                compareSort(tempList, list, bottomSubArray_Index, bottomSubArray_Index, bottomSubArray_Index+subArray_size, topSubArray_Index, topSubArray_Index+subArray_size);
            } else {
                compareSort(list, tempList, bottomSubArray_Index, bottomSubArray_Index, bottomSubArray_Index+subArray_size, topSubArray_Index, topSubArray_Index+subArray_size);
            }

            bottomSubArray_Index += 2*subArray_size;
            topSubArray_Index = bottomSubArray_Index+subArray_size;
        }

        if (bottomSubArray_Index < listSize) {
            int tempTopSubArray_Index = ((listSize-bottomSubArray_Index)/2)+bottomSubArray_Index;
            if (onTempList) {
                compareSort(tempList, list, bottomSubArray_Index, bottomSubArray_Index, tempTopSubArray_Index, tempTopSubArray_Index, listSize);
            } else {
                compareSort(list, tempList, bottomSubArray_Index, bottomSubArray_Index, tempTopSubArray_Index, tempTopSubArray_Index, listSize);
            }
        }

        subArray_size *= 2;
        onTempList = !onTempList;

    } // Outer while

    onTempList = !onTempList; // If we broke out, then we need to flip back to what it was before
    if (!onTempList) list = tempList;

}

template <class T>
void QuickSort(vector<T> &list, const int lowerIndex, const int upperIndex) {

    if ((upperIndex-lowerIndex) == 0) {
        return;
    }

    int pivot = -1;
    if (((upperIndex+1)-lowerIndex) > 2) {
        // Using median-of-three method to get a good pick for pivot
        vector<T> medianOfThree_array = {list[lowerIndex], list[(upperIndex-lowerIndex)/2], list[upperIndex]};
        InsertionSort(medianOfThree_array, 0, medianOfThree_array.size()-1);

        int tempIterator = lowerIndex;
        while (pivot == -1) {
            if (list[tempIterator] == medianOfThree_array[1]) {
                pivot = tempIterator;
            }
            tempIterator++;
        }

        swap(list, upperIndex, pivot); // Pivot is now at end of list
    }
    pivot = upperIndex;
    

    int bigItemFromLeft = lowerIndex;
    int smallItemFromRight = pivot-1;
    bool pivotSorted = false;

    while (!pivotSorted) {

        while ((list[bigItemFromLeft] <= list[pivot]) && (bigItemFromLeft < upperIndex)) {
            bigItemFromLeft++;
        }

        while ((list[smallItemFromRight] > list[pivot]) && (smallItemFromRight > lowerIndex)) {
            smallItemFromRight--;
        }

        if (bigItemFromLeft >= smallItemFromRight) { // If they are equal, that means pivot is either biggest or smalles element
            pivotSorted = true;
        } else {
            swap(list, bigItemFromLeft, smallItemFromRight);
        }
    }

    swap(list, bigItemFromLeft, pivot);
    pivot = bigItemFromLeft;

    // We want to make sure there are lists to recurse into
    if (pivot-1 >= lowerIndex) QuickSort(list, lowerIndex, pivot-1);
    if (pivot+1 <= upperIndex) QuickSort(list, pivot+1, upperIndex);


}

template <class T>
void ShellSort(vector<T> &list, const int lowerIndex, const int upperIndex) {

    int gap = ((upperIndex-lowerIndex))/2; // int division

    while (gap > 1) {
        
        for (int i = lowerIndex; i < (lowerIndex+gap); i++) {
            int currIndexSubArray = i;
            int nextItemIndexInSubArray = i+gap;
            while (nextItemIndexInSubArray <= upperIndex) {
                if (list[nextItemIndexInSubArray] < list[currIndexSubArray]) {
                    swap(list, currIndexSubArray, nextItemIndexInSubArray);
                }
                nextItemIndexInSubArray += gap;
            }
        }
        gap /= 2;
    }

    InsertionSort(list, 0, list.size()-1);

}

template <class T>
void swap(vector<T> &list, int index1, int index2) {
    T temp = list[index1];

    list[index1] = list[index2];
    list[index2] = temp;
}






string toLowercase(string str) // Borrowed Code
{
    string result = "";
    for (int i = 0; i < str.length(); i++) {
        // Convert each character to lowercase using tolower
        char ch = str[i];
        result += tolower(ch);
    }
    return result;
}

template <class T>
void printList(const vector<T> &list) {
    for (T item : list) {
        cout << item << "  ";
    }
}







int main(int argc, char *argv[]) {


    /* 
        TODO: Use driver code
    */

    string sortMethod;
    int size;
    bool toPrint;
    string userPrintChoice;
    if (argc > 1) {
        sortMethod = toLowercase(argv[1]);
        size = std::stoi(argv[2]);
        if (argc > 3) {
            userPrintChoice = toLowercase(argv[3]);
            (userPrintChoice.compare("print")) ? toPrint = false : toPrint = true;
        }
    } else {
        cout << "Enter desired sorting algorithm: ";
        cin >> sortMethod;
        cout << "Enter list size: ";
        cin >> size;
        cout << "Print list? (y/n)";
        cin >> userPrintChoice;
        (userPrintChoice == "y") ? toPrint = true : toPrint = false;
    }

    srand(time(0));
    vector<int> testList;
    for (int i = 0; i < size; i++) {
        int toAdd = rand()%size*4+1;
        testList.push_back(toAdd);
    }

    if (toPrint) {
        cout << "Unsorted List: ";
        printList(testList);
        cout << "\n\nSorted List:   ";
    }

    if (sortMethod == "bubble") {
        BubbleSort(testList, 0, size-1);
    } else if (sortMethod == "insertion") {
        InsertionSort(testList, 0, size-1);
    } else if (sortMethod == "merge") {
        MergeSort(testList, 0, size-1);
    } else if (sortMethod == "quick") {
        QuickSort(testList, 0, size-1);
    } else if (sortMethod == "shell") {
        ShellSort(testList, 0, size-1);
    } else if (sortMethod == "iterative") {
        IterativeMergeSort(testList, 0, size-1);
    }
    
    if (toPrint) printList(testList);

    // // Debug
    // srand(time(0));
    // int size = 7;
    // vector<int> testList;
    // for (int i = 0; i < size; i++) {
    //     int toAdd = rand()%(size*4);
    //     testList.push_back(toAdd);
    // }

    // IterativeMergeSort(testList, 0, size-1);

    // for (int item : testList) {
    //     cout << item << "  ";
    // }
    
}