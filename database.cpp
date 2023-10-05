// FILE: database.cpp
// CLASS implemented: database (see database.h for documentation)

// INVARIANT for the database ADT:
//   1. The items in the database are stored in a dynamic array, where each entry of the array includes
//      a company name, a pointer to the head of the linked list of products, and a
//      a pointer to the tail of the linked list of products
//   2. The number of slots in the array of companies is stored in member varibale aloc_slots
//   3. The number of used slots of the array of companies is stored in member varibale used_slots


#ifndef DATABASE_CPP
#define eaadsahashbasdbiaihdaidoadhquadouqwduqwhdouqwdouqwchuowecouadscbasATABASE_CPP

#include "database.h"

//#define USEDEBUG

#ifdef USEDEBUG
#define Debug( x ) std::cout << x
#else
#define Debug( x )
#endif


namespace coen79_lab7
{
    //Constructor
    database::database(const size_type& initial_capacity) {
        used_slots = 0;
        aloc_slots = initial_capacity;
        company_array = new company[aloc_slots];
    }
    
    //Copy Constructor
    database::database(const database &src) {
        Debug("Copy constructor..." << std::endl);
        used_slots = src.used_slots;
        aloc_slots = src.aloc_slots;
        company_array = new company[aloc_slots];
	//Iterate through both arrays copying companies from src company array into this company array
        for (size_type i = 0; i < used_slots; i++) {
            company_array[i] = src.company_array[i];
        }
    }
    
    //Assignment Operator
    database& database::operator= (const database &rhs) {
        Debug("Assignment operator..." << std::endl);
        std::cout << "copying elements of database...";
	company *larger_array;
	//Delete current company array and intialize a new one with size of rhs' company array
	delete[]company_array;
        used_slots = rhs.used_slots;
        aloc_slots = rhs.aloc_slots;
        larger_array = new company[aloc_slots];
	//Iterate through both arrays and copy companies from src company into new array 
        for (size_type i = 0; i < used_slots; i++) {
            larger_array[i] = rhs.company_array[i];
        }
	//Set company_array to be the new array
        company_array = larger_array;
        return *this;
    }
    
    //Destructor
    database::~database() {
	delete[]company_array;
    }
    
    //Reserve more memory so that capacity becomes new_capacity
    void database::reserve(size_type new_capacity) {
        Debug("Reserve..." << std::endl);

        if (new_capacity == aloc_slots)
            return; // The allocated memory is already the right size.
        
        if (new_capacity < used_slots)
            new_capacity = used_slots; // Canít allocate less than we are using.
        company *larger_array;
	//Intialze new array of with new_capacity
        larger_array = new company[new_capacity];
	//Copy data from this company array into new array
        for (size_type i = 0; i < used_slots; i++) {
            larger_array[i] = company_array[i];
        }
	//Delete current company array and set company_array to be the new array
        delete[]company_array;
        company_array = larger_array;
        aloc_slots = new_capacity;
    }
    
    //Insert company into database, and returns whether or not the insertion was successful
    bool database::insert_company(const std::string &entry) {
        
        Debug("Insert company..." << std::endl);

        assert(entry.length() > 0);
        //Search database for company        
        size_type pos = search_company(entry);
        
        // If you find a company that is false, because there are duplicates
        if (pos != COMPANY_NOT_FOUND) {
            return false;
	}
	//If not enough memory for company, reserve more
        if (used_slots == aloc_slots)
            reserve(aloc_slots + 1);
	//Insert new company
        company_array[used_slots] = *(new company(entry));
        used_slots++;
        return true;
    }
    
    //Insert item into company, and return whether or not the insertion was successful
    bool database::insert_item(const std::string &company, const std::string &product_name, const float &price) {
        Debug("Insert item..." << std::endl);

        assert(company.length() > 0 && product_name.length() > 0);
        //Search database for company
        size_type pos = search_company(company);
	//If company doesn't exist, return false
        if (pos == COMPANY_NOT_FOUND) {
            return false;
        }
	//Insert item into company, and return whether or not the insertion was sucessful
        return company_array[pos].insert(product_name, price);
    }
    
    //Delete company from database, and return whether or not the deletion was successful
    bool database::erase_company(const std::string &company) {
        //Search database for company        
        size_type company_index = search_company(company);
	//If company doesn't exist, return false
        if (company_index == COMPANY_NOT_FOUND) {
            return false;
        }
	//Shift array of companies, deleting target company in the process
        for (size_type i = company_index; i < used_slots; i++) {
            company_array[i] = company_array[i + 1];
        }
        used_slots--;
        return true;
    }
    
    //Delete item from company, and return whether or not the deletion was successful 
    bool database::erase_item(const std::string& cName, const std::string& pName) {
        
        assert(cName.length() > 0 && pName.length() > 0);
        //Search database for company
        size_type company_index = search_company(cName);
	//If company doesn't exist return false
        if (company_index == COMPANY_NOT_FOUND) {
            return false;
        }
	//Delete item from company, and return whether or not the deletion was successful 
        return company_array[company_index].erase(pName);
    }
    
    
    //Search database for a company and return its index
    database::size_type database::search_company(const std::string& company) {
        assert(company.length() > 0);
	//Iterate through company array
        for (int i = 0; i < used_slots; i++){
	    //Once target company is found return its index
            if (!(company_array[i].get_name()).compare(company)){
                return i;
	    }
	}
	//If company doesn't exist return not found
        return COMPANY_NOT_FOUND;
    }
    
    //Print all items in a company
    bool database::print_items_by_company(const std::string& cName) {
        assert(cName.length() > 0);
	//Search database for company
        size_type c_index = search_company(cName);
        //If company doesn't exist, return false
        if (c_index == COMPANY_NOT_FOUND) {
            return false;
        }
        //Print out all items in company
        std::cout << "Printing the products of " << cName << ":"<< std::endl;
        company_array[c_index].print_items();
        std::cout << std::endl;
        
        return true;
    }
    
    //Print out all companies in the database
    void database::print_companies() {
        std::cout << "Company List" << std::endl;
	//Iterate through all companies in the database
        for (int i = 0; i < used_slots; i++) {
	    //Print out name of company
            std::cout << "- " << company_array[i].get_name() << std::endl;
        }
    }
}

#endif
