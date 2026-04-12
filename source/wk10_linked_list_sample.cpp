//------------------------------------------------------------------------------
// wk10_linked_list_sample.cpp
// 
// This app builds a linked list of struct items, called "nodes".
// 
// The linked list is the basic building block for many other advanced
// data structures like stacks, queues, deques, circular lists,
// doubly linked lists, and more.
// 
// Once you learn the linked list data structure all these other data 
// structures are just variations.
// 
// A linked list works like this:
//      -Node is a struct (it could be a class).
// 
//      -Each Node instance holds data and a pointer to the next list Node.
// 
//		-A NULL pointer indicates this Node is the last one in the list.
// 
//		-Each Node is added to the end of the list (the "tail"), or to the
//		 beginning of the list (the "head"). Or, Nodes can be inserted to
//       maintain sorted order.
// 
//		-To add a Node to the end of the list, dynamically allocate the
//		 Node with the new keyword. Then set the tail pointer to the new Node.
// 
//		-To add a Node to the head of the list, dynamically allocate the
//		 Node and set its pointer to the current head pointer. Then set the
//       head pointer to the new Node.
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// This app uses a static array to hold player names. For each name, 
// we generate a random "lucky number" not guaranteed to be unique.
// 
// We dynamically allocate memory for a Node struct for each name and 
// lucky number, then we add it to the tail of the list.
// 
// Then we generate a "winning lucky number" and display the winning name,
// or display that nobody won.
//------------------------------------------------------------------------------
#include <iostream>		// cout, cin
#include <string>		// C++ string functionality
#include <cstdlib>		// srand(), rand() for generating random lucky numbers
#include <ctime>		// time(NULL) for seeding random number generation

//------------------------------------------------------------------------------
// constants
//------------------------------------------------------------------------------
constexpr int DIE_SIDES = 6;      // simulate a 6-sided die roll

//------------------------------------------------------------------------------
struct Node
{
    std::string player;		// player name
    int lucky;  			// a random int to simulate a die roll 
    Node* pNext;        	// pointer to the next Node, initially nullptr

    Node() : lucky(0), pNext(nullptr) { }
};

//------------------------------------------------------------------------------
// local function prototypes
//------------------------------------------------------------------------------
Node* createList(Node*& pTail);
Node* addNode(Node* pHead);
Node* findWinner(Node* pHead, int winner);
void displayResults(Node* pWinner);

//------------------------------------------------------------------------------
// entry point
//------------------------------------------------------------------------------
int main()
{
    // Always initialize pointers to 0
    Node* pHead = nullptr;
    Node* pTail = nullptr;

    // Seed rand() with number of seconds elapsed since midnight on Jan 1, 1970
    srand(static_cast<unsigned int>(time(0)));

    // Create all list nodes from the static array in createList()
    pHead = createList(pTail);

    // Generate the winning number and find the winner, if any
    int winner = rand() % DIE_SIDES + 1;
    std::cout << "\nThe winning number is " << winner << "!\n\n";

    Node* pWinner = findWinner(pHead, winner);

    displayResults(pWinner);
}

//------------------------------------------------------------------------------
// build the linked list, return pointer to list head
//------------------------------------------------------------------------------
Node* createList(Node*&pTail)
{
    static std::string names[] = { "Joe", "Sally", "Gina", "Alec" };

    // list initially has one Node that is both head and tail
    Node* pHead = nullptr;

    int nPlayers = sizeof(names) / sizeof(std::string);

    for (int i = 0; i < nPlayers; i++)
    {
        pTail = addNode(pTail);
        if (i == 0)
            pHead = pTail;

        // set player name and display it
        pTail->player = names[i];

        // generate player's lucky number
        pTail->lucky = rand() % DIE_SIDES + 1;
    }

    return pHead;
}

//------------------------------------------------------------------------------
// -creates a new Node and makes it the new list tail (last Node in the list)
//------------------------------------------------------------------------------
Node* addNode(Node* pTail)
{
    Node* p = pTail;            // use pList to traverse list
    Node* pNode = new Node;

    // if the list is empty, the new Node becomes the new head and tail
    if (pTail != nullptr)
        pTail->pNext = pNode;

    return pNode;
}

// returns a pointer to the list item with the winning number,
// or nullptr if there's no matching number in the list 
//------------------------------------------------------------------------------
Node* findWinner(Node* pHead, int lucky)
{
    // traverse the list and find the winner
    Node* pNode = pHead;
    Node* pWinner = nullptr;

    while (pNode != nullptr)
    {
        // display each item's info
        std::cout << "\t" << pNode->player << "'s number is "
            << pNode->lucky << "\n";

        // check list item for lucky number
        if (pNode->lucky == lucky)
            pWinner = pNode;

        // go to the next list item
        pNode = pNode->pNext;
    }

    std::cout << '\n';

    return pWinner;
}

//------------------------------------------------------------------------------
// display info in the passed list item,
// or indicate there's no winner with the passed number
//------------------------------------------------------------------------------
void displayResults(Node* pWinner)
{
    if (pWinner == nullptr)
        std::cout << "Nobody won!\n";

    else
        std::cout << pWinner->player << " wins!\n";
}
