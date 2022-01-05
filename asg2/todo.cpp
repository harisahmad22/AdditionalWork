/********************************************************************************                                                    
Name:        Haris Ahmad                                                                                                                 
E-mail:      hahma485@mtroyal.ca
Course:      COMP 1633 - 001                                                                                                                                                  
Assignment:  2                                                                                                                                                              
Due Date:    February 25th, 2021                                                                                                                                              
Instructor:  Paul Pospisil                                                                                                                                                    
Source File: todo.cpp                                                                                                                                                         

=================================================================================                                                                        
Purpose:                                                                                                                                                                     

  To take a user inputted todo list and perform a series of possibilities to that
  list including adding, removing, or updating items.                                                                                                                        


Details:                                                                                                                                                                      

  Input - The user will be prompted to input a file which will contain the items
          of a todo list with a corresponding number next to them which
          determines each specific items priority level.

        - A menu choice will then be available for the user if the file is opened
          succesfully and the user will be able to perform multiple tasks on the
          todo list from there on.

  Output - The program will output the finalized to do list to a file based on 
           the users input.


Assumptions & Limitations:

  - The file inputted by the user will be ranked from highest to lowest (3 to 1)
  - There will be no duplicate items in the to do list
  - There will only be valid priority levels in the todo list (not greater than
    3 or less than 1)

  - The user must input item descriptions between 1-30 characters
  - The file name must be between 1-30 characters
********************************************************************************/
#include "ioutil.h"
#include "todo_list.h"

void menu(To_Do_Item_Ptr &head);

void process_display_items(To_Do_Item_Ptr &head);
void process_add_item(To_Do_Item_Ptr &head, char str_choice[]);
void process_remove_item(To_Do_Item_Ptr &head, char str_choice[]);
void process_update_item(To_Do_Item_Ptr &head, char str_choice[]);
void process_quit(To_Do_Item_Ptr &head);

int main()
{
    char prompt[MAX_DESCRIPTION + 1] = "Please Enter Filename: ";
    char str[MAX_LENGTH + 1];
    bool eof;
    
    ifstream input;
    ofstream output;

    To_Do_Item_Ptr head = NULL;
    
    eof = false;
    
    readString (prompt, str, MAX_LENGTH, 0, eof);

    if (eof)
    {
	cout << endl << endl;
	cout << "***  EXITING PROGRAM  ***";
	cout << endl << endl;
    }
    else if (strlen(str) == 0)
    {
	cout << endl << endl;
	cout << "***  NO FILE NAME ENTERED  ***";
	cout << endl;
	cout << "***  CREATING A NEW LIST  ***";
	cout << endl << endl;

	menu(head);
    }
    else if (strlen(str) >= MIN_LENGTH && strlen(str) <= MAX_LENGTH)
    {
	input.open(str);
	
	if (input.fail())
	{
	    cout << endl << endl;
	    cout << "***  COULD NOT OPEN FILE  ***";
	    cout << endl << endl;
	}
	else
	{
	    cout << "Opening File: " << str << endl << endl;

	    load (input, head);

	    input.close();
	    
	    menu(head);
	}
    }

    return 0;
}


/********************************************************************************
 * Function:  menu

 * Purpose:   provide the user with a menu that lists the different operations
              that can be performed on the inputted todo list.

 * Input:     head - A pointer which will either be null or a reference to the 
                     first node in the linked list.

 * Output:    head - A pointer which will either be null or a reference to the 
                     first node in the linked list.

 * Return:    Nothing.

 * Details:   The function accepts exactly one valid character and will call the
              operation which corresponds to the character that was entered.
 *******************************************************************************/
void menu(To_Do_Item_Ptr &head)
{
    char prompt [MAX_DESCRIPTION + 1] = "choice: ";
    char str_choice [MIN_LENGTH + 1];
    bool eof;
    
    cout << endl;
    cout << "To-Do List Manager: " << endl << endl;
    cout << "d) display list" << endl;
    cout << "a) add item" << endl;
    cout << "r) remove item" << endl;
    cout << "u) update item priority" << endl;
    cout << "q) quit" << endl << endl;

    readString(prompt, str_choice, MAX_LENGTH, MIN_LENGTH, eof);

    if (strlen(str_choice) == 1)
    {
	while (str_choice[0] != 'q')
	{
	    switch (str_choice[0])
	    {
	    case 'd':
		cout << "you chose display!" << endl << endl;
		process_display_items (head);
		
		break;
		
	    case 'a':
		cout << "you chose add item!" << endl << endl;
		process_add_item (head, str_choice);
		
		break;
		
	    case 'r':
		cout << "you chose remove item!" << endl << endl;
		process_remove_item (head, str_choice);
		
		break;
		
	    case 'u':
		cout << "you chose update items!" << endl << endl;
		process_update_item (head, str_choice);
		
		break;
		
	    default:
		cout << "You chose an invalid choice, ";
		cout << "please select a valid entry - \n\n";
		
		break;
	    }
	    char prompt [] = "Enter new choice: ";
	    readString(prompt, str_choice, MAX_LENGTH, MIN_LENGTH, eof);
	}
    }
    else
    {
	while (str_choice[0] != 'q')
	{
	    cout << "You chose an invalid choice, ";
	    cout << "please select a valid entry - \n\n";
	    cout << "Enter new choice: ";
	    char prompt [] = "Enter new choice: ";
	    readString(prompt, str_choice, MAX_LENGTH, MIN_LENGTH, eof);
	}
    }
    
    switch (str_choice[0])
    {
    case 'q':
	process_quit(head);
	
	return;
    }
    
    return;
}


/********************************************************************************
 * Function:  process_display_items

 * Purpose:   To display the items of the todo list to the user

 * Input:     head - A pointer which will either be null or a reference to the 
                     first node in the linked list.

 * Output:    head - A pointer which will either be null or a reference to the 
                     first node in the linked list.

 * Return:    Nothing. 

 * Details:   Calls upon the display_list function to display to the user.

 *******************************************************************************/
void process_display_items(To_Do_Item_Ptr &head)
{
    display_list (head, cout);
    
    return;
}


/********************************************************************************
 * Function:  process_add_item

 * Purpose:   To arrange the new item from the add_item function into its correct
              position based on its priority

 * Input:     str_choice - A character which determines which operation the
                           user wants to perform.
              head       - A pointer which will either be null or a reference to
                           the first node in the linked list.

 * Output:    head - A pointer which will either be null or a reference to the 
                     first node in the linked list.

 * Return:    Nothing. 

 * Details:   Takes in the item description using readString and then sorts the
              item in the todo_list based on what the user selected.

              Provides the user with prompts for their entry on the item's
              desccription and item's priority level in the todo list.

 *******************************************************************************/
void process_add_item(To_Do_Item_Ptr &head, char str_choice[])
{
    To_Do_Item_Ptr add_item = NULL;
    
    char prompt1[MAX_DESCRIPTION + 1] = "Describe new item (1-60 chars): ";
    char prompt2[MAX_DESCRIPTION + 1] = "Enter priority level (h/m/l): ";

    char str_description[MAX_DESCRIPTION + 1];
    char str_priority_level[PRIORITY + 1];
    bool eof;
    bool invalid_selection = true;
    int priority;

    readString(prompt1, str_description, MAX_DESCRIPTION, MIN_DESCRIPTION, eof);
    
    if (eof)
    {
	str_choice[0] = 'q';

	return;
    }
    else
    {
	readString(prompt2, str_priority_level, PRIORITY, PRIORITY, eof);	    
	
	while (invalid_selection == true)
	{	    
	    if (eof)
	    {	    
		str_choice[0] = 'q';
		
		return;
	    }
	    else
	    {		
		switch (str_priority_level[0])
		{
		case 'h':
		{
		    priority = 3;
		    
		    add_item = create_node (str_description, priority);		    
		    insert_item (head, add_item);		    		    
		    cout << endl << endl;
		    
		    invalid_selection = false;
			
		    break;
		}
		
		case 'm':
		{
		    priority = 2;

		    add_item = create_node (str_description, priority);	    
		    insert_item (head, add_item);		    
		    cout << endl << endl;
		    
		    invalid_selection = false;
		    
		    break;
		}   

		case 'l':
		{
		    priority = 1;

		    add_item = create_node (str_description, priority);		    
		    insert_item (head, add_item);		    
		    cout << endl << endl;
		    
		    invalid_selection = false;
		    
		    break;
		}   

		default:
		{
		    cout << endl << endl;
		    cout << "*** Invalid priority level selected, ";
		    cout << "please re-enter a valid entry ***";
		    cout << endl << endl;
		    readString (prompt2, str_priority_level, PRIORITY, PRIORITY, eof);			    		    
		    
		    break;
		}
		}
	    }
	}
    }

    return;
}


/********************************************************************************
 * Function:  process_remove_item

 * Purpose:   To remove an item from the todo list

 * Input:     head       - A pointer which will either be null or a reference to 
                           the first node in the linked list.
              str_choice - A character which determines which operation the
                           user wants to perform.

 * Output:    head - A pointer which will either be null or a reference to 
                     the first node in the linked list.

 * Return:    Nothing. 

 * Details:   Reads the user input using readString and then searches for the
              item in the todo list that the user wants to remove.

 *******************************************************************************/
void process_remove_item(To_Do_Item_Ptr &head, char str_choice[])
{
    To_Do_Item_Ptr delete_item = NULL;

    char prompt1[MAX_LENGTH + 1] = "Enter item number: ";
    char prompt2 [MAX_LENGTH + 1] = "(y/n): ";
     
    int position = 0;
    
    bool eof;
    bool match;
    bool yes_no;

    position = readInt (prompt1, eof);

    if (eof)
    {
	str_choice[0] = 'q';

	return;
    }
    else
    {
	search(head, position, delete_item, match);
	
	while (!match && !eof)
	{
	    cout << endl;
	    cout << "*** No item found in that position  ***";
	    cout << endl;

	    position = readInt (prompt1, eof);
	    search (head, position, delete_item, match);
	}

	if (eof)
	{
	    str_choice [0] = 'q';

	    return;
	}        
	else
	{
	    if (strlen(delete_item->description) > 0)
	    {
		cout << "Remove item " << '"' << delete_item->description << '"';
		cout << ' ';
		
		yes_no = readBool (prompt2, eof);
		
		cout << endl << endl;
		
		if (yes_no == true)
		{
		    remove_item (head, delete_item);
		}
	    }
	    else
	    {
		cout << "***  No item found in that position  ***";
		cout << endl << endl;
	    }
	}
    }
    
    return;
}


/********************************************************************************
 * Function:  process_update_item

 * Purpose:   To update an item's priority on the todo list 

 * Input:     head       - A pointer which will either be null or a reference to 
                           the first node in the linked list.
              str_choice - A character which determines which operation the
                           user wants to perform.

 * Output:    head - A pointer which will either be null or a reference to 
                     the first node in the linked list.

 * Return:    Nothing. 

 * Details:   Takes in 3 input values from the user asking what item they'd like
              to update, if that is the correct value, and the priority level
              you'd like to update it to.

              

 *******************************************************************************/
void process_update_item(To_Do_Item_Ptr &head, char str_choice [])
{
    To_Do_Item_Ptr update_item = NULL;    
    To_Do_Item_Ptr selected_item = NULL;
    
    int priority;
    int position;
    
    char prompt1 [] = "Enter item number: " ;
    char prompt2 [] = "(y/n): ";
    char prompt3 [] = "Enter priority level (h/m/l): ";
    char str_priority [PRIORITY + 1];

    bool yes_no = false;
    bool found = false;
    bool eof = false;
    bool invalid = true;

    if (head == NULL)
    {
	cout << endl << "The list is empty" << endl;
    }
    else
    {
	position = readInt (prompt1, eof);

	if (eof)
	{
	    str_choice[0] = 'q';

	    return;
	}
	else
	{
	    search (head, position, selected_item, found);

	    while (!found && !eof)
	    {
		    cout << endl << "Invalid input, please re-enter" << endl;
		    position = readInt (prompt1, eof);
		    search (head, position, selected_item, found);	
	    }	    
	    if (eof)    
	    {
		str_choice [0] = 'q';

		return;
	    }
	    else
	    {
		cout << "Reprioritize " << '"' << selected_item->description;
		cout << '"' << ' ';

		yes_no = readBool (prompt2, eof);

		if (eof)
		{
		    str_choice[0] = 'q';

		    return;
		}
		else
		{
		    while (invalid == true)
		    {
			if (eof)
			{
			    str_choice [0] = 'q';

			    invalid = false;
			    
			    return;
			}
			else if(yes_no == true)
			{
			    readString (prompt3, str_priority, PRIORITY,
					PRIORITY, eof);
			    
			    switch (str_priority[0])
			    {
			    case 'h':				
				priority = 3;
				update_item = create_node
				    (selected_item->description, priority);				
				remove_item (head, selected_item);
				insert_item (head, update_item);
				
				cout << endl << endl;
				invalid = false;
				
				break;
				
			    case 'm':
				priority = 2;
				update_item = create_node
				    (selected_item->description, priority);
				remove_item (head, selected_item);
				insert_item (head, update_item);
				
				cout << endl << endl;
				invalid = false;

				break;
			    
			    case 'l':
				priority = 1;
				update_item = create_node
				    (selected_item->description, priority);
				remove_item (head, selected_item);
				insert_item (head, update_item);
				
				cout << endl << endl;
				invalid = false;

				break;

			    default:
				cout << endl << endl;
				cout << "*** Invalid priority level selected, ";
				cout << "please re-enter a valid entry ***";
				cout << endl << endl;
				readString
				    (prompt3, str_priority,
				     PRIORITY, PRIORITY, eof);			    		    
								
				break;				
			    }
			}
			else if (yes_no == false)
			{
			    str_choice[0] = 'q';

			    cout << endl << endl;
			    
			    return;
			}
		    }
		}
	    }
	}
    }


	    
    return;
}


/********************************************************************************
 * Function:  process_quit

 * Purpose:   To quit the program but prompt the user to input an output file
              before the program exits.

 * Input:     head- A pointer which will either be null or a reference to 
                    the first node in the linked list.

 * Output:    head - A pointer which will either be null or a reference to 
                     the first node in the linked list.

 * Return:    Nothing. 

 * Details:   Provides the user with the prompts to enter an output file and
              then writes down the todo list items onto the output file by
              calling other upon other functions.

 *******************************************************************************/
void process_quit (To_Do_Item_Ptr &head)
{
    char prompt []
	= "Enter the name of an output file (1-30 characters inclusive): ";
    char str_file [MAX_LENGTH + 1];
    bool eof;
    ofstream output;

    cout << endl << "***  QUITTING PROGRAM  ***" << endl << endl;
    
    readString (prompt, str_file, MAX_LENGTH, MIN_LENGTH, eof);

    cout << endl;
    
    while (eof)
    {
	cout << endl << "Invalid file name inputted, ";
	cout << "please enter a valid filename" << endl;

	readString (prompt, str_file, MAX_LENGTH, MIN_LENGTH, eof);

	cout << endl;
    }

    output.open (str_file);

    if (output.fail())
    {
	cout << endl << "File could not be opened" << endl;
    }
    else
    {
	write (output, head);
	output.close();
	destroy_list (head);
    }
	
    return;
}
