// FILE: company.cpp
// CLASS implemented: company (see company.h for documentation)


#include <cassert>
#include "company.h"

//#define USEDEBUG

#ifdef USEDEBUG
#define Debug( x ) std::cout << x
#else
#define Debug( x )
#endif

namespace coen79_lab7
{
    //Default Constructor
    company::company() {
        this->company_name = "";
        this->head_ptr = NULL;
        this->tail_ptr = NULL;
    }
    
    //Constructor
    company::company(const std::string& company_name) {
        assert(company_name.length() > 0);
        this->company_name = company_name;
        this->head_ptr = NULL;
        this->tail_ptr = NULL;
    }
    
    //Copy Constructor
    company::company(const company &src) {
        Debug("Company copy constructor..." << std::endl);
        company_name = src.company_name;
        list_copy(src.head_ptr, head_ptr, tail_ptr);
    }

    //Assignment operator
    company& company::operator =(const company &src) {
        Debug("Company assignemnt operator..." << std::endl);
        list_clear(head_ptr);
        company_name = src.company_name;
        list_copy(src.head_ptr, head_ptr, tail_ptr);
        return *this;
    }
    
    //Destructor
    company::~company() {
        list_clear(head_ptr);
    }
    
    //Returns name of company
    std::string company::get_name() const {
        return company_name;
    }
    
    //Returns constant pointer to head of company
    const node *company::get_head() const {
        return head_ptr;
    }
    
    //Returns constant pointer to tail of company
    const node *company::get_tail() const {
        return tail_ptr;
    }
    
    //Returns pointer to head of company
    node* company::get_head() {
        return head_ptr;
    }
    
    //Returns pointer to tail of company
    node* company::get_tail() {
        return tail_ptr;
    }
    
    //Prints out items contained in company
    void company::print_items() {
        list_print(head_ptr);
    }
    
    //Inserts new item into company, and returns whether or not the insertion was successful
    bool company::insert(const std::string& product_name, const float& price) {
        
        assert(product_name.length() > 0);
	//If the item is already in the list, do not insert item, and return false
        if (list_contains_item(head_ptr, product_name)) {
            return false;
        }
        //If the list is empty, then intialize is it with the new product
        if (head_ptr == NULL) {
	    list_init(head_ptr, tail_ptr, product_name, price);
        }
	//Insert the new product as the tail of the list of the company's products
        else {
	    node* temp;
	    temp = tail_ptr;
            list_tail_insert(tail_ptr, product_name, price);
	    temp->setLink(tail_ptr);
        }
        
        return true;
    }

    //Remove a product from the company, and returns whether or not the deletion was successful
    bool company::erase(const std::string& product_name) {
        assert(product_name.length() > 0);
	//If the product is not contained in the list, return false
        if (!list_contains_item(head_ptr, product_name))
            return false;
	//If the product is the head of the list, remove the list's head
        if (list_search(head_ptr, product_name) == head_ptr) {
            list_head_remove(head_ptr);
            return true;
        }
        node* cursor;
	//Iterate through list of products
        for (cursor = head_ptr; cursor->getLink() != NULL; cursor = cursor->getLink())
	    //When product is found, break so that the cursor is the node before the node to be erased
            if (product_name == cursor->getLink()->getName()) {
                break;
            }
        node* remove_ptr;
        remove_ptr = cursor->getLink();
	//If the we are removing the tail pointer set tail pointer to point to the previous node 
        if (remove_ptr == tail_ptr) {
            tail_ptr = cursor;
        }
	//Delete the node and return true
        cursor->setLink(remove_ptr->getLink());
        delete remove_ptr;
        return true;
    }
    
    
}
