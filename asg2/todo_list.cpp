#include "todo_list.h"
#include "ioutil.h"

/********************************************************************************
 * Function:  load

 * Purpose:   To create a linked list in memory based off of the todo list items 
              in the input file.

 * Input:     infile - A file which handles the users input
              head   - A pointer which keeps reference to the first item in a 
                       linked list.

 * Output:    head - A pointer which will either be null or a reference to the 
                     first node in the linked list.

 * Return:    Nothing.

 * Details:   Takes in the priority level of an item in the todo list and
              places it in a while loop so that until the end of file is reached
              it will load the file onto a new node in the linked list.

 *******************************************************************************/
void load (istream &infile, To_Do_Item_Ptr &head)
{
    To_Do_Item_Ptr temp = NULL;
    char description [MAX_DESCRIPTION + 1];
    int priority;
    
    infile >> priority;

    while (!infile.eof())
    {
	infile.ignore();
	infile.getline(description, MAX_DESCRIPTION);
	temp = create_node(description, priority);

	insert_item(head, temp);
	temp = NULL;
	infile >> priority;
    }
    
    return;
}


/********************************************************************************
 * Function:  write

 * Purpose:   To write the finalized todo list from the file that the user inputted
              onto an output file.

 * Input:     head - A pointer which will either be null or a reference to the 
                     first node in the linked list.

 * Output:    outfile - The file that the user will be outputting the list on to.

 * Return:    Nothing.

 * Details:   Creates a pointer equivalent to the head pointer and then copies
              the priority and description of the head pointer onto an outfile

 *******************************************************************************/
void write (ostream &outfile, To_Do_Item_Ptr head)
{
    To_Do_Item_Ptr current;    

    current = head;

    while (current != NULL)
    {
	outfile << current->priority << ' ' << current->description << ' ';
	outfile << endl;
	current = current->next;
    }	
    
    return;
}


/********************************************************************************
 * Function:  create_node

 * Purpose:   Creates a node for a new item in the todo list

 * Input:     desc     - A character string about the description of a todo item.
              priority - An integer that is allocated to a certain priority level
                         on the todo list. 

 * Output:    nextItem - A pointer that refers to the new item in the list

 * Return:    A node referring to the next item in the todo list.

 * Details:   Creates a node by giving a local pointer the value of the priority
              of an item and then it copies the description of the item as well
              to that pointer.

 *******************************************************************************/
To_Do_Item_Ptr create_node (const char desc[], int priority)
{
    To_Do_Item_Ptr nextItem = new To_Do_Item;

    nextItem->priority = priority;
    strcpy (nextItem->description, desc);
    nextItem->next = NULL;
    
    return nextItem;
}


/********************************************************************************
 * Function:  search

 * Purpose:   Searches for an item on the todo list based off of the items
              position in that list. 

 * Input:     head     - A pointer which will either be null or a reference to 
                         the first node in the linked list.
              position - A integer which is assigned to an item based on their
                         position in the todo list (top down).
              
 * Output:    found    - A boolean which determines whether or not the item
                         in the todo list that is being searched for was found.
              node     - A pointer which receives the position of an item in
                         the todo list.

 * Return:    Nothing.

 * Details:   Searches for the desrired item in a list and upon reaching it the
              boolean value will be assigned to true. 

 *******************************************************************************/
void search (To_Do_Item_Ptr &head, int position, To_Do_Item_Ptr &node,
	     bool &found)
{
    int count = 1;
    To_Do_Item_Ptr located_node = head;
    
    if (head == NULL)
    {
	cout << endl << "List is empty" << endl;
    }
    else
    {
	while (position != count && located_node != NULL)
	{
	    located_node = located_node->next;
	    count ++;
	}
	if (located_node != NULL)
	{
	    node = located_node;
	    found = true;
	}
	else
	{
	    found = false;
	}
    }
	
    return;
}


/********************************************************************************
 * Function:  is_list_empty

 * Purpose:   To determine whether or not the todo list provided by the user is
              empty.

 * Input:     head - A pointer which will either be null or a reference to 
                     the first node in the linked list.

 * Output:    truth_value - A boolean that detemines if the head is null. 

 * Return:    The boolean truth_value

 * Details:   Uses an if-else statement to determine whether or not the head
              pointer is null. If it is then the boolean "truth_value" will
              evaluate to true and if it not null the boolean wil evaluate to
              false.

 *******************************************************************************/
bool is_list_empty(To_Do_Item_Ptr &head)
{
// Hello, I know this function is completely uselsess/redundant but im very
// proud of it. Please don't dock me marks for this. Thank you.

    bool truth_value;

    if (head == NULL)
    {
	truth_value = true;
    }
    else
    {
	truth_value = false;
    }

    return truth_value;
}


/********************************************************************************
 * Function:  insert_item

 * Purpose:   To insert a new item into the user provided todo list.

 * Input:     node - A pointer which receives the position of an item in the 
                     todo list.

 * Output:    head - A pointer which will either be null or a reference to 
                     the first node in the linked list.

 * Return:    Nothing.

 * Details:   Sorts where the new item in the function should be placed based on
              the priority it holds compared to the priority of the previous
              items on the list. If the list is empty it was immediately place
              the item onto the list in the desired spot.

 *******************************************************************************/
void insert_item (To_Do_Item_Ptr &head, To_Do_Item_Ptr node)
{
    To_Do_Item_Ptr previous;
    To_Do_Item_Ptr new_item;
    
    if (is_list_empty(head) == false)
    {
	previous = NULL;
	new_item = head;
	
	while (new_item != NULL && node->priority <= new_item->priority)
	{
	    previous = new_item;
	    new_item = new_item->next;	    
	}
	
	if (previous == NULL)
	{
	    previous = node;
	    head = previous;
	    node->next = new_item;	    
	}
	else
	{
	    previous->next = node;
	    node->next = new_item;
	}
    }
    else
    {
	head = node;
	head->next = NULL;
    }

    previous = NULL;
    new_item = NULL;
	
    return;
}


/********************************************************************************
 * Function:  remove_item

 * Purpose:   To remove a given item in the to do list provided by the user.

 * Input:     node - A pointer which receives the position of an item in the 
                     todo list.

 * Output:    head - A pointer which will either be null or a reference to 
                     the first node in the linked list.

 * Return:    Nothing.

 * Details:   Removes an item from the todo list by 

 *******************************************************************************/
void remove_item (To_Do_Item_Ptr &head, To_Do_Item_Ptr &node)
{
    To_Do_Item_Ptr previous = NULL;
    To_Do_Item_Ptr current = head;

    while (strcmp(current->description, node->description) != 0)
    {
	previous = current;
	current = current->next;
    }
    
    if (previous == NULL)
    {
	head = current->next;
	delete node;
    }
    else
    {
	previous->next = current->next;
	delete node;
    }

    node = NULL;
    previous = NULL;
    
    return;
}


/********************************************************************************
 * Function:  display_list

 * Purpose:   To display the items in the todo list file to the user.

 * Input:     head - A pointer which will either be null or a reference to 
                     the first node in the linked list.

 * Output:    out - An output which will display the items in the todo list
                    based on their priority level.

 * Return:    Nothing.

 * Details:   The function uses various while loops and increments up a int
              value by 1 every time it goes through the loop until the list is
              empty. It then also sorts the items based on their priority level
              into high, medium, or low on the display list output to the user.

 *******************************************************************************/
void display_list (To_Do_Item_Ptr head, ostream &out)
{
    To_Do_Item_Ptr current;
    int num_items = 0;
    
    current = head;

    if (current == NULL || current->priority == 0)
    {
	cout << endl << "***  There are no todo items in the list  ***" << endl;
	cout << endl;
    }

    if (current != NULL && current->priority == 3)
    {
	cout << endl << "High Priority: " << endl << endl;
	while (current != NULL && current->priority == 3)
	{
	    num_items++;
	    
	    cout << num_items << ":      - ";
	    cout << current->description << endl;
	    current = current->next;
	}
    }
    if (current != NULL && current->priority == 2)
    {
	cout << endl << "Medium Priority: " << endl << endl;
	while (current != NULL && current->priority == 2)
	{
	    num_items++;
	    
	    cout << num_items << ":      - ";
	    cout << current->description << endl;
	    current = current->next;
	}
    }
    if (current != NULL && current->priority == 1)
    {
	cout << endl << "Low Priority: " << endl << endl;
	while (current != NULL && current->priority == 1)
	{

	    num_items++;
	    
	    cout << num_items << ":      - ";
	    cout << current->description << endl;
	    current = current->next;
	}
    }

    cout << endl << endl;

    return;
}


/********************************************************************************
 * Function:  destroy_list

 * Purpose:   To make the todo list empty.

 * Input:     head - A pointer which will either be null or a reference to 
                     the first node in the linked list.

 * Output:    head - A pointer which will either be null or a reference to 
                     the first node in the linked list.

 * Return:    Nothing.

 * Details:   By creating a new pointer the function keeps traversing the list
              and deleting every item within that list. 

 *******************************************************************************/
void destroy_list (To_Do_Item_Ptr &head)
{
    To_Do_Item_Ptr temp = NULL;

    while (head != NULL)
    {
	temp = head->next;
	delete head;
	head = temp;
    }

    head = NULL;
    temp = NULL;
    
    return;
}
