// ooop_lab1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Data.h"
#include "Storage.h"
#include "Operations.h"
#include "Interface.h"
#include "Structures.h"
#include "Sparse.h"

#include <vector>
#include <set>
#include <map>



int main() {
    Interface menu;
    bool temp = 1;
    while(temp){
        temp = menu.GetCommand();
    }


	/*List<int> List(15);
	List.addToList(14, 0);
	List.addToList(3, 1);
	List.addToList(25, 1);
	List.addToList(23, 0);
	List.addToList(11, 3);
	List.addToList(1, 2);
	List.print();*/

    return 0;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
