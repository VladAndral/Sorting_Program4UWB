#include "sorts.h"
// #include <vector>
#include <chrono>
#include <iostream>
#include <sys/time.h>
#include <cmath>

using std::vector;
using std::cout;
using std::cin;
using std::endl;
using std::srand;
using std::string;
using std::cerr;

/* 
    1. Develop, compile, and test locally
    2. Push to git
    3. Pull on LinuxLabs and run
*/



// template <class T>
// void printList(const vector<T> &list) {
//     for (T item : list) {
//         cout << item << "  ";
//     }
// }







// int main(int argc, char *argv[]) {


//     /* 
//         TODO: Use driver code
//     */

//     string sortMethod;
//     int size;
//     bool toPrint;
//     string userPrintChoice;
//     if (argc > 1) {
//         sortMethod = toLowercase(argv[1]);
//         size = std::stoi(argv[2]);
//         if (argc > 3) {
//             userPrintChoice = toLowercase(argv[3]);
//             (userPrintChoice.compare("print")) ? toPrint = false : toPrint = true;
//         }
//     } else {
//         cout << "Enter desired sorting algorithm: ";
//         cin >> sortMethod;
//         cout << "Enter list size: ";
//         cin >> size;
//         cout << "Print list? (y/n)";
//         cin >> userPrintChoice;
//         (userPrintChoice == "y") ? toPrint = true : toPrint = false;
//     }

//     srand(time(0));
//     vector<int> testList;
//     for (int i = 0; i < size; i++) {
//         int toAdd = rand()%size*4+1;
//         testList.push_back(toAdd);
//     }

//     if (toPrint) {
//         cout << "Unsorted List: ";
//         printList(testList);
//         cout << "\n\nSorted List:   ";
//     }

//     if (sortMethod == "bubble") {
//         BubbleSort(testList, 0, size-1);
//     } else if (sortMethod == "insertion") {
//         InsertionSort(testList, 0, size-1);
//     } else if (sortMethod == "merge") {
//         MergeSort(testList, 0, size-1);
//     } else if (sortMethod == "quick") {
//         QuickSort(testList, 0, size-1);
//     } else if (sortMethod == "shell") {
//         ShellSort(testList, 0, size-1);
//     } else if (sortMethod == "iterative") {
//         IterativeMergeSort(testList, 0, size-1);
//     }
    
//     if (toPrint) printList(testList);

//     // // Debug
//     // srand(time(0));
//     // int size = 7;
//     // vector<int> testList;
//     // for (int i = 0; i < size; i++) {
//     //     int toAdd = rand()%(size*4);
//     //     testList.push_back(toAdd);
//     // }

//     // IterativeMergeSort(testList, 0, size-1);

//     // for (int item : testList) {
//     //     cout << item << "  ";
//     // }
    
// }




/* 
        PROJECT DRIVER CODE
*/


//Global functions
void InitVector(vector<int> &item_vector, int rand_max) {
    if (rand_max < 0) {
        return;
    }
    vector<int> pool(rand_max);
    for (int i = 0; i < rand_max; i++) {
        pool[i] = i;
    }
    int spot;
    for (int i = 0; i < rand_max; i++) {
        spot = rand() % (pool.size());
        item_vector[i] = pool[spot];
        pool.erase(pool.begin() + spot);
    }
}

void PrintVector(const vector<int> &item_vector, string name) {
    int size = item_vector.size();
    for (int i = 0; i < size; i++) {
        cout << item_vector[i] << " ";
    }
    cout << endl;
}
// Function to calculate elapsed time
// Microseconds
int Elapsed(const timeval &start, const timeval &end) {
    return (end.tv_sec - start.tv_sec) * 1000000
    + (end.tv_usec - start.tv_usec);
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

void export_times() {

    struct timeval start_time, end_time;

    vector<string> daList = {"bubble", "insertion", "merge", "iterative", "quick", "shell"};
    
    // cout << "something!!!!!!";

    for (string sort_name : daList) {

        cout << sort_name + ": ";

        // for (int i = 2; i < 100000; i*=2) {
        for (int i = 0; i <= 10; i++) {

            // int size = i;
            int size = 1000*i;

            srand(1);
            vector<int> items(size);
            InitVector(items, size);

            gettimeofday(&start_time, 0);
            if (sort_name == "bubble") {
                BubbleSort(items, 0, size-1);
            } else if (sort_name == "insertion") {
                InsertionSort(items, 0, size-1);
            } else if (sort_name == "merge") {
                MergeSort(items, 0, size-1);
            } else if (sort_name == "iterative") {
                IterativeMergeSort(items, 0, size-1);
            } else if (sort_name == "quick") {
                QuickSort(items, 0, size-1);
            } else if (sort_name == "shell") {
                ShellSort(items, 0, size-1);
            }
            gettimeofday(&end_time, 0);
            int timeElapsed = Elapsed(start_time, end_time);


            cout << std::to_string(timeElapsed) + " ";


        }

        cout << "\n";
        
    }

}

int main(int argc, char* argv[]) {

    // cout << "something";
    int size = 0;
    string sort_name = "";
    bool print_out = false;


    if ((argc < 3) || (argc > 4)) {

        if (argc == 1) {
            // cout << "Print runtimes for different array sizes? [y/n]";
            // string userInput;
            // cin >> userInput;
            // if (userInput == "y") export_times();

            // // Debug
            // size = 10;
            // vector<int> items(size);
            // InitVector(items, size);
            // ShellSort(items, 0, size-1);
            // return 0;

        }


        else {
            cerr << "Usage: Sorter algorithm size [Print]" << endl;
            return -1;
        }
    }
    
    sort_name = toLowercase(string(argv[1]));
    size = atoi(argv[2]);

    if (size <= 0) {
        cerr << "Vector size must be positive" << endl;
        return -1;
    }

    if (argc == 4) {
        string print_arr = toLowercase(string(argv[3]));
        if (print_arr == "print") {
            print_out = true;
        } else {
            cerr << "Usage: Sorter algorithm size [Print]" << endl;
            return -1;
        }
    }

    srand(1);
    vector<int> items(size);
    InitVector(items, size);
    if (print_out) {
        cout << "Initial:" << endl;
        PrintVector(items, string("items"));
        cout << endl;
    }

    //get time to measure the time it takes to sort
    struct timeval start_time, end_time;
    gettimeofday(&start_time, 0);
    if (sort_name == "bubble") {
        BubbleSort(items, 0, size-1);
    } else if (sort_name == "insertion") {
        InsertionSort(items, 0, size-1);
    } else if (sort_name == "merge") {
        MergeSort(items, 0, size-1);
    } else if (sort_name == "quick") {
        QuickSort(items, 0, size-1);
    } else if (sort_name == "shell") {
        ShellSort(items, 0, size-1);
    } else if (sort_name == "iterative") {
        IterativeMergeSort(items, 0, size-1);
    }
    
    gettimeofday(&end_time, 0);
    
    if (print_out) {
        cout << "Sorted:" << endl;
        PrintVector(items, string("item"));
    }
    cout << "Time (microsecs): " << Elapsed(start_time, end_time) << endl;
    return 0;
}
