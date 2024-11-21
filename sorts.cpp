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
    int sortedPortion = 0;
    int size = list.size();
    while (sortedPortion < size-1) {
        
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


    string sortMethod;
    int size;
    int max;
    if (argc > 1) {
        sortMethod = toLowercase(argv[1]);
        size = std::stoi(argv[2]);
        max = std::stoi(argv[3]);
    } else {
        cout << "Enter desired sorting algorithm: ";
        cin >> sortMethod;
        cout << "Enter list size: ";
        cin >> size;
        cout << "Enter list max number: ";
        cin >> max;
    }

    srand(time(0));
    vector<int> testList;
    for (int i = 0; i < size; i++) {
        int toAdd = rand()%max+1;
        testList.push_back(toAdd);
    }

    cout << "Unsorted List: ";
    printList(testList);
    cout << "\nSorted List:   ";

    if (sortMethod == "bubble") {
        BubbleSort(testList, 0, max);

    } else if (sortMethod == "insertion") {
        InsertionSort(testList, 0, max);
    }
    
    printList(testList);

    // // Debug
    // srand(time(0));
    // int size = 7;
    // vector<int> testList;
    // for (int i = 0; i < size; i++) {
    //     int toAdd = rand()%20;
    //     testList.push_back(toAdd);
    // }

    // BubbleSort(testList, 0, 19);

    // for (int item : testList) {
    //     cout << item << "  ";
    // }
    
}