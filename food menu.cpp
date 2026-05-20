//Name: miqdad Osama
//ID: 451115067
//group: 6013
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <unordered_map>
const int limit = 10;
using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::fstream;
using std::ifstream;
using std::ios;
using std::ofstream;
using std::setw;
using std::string;

struct mealData{

    int ID;
    string name;
    double price;
    string category;
};

//-----------------------------------------------------
// Linked list
//-----------------------------------------------------

// linked list for add, edit, del, print, search and exit

class Trach;
class menuOperation{

private:
    struct menuLink
    {

        mealData *meal;
        menuLink *link;
    } *mLink;

    std::unordered_map<int , mealData*> hashmap; //hash table data structure

public:
    menuOperation(); // for initializ the pointer
    void createNewNode_Method(mealData *meal, fstream &Myfile, int IDMeal, string nameMeal, double priceMeal, string categoryMeal);
    void write_to_file(mealData *meal, fstream &Myfile, int IDMeal, string nameMeal, double priceMeal, string categoryMeal);
    void FileToLinkList(mealData *meal, fstream &Myfile);                  // convert the file into linklist
    void addNewMeal(mealData *meal, fstream &Myfile);                      // for add new meal to menu
    void editMealData(mealData *meal, fstream &Myfile, int IDmatch);       // for edit the meal information
    void SearchMeal(Trach *t, mealData *meal, fstream &Myfile, int IDKey); // For seacrch for a specific meal
    void del(Trach *t, mealData *meal, fstream &Myfile, int IDKey);        // for delete meal information
    void displayMenu(mealData *meal);                                      // for display the mean
    ~menuOperation();
};

//-----------------------------------------------------
// Stack
//-----------------------------------------------------

// Stack for saving the deleted meals
class Trach{

private:
    mealData *arr[limit];
    int top;

public:
    Trach();
    void pushToTrach(mealData *meal);
    void popFromTrach(menuOperation *menuObj, mealData *meal, fstream &Myfile, int IDkey);
};

//---------------------------------
// function related to Trach "Stack"
//--------------------------------

Trach::Trach(){

    top = -1;
}

void Trach::pushToTrach(mealData *meal){

    if (top == limit - 1)
    {

        cout << "Sorry, the trach is full" << endl;
        return;
    }

    top++;
    arr[top] = new mealData(*meal);
}

void Trach::popFromTrach(menuOperation *menuObj, mealData *meal, fstream &Myfile, int IDkey){

    int IDStack;
    string nameStack;
    double priceStack;
    string categoryStack;

    if (top == -1){

        cout << "The trach is empty" << endl;
        return;
    }

    for (int i = top; i >= 0; i--){

        if (arr[i]->ID == IDkey){

            IDStack = arr[i]->ID;
            nameStack = arr[i]->name;
            priceStack = arr[i]->price;
            categoryStack = arr[i]->category;

            menuObj->createNewNode_Method(meal, Myfile, IDStack, nameStack, priceStack, categoryStack);
            menuObj->write_to_file(meal, Myfile, IDStack, nameStack, priceStack, categoryStack);

            delete arr[i];
            top--;
            return;
        }
    }
}

//---------------------------------
// function related to menuOperation "Linked list"
//--------------------------------

menuOperation::menuOperation(){

    mLink = NULL;
}

void menuOperation::createNewNode_Method(mealData *meal, fstream &Myfile, int IDMeal, string nameMeal, double priceMeal, string categoryMeal){

    menuLink *temp, *r;
    // if the list is empty
    if (mLink == NULL){

        meal->ID = IDMeal;
        meal->name = nameMeal;
        meal->price = priceMeal;
        meal->category = categoryMeal;

        temp = new menuLink;
        temp->meal = new mealData;
        *(temp->meal) = *meal;
        temp->link = NULL;
        mLink = temp;

        hashmap[IDMeal] = temp->meal;
    }

    // if we have nodes are exiting
    else{

        temp = mLink;
        while (temp->link != NULL){

            temp = temp->link;
        }

        meal->ID = IDMeal;
        meal->name = nameMeal;
        meal->price = priceMeal;
        meal->category = categoryMeal;

        r = new menuLink;
        r->meal = new mealData;
        *(r->meal) = *meal;
        ;
        r->link = NULL;
        temp->link = r;

        hashmap[IDMeal] = r->meal;
    }
}

void menuOperation::write_to_file(mealData *meal, fstream &Myfile, int IDMeal, string nameMeal, double priceMeal, string categoryMeal){

    Myfile.open("MenuFile.txt", ios::app);
    Myfile << IDMeal << "," << nameMeal << "," << priceMeal << "," << categoryMeal << endl;
    Myfile.close();
}

void menuOperation::FileToLinkList(mealData *meal, fstream &Myfile){

    Myfile.open("MenuFile.txt", ios::in);
    string IDTemp, nameTemp, priceTemp, categoryTemp;

    if (Myfile.peek() == ifstream::traits_type::eof()){

        cout << "\n-----------------------------------------" << endl;
        cout << "There is no \"content inside a file\" !!" << endl;
        cout << "-----------------------------------------" << endl;
        Myfile.close();
        return;
    }

    else{

        while (getline(Myfile, IDTemp, ',')){

            getline(Myfile, nameTemp, ',');
            getline(Myfile, priceTemp, ',');
            getline(Myfile, categoryTemp);

            int IDfinal = stoi(IDTemp);
            double pricefinal = stod(priceTemp);

            menuOperation::createNewNode_Method(meal, Myfile, IDfinal, nameTemp, pricefinal, categoryTemp);
        }
    }

    Myfile.close();
}

void menuOperation::addNewMeal(mealData *meal, fstream &Myfile){

    int IDMeal;
    string nameMeal;
    double priceMeal;
    string categoryMeal;

    cout << "Pleas Enter the meal information: " << endl;
    cout << "Enter ID of the meal: ";
    cin >> IDMeal;

    cout << "\nEnter Name of the meal: ";
    cin >> nameMeal;

    cout << "\nEnter price of the meal: ";
    cin >> priceMeal;

    cout << "\nEnter category of the meal: ";
    cin >> categoryMeal;

    meal->ID = IDMeal;
    meal->name = nameMeal;
    meal->price = priceMeal;
    meal->category = categoryMeal;

    menuOperation::createNewNode_Method(meal, Myfile, IDMeal, nameMeal, priceMeal, categoryMeal);
    menuOperation::write_to_file(meal, Myfile, IDMeal, nameMeal, priceMeal, categoryMeal);

    cout << "\nThe new meal was added successfully" << endl;
}

void menuOperation::editMealData(mealData *meal, fstream &Myfile, int IDmatch){

    Myfile.open("MenuFile.txt",ios::in);

    if (mLink == NULL){

        char YesOrNo;
        cout << "The menu is empty, you want to add new meals [Y/N]: ";
        cin >> YesOrNo;

        do{
            YesOrNo = (char)toupper(YesOrNo);

            if (YesOrNo == 'Y'){

                cout << "\n" << setw(50) << "---------------Welcome to add function menu:---------------" << endl;
                menuOperation::addNewMeal(meal, Myfile);
            }

            if (YesOrNo == 'N'){

                cout << "\n" << "Good Bye :)" << endl;
                return;
            }
        } while (YesOrNo != 'Y' && YesOrNo != 'N');
    }

    fstream tempFile;
    tempFile.open("tempFile.txt", ios::out);

    if (tempFile.fail()){

        cerr << "Error creating a file is falied" << endl;
        cerr << "The edit operation is failed !!" << endl;
        Myfile.close();
        return;
    }

    int ch;
    string IDTemp, nameTemp, priceTemp, categoryTemp;

    bool found = false;

    while (getline(Myfile, IDTemp, ',')){

        getline(Myfile, nameTemp, ',');
        getline(Myfile, priceTemp, ',');
        getline(Myfile, categoryTemp);

        int IDtempOLD = stoi(IDTemp);

        if (IDmatch == IDtempOLD){

            found = true;

            do{
                cout << "\nWhat is the information you want to edit for a specific meal:\n"
                    << "[1] Edit Name \n"
                    << "[2] Edit Price \n"
                    << "[3] Edit category \n"
                    << "[4] Exit \n"
                    << "Enter the Number: ";
                cin >> ch;
                cout << endl;

                if (ch == 1){

                    cout << "Enter the new Name for the meal: ";
                    cin >> nameTemp;
                }

                else if (ch == 2){

                    cout << "Enter the new price for the meal: ";
                    cin >> priceTemp;
                }

                else if (ch == 3){

                    cout << "Enter the new category for the meal: ";
                    cin >> categoryTemp;
                }

                else{

                    cerr << "Sorry, Wrong number :(" << endl;
                }
            } while (ch != 4);

            menuLink *tempNode = mLink;
            while (tempNode != NULL){

                if(tempNode->meal->ID == IDmatch){

                    tempNode->meal->name = nameTemp;
                    tempNode->meal->price = stod(priceTemp);
                    tempNode->meal->category = categoryTemp;

                    hashmap[IDmatch] = tempNode->meal;

                    break;
                }
                tempNode = tempNode->link;
            }
        }

        tempFile << IDTemp << "," << nameTemp << "," << priceTemp << "," << categoryTemp << endl;
    }

    Myfile.close();
    tempFile.close();

    if(!found){

        cout << "Sorry, Wrong ID Number :(" << endl;
        remove("tempFile.txt");
        return;
    }

    Myfile.open("MenuFile.txt", ios::out);
    tempFile.open("tempFile.txt", ios::in);

    if(Myfile.is_open() && tempFile.is_open()){

        while (getline(tempFile, IDTemp, ',')){

            getline(tempFile, nameTemp, ',');
            getline(tempFile, priceTemp, ',');
            getline(tempFile, categoryTemp);

            Myfile << IDTemp << "," << nameTemp << "," << priceTemp << "," << categoryTemp << endl;
         }
    }

    Myfile.close();
    tempFile.close();

    remove("tempFile.txt");

    cout << "Meal updated successfully !!" << endl;
}

void menuOperation::SearchMeal(Trach * t, mealData * meal, fstream & Myfile, int IDKey){

    char ch;

    if (hashmap.find(IDKey) != hashmap.end()){

        mealData* foundMeal = hashmap[IDKey];

        cout << "ID: " << foundMeal->ID << " | "
            << "Name: " << foundMeal->name << " | "
            << "price: " << foundMeal->price << " | "
            << "Category: " << foundMeal->category << endl;

        cout << "\nDo you want to delete this meal [Press Y]: ";
        cin >> ch;
        ch = toupper(ch);
        if (ch == 'Y'){

             menuOperation::del(t, meal, Myfile, IDKey);
            return;
        }

        else{

            return;
        }
    }

    cerr << "Sorry, Wrong ID :(" << endl;
    cout << "Do you want to show the menu to get better information [Press Y]: ";
    cin >> ch;
    ch = toupper(ch);
    if (ch == 'Y'){

        menuOperation::displayMenu(meal);
    }

    else{

        return;
    }
}

void menuOperation::del(Trach * t, mealData * meal, fstream & Myfile, int IDKey){

    remove("MenuFile.txt");
    menuLink *temp, *old;
    temp = mLink;

    while (temp != NULL){

        if (temp->meal->ID == IDKey){

            if (temp == mLink){

                mLink = temp->link;
            }

            else{

                old->link = temp->link;
            }

            t->pushToTrach(temp->meal);
            menuLink *toDelete = temp;
            delete toDelete;
            hashmap.erase(IDKey);
            break;
        }

        else{

            old = temp;
            temp = temp->link;
        }
    }

    menuLink *afterDel = mLink;

    while (afterDel != NULL){

        menuOperation::write_to_file(meal, Myfile,
            afterDel->meal->ID, afterDel->meal->name,
            afterDel->meal->price, afterDel->meal->category);

        afterDel = afterDel->link;
    }
}

void menuOperation::displayMenu(mealData * meal){

    if (mLink == NULL){

        cout << "The menu is empty" << endl;
        return;
    }

    menuLink *temp = mLink;
    cout << "\n\nFood menu------------------------------------" << endl;

    while (temp != NULL){

        cout << "|" << "ID: " << temp->meal->ID << "  "
            << "Name: " << temp->meal->name << "  "
            << "price: " << temp->meal->price << "  "
            << "Category: " << temp->meal->category << endl;

            temp = temp->link;
    }

    cout << "-----------------------------------------------" << endl;
}

menuOperation::~menuOperation(){

    menuLink *temp = mLink;
    while (temp != NULL){

        menuLink *next = temp->link;
        delete temp->meal;
        delete temp;
        temp = next;
    }
 }

// main function
bool checkIffileIsOpen(fstream & Myfile);

int main(){

    menuOperation MenuObject;
    Trach t;
    mealData m;
    int ch, ID;

    fstream Myfile;
    bool result = checkIffileIsOpen(Myfile);

    if (result == true){

        MenuObject.FileToLinkList(&m, Myfile);

        cout << endl;

        cout << setw(50) << "------Menu operation------ " << "\n"
        << "[1] Add new meal \n"
        << "[2] Eddit existing meal information \n"
        << "[3] Search \n"
        << "[4] Delete meal for menu \n"
        << "[5] Undo the delete operation\n"
        << "[6] Dsiplay the menu \n"
        << "[7] exit \n"
        << "Enter the number: ";
        cin >> ch;
        cout << endl;

        do{
            if(ch == 1){

                MenuObject.addNewMeal(&m, Myfile);
            }

            else if (ch == 2){

                cout << "Enter the meal ID: ";
                cin >> ID;

                MenuObject.editMealData(&m, Myfile, ID);
            }

            else if (ch == 3){

                cout << "Enter the meal ID: ";
                cin >> ID;

                MenuObject.SearchMeal(&t, &m, Myfile, ID);
            }

            else if (ch == 4){

                cout << "Enter the meal ID: ";
                cin >> ID;

                MenuObject.SearchMeal(&t, &m, Myfile, ID);
            }

            else if (ch == 5){

                cout << "Enter the meal ID: ";
                cin >> ID;

                t.popFromTrach(&MenuObject, &m, Myfile, ID);
            }

            else if (ch == 6){

                MenuObject.displayMenu(&m);
            }

            cout << endl;
            cout << setw(50) << "------Welcome back :)------ " << "\n"
                << "[1] Add new meal \n"
                << "[2] Eddit existing meal information \n"
                << "[3] Search \n"
                << "[4] Delete meal for menu \n"
                << "[5] Undo the delete operation\n"
                << "[6] Dsiplay the menu \n"
                << "[7] exit \n"
                << "Enter the number: ";
            cin >> ch;
            cout << endl;

        } while (ch != 7);
    }

    else{

        cout << "Sorry, somthing want wrong :(" << endl;
    }

    return 0;
}

// To check if the file is open or not
bool checkIffileIsOpen(fstream & Myfile){

    Myfile.open("MenuFile.txt" , ios::in | ios::out);

    if (Myfile.is_open()){

        cout << "This file was created successfully!!\n"
            << "The program is starting ....\n"
            << endl;
        Myfile.close();
        return true;
    }

    else{

        ofstream createNewFile("MenuFile.txt");
        if(createNewFile.is_open()){
            cout << "File 'MenuFile.txt' was not found, so it was created successfully\n " << endl;
            createNewFile.close();
            return true;
        }

        else{

            cerr << "Error: could not create the file. Check folder permissions." << endl;
            return false;
        }
    }
}
