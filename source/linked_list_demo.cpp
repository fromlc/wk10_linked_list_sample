//------------------------------------------------------------------------------
// linked_list_demo.cpp
// 
// This app builds a linked list of struct items, commonly called "nodes".
// 
// A linked list is the first custom data structure that computer science
// students study. This is because the linked list is the basic building
// block for many other advanced data structures like stacks, queues,
// deques, circular lists, doubly linked lists, and more.
// 
// Once you learn the linked list data structure all these other data 
// structures are just simple variations.
// 
// Here's how a linked list works:
//		-each struct item has a pointer field used to find the next item
//			in the list. 
// 
//		-the pointer field is of the same type as the struct - this
//			is the "signature" of a struct intended for use as a list item.
// 
//		-the pointer field is initially set to nullptr to indicate this item
//		 is the end of the list.
// 
//		-each item is added to the end of the list (the "tail"), or to the
//		 beginning of the list (the "head"). 
// 
//		-when adding an item to the tail of the list, dynamically allocate the
//		 item and set the pointer of the current tail item to the address of
//		 the newly allocated item so that each new item becomes the new tail
//		 of the list.
// 
//		-when adding an item to the head of the list, dynamically allocate the
//		 item and set its pointer to the current head item.	This is the method
//		 we'll use in this demo (can you see why this way is easier?)
//
// When you create a linked list of structs, you'll replace the struct type 
// name (here this type name is "ListItem") with your own custom data type 
// name, for instance "July4Trips".
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// This app will loop to get names from the user. For each name, we generate
// a random "lucky number" that may not be unique.
// 
// We dynamically allocate memory for a ListItem struct for each name and 
// lucky number, then we add it to the head of the list.
// 
// After the user enters all the names they want, we generate a "winning lucky
// number" and display the winning name, or display that nobody won.
//------------------------------------------------------------------------------
#include <iostream>		// cout, cin
#include <string>		// C++ string functionality
#include <new>			// dynamic memory allocation with keyword new
#include <cstdlib>		// srand(), rand() for generating random lucky numbers
#include <ctime>		// time(NULL) for seeding random number generation
#include <vector>

//------------------------------------------------------------------------------
// using symbols
//------------------------------------------------------------------------------
using std::bad_alloc;
using std::cin;
using std::cout;
using std::stoi;
using std::string;

//------------------------------------------------------------------------------
// constants
//------------------------------------------------------------------------------

// for output
constexpr char CRLF = '\n';

// for app control
constexpr int MAX_NAMES = 3;
constexpr int MAX_LUCKY = 10;

// for error reporting to OS
constexpr int ERR_ALL_OK = 0;
constexpr int ERR_BAD_ALLOC = 1;
constexpr int ERR_NO_WINNER = 2;

//------------------------------------------------------------------------------
// ListItem : holds a name and a randomly generated integer, plus
// a pointer to the next ListItem.
//------------------------------------------------------------------------------
struct ListItem {
	string name;				// one-word name input by the user
	int lucky = 0;				// a random int
	ListItem* pNext = nullptr;	// pointer to the next ListItem, initially nullptr
};

//------------------------------------------------------------------------------
// globals
//------------------------------------------------------------------------------
namespace g {
	ListItem* pHead = nullptr;
}

//------------------------------------------------------------------------------
// local function prototypes
//------------------------------------------------------------------------------
void CreateList(int);
ListItem* PrepareItem(int);
void FillItem(ListItem*, int);
void AddItem(ListItem*);
int DisplayWinningNumber();
ListItem* FindWinner(int);
int DisplayResults(ListItem*, int);

//------------------------------------------------------------------------------
// entry point
//------------------------------------------------------------------------------
int main() {

	// seed rand() with number of seconds elapsed since midnight on Jan 1, 1970
	// static_cast fixes type conversion warning
	srand(static_cast<unsigned int>(time(0)));

	// create the appropriate number of list items
	CreateList(MAX_NAMES);

	// generate the winning number and find the winner, if any
	int lucky = DisplayWinningNumber();
	ListItem* pItem = FindWinner(lucky);

	// display the results
	int retcode = DisplayResults(pItem, lucky);

	return retcode;
}

//------------------------------------------------------------------------------
// build the linked list 
//------------------------------------------------------------------------------
void CreateList(int max) {

	cout << "\nEnter names for " << max << " players.\n";

	for (int i = 0; i < max; i++) 	{

		ListItem* pItem = PrepareItem(i + 1);
		AddItem(pItem);
	}
}

//------------------------------------------------------------------------------
// dynamically allocate a ListItem struct and fill it with data
//------------------------------------------------------------------------------
ListItem* PrepareItem(int numItem) {

	ListItem* pItem;

	try {
		pItem = new(ListItem);
	}
	catch (const bad_alloc& e) {
		cout << "ListItem allocation failed: " << e.what() << '\n';
		exit(ERR_BAD_ALLOC);
	}

	// fill the newly allocated ListItem with data
	FillItem(pItem, numItem);

	return pItem;
}

//------------------------------------------------------------------------------
// fill the passed ListItem struct	with data
//------------------------------------------------------------------------------
void FillItem(ListItem* pItem, int numItem) {

	// get a name from user
	cout << "\nName for player " << numItem << ": ";
	// #TODO validate name
	cin >> pItem->name;

	// generate a number between 1 and MAX_LUCKY for this name
	pItem->lucky = rand() % MAX_LUCKY + 1;
}

//------------------------------------------------------------------------------
// add the passed ListItem struct to the head of the list
//------------------------------------------------------------------------------
void AddItem(ListItem* pItem) {

	// set this item as the list head (first item in the list)
	pItem->pNext = g::pHead;
	g::pHead = pItem;
}

//------------------------------------------------------------------------------
// generate, display, and return the winning number
//------------------------------------------------------------------------------
int DisplayWinningNumber() {

	int winner = rand() % MAX_LUCKY + 1;
	cout << "\nThe winning number is " << winner << "!\n";

	return winner;
}

//------------------------------------------------------------------------------
// returns a pointer to the list item with the winning number,
// or nullptr if there's no matching number in the list 
//------------------------------------------------------------------------------
ListItem* FindWinner(int lucky) {

	// traverse the list and find the winner
	ListItem* pItem = g::pHead;

	while (pItem != nullptr) {

		// display each item's info
		cout << '\n' << pItem->name << " has lucky number " << pItem->lucky << std::endl;

		// check list item for winning lucky number
		if (pItem->lucky == lucky)
			break;

		// go to the next list item
		pItem = pItem->pNext;
	}

	cout << '\n';

	return pItem;
}

//------------------------------------------------------------------------------
// display the info in the passed list item,
// or indicate there's no winner with the passed number
//------------------------------------------------------------------------------
int DisplayResults(ListItem* pWinner, int lucky) {

	if (pWinner == nullptr) {

		// we need the passed lucky number for this
		cout << "\nSorry, there's no winner for lucky number "
			<< lucky << '\n';

		return ERR_NO_WINNER;
	}

	cout << "\nThe winner is " << pWinner->name << " with lucky number "
		<< pWinner->lucky << '\n';
	
	return ERR_ALL_OK;
}
