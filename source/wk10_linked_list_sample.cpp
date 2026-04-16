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
//      -Node is a struct (or a class).
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
// lucky number, then we add it to the head of the list.
// 
// Then we generate a "winning lucky number" and display the winner's name,
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
Node* createList();
Node* addNode(Node* pHead);
Node* findWinner(Node* pHead, int winner);
void displayResults(Node* pWinner);
void releaseNodes(Node*& pHead);

//------------------------------------------------------------------------------
// entry point
//------------------------------------------------------------------------------
int main()
{
    // Always initialize pointers to 0
    Node* pHead = nullptr;

    // seed rand() with number of seconds elapsed since midnight on Jan 1, 1970
    srand(static_cast<unsigned int>(time(0)));

    // Create all list nodes from the static array in createList()
    pHead = createList();

    // generate the winning number and find the winner, if any
    int winner = rand() % DIE_SIDES + 1;
    std::cout << "\nThe winning number is " << winner << ".\n\n";

    Node* pWinner = findWinner(pHead, winner);

    displayResults(pWinner);

    // free allocated Node memory
    releaseNodes(pHead);
}

//------------------------------------------------------------------------------
// -builds the linked list, return pointer to list head
//------------------------------------------------------------------------------
Node* createList()
{
    static std::string names[] = { "Joe", "Sally", "Gina", "Alec" };

    Node* pHead = nullptr;

    int nPlayers = sizeof(names) / sizeof(std::string);
    for (int i = 0; i < nPlayers; i++)
    {
        pHead = addNode(pHead);

        // set player name and display it
        pHead->player = names[i];

        // generate player's lucky number
        pHead->lucky = rand() % DIE_SIDES + 1;
    }

    return pHead;
}

//------------------------------------------------------------------------------
// -create a new Node and make it the new list head (first Node in the list)
// -returns pointer to the new list head
//------------------------------------------------------------------------------
Node* addNode(Node* pHead)
{
    Node* pNode = new Node;

    pNode->pNext = pHead;
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

//------------------------------------------------------------------------------
// free linked list's allocated Node memory
//------------------------------------------------------------------------------
void releaseNodes(Node*& pHead)
{
    Node*pDelete = pHead;

    // delete each Node, but save its pNext pointer first!
    while (pDelete != nullptr)
    {
        Node* p = pDelete->pNext;
        delete pDelete;
        pDelete = p;
    }

    // set pHead to 0 so the list remains valid
    pHead = nullptr;
}
