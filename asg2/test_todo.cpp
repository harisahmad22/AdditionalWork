#include <sstream>
#include "todo_list.h"
#include <gtest/gtest.h>

const int low_priority = 1;
const int medium_priority = 2;
const int high_priority = 3;

TEST(test_todo, Remove_First_Item_Of_Multiple_Items)
{
    To_Do_Item_Ptr head = NULL;
    To_Do_Item_Ptr node = NULL;
    To_Do_Item_Ptr temp = NULL;

    temp = create_node ("first_item", '3');
    insert_item (head, temp);
    
    node = temp;

    temp = create_node ("second_item", '2');
    insert_item (head, temp);

    remove_item (head, node);
    delete node;

    ASSERT_EQ (head->priority, '2');

    destroy_list (head);
}

TEST(test_todo, Remove_Middle_Item_Of_Multiple_Items)
{
    To_Do_Item_Ptr head = NULL;
    To_Do_Item_Ptr node = NULL;
    To_Do_Item_Ptr temp = NULL;

    temp = create_node ("first_item", '3');
    insert_item (head, temp);
    
    temp = create_node ("second_item", '2');
    insert_item (head, temp);

    node = temp;

    temp = create_node ("third_item", '1');
    insert_item (head, temp);

    remove_item (head, node);
    delete node;

    ASSERT_EQ (head->next->priority, '1');

    destroy_list (head);
}

TEST(test_todo, Remove_Last_Item_Of_Multiple_Items)
{
    To_Do_Item_Ptr head = NULL;
    To_Do_Item_Ptr node = NULL;
    To_Do_Item_Ptr temp = NULL;

    bool match = false;
    
    temp = create_node ("first_item", '3');
    insert_item (head, temp);
    
    temp = create_node ("second_item", '2');
    insert_item (head, temp);

    temp = create_node ("third_item", '1');
    insert_item (head, temp);
    
    remove_item (head, temp);
    delete node;

    search (head, 3, temp, match);
    
    ASSERT_FALSE (match == true);

    destroy_list (head);
}

TEST(test_todo, Remove_From_Singleton_List)
{
    To_Do_Item_Ptr head = NULL;
    To_Do_Item_Ptr temp = NULL;
    To_Do_Item_Ptr node = NULL;

    temp = create_node ("only item", '1');
    insert_item (head, temp);

    node = temp;

    remove_item (head, node);
    delete node;

    ASSERT_TRUE (head == NULL);

    destroy_list(head);
}

TEST(test_todo, Add_To_Start_Of_Filled_List)
{
    To_Do_Item_Ptr head = NULL;
    To_Do_Item_Ptr temp = NULL;

    temp = create_node ("previous_node_middle", '2');
    insert_item (head, temp);

    temp = create_node ("new_node_high", '3');
    insert_item (head, temp);

    ASSERT_EQ (head->priority, '3');

    destroy_list (head);
}

TEST(test_todo, Add_To_Middle_Of_Filled_List)
{
    To_Do_Item_Ptr head = NULL;
    To_Do_Item_Ptr temp = NULL; 

    temp = create_node ("previous_node_high", '3');
    insert_item (head, temp);

    temp = create_node ("previous_node_low", '1');
    insert_item (head, temp);
    
    temp = create_node ("new_node_middle", '2');
    insert_item (head, temp);

    ASSERT_EQ (head->next->priority, '2');

    destroy_list (head);
}

TEST(test_todo, Add_To_End_Of_Filled_List)
{
    To_Do_Item_Ptr head = NULL;
    To_Do_Item_Ptr temp = NULL; 

    temp = create_node ("previous_node_high", '3');
    insert_item (head, temp);

    temp = create_node ("previous_node_middle", '2');
    insert_item (head, temp);
    
    temp = create_node ("new_node_low", '1');
    insert_item (head, temp);

    ASSERT_EQ (head->next->next->priority, '1');

    destroy_list (head);
}

TEST(test_todo, Add_To_Empty_List)
{
    To_Do_Item_Ptr head = NULL;
    To_Do_Item_Ptr temp = NULL;
    To_Do_Item_Ptr node = NULL;

    bool match = true;

    temp = create_node ("only_item", '1');
    insert_item (head, temp);

    search (head, 1, node, match);

    ASSERT_TRUE (match == true);

    destroy_list (head);	
}
