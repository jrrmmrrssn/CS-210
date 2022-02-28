/*
/	Author:		Jeremy Morrison
/	Course:		CS210 Programming Languages 22EW3
/	Date:		02/22/2022
*/


#include <Python.h>

#include <iostream>

#include <iomanip>

#define NOMINMAX

#include <Windows.h>

#undef NOMINMAX

#include <cmath>

#include <string>

#include <fstream>

using namespace std;

/*

Description:

To call this function, simply pass the function name in Python that you wish to call.

Example:

callProcedure("printsomething");

Output:

Python will print on the screen: Hello from python!

Return:

None

*/

void CallProcedure(string pName)

{

	char* procname = new char[pName.length() + 1];

	std::strcpy(procname, pName.c_str());

	Py_Initialize();

	PyObject* my_module = PyImport_ImportModule("PythonFile");

	PyErr_Print();

	PyObject* my_function = PyObject_GetAttrString(my_module, procname);

	PyObject* my_result = PyObject_CallObject(my_function, NULL);

	Py_Finalize();

	delete[] procname;

}

/*

Description:

To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send

Example:

int x = callIntFunc("PrintMe","Test");

Output:

Python will print on the screen:

You sent me: Test

Return:

100 is returned to the C++

*/

int callIntFunc(string proc, string param)

{

	char* procname = new char[proc.length() + 1];

	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];

	std::strcpy(paramval, param.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;

	// Initialize the Python Interpreter

	Py_Initialize();

	// Build the name object

	pName = PyUnicode_FromString((char*)"PythonFile");

	// Load the module object

	pModule = PyImport_Import(pName);

	// pDict is a borrowed reference

	pDict = PyModule_GetDict(pModule);

	// pFunc is also a borrowed reference

	pFunc = PyDict_GetItemString(pDict, procname);

	if (PyCallable_Check(pFunc))

	{

		pValue = Py_BuildValue("(z)", paramval);

		PyErr_Print();

		presult = PyObject_CallObject(pFunc, pValue);

		PyErr_Print();

	}

	else

	{

		PyErr_Print();

	}

	//printf("Result is %d\n", _PyLong_AsInt(presult));

	Py_DECREF(pValue);

	// Clean up

	Py_DECREF(pModule);

	Py_DECREF(pName);

	// Finish the Python Interpreter

	Py_Finalize();

	// clean

	delete[] procname;

	delete[] paramval;

	return _PyLong_AsInt(presult);

}

/*

Description:

To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send

Example:

int x = callIntFunc("doublevalue",5);

Return:

25 is returned to the C++

*/

int callIntFunc(string proc, int param)

{

	char* procname = new char[proc.length() + 1];

	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;

	// Initialize the Python Interpreter

	Py_Initialize();

	// Build the name object

	pName = PyUnicode_FromString((char*)"PythonFile");

	// Load the module object

	pModule = PyImport_Import(pName);

	// pDict is a borrowed reference

	pDict = PyModule_GetDict(pModule);

	// pFunc is also a borrowed reference

	pFunc = PyDict_GetItemString(pDict, procname);

	if (PyCallable_Check(pFunc))

	{

		pValue = Py_BuildValue("(i)", param);

		PyErr_Print();

		presult = PyObject_CallObject(pFunc, pValue);

		PyErr_Print();

	}

	else

	{

		PyErr_Print();

	}

	//printf("Result is %d\n", _PyLong_AsInt(presult));

	Py_DECREF(pValue);

	// Clean up

	Py_DECREF(pModule);

	Py_DECREF(pName);

	// Finish the Python Interpreter

	Py_Finalize();

	// clean

	delete[] procname;

	return _PyLong_AsInt(presult);

}

/*

Description:

When this function is called, it will produce a menu to prompt user input.

Example:

DrawMenu();

Output:

Outputs a menu that will take user input between 1-4. User input will then execute the appropriate Python function.

That is, a user input of 1 will output a list of unique words and their number of appearances, input of 2 will

search for the number of a single item's appearances, an input of 3 will print a histogram of each item's appearances,

and an input of 4 will quit the program.

Return:

None

*/

void DrawMenu() {

	//Initialize variables

	int menuLoop = 0; 

	int wordCount = 0;

	int itemQuantity = 0;

	string searchTerm; 

	string itemName;

	string blueColor = "\033[34;1m"; 

	string defaultColor = "\033[33;1m"; 

	ifstream fileInput; 

	while (menuLoop != 4) {

		//Display menu and get user input

		std::cout << defaultColor;

		std::cout << "[1] Calculate the number of times each item appears" << std::endl;

		std::cout << "[2] Calculate the frequency of a specific item" << std::endl;

		std::cout << "[3] Create a histogram based on the number of appearances of each item" << std::endl;

		std::cout << "[4] Quit" << std::endl;

		std::cin >> menuLoop;

		//Check user input. If not valid, get valid input.

		while (std::cin.fail()) {

			std::cin.clear();

			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			std::cout << "Please input valid menu option: ";

			std::cin >> menuLoop;

		}



		//Switch statement for user input

		switch (menuLoop) {

		//Case 1: Calculate the number of times each item appears, then print a list

		case 1:

			system("CLS"); //Clear screen

			CallProcedure("CountAll"); //Call Python function "CountAll"

			std::cout << std::endl; 

			break;

		//Case 2: Calculate the number of times a specific item appears, then print result.

		case 2:

			system("CLS");

			std::cout << "Which item would you like to see?" << std::endl;

			std::cin >> searchTerm;

			//Call Python function

			wordCount = callIntFunc("CountInstances", searchTerm);

			//Print result

			std::cout << std::endl << searchTerm << " : " << wordCount << std::endl << std::endl;

			break;

			//Case 3: Print a histogram based on how many times each item appears

		case 3:

			system("CLS"); 

			CallProcedure("CollectData"); //Call Python function CollectData

			fileInput.open("frequency.dat"); //Open frequency.dat

			fileInput >> itemName; 

			fileInput >> itemQuantity; 

			//print histogram

			while (!fileInput.fail()) {

				//Set color

				std::cout << defaultColor;

				//Print item name

				std::cout << std::setw(14) << std::left << itemName << std::setw(6);


				std::cout << blueColor;

				//Print itemQuantity

				for (int i = 0; i < itemQuantity; i++) {

					std::cout << std::right << "*";

				}

				//next line

				std::cout << std::endl;

				fileInput >> itemName;

				fileInput >> itemQuantity;

			}

			//Close frequency.dat

			fileInput.close();

			std::cout << defaultColor << endl;

			break;

			//Case 4: Quit the program.

		case 4:

			return;

		default:

			std::cout << "Please input valid menu option: ";

			std::cout << std::endl;

			break;

		}

	}

}

//Main method

void main()

{

	//Display user menu

	DrawMenu();

}