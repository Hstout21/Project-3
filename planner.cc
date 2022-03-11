/*************************************************************************
      Hunter Stout   -   3/9/2022
      planner.cc     -   Class Implementation File.
*************************************************************************/
#include <vector>
#include "planner.h"

using namespace std;

//############ B I G   3 ############

Planner::Planner() { //Constructor
    head = NULL;
}

Planner::~Planner() { //Deconstructor
    node* decon_ptr;
    while (head != NULL) {
        decon_ptr = head;
        head = head -> link();
        delete decon_ptr;
    }
}

Planner::Planner(const Planner& other) { //Copy Constructor
    if (other.head == NULL) { //Empty file.
        head = NULL;
        return;
    }
    else {
        node *src, *dest; //Normal copy route.
        head = new node(other.head -> data());
        src = other.head -> link();
        dest = head;
        while (src != NULL) {
            dest -> set_link(new node(src -> data()));
            src = src -> link();
            dest = dest -> link();
        }
        delete src;
        delete dest;
    }
}

Planner& Planner::operator = (const Planner& other) { //Assignment Constructor
    if (this == &other) { //Copy check.
        return *this;
    }
    //Deconstructor
    node* decon_ptr;
    while (head != NULL) {
        decon_ptr = head;
        head = head -> link();
        delete decon_ptr;
    }
    //Copy Constructor
    if (other.head == NULL) {
        head = NULL;
    }
    else {
        node *src, *dest;
        head = new node(other.head -> data());
        src = other.head -> link();
        dest = head;
        while (src != NULL) {
            dest -> set_link(new node(src -> data()));
            src = src -> link();
            dest = dest -> link();
        }
        delete src;
        delete dest;
    }
    return *this;
}

//########## P R I V A T E ##########

void Planner::sortByDue() {
    vector<Assignment> a_list;
    int counter = 0;
    const node* cursor = head;

    //Copies data into vector
    while(cursor != NULL){
        a_list.push_back(cursor -> data());
        counter++;
        cursor = cursor -> link();
    }

    //Deletes linked list.
    node *temp = head, *next_ptr;
    while(temp != NULL){
        next_ptr = temp-> link();
        delete temp;
        temp = next_ptr;
    }
    delete temp;
    delete head;
    delete next_ptr;
    head = NULL;

    //Bubble sorts vector by due date.
    Assignment temp_assignment;
    bool done = false;
    while (!done) {
        done = true;
        for (int i = 0; i < counter - 1; i++) {
            if (a_list[i + 1].get_due() < a_list[i].get_due()) {
                temp_assignment = a_list[i];
                a_list[i] = a_list[i + 1];
                a_list[i + 1] = temp_assignment;
                done = false;
            }
        }
    }

    //Rebuilds linked list
    for (int i = 0; i < counter; i++) {
        if (head == NULL) { //Starts list.
            head = new node(a_list[i]);
        }
        else { //Route for rest of the list.
            node* tmp_cursor = head;
            while (tmp_cursor -> link() != NULL) {
                tmp_cursor = tmp_cursor -> link();
            }
            tmp_cursor -> set_link(new node(a_list[i]));
            delete tmp_cursor;
        }
    }

    //Delete vector and frees memory.
    a_list.clear();
    a_list.shrink_to_fit();
    counter = 0;
}

size_t Planner::findNewOrOld(const int nOrO) {
    size_t time = 0;
    if (head == NULL) { //Empty list route.
        return time;
    }
    else { //Normal list route.
        vector<Assignment> a_list;
        int counter = 0;
        const node* cursor = head;

        //Copies data into vector.
        while(cursor != NULL){
            a_list.push_back(cursor -> data());
            counter++;
            cursor = cursor -> link();
        }

        //Bubble sorts vector by entered date.
        Assignment temp_assignment;
        bool done = false;
        while (!done) {
            done = true;
            for (int i = 0; i < counter - 1; i++) {
                if (a_list[i + 1].get_entered() < a_list[i].get_entered()) {
                    temp_assignment = a_list[i];
                    a_list[i] = a_list[i + 1];
                    a_list[i + 1] = temp_assignment;
                    done = false;
                }
            }
        }

        if (nOrO == 0) { //Oldest entered assignment route.
            time = a_list[0].minutes_waiting();
        }
        else if (nOrO == 1) { //Newest entered assignment route.
            for (int i = 0; i < counter; i++) {
                if (i == counter - 1) { //Last element
                    time = a_list[i].minutes_waiting();
                }
            }
        }

        if (time > 1000000000) { //Error checks for past due date.
            time = 0; 
        }

        //Deletes vector and frees memory.
        a_list.clear();
        a_list.shrink_to_fit();
        delete cursor;
    }
    return time;
}

//####### L O A D  &  S A V E #######

void Planner::load(std::istream& ins) {
    Assignment placeholder;
    int test = 0;
    //Loop loads entire file.
    while (ins >> placeholder) {
        if (head == NULL) { //Starts list.
            head = new node(placeholder);
            test++;
        }
        else { //Route for rest of the list.
            node* cursor = head;
            while (cursor -> link() != NULL) {
                cursor = cursor -> link();
            }
            cursor -> set_link(new node(placeholder));
            delete cursor;
            test++;
        }
    }
    sortByDue(); //Sorts linked list by due date.
}

void Planner::save(std::ostream& outs)const {
     const node* cursor = head;
     while(cursor != NULL){ //Saves entire list to file.
        outs << cursor -> data();
        cursor = cursor -> link();
     }
     delete cursor;
}

//########## H E L P E R S ########## (MAIN HELPERS)

void Planner::add(const Assignment a) {
    if (head == NULL) { //Starts list.
        head = new node(a);
    }
    else { //Route for started list.
        node* cursor = head;
        while (cursor -> link() != NULL) {
            cursor = cursor -> link();
        }
        cursor -> set_link(new node(a));
        sortByDue(); //Sorts list by due date.
        delete cursor;
    }
}

void Planner::remove(const string hw_name) {
    const node* cursor = head;
    vector<Assignment> a_list;
    Assignment a;
    int v_size = 0;

    //Copies linked list into vector, ignores removed elements.
    while(cursor != NULL){
        a = cursor -> data();
        if (a.get_name() != hw_name) {
            a_list.push_back(a);
            v_size++;
        }
        cursor = cursor -> link();
    }
    delete cursor;

    //Deletes linked list.
    node *temp = head, *next_ptr;
    while(temp != NULL){
        next_ptr = temp-> link();
        delete temp;
        temp = next_ptr;
    }
    delete temp;
    delete head;
    delete next_ptr;
    head = NULL;

    //Rebuilds new linked list.
    for (int i = 0; i < v_size; i++) {
        if (head == NULL) { //Starts list.
            head = new node(a_list[i]);
        }
        else { //Route for started list.
            node* tmp_cursor = head;
            while (tmp_cursor -> link() != NULL) {
                tmp_cursor = tmp_cursor -> link();
            }
            tmp_cursor -> set_link(new node(a_list[i]));
            delete tmp_cursor;
        }
    }

    //Deletes vector & frees memory.
    a_list.clear();
    a_list.shrink_to_fit();
}

void Planner::display(ostream& outs)const {
    const node* cursor = head;
    while(cursor != NULL){ //Displays list to cout.
        cout << cursor -> data();
        cursor = cursor -> link();
    }
    delete cursor;
}

Assignment Planner::find(const std::string hw_name) {
    const node* cursor = head;
    Assignment a, notFound;
    while(cursor != NULL){ //Checks entire list.
        a = cursor -> data();
        if (a.get_name() == hw_name) { //Checks for entered name.
            delete cursor;
            return a; //Returns if found.
        }
        cursor = cursor -> link();
    }
    delete cursor;
    cout << endl << "No assignments found with this name!" << endl << endl;
    return notFound; //Returns blank if not found.
}

//########## H E L P E R S ########## (TIME HELPERS)

int Planner::waiting() {
     const node* cursor = head;
     int counter = 0;
     while(cursor != NULL){ //Counts how many items are in the list.
         counter++;
         cursor = cursor -> link();
     }
     delete cursor;
     return counter;
}

size_t Planner::due_next() {
    size_t time = 0;
    if (head == NULL) { //Empty list.
        cout << endl << "Error: Please add an assignment to see what is due next." << endl;
    }
    else { //1 or more item in list.
        Assignment a = head -> data();
        time = a.minutes_til_due(); //Grabs homework due next.
    }
    if (time > 1000000000) { //Error checks for past due.
        time = 0; 
    }
    return time;
}

size_t Planner::average_wait() {
    const node* cursor = head;
    size_t time = 0, total_time = 0, counter = 0;
    Assignment a;
    while(cursor != NULL){ //Runs through entire list.
        a = cursor -> data();
        time = a.minutes_til_due();
        if (time > 1000000000) { //Error checks for past due.
            time = 0;
            counter--; //Adjusts assignment count if number is invalid.
        }
        total_time += time; //Adds up all times unless invalid.
        counter++;
        cursor = cursor -> link();
    }
    delete cursor;
    return (total_time / counter); //Returns average.
}

void Planner::find_all(const DateTime date) {
     const node* cursor = head;
     Assignment a;
     int counter = 0;
     cout << endl;
     while(cursor != NULL){ //Runs through entire list.
         a = cursor -> data();
         if (a.get_due() < date) {
            cout << cursor -> data(); //Outputs homework due before selected time.
            counter++;
         }
         cursor = cursor -> link();
     }
     if (counter == 0) { //Output for nothing found.
         cout << "No assignments due before specified date." << endl << endl;
     }
     delete cursor;
}