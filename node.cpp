
#ifndef ITEM_CPP
#define ITEM_CPP

#include "node.h"

namespace coen79_lab7
{
    //Constructor
    node::node(const std::string &itemName, const float &newPrice, node *nextNode) {
        name = itemName;
        price = newPrice;
        link = nextNode;
    }
    
    //Set name to parameter newName
    void node::setName(const std::string &newName) {
        name = newName;
    }
    
    //Set price to parameter newPrice
    void node::setPrice(const float &newPrice) {
        price = newPrice;
    }
    
    //Set link to parameter new_next
    void node::setLink(node *new_next) {
        link = new_next;
    }
    
    //Return pointer to node
    node* node::getLink() {
        return link;
    }
    
    //Return constant pointer to node
    const node* node::getLink() const {
        return link;
    }
    
    //Return name of node
    std::string node::getName() const{
        return name;
    }
    
    //Return price of node 
    float node::getPrice() const {
        return price;
    }
    
    //Intialize list with one node
    void list_init(node*& head, node*& tail, const std::string& newName, const float& newPrice) {
        head = new node(newName, newPrice, NULL);
        tail = head;
    }
    
    //Insert new node at the tail
    void list_tail_insert(node*& tail, const std::string &newName, const float &newPrice) {
        tail = new node(newName, newPrice, NULL);
    }
    
    //Delete all nodes in the list
    void list_clear(node*& head) {
        while (head != NULL)
            list_head_remove(head);
    }
    
    //Copy data from one list with head old_head into another list with head and tail new_head and new_tail respectivly
    void list_copy(const node *old_head, node* &new_head, node* &new_tail) {
        new_head = NULL;
        new_tail = new_head;
        
        const node *cur = old_head;
	//Iterate through list that is being copied from
        while (cur != NULL) {
	    //Intialize the list when empty with node at cursor
            if (new_head == NULL) {
                new_head = new node(cur->getName(), cur->getPrice());
                new_tail = new_head;
            }
	    //Copy node at cursor at the tail of the list
            else {
                new_tail->setLink(new node(cur->getName(), cur->getPrice()));
                new_tail = new_tail->getLink();
            }
	    //Iterate cursor
            cur=cur->getLink();
        }
    }
    
    //Remove head pointer from the list
    void list_head_remove(node*& head) {
        node* remove_ptr;
        remove_ptr = head;
        head = head->getLink();
        delete remove_ptr;
    }
    
    //Print out the list
    void list_print(node *head) {
        node *cur = head;
	//Iterate through each node in the list
        while (cur != NULL) {
	    //Print out name, and price of each node
            std::cout << "- " << cur->getName() << ", where the price is $" << cur->getPrice() << std::endl;
            cur = cur->getLink();
        }
    }
    
    //Return whether or not a node with the name newName in the list with head head_ptr
    bool list_contains_item(node *head_ptr, const std::string& newName) {
        return (list_search(head_ptr, newName) != NULL);
    }
    
    //Searches list with head head_ptr, and returns pointer to node with name target if it exists, otherwise returns NULL
    node* list_search(node* head_ptr, const std::string& target)
    {
        node *cursor;
        //Iterate through list
        for (cursor = head_ptr; cursor != NULL; cursor = cursor->getLink( ))
	    //If the node at the cursor has the name target, return it
            if (target == cursor->getName( ))
                return cursor;
	//If no node is found, return NULL
        return NULL;
    }
    
    //Searches list with head head_ptr, and returns constant pointer to node with name target if it exists, otherwise returns NULL
    const node* list_search(const node* head_ptr, const std::string & target)
    {
        const node *cursor;
        //Iterate through list        
        for (cursor = head_ptr; cursor != NULL; cursor = cursor->getLink( ))
            //If the node at the cursor has the name target, return it
            if (target == cursor->getName( ))
                return cursor;
        //If no node is found, return NULL
        return NULL;
    }
    
}

#endif
