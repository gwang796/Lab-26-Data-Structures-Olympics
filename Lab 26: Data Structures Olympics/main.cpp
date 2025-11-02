//
//  main.cpp
//  COMSC-210 | Lab 26: Data Structures Olympics | Guo An Wang
//  IDE: Xcode
//  Professors version
//  Created by Guo An Wang on 11/1/25.
//

#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <algorithm>
#include <set>
#include <list>
#include <iomanip>
using namespace std;

// const int SZ = 20000, COLS = 3, ROWS = 4, TESTS = 4;
const int STRUCTURES = 3;
const int ROWS = 4, COLS = 3;
const int LAYER = 2; //for second array that accumulates all times
const int W1 = 10;
const int RUNS = 5;

int main() {
    int results[ROWS][COLS][LAYER] = {0};
    //rows : 0 = READ, 1 = SORT, 2 = INSERT, 3 = DELETE
    //cols : 0 = Operation, 1 = Vector, 2 = List, 3 = Set
    //Layer : 0 = run of that time, 1 = accumulated times
    string cd;
    
    for (int i = 0; i < RUNS; i++) {
        vector<string> data_vector;
        list<string> data_list;
        set<string> data_set;
        // testing for READ operations
        for (int j = 0; j < STRUCTURES; j++) {
            ifstream fin("codes.txt");
            auto start = chrono::high_resolution_clock::now();
            switch(j) {
                case 0: {  // read into a vector
                    while (fin >> cd)
                            data_vector.push_back(cd);
                    auto end = chrono::high_resolution_clock::now();
                    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
                    results[0][j][0] = duration.count(); //time for that run
                    results[0][j][1] += results[0][j][0]; //add it to accumalative
                    break;
                }
                case 1: {  // read into a list
                    while (fin >> cd)
                            data_list.push_back(cd);
                    auto end = chrono::high_resolution_clock::now();
                    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
                    results[0][j][0] = duration.count(); //time for that run
                    results[0][j][1] += results[0][j][0]; //add it to accumalative
                    break;
                }
                case 2: {  // read into a set
                    while (fin >> cd)
                            data_set.insert(cd);
                    auto end = chrono::high_resolution_clock::now();
                    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
                    results[0][j][0] = duration.count(); //time for that run
                    results[0][j][1] += results[0][j][0]; //add it to accumalative
                    break;
                }
            }
            fin.close();
        }

        // testing for SORT operations
        for (int j = 0; j < STRUCTURES; j++) {
            auto start = chrono::high_resolution_clock::now();
            switch(j) {
                case 0: {  // sort a vector
                    sort(data_vector.begin(), data_vector.end());
                    auto end = chrono::high_resolution_clock::now();
                    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
                    results[1][j][0] = duration.count();
                    results[1][j][1] += results[1][j][0]; //add it to accumalative
                    break;
                }
                case 1: {  // sort a list
                    data_list.sort();
                    auto end = chrono::high_resolution_clock::now();
                    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
                    results[1][j][0] = duration.count();
                    results[1][j][1] += results[1][j][0]; //add it to accumalative
                    break;
                }
                case 2: {  // can't sort a set, so set to -1
                    results[1][j][0] = -1;
                    results[1][j][1] = results[1][j][0]; //add it to accumalative
                    break;
                }
            }
        }

        // testing for INSERT operations
        for (int j = 0; j < STRUCTURES; j++) {
            int ind_v = data_vector.size() / 2;
            int ind_l = data_list.size() / 2;
            auto start = chrono::high_resolution_clock::now();
            switch(j) {
                case 0: {  // insert into a vector
                    data_vector.insert(data_vector.begin() + ind_v, "TESTCODE");
                    auto end = chrono::high_resolution_clock::now();
                    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
                    results[2][j][0] = duration.count();
                    results[2][j][1] += results[2][j][0]; //add it to accumalative
                    break;
                }
                case 1: {  // insert into a list
                    auto it = data_list.begin();
                    advance(it, ind_l);
                    data_list.insert(it, "TESTCODE");
                    auto end = chrono::high_resolution_clock::now();
                    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
                    results[2][j][0] = duration.count();
                    results[2][j][1] += results[2][j][0]; //add it to accumalative
                    break;
                }
                case 2: {  // insert into a set
                    data_set.insert("TESTCODE");
                    auto end = chrono::high_resolution_clock::now();
                    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
                    results[2][j][0] = duration.count();
                    results[2][j][1] += results[2][j][0]; //add it to accumalative
                    break;
                }
            }
        }

        // testing for DELETE operations
        for (int j = 0; j < STRUCTURES; j++) {
            // select a target value in the vector
            int ind = data_vector.size() / 2;
            string target_v = data_vector[ind];

            // select a target value in the list
            auto it1 = data_list.begin();
            advance(it1, ind);
            string target_l = *it1;

            // select a target value in the set
            auto it2 = data_set.begin();
            advance(it2, ind);
            string target_s = *it2;
            
            auto start = chrono::high_resolution_clock::now();
            switch(j) {
                case 0: {  // delete by value from vector
                    data_vector.erase(remove(data_vector.begin(), data_vector.end(), target_v));
                    auto end = chrono::high_resolution_clock::now();
                    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
                    results[3][j][0] = duration.count();
                    results[3][j][1] += results[3][j][0]; //add it to accumalative
                    break;
                }
                case 1: {  // delete by value from list
                    data_list.remove(target_l);
                    auto end = chrono::high_resolution_clock::now();
                    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
                    results[3][j][0] = duration.count();
                    results[3][j][1] += results[3][j][0]; //add it to accumalative
                    break;
                }
                case 2: {  // delete by value from set
                    data_set.erase(target_s);
                    auto end = chrono::high_resolution_clock::now();
                    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
                    results[3][j][0] = duration.count();
                    results[3][j][1] += results[3][j][0]; //add it to accumalative
                    break;
                }
            }
        }
        
    }

    string labels[] = {"Read", "Sort", "Insert", "Delete"};
    cout << "Total number of Runs: " << RUNS << endl;
    cout << setw(W1) << "Operation" << setw(W1) << "Vector" << setw(W1) << "List"
         << setw(W1) << "Set" << endl;
    for (int i = 0; i < ROWS; i++) {
        cout << setw(W1) << labels[i];
        for (int j = 0; j < COLS; j++)
            cout << setw(W1) << results[i][j][1];
        cout << endl;
    }
    

    return 0;
}
