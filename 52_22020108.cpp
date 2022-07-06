//Mohammad Ozair Tariq
//22020108
//CS 100
//Project
//Club Manager

#include <iostream>
#include <fstream>      //for using ofstream and ifstream to read, write and creat text files
#include <string>
#include <iomanip>      //to use the setw() function to set the width fo beautifying the system
#include <cstdlib>      //to be used for generating a random id number for a new member
#include <ctime>
#include <sstream>      //to use the str() function
using namespace std;

//Defining all the functions needed:
void menu();
void add_member();
void view_members();
void delete_member();
void show_member();
void generate_bill();
void booking_ticket();
void avengers();
void tom_and_jerry();
void fast_and_furious();
void superstar();
bool check_input(double movie);
bool ValidateOption(double Option_Validate);
void store_coordinates(int row, int col, string document_name);
int str_to_int(string x);
bool document_check(string document_name, int row, int column);
bool coordinate_check(int row, int column);

bool ValidateOption(double Option_Validate){
    if(Option_Validate < 1 || Option_Validate > 6){
        return false;
    }
    else if(cin.fail()){    //this will be true if a string is input instead of a decimal/integer
        string DummyOption;
        cin.clear();    //to reset cin
        getline(cin, DummyOption);    //store whatever was input as trash
        return false;
    }
    else{    //if input was not a string but a decimal/integer
        return true;
    }
}

void menu(){
    //Menu Options:
    double option = 0;

    //This block of code will print the entire meu and the options to select from:
    while(option != 6){
        cout << setw(78) << "THE LAHORE CANTONMENT CLUB\n\n";
        cout << setw(76) << "CLUB MANAGMENT SYSTEM\n\n";
        cout << setw(68) << "MAIN MENU:\n";
        cout << setw(82) << "1: View information of members\n";
        cout << setw(82) << "2: Add a new member           \n";
        cout << setw(82) << "3: Monthly Bill of members    \n";
        cout << setw(82) << "4: Delete an existing member  \n";
        cout << setw(82) << "5: Book a ticket for a movie  \n";
        cout << setw(82) << "6: Exit                       \n";
        cout << setw(82) << "     Your Option: ";
        cin >> option;      //taking input from the user
        cout << endl;

        bool validate = ValidateOption(option);    //storing input in validate

        if(option == 6){        //Running the specific function depending on the option input by the individual
            exit(-1);
        }
        else if (option == 5){
            booking_ticket();
        }
        else if (option == 4){
            delete_member();
        }
        else if (option == 3){
            generate_bill();
        }
        else if(option == 2){
            add_member();
        }
        else if(option == 1){
            view_members();
        }
        else if(!validate){        //Checking to see if the option entered is valid or not
            system("clear");
            cout << "Option is not valid. Re-enter your option: \n\n";
        }
    }
}

void view_members(){        //to view the existing members already in the database
    system("clear");        //clears the screen

    bool exist = false;    //for checking if there are any existing members

    ifstream document;     //ifstream used to read from document
    document.open("people.txt");    //used to open the text file called people.txt

    if(!document.is_open()){    //checks if file is open
        cout << "Document not open. Try Again!\n";    //Prompts user to first add members and then view them
    }
    else{
        cout << setw(68) << "Members " << endl;
        string info;

        while(getline(document, info)){
            exist = true;    //if info is extracted this is set to be true
            cout << "\t\t\t\t\t" << info << endl;
        }

        if(exist == false){    //if no info wil be extracted then it will be false
            cout << "\t\t\t\t\t\t There are currently no Members\n\n\n";
        }
    }

    document.close();    //closing the text file which was opened

    string now;    //to ask user what they want to do next
    cout << "PRESS 0 TO GO TO MENU" << endl;
    cout << "PRESS 6 TO EXIT" << endl;
    cin >> now;     //taking input from the user

    if(now == "0"){     //taking back to the main menu if user inputs 0
        system("clear");
        menu();
    }
    else if(now == "6"){        //exiting the program if user inputs 6
        exit(-1);
    }
    else{
        view_members();    //keeps running this function until valid input is received
    }
}

void add_member(){      //to add new members into the database
    system("clear");    //clears the screen

    ofstream member_list;
    member_list.open("people.txt", ios::app);    //this creates a text file in order to write data of new members into the file

    ifstream check_id;
    check_id.open("people.txt");    //opens members file to read the existing IDs of the members already created
    int ID;
    srand(time(0));     //initializing random number generator
    ID = rand();    //assigns a random value as the ID

    int id, p, q, r, s, t;    //p, q, r, s, t declared to maintain format only.
    while (check_id >> id >> p >> q >> r >> s >> t){    // runs as long as there is data in the file
        if (id == ID){    //checks if ID has been replicated
            ID = id + 1;
            break;
        }
    }

    check_id.close();       //closing the text file. We always have to close a text file are opening it

    member_list << ID << "\t";      //sending ID to the text file "people.txt" using member_list

    cout << endl << "Input First Name: ";

    string first_name;
    cin >> first_name;

    member_list << first_name << "\t";      //sending first name to the text file "people.txt" using member_list

    cout << "Input Last Name: ";

    string last_name;
    cin >> last_name;

    member_list << last_name << "\t";       //sending last name to the text file "people.txt" using member_list

    cout << "Input Age: ";

    int member_age;
    while(!(cin >> member_age)){    //validation check to make sure only integer values for the age are input
        cin.clear();
        cin.ignore(10000, '\n');    //this will only skip upto 10000 characters so it assumes that the user does not input a very long number and then move to the next line
        cout  << "Invalid input, try again" ;
    }

    member_list << member_age << "\t";    //sending age to the text file "people.txt" using member_list

    cout << "Input Mobile Number: (00000000000) ";

    string cell_number;
    cin.ignore();
    getline(cin,cell_number);

    member_list << cell_number  << "\t";    //sending phone number to the text file "people.txt" using member_list

    system("clear");        //clearing the screen

    cout << "Enter facility to be used by member: \n Option 1: Gym \n Option 2: Squash \n Option 3: Gym & Squash \n";
    int facility_used;

    while(true){    //validation check to make sure only integer values 1, 2 and are input
        cin >> facility_used;
        cin.clear();
        cin.ignore(10000, '\n');

        if(facility_used == 1 || facility_used == 2 || facility_used == 3){
            break;
        }
        else{
            cout  << "Invalid input, try again: ";
        }
    }

    member_list << facility_used  << "\t\n";

    system("clear");

    cout << "\n";
    cout << "A new member with ID number " << ID << " has been added to the club!\n\n";
    member_list.close();
}

void generate_bill(){
    system("clear");
    const int f_gym  = 20000;    //the charges of gym
    const int f_squash = 15000;    //the charges of squash

    ifstream document;
    document.open("people.txt");

    if(!document.is_open()){    //checks if document is open
        cout << "Document not open. Try Again." << endl;
    }
    else{
        int id;
        string first_name;
        string last_name;
        int member_age;
        string cell_number;
        int facility_used;
        cout << setw(70) << "Monthly Bills:";

        while(document >> id >> first_name >> last_name >> member_age >> cell_number >> facility_used){    //runs till info exists in document
            int charges = 0;
            if(facility_used == 3){    //gym and squash both
                charges = charges + f_gym + f_squash;
                cout << "\n\t\t\t\t\t\t" << id << "\t" << first_name << "\t" << last_name << "\t" << "Rs." << charges << endl << endl;
            }
            else if(facility_used == 2){    //only squash
                charges = charges + f_squash;
                cout << "\n\t\t\t\t\t\t" << id << "\t" << first_name << "\t" << last_name << "\t"  << "Rs." << charges  << endl << endl;
            }
            else if(facility_used == 1){    //only gym
                charges = charges + f_gym;
                cout << "\n\t\t\t\t\t\t" << id << "\t" << first_name << "\t" << last_name << "\t" << "Rs." <<  charges << endl << endl;
            }
        }
    }

    cout << "ENTER 0 TO GO TO MENU" << endl;
    cout << "ENTER 6 TO EXIT" << endl;
    string now;    //asks user what to do next
    cin >> now;

    if(now == "6"){
        exit(-1);
    }
    else if(now == "0"){
        system("clear");
    }
    else{
        generate_bill();    //keeps repeating till a valid input is provided
    }
}

void show_member(){    //function to display members for the delete function and check if there is any data in the file
    ifstream sdocument;
    sdocument.open("people.txt") ;

    int x = 0;
    int id;
    string first_name;
    string last_name;
    int member_age;
    string cell_number;
    int facility_used;

    cout << setw(70) << "Members:" << endl;

    while(sdocument >> id >> first_name >> last_name >> member_age >> cell_number >> facility_used){
        cout << "\t\t\t\t\t\t\t" << id << "\t" << first_name <<  "\t" << last_name  << endl;
        x++;
    }

    if(x == 0){
        system("clear");
        cout << "There are currently no members" << endl;
        menu();
    }

    sdocument.close();
}

void delete_member(){
    system("clear");

    bool member_ID = false;    //checks if the relevant member ID exists

    ofstream temp_doc;
    temp_doc.open("temporary.txt");    //temp file created which will store everything in the other file except contact being deleted

    ifstream document;
    document.open("people.txt") ;

    if(!document.is_open()){    //to check if the document is open
        cout << "Document not open. Try Again." << endl;
    } 
    else{
        show_member();
        int id;
        string first_name;
        string last_name;
        int member_age;
        string cell_number;
        int facility_used;
        int tempID;

        cout << "Enter ID to be removed: ";

        while(!(cin >> tempID)){
        cin.clear();
        cin.ignore(10000, '\n');
        cout  << "Invalid input, try again" << " ";
        }

        while(document >> id >> first_name >> last_name >> member_age >> cell_number >> facility_used){
            if(id != tempID){
                temp_doc << id << "\t" << first_name << "\t" << last_name << "\t" << member_age <<  "\t" << cell_number <<  "\t" << facility_used << endl;
            }
            else if(id == tempID){
                member_ID = true;
                continue;
            }
        }

        if(member_ID == false){
            cout << "Invalid ID" << endl;
        }
        else{
            cout << "Member Deleted Successfully" << endl;
        }

    }

    temp_doc.close();
    document.close();

    remove("people.txt");    //deleted the old file after copying the text to newer one named temporary.txt
    rename("temporary.txt","people.txt");    //temporary is renamed to the old file's name
    cout << endl;
}

bool check_input(double movie){
    if(movie < 1 || movie > 5){
        return false;
    }
    else if(cin.fail()){
        cin.clear();
        cin.ignore(10000, '\n');
        return false;
        }
    else{
        return true;
    }
}

void booking_ticket(){
    double movie;
    
    while(1){
        cout << "1: The Avengers: Endgame at 10:00 am \n";
        cout << "2: Tom & Jerry(2021) at 2:00 pm \n";
        cout << "3: Fast and Furious 8 at 7:00 pm \n";
        cout << "4: Superstar at 11:00 pm \n";
        cout << "5: Exit Ticket Booking \n";
        cout << "Your option: ";
        cin >> movie;
        cout << endl;
        
        if(movie == 5){
            return;
        }

        bool flag = check_input(movie);
        
        if(movie == 4){
            superstar();
        }
        else if(movie == 3){
            fast_and_furious();
        }
        else if(movie == 2){
            tom_and_jerry();
        }
        else if(movie == 1){
            avengers();
        }
        else if(!flag){
            cout << "Invalid Input, Re-enter your option: " << endl;
        }
    
        return;
    }
}

const int Xrows = 5;
const int Xcols = 5;
string X_plus_array[Xrows][Xcols];
bool seat = false;

void store_coordinates(int row, int col, string document_name){    //received a boolean variable
    X_plus_array[row][col] = "X\t";

    ofstream my_document;
    my_document.open(document_name.c_str(), ios::app);
    
    int frow, fcol;
    ifstream mydoc;
    mydoc.open(document_name.c_str());
   
    if(mydoc.is_open()){
        while(mydoc >> frow >> fcol){
            X_plus_array[frow][fcol] = "X\t";
        }
        
        int i = 0;
        while(i < Xrows){
            for(int j = 0; j < Xcols; j++){
                cout << X_plus_array[i][j];
            }
            i++;
            cout << endl;
        }
    }
    
    else cout << "Unable to open the file " << endl;

    my_document << row << " ";
    my_document << col << endl;
    cout << endl;
    cout << "Your seat has been reserved. " << endl;
    mydoc.close();
    my_document.close();
}

int str_to_int(string x){    //receive s and q as parameters
    int y = 0;
    stringstream str;
    str << x;    //send str x as string
    str >> y;    //str will convert x to an integer y
    return y;
}

bool document_check(string document_name, int row, int column){
    ofstream my_document;
    my_document.open(document_name.c_str(), ios::app);
    
    string line;
    ifstream mydoc;
    mydoc.open(document_name.c_str());    //use of c-string, which only has array of characters
    
    if(mydoc.is_open()){
        while(getline(mydoc,line)){    //read coordinates from the file, line by line
            string s(1,line[0]);    //stores row coordinate
            string q(1,line[2]);    //stores column coordinate
            int row_doc = str_to_int(s);    //sending input to str2int function, received the int coord
            int col_doc = str_to_int(q);    //sending column coordinate to the function
            
            if(row == row_doc && column == col_doc){
                return false;
            }
        }
    }
    else{
        cout << "Unable to open the file " << endl;
    }
    mydoc.close();
    my_document.close();
    return true;
}

bool coordinate_check(int row, int column){
    if(row < 0 || row > 4 || column < 0 || column > 4){
        return false;
    }
    else if(cin.fail()){
        cin.clear();
        cin.ignore(10000, '\n');
        return false;
    }
    else{
        return true;
    }
}

void avengers(){
    int row, col;
    
    int i = 0;
    while(i < Xrows){
        for(int j = 0; j < Xcols; j++){
            X_plus_array[i][j] = "[]\t";
        }
        i++;
    }
    
    while(seat == 0){
        cout << "Enter row from 0 to 4:\n";
        cin >> row;
        cout << "Enter column from 0 to 4:\n";
        cin >> col;
        
        bool flag = coordinate_check(row, col);
        if(!flag){
            cout << "Invalid Input, Re-enter your option: " << endl;
        }
        else{
            seat = document_check("avengers.txt", row, col);    //document_check will return a boolean variable
            if(seat == false){
                cout << endl;
                cout << "Seat occupied, Re-enter your coordinates: \n";
                }
            //seat occupied due to which user will be required to re-enter the coordinates
        }
    }
    //else if document_check returns true, which means no coordinates were found and coordinates will be stored using the store_coordinate function
    store_coordinates(row, col, "avengers.txt"); //seat == true
    seat = false;
}

void tom_and_jerry(){
    int row, col;
    
    int i = 0;
    while(i < Xrows){
        for(int j = 0; j < Xcols; j++){
            X_plus_array[i][j] = "[]\t";
        }
        i++;
    }
    
    while(seat == 0){
        cout << "Enter row from 0 to 4:\n";
        cin >> row;
        cout << "Enter column from 0 to 4:\n";
        cin >> col;
        
        bool flag = coordinate_check(row, col);
        if(!flag){
            cout << "Invalid Input, Re-enter your option: " << endl;
        }
        else{
            seat = document_check("tom_and_jerry.txt", row, col);    //document_check will return a boolean variable
            if(seat == false){
                cout << endl;
                cout << "Seat occupied, Re-enter your coordinates: \n";
                }
            //seat occupied due to which user will be required to re-enter the coordinates
        }
    }
    //else if document_check returns true, which means no coordinates were found and coordinates will be stored using the store_coordinate function
    store_coordinates(row, col, "tom_and_jerry.txt"); //seat == true
    seat = false;
}

void fast_and_furious(){
    int row, col;
    
    int i = 0;
    while(i < Xrows){
        for(int j = 0; j < Xcols; j++){
            X_plus_array[i][j] = "[]\t";
        }
        i++;
    }
    
    while(seat == 0){
        cout << "Enter row from 0 to 4:\n";
        cin >> row;
        cout << "Enter column from 0 to 4:\n";
        cin >> col;
        
        bool flag = coordinate_check(row, col);
        if(!flag){
            cout << "Invalid Input, Re-enter your option: " << endl;
        }
        else{
            seat = document_check("fast_and_furious.txt", row, col);    //document_check will return a boolean variable
            if(seat == false){
                cout << endl;
                cout << "Seat occupied, Re-enter your coordinates: \n";
                }
            //seat occupied due to which user will be required to re-enter the coordinates
        }
    }
    //else if document_check returns true, which means no coordinates were found and coordinates will be stored using the store_coordinate function
    store_coordinates(row, col, "fast_and_furious.txt"); //seat == true
    seat = false;
}

void superstar(){
    int row, col;
    
    int i = 0;
    while(i < Xrows){
        for(int j = 0; j < Xcols; j++){
            X_plus_array[i][j] = "[]\t";
        }
        i++;
    }
    
    while(seat == 0){
        cout << "Enter row from 0 to 4:\n";
        cin >> row;
        cout << "Enter column from 0 to 4:\n";
        cin >> col;
        
        bool flag = coordinate_check(row, col);
        if(!flag){
            cout << "Invalid Input, Re-enter your option: " << endl;
        }
        else{
            seat = document_check("superstar.txt", row, col);    //document_check will return a boolean variable
            if(seat == false){
                cout << endl;
                cout << "Seat occupied, Re-enter your coordinates: \n";
                }
            //seat occupied due to which user will be required to re-enter the coordinates
        }
    }
    //else if document_check returns true, which means no coordinates were found and coordinates will be stored using the store_coordinate function
    store_coordinates(row, col, "superstar.txt"); //seat == true
    seat = false;
}

//Main function starts here:
int main(){
    
    menu();
    
}