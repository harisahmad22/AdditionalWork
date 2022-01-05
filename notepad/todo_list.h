#ifndef TODO_LIST_H
#define TODO_LIST_H
#include <iostream>
#include <cstring>
#include <fstream>
#include <istream>
#include <ostream>
#include "ioutil.h"

using namespace std;

const int MAX_DESCRIPTION = 60;
const int MIN_DESCRIPTION = 1;
const int MAX_LENGTH = 30;
const int MIN_LENGTH = 1;
const int PRIORITY = 1;

typedef struct To_Do_Item * To_Do_Item_Ptr;

struct To_Do_Item
{
    char description [MAX_DESCRIPTION + 1];
    int priority;
    To_Do_Item_Ptr next;
};

void load (istream &infile, To_Do_Item_Ptr &head);
void write (ostream &outfile, To_Do_Item_Ptr head);
To_Do_Item_Ptr create_node (const char desc[], int priority);
void search (To_Do_Item_Ptr &head, int position, To_Do_Item_Ptr &node, bool &found);
void insert_item (To_Do_Item_Ptr &head, To_Do_Item_Ptr node);
void remove_item (To_Do_Item_Ptr &head, To_Do_Item_Ptr &node);
void display_list (To_Do_Item_Ptr head, ostream &out);
void destroy_list (To_Do_Item_Ptr &head);

#endif
