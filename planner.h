/*************************************************************************
      Hunter Stout   -   3/9/2022
      planner.h      -   Header File.
*************************************************************************/
#ifndef PLANNER
#define PLANNER

#include <iostream>
#include "node.h"

class Planner{
    public:
        //*********************************************************
        // Function: Planner
        // Purpose: Constructor for planner class.
        //*********************************************************
        Planner();

        //*********************************************************
        // Function: ~Planner
        // Purpose: Deconstructor for planner class.
        //*********************************************************
        ~Planner();

        //*********************************************************
        // Function: Planner (Copy Constructor)
        // Purpose: Copy constructor for planner class.
        // Params: other - Copy planner.
        //*********************************************************
        Planner(const Planner& other);

        //*********************************************************
        // Function: Planner (Assignment Operator)
        // Purpose: Assignment Constructor for planner class.
        // Params: other - Copy planner.
        //*********************************************************
        Planner& operator = (const Planner& other);
        
        //*********************************************************
        // Function: add
        // Purpose: Adds node to list.
        // Params: a - Assignment node thats being added.
        // Calls: sortByDue
        //*********************************************************
        void add(const Assignment a);

        //*********************************************************
        // Function: display
        // Purpose: Displays linked list to outs.
        // Params: outs - Specified output.
        //*********************************************************
        void display(std::ostream& outs)const;

        //*********************************************************
        // Function: find
        // Purpose: Finds specified node inside the linked list.
        // Params: hw_name - Name attached to specified node.
        //*********************************************************
        Assignment find(const std::string hw_name);

        //*********************************************************
        // Function: remove
        // Purpose: Removes specified node from the linked list.
        // Params: hw_name - Name attached to specified node.
        //*********************************************************
        void remove(const std::string hw_name);

        //*********************************************************
        // Function: waiting
        // Purpose: Counts number of assignments in the linked list.
        //*********************************************************
        int waiting();

        //*********************************************************
        // Function: due_next
        // Purpose: Finds assignment due next in the linked list.
        // Return: Number of assignments.
        //*********************************************************
        size_t due_next();

        //*********************************************************
        // Function: average_wait
        // Purpose: Finds average time until due date for entire list.
        // Return: Returns average wait time.
        //*********************************************************
        size_t average_wait();

        //*********************************************************
        // Function: oldest
        // Purpose: Finds oldest entered assignment in linked list.
        // Return: Time of oldest assignment.
        // Calls: findNewOrOld
        //*********************************************************
        size_t oldest() {return findNewOrOld(0);}

        //*********************************************************
        // Function: newest
        // Purpose: Finds newest entered assignment in linked list.
        // Return: Time of newest assignment.
        // Calls: findNewOrOld
        //*********************************************************
        size_t newest() {return findNewOrOld(1);}

        //*********************************************************
        // Function: find_all
        // Purpose: Finds all homework in list due before selected time.
        // Params: date - Selected time to check.
        //*********************************************************
        void find_all(const DateTime date);

        //*********************************************************
        // Function: load
        // Purpose: Inputs entire file into a linked list.
        // Params: ins - Selected input method.
        // Calls: sortByDue
        //*********************************************************
        void load(std::istream& ins);

        //*********************************************************
        // Function: save
        // Purpose: Outputs entire linked list into a file.
        // Params: outs - Selected output method.
        //*********************************************************
        void save(std::ostream& outs)const;

    private:
        // :D
        node* head;

        //*********************************************************
        // Function: sortByDue
        // Purpose: Bubble sorts linked list by due dates (Soon-Far).
        //*********************************************************
        void sortByDue();

        //*********************************************************
        // Function: findNewOrOld
        // Purpose: Bubble sorts linked list by entered dates,
        //          then returns either the first or last time
        //          based on the inputed parameter.
        // Params: nOrO - Used to choose either newest or oldest.
        // Return: Time of the newest or oldest entered date.
        //*********************************************************
        size_t findNewOrOld(const int nOrO);
};

#endif