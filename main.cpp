#include <iostream>
//#include <conio.h>
#include <string.h>
#include <fstream>
#include <queue>
#include <string>
#include <stdlib.h>
#include <ctime>
#include <sstream>
#include <stack>
using namespace std;

void civilian(void);
void police(void);
void referenceNumber(void);
void polCreateAccount(void);
void polExistingAccount(void);
void addToList(string,string,string,string);
void profile(void);
void PNPheader(void);
void createFile(void);
void accountsFile(string, int, string, string);
void complaintsFile(queue<string>,queue<string>,queue<string>,queue<string>,queue<string>);
void criminalEntry(void);
void displayAllRecords(void);
void displayList(string, string);
int verification(int, string, string);
void showInformation(string,string);
void searchByName(string);
void searchByReference(string);
void removeRecord(string,string);
void editRecord(string,string);
bool checkReferenceRep(string);
void dateRecords(void);
void getDates(void);
string referenceNum;
int e_badgeNo;
stack<int> dates;
stack<string> names, months, days, years;
void recPerDay(void);
void recPerMonth(void);
void recPerYear(void);
void printInText(void);
void policeInCharge(void);

struct police_info {
    string policeName;
    int badgeNo;
    string station;
    string password;
    police_info *next;
}; police_info *policeHead = NULL;

struct criminalRecords {
    string lastName;
    string firstName;
    string alias;
    string reference;
    string nationality;
    string citizen;
    string gender;
    float height;
    float weight;
    string eyeColor;
    string hairColor;
    string birthdate;
    int age;
    string features;
    string arrestInfo;
    string currentStatus;
    string entryDate;
    criminalRecords *next;
}; criminalRecords *crimHead = NULL;
void getInformation(string,string,criminalRecords *tail, criminalRecords *temp);
void editTextfile(string,string,criminalRecords *temp);

int main(){
    
    int user;
    PNPheader();
    cout << "NOTE: This program is case-sensitive.\n";
    cout << endl;
    cout << "[1] User" << endl;
    cout << "[2] Police" << endl;
    cout << "Enter choice: ";
    cin >> user;
    if (user == 1){
        civilian();
    } else if (user == 2){
        police();
        return 0;
    } else{
        cout << endl << "Invalid Input.";
        return 0;
    }
}

void civilian() {
    string q_compName, q_compNo, q_compEmail, q_accused, q_complaint;
    int userCh;
    queue<string> compName;
    queue<string> compNo;
    queue<string> compEmail;
    queue<string> accused;
    queue<string> complaint;
    
    cout << endl << "[1] Complain" << endl;
    cout << "[2] Exit" << endl;
    cout << "Enter choice: ";
    cin >> userCh;
    if (userCh == 1){
        char ans;
        ans = 'Y';
        while (ans == 'y' or ans == 'Y') {
            cout << endl << "Enter Your Complete Name: ";
            cin >> ws;
            getline(cin, q_compName);
            compName.push(q_compName);
            cout << "Enter Your Contact Number: ";
            cin >> q_compNo;
            compNo.push(q_compNo);
            cout << "Enter Your Email Address: ";
            cin >> q_compEmail;
            compEmail.push(q_compEmail);
            cout << "Enter Name of Accused: ";
            cin >> ws;
            getline(cin, q_accused);
            accused.push(q_accused);
            cout << "Enter Your Complaint: ";
            cin >> ws;
            getline(cin, q_complaint);
            complaint.push(q_complaint);
            
            cout << "\nWould you like to send in another complaint? Y/N ";
            cin >> ans;
            
            while (ans != 'n' and ans != 'N') {
                if (ans == 'y' or ans == 'Y') {
                    break;
                } else {
                    cout << "Invalid input";
                    cout << "\nWould you like to send in another complaint? Y/N ";
                    cin >> ans;
                }
            }
        }
        complaintsFile(compName,compNo,compEmail,accused,complaint);
        cout << endl << "Thank you for using the program!";
        cout << endl << "We'll get back to you once your complain is processed.\n";
    } else {
        cout << endl << "Thank you for using the program!\n";
    }
}

void police(void) {
    int polCh;
    cout << endl <<"[1] Log In" << endl;
    cout << "[2] Sign Up" << endl;
    cout << "Enter choice: ";
    cin >> polCh;
    if (polCh == 1){
        polExistingAccount();
    } else if (polCh == 2) {
        polCreateAccount();
    }
}

void menu(void) {
    int choice;
    string text;
    ifstream complaints("Complaints.txt");
    string line;
    char review;
    complaints >> line;
    if (line != "") {
        cout << "\nComplaints received!" << endl;
        cout << "NOTE: Once reviewed, complaints will be cleared." << endl;
        cout << "Would you like to review them? Y/N";
        cin >> review;
        if (review == 'y' or review == 'Y') {
            cout << endl << endl << "COMPLAINTS\n\n" << line;
            while (getline(complaints,line)) {
                cout << line << endl;
            }
            ofstream complaint("Complaints.txt");
            complaint << "";
            complaint.close();
        }
    }
    cout << "\nMENU" << endl;
    cout << "[1] In Custody List" << endl;
    cout << "[2] Wanted List" << endl;
    cout << "[3] Missing Persons List" << endl;
    cout << "[4] On Bail List" << endl;
    cout << "[5] Add Record" << endl;
    cout << "[6] View All Records" << endl;
    cout << "[7] View Records by Date" << endl;
    cout << "[8] View Police-In-Charge" << endl;
    cout << "[9] Search Record" << endl;
    cout << "[10] Log Out" << endl;
    cout << "[11] Exit\n> ";
    cin >> choice;
    
    switch (choice) {
        case 1:
            displayList("In Custody","LIST OF PERSONS IN CUSTODY");
            break;
        case 2:
            displayList("Wanted","LIST OF WANTED PERSONS");
            break;
        case 3:
            displayList("Missing","LIST OF MISSING PERSONS");
            break;
        case 4:
            displayList("On Bail","LIST OF PERSONS ON BAIL");
            break;
        case 5:
            char answer;
            answer = 'y';
            while (answer == 'Y' or answer == 'y') {
                referenceNumber();
                criminalEntry();
                cout << "\nWould you like to add another record? ";
                cin >> answer;
                referenceNum = "";
            }
            createFile();
            menu();
            break;
        case 6:
            displayAllRecords();
            menu();
            break;
        case 7:
            dateRecords();
            break;
        case 8:
            policeInCharge();
            break;
        case 9:
            int choice;
            cout << "\n[1] Search by Last Name" << endl;
            cout << "[2] Search by Reference ID\n> " << endl;
            cin >> choice;
            switch (choice) {
                case 1: {
                    string name;
                    cout << "\nEnter Last Name: ";
                    cin >> ws;
                    getline(cin,name);
                    searchByName(name);
                    break;
                }
                case 2: {
                    string refNum;
                    cout << "\nEnter Reference No: ";
                    cin >> refNum;
                    searchByReference(refNum);
                    break;
                }
                default:
                    cout << "\nInvalid input";
                    break;
            }
            menu();
            break;
        case 10:
            police();
            break;
        case 11:
            exit(0);
            break;
        default:
            cout << "Invalid input";
            menu();
            break;
    }
}

void policeInCharge(void) {
    cout << endl << endl << "POLICE IN CHARGE\n";
    ifstream accounts("Accounts.txt");
    string police[1000];
    string line;
    int i = 1;
    int ch;
    while (getline(accounts,line)) {
        police[i] = line;
        cout << "[" << i << "] " << line << '\n';
        getline(accounts,line);
        getline(accounts,line);
        getline(accounts,line);
        getline(accounts,line);
        i++;
    }
    accounts.close();
    cout << "> ";
    cin >> ch;
    ifstream policeFile("Police/"+police[ch]+".txt");
    string line2;
    string name;
    string names[1000];
    string folders[1000];
    string folder;
    i = 1;
    cout << endl << endl << "Officer " + police[ch] << endl;
    getline(policeFile,line2);
    while (getline(policeFile,name)){
        cout << "[" << i << "] " << name << '\n';
        getline(policeFile,folder);
        getline(policeFile,line2);
        getline(policeFile,line2);
        names[i] = name;
        folders[i] = folder;
        i++;
    }
    policeFile.close();
    int open;
    cout << "\n[0] Return to Menu\nOpen: ";
    cin >> open;
    cout << endl << endl;
    if (open == 0) menu();
    else {
        showInformation(folders[open], names[open]+".txt");
        int choice;
        cout << "\n[1] Return to list";
        cout << "\n[2] Return to Police In Charge";
        cout << "\n[3] Return to Menu";
        cout << "\n[4] Edit Record";
        cout << "\n[5] Delete Record\n> ";
        cin >> choice;
        switch (choice) {
            case 1: {
                string line2;
                cout << endl << endl << "Officer " + police[ch] << endl;
                getline(policeFile,line2);
                while (getline(policeFile,name)){
                    cout << "[" << i << "] " << name << '\n';
                    getline(policeFile,folder);
                    getline(policeFile,line2);
                    getline(policeFile,line2);
                    names[i] = name;
                    folders[i] = folder;
                    i++;
                }
                policeFile.close();
            }
                break;
            case 2:
                policeInCharge();
                break;
            case 3:
                menu();
                break;
            case 4:
                editRecord(folders[open], names[open]);
                menu();
                break;
            case 5:
                removeRecord(folders[open], names[open]);
                cout << endl << "Record successfully deleted." << endl;
                menu();
                break;
            default:
                cout << "Invalid Input";
                break;
        }
    }
}

void polExistingAccount(void){
    string e_station, e_password;
    char ans1;
    int ans;
    cout << endl << "Enter Badge Number: ";
    cin >> e_badgeNo;
    cout << "Enter Station: ";
    cin >> e_station;
    cout << "Enter Password: ";
    cin >> e_password;
    if(verification(e_badgeNo, e_station, e_password) == 0) {
        cout << endl << "Login Successful!" << endl;
        menu();
    } else if(verification(e_badgeNo, e_station, e_password) == 1) {
        cout << "\nAccount Not Found!" << endl;
        cout << "[1] Log in\n[2] Create New Account\n> ";
        cin >> ans;
        if (ans == 1)
            polExistingAccount();
        else if (ans == 2)
            polCreateAccount();
    } else if(verification(e_badgeNo, e_station, e_password) == 2) {
        cout << "\nStation Location does not match Badge Number!\nLog in again? ";
        cin >> ans1;
        if (ans1 == 'Y' or ans1 == 'y') {
            polExistingAccount();
        }
    } else if(verification(e_badgeNo, e_station, e_password) == 3) {
        cout << "\nPassword does not match Badge Number!\nLog in again? ";
        cin >> ans1;
        if (ans1 == 'Y' or ans1 == 'y') {
            polExistingAccount();
        }
    }
    return;
}

void polCreateAccount(void) {
    police_info *tail = new police_info;
    police_info *temp = new police_info;
    char opt;
    cout << "\nEnter Name: ";
    cin.ignore();
    getline(cin, tail->policeName);
    string pName = tail->policeName;
    cout << "Enter Badge Number: ";
    cin >> tail->badgeNo;
    e_badgeNo = tail->badgeNo;
    cout << "Enter Station: ";
    cin >> tail->station;
    string pStation = tail->station;
    cout << "Enter Password: ";
    cin >> tail->password;
    string pPass = tail->password;
    accountsFile(pName, e_badgeNo, pStation, pPass);
    tail->next = NULL;
    if (policeHead == NULL) {
        policeHead = tail;
    }
    else {
        temp = policeHead;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = tail;
    }
    cout << endl << "Account Created!" << endl << "Would you like to log in? Y/N" << endl;
    cin >> opt;
    if (opt == 'Y'||opt == 'y') {
        menu();
    } else if (opt == 'N'||opt == 'n') {
        cout << "\nThank you for signing up, Officer " << tail->policeName << "." << endl;
    }
    return;
}

class BinarySearchTree {
private:
    struct tree_node{
        tree_node*left;
        tree_node*right;
        char data;
    };
    
    tree_node*root;
public:
    BinarySearchTree() {
        root= NULL;
    }
    
    bool isEmpty() const {
        return root==NULL;
    }
    
    void print_preorder();
    void preorder(tree_node*);
    void insert(char);
};

void BinarySearchTree::insert(char d) {
    tree_node*t = new tree_node;
    tree_node*parent;
    t->data= d;
    t->left = NULL;
    t->right = NULL;
    parent = NULL;
    if (isEmpty()) root =t;
    else {
        tree_node*curr;
        curr=root;
        while (curr) {
            parent=curr;
            if (t->data>curr->data) curr=curr->right;
            else curr=curr ->left;
        }
        if (t->data<parent->data)
            parent->left = t;
        else
            parent ->right = t;
    }
}

void BinarySearchTree::print_preorder() {
    preorder(root);
    if (checkReferenceRep(referenceNum)) {
        referenceNum = "";
        referenceNumber();
    }
}

void BinarySearchTree::preorder(tree_node*p) {
    if (p!=NULL) {
        referenceNum = referenceNum + p->data;
        if (p->left) preorder (p->left);
        if (p->right) preorder (p->right);
    }
    else
        return;
}

void referenceNumber(void) {
    BinarySearchTree b;
    char c, r;
    for (int i=0; i<4; i++) {
        r = rand() % 26;
        c = 'A' + r;
        b.insert(c);
        cout << c;
    }
    for (int i = 0; i < 4; i++) {
        r = (rand()%10);
        c = '0' + r;
        b.insert(c);
        cout << c;
    }
    b.print_preorder();
}

void addToList(string folder,string firstname, string lastname, string reference) {
    ofstream file(folder+"/"+folder+".txt",ios::app);
    file << reference << endl;
    file << lastname << ", " << firstname << endl << endl;
    file.close();
    return;
}

void PNPheader(void) {
    ifstream file("PNP Header.txt");
    string line;
    while (getline(file,line) ){
        cout << line << '\n';
    }
    file.close();
}

void accountsFile(string name, int badgeNo, string station, string password) {
    ofstream accounts;
    accounts.open("Accounts.txt",ios::app);
    accounts << name << endl;
    accounts << badgeNo << endl;
    accounts << station << endl;
    accounts << password << endl;
    accounts << "\n";
    accounts.close();
}

void complaintsFile(queue<string> name, queue<string> number, queue<string> email, queue<string> accused, queue<string> complain) {
    ofstream complaints;
    string line;
    complaints.open("Complaints.txt",ios::app);
    while (!name.empty()) {
        complaints << name.front() << endl;
        complaints << number.front() << endl;
        complaints << email.front() << endl;
        complaints << accused.front() << endl;
        complaints << complain.front() << endl;
        complaints << endl;
        name.pop();
        number.pop();
        email.pop();
        accused.pop();
        complain.pop();
    }
    complaints.close();
}

void criminalEntry(void) {
    criminalRecords *tail = new criminalRecords;
    criminalRecords *temp = new criminalRecords;
    int status;
    tail->reference = referenceNum;
    cout << "\nFill-Up Information\n";
    cout << "\nEnter Last Name: ";
    cin >> ws;
    getline(cin, tail->lastName);
    cout << "Enter First Name: ";
    istream& ignore (streamsize n = 1, int delim = EOF);
    getline(cin, tail->firstName);
    cout << "Enter Alias: ";
    getline(cin, tail->alias);
    cout << "Enter Nationality: ";
    cin >> tail->nationality;
    cout << "Filipino Citizen: ";
    cin >> tail->citizen;
    cout << "Sex: ";
    cin >> tail->gender;
    cout << "Weight (in kg): ";
    cin >> tail->weight;
    cout << "Height (in cm): ";
    cin >> tail->height;
    cout << "Eye Color: ";
    cin >> ws;
    getline(cin, tail->eyeColor);
    cout << "Hair Color: ";
    cin >> ws;
    getline(cin, tail->hairColor);
    cout << "Birth Date: ";
    cin >> ws;
    getline(cin, tail->birthdate);
    cout << "Age: ";
    cin >> tail->age;
    cout << "Distinctive Features: ";
    cin >> ws;
    getline(cin, tail->features);
    cout << "Information: ";
    cin >> ws;
    getline(cin, tail->arrestInfo);
    status = 5;
    while (status < 1 or status > 4) {
        cout << "Current Status: ";
        cout << "\n[1] In Custody\n[2] Wanted\n[3] Missing\n[4] On Bail\n";
        cin >> status;
        switch (status) {
            case 1:
                tail->currentStatus = "In Custody";
                break;
            case 2:
                tail->currentStatus = "Wanted";
                break;
            case 3:
                tail->currentStatus = "Missing";
                break;
            case 4:
                tail->currentStatus = "On Bail";
                break;
            default:
                cout << "\nInvalid input\n";
                break;
        }
    }
    tail->entryDate = "";
    while (tail->entryDate.size() != 10) {
        cout << "Date of Entry (mm dd yyyy): ";
        cin >> ws;
        getline(cin,tail->entryDate);
    }
    tail->next = NULL;
    if (crimHead == NULL) {
        crimHead = tail;
    }
    else {
        temp = crimHead;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = tail;
    }
    return;
}

void createFile() {
    criminalRecords *temp = new criminalRecords;
    police_info *police = new police_info;
    police = policeHead;
    temp = crimHead;
    ofstream profile;
    ofstream allRecords;
    ofstream dateRecords;
    while (temp != NULL) {
        profile.open(temp->currentStatus+"/"+temp->lastName+", "+temp->firstName+".txt");
        ifstream file("PNP Header.txt");
        string line;
        while (getline(file,line) ){
            profile << line << '\n';
        }
        file.close();
        profile << "\nNAME: \t\t" << temp->lastName + ", " + temp-> firstName << endl;
        profile << "\nALIAS: \t\t" << temp->alias << endl;
        profile << "\nREFERENCE NO: \t" << temp->reference << endl;
        profile << "\nNATIONALITY: \t" << temp->nationality << "\t\t\tCITIZEN: " << temp->citizen << endl;
        profile << "\nGENDER: \t" << temp->gender << endl;
        profile << "\nWEIGHT: \t" << temp->weight << " KG" << "\t\t\t\tHEIGHT: " << temp->height << " CM" << endl;
        profile << "\nEYE COLOR: \t" << temp->eyeColor << "\t\t\t\tHAIR COLOR: " << temp->hairColor << endl << endl;
        profile << "DATE OF BIRTH: \t" << temp->birthdate << "\t\tAGE: " << temp->age << endl << endl;
        profile << "DISTINCTIVE FEATURES:\n\t" << temp->features << endl << endl;
        profile << "INFORMATION:\n\t" << temp->arrestInfo << endl << endl;
        profile << "CURRENT STATUS:\n\t" << temp->currentStatus << endl << endl;
        ifstream accounts("Accounts.txt");
        string line1;
        string badge1;
        string policeName;
        while (getline(accounts,line)) {
            getline(accounts,badge1);
            stringstream geek(badge1);
            int x = 0;
            geek >> x;
            if (e_badgeNo == x)
                policeName = line;
            getline(accounts, line);
            getline(accounts, line);
            getline(accounts, line);
        }
        profile << "POLICE IN-CHARGE:\n\tOfficer " << policeName << endl << endl;
        accounts.close();
        profile.close();
        addToList(temp->currentStatus,temp->firstName,temp->lastName,temp->reference);
        allRecords.open("All Records.txt",ios::app);
        allRecords << temp->reference << endl;
        allRecords << temp->lastName << ", " << temp->firstName << endl;
        allRecords << temp->currentStatus << endl << endl;
        allRecords.close();
        dateRecords.open("Date Records.txt",ios::app);
        dateRecords << temp->reference << endl;
        dateRecords << temp->lastName << ", " << temp->firstName << endl;
        dateRecords << temp->entryDate << endl << endl;
        dateRecords.close();
        ofstream police("Police/"+ policeName +".txt",ios::app);
        police << temp->reference << endl;
        police << temp->lastName << ", " << temp->firstName << endl;
        police << temp->currentStatus << endl << endl;
        police.close();
        temp = temp->next;
    }
    crimHead = temp;
    return;
}

void displayAllRecords(void) {
    ifstream file("All Records.txt");
    string line;
    string name;
    string folder;
    string names[1000];
    string folders[1000];
    int i = 1;
    cout << "\nALL RECORDS" << endl << endl;
    getline(file,line);
    while (getline(file,name)){
        cout << "[" << i << "] " << name << '\n';
        getline(file,folder);
        getline(file,line);
        getline(file,line);
        names[i] = name;
        folders[i] = folder;
        i++;
    }
    file.close();
    int open;
    cout << "\n[0] Return to Menu\nOpen: ";
    cin >> open;
    cout << endl << endl;
    if (open == 0) menu();
    else {
        showInformation(folders[open], names[open]+".txt");
        int choice;
        cout << "\n[1] Return to list";
        cout << "\n[2] Return to Menu";
        cout << "\n[3] Edit Record";
        cout << "\n[4] Delete Record\n> ";
        cin >> choice;
        switch (choice) {
            case 1:
                displayAllRecords();
                break;
            case 2:
                menu();
                break;
            case 3:
                editRecord(folders[open], names[open]);
                displayAllRecords();
                break;
            case 4:
                removeRecord(folders[open], names[open]);
                cout << endl << "Record successfully deleted." << endl;
                displayAllRecords();
                break;
            default:
                cout << "Invalid Input";
                break;
        }
    }
}

void displayList(string text, string caption) {
    ifstream file(text+"/"+text+".txt");
    string line;
    string names[1000];
    int i = 1;
    getline(file,line);
    cout << endl << caption << endl << endl;
    while (getline(file,line)){
        cout << "[" << i << "] " << line << '\n';
        names[i] = line;
        getline(file,line);
        getline(file,line);
        i++;
    }
    file.close();
    int open;
    cout << "\n[0] Return to Menu\nOpen: ";
    cin >> open;
    cout << endl;
    if (open == 0) menu();
    else {
        int choice;
        showInformation(text, names[open]+".txt");
        cout << "\n[1] Return to " + text + " list";
        cout << "\n[2] Return to Menu";
        cout << "\n[3] Edit Record";
        cout << "\n[4] Delete Record\n> ";
        cin >> choice;
        switch (choice) {
            case 1:
                displayList(text,caption);
                break;
            case 2:
                menu();
                break;
            case 3:
                editRecord(text, names[open]);
                menu();
                break;
            case 4:
                removeRecord(text, names[open]);
                cout << endl << "Record successfully deleted." << endl;
                menu();
                break;
            default:
                cout << "Invalid Input";
                break;
        }
    }
}

void showInformation(string folder, string filename) {
    ifstream file(folder+"/"+filename);
    string line;
    while (getline(file,line)){
        cout << line << "\n";
    }
    file.close();
}

int verification(int badgeNo, string station, string password) {
    ifstream file("Accounts.txt");
    string line;
    while (getline(file,line)){
        if (line == to_string(badgeNo)) {
            getline(file, line);
            if (line == station) {
                getline(file, line);
                if (line == password) {
                    return 0;
                }
                return 3;
            }
            return 2;
        }
    }
    file.close();
    return 1;
}

void searchByName(string name) {
    ifstream file("All Records.txt");
    string line;
    string status;
    while (getline(file,line)) {
        if (line.find(name) != string::npos) {
            getline(file,status);
            showInformation(status, line+".txt");
        }
    }
}

void searchByReference(string reference) {
    ifstream file("All Records.txt");
    string line;
    string name;
    string status;
    while (getline(file,line)) {
        if (line == reference) {
            getline(file,name);
            getline(file,status);
            showInformation(status, name+".txt");
        }
    }
}

void removeRecord(string folder, string name) {
    //remove name from private file [Missing, etc...]
    ifstream privateFolder(folder+"/"+folder+".txt");
    ofstream privateFolder2(folder+"/"+folder+"2.txt");
    string line;
    string namee;
    while (getline(privateFolder,line)) {
        getline(privateFolder,namee);
        if (namee.find(name) != string::npos) {
            getline(privateFolder,line);
        } else {
            privateFolder2 << line << endl;
            privateFolder2 << namee << endl;
            getline(privateFolder,line);
            privateFolder2 << line << endl;
        }
    }
    privateFolder.close();
    privateFolder2.close();
    
    ifstream finalRead(folder+"/"+folder+"2.txt");
    ofstream finalWrite(folder+"/"+folder+".txt");
    string newLine;
    while (getline(finalRead, newLine)) {
        finalWrite << newLine << endl;
    }
    finalRead.close();
    finalWrite.close();
    
    //clear personal textfile record
    ofstream record(folder+"/"+name+".txt");
    record << "";
    record.close();
    
    //remove name from all records list
    ifstream all("All Records.txt");
    ofstream all2("All Records2.txt");
    string line1;
    string name1;
    while (getline(all,line1)) {
        getline(all,name1);
        if (name1.find(name) != string::npos) {
            getline(all,line1);
            getline(all,line1);
        } else {
            all2 << line1 << endl;
            all2 << name1 << endl;
        }
    }
    all.close();
    all2.close();
    ifstream finalRead2("All Records2.txt");
    ofstream finalWrite2("All Records.txt");
    string newLine1;
    while (getline(finalRead2, newLine1)) {
        finalWrite2 << newLine1 << endl;
    }
    finalRead2.close();
    finalWrite2.close();
    
    //remove from date records textfile
    ifstream date("Date Records.txt");
    ofstream date2("Date Records2.txt");
    string linee;
    string nameee;
    while (getline(date,linee)) {
        getline(date,nameee);
        if (nameee.find(name) != string::npos) {
            getline(date,linee);
            getline(date,linee);
        } else {
            date2 << linee << endl;
            date2 << nameee << endl;
        }
    }
    date.close();
    date2.close();
    ifstream finaldate2("Date Records2.txt");
    ofstream finaldate("Date Records.txt");
    string newLinee;
    while (getline(finaldate2, newLinee)) {
        finaldate << newLinee << endl;
    }
    finaldate2.close();
    finaldate.close();
    
    //remove name from police records list
    ifstream accounts("Accounts.txt");
    string line12;
    string badge12;
    string policeName;
    while (getline(accounts,line)) {
        getline(accounts,badge12);
        stringstream geek(badge12);
        int x = 0;
        geek >> x;
        if (e_badgeNo == x)
            policeName = line;
        getline(accounts, line);
        getline(accounts, line);
        getline(accounts, line);
    }
    
    ifstream p("Police/"+policeName+".txt");
    ofstream p2("Police/"+policeName+"2.txt");
    string pline;
    string pname;
    while (getline(p,pline)) {
        getline(p,pname);
        if (pname.find(name) != string::npos) {
            getline(p,pline);
            getline(p,pline);
        } else {
            p2 << pline << endl;
            p2 << pname << endl;
        }
    }
    p.close();
    p2.close();
    ifstream pp("Police/"+policeName+"2.txt");
    ofstream pp2("Police/"+policeName+".txt");
    string pline2;
    while (getline(pp, pline2)) {
        pp2 << pline2 << endl;
    }
    pp.close();
    pp2.close();
}

void editRecord(string folder, string name) {
    criminalRecords *tail = new criminalRecords;
    criminalRecords *temp = new criminalRecords;
    getInformation(folder, name, tail, temp);
    int choice;
    cout << endl << "What would you like to edit: " << endl;
    cout << "[1] Alias" << endl;
    cout << "[2] Height" << endl;
    cout << "[3] Weight" << endl;
    cout << "[4] Eye Color" << endl;
    cout << "[5] Hair Color" << endl;
    cout << "[6] Date of Birth" << endl;
    cout << "[7] Features" << endl;
    cout << "[8] Information" << endl;
    cout << "[9] Current Status" << endl;
    cout << "[0] Return to Menu\n> ";
    cin >> choice;
    
    switch (choice) {
        case 1:
            cout << "Enter Alias: ";
            cin >> ws;
            getline(cin,tail->alias);
            break;
        case 2:
            cout << "Enter Height: ";
            cin >> tail->height;
            break;
        case 3:
            cout << "Enter Weight: ";
            cin >> tail->weight;
            break;
        case 4:
            cout << "Enter Eye Color: ";
            cin >> ws;
            getline(cin, tail->eyeColor);
            break;
        case 5:
            cout << "Enter Hair Color: ";
            cin >> ws;
            getline(cin, tail->hairColor);
            break;
        case 6:
            cout << "Enter Date of Birth: ";
            cin >> ws;
            getline(cin, tail->birthdate);
            break;
        case 7:
            cout << "Enter Distinctive Features: ";
            cin >> ws;
            getline(cin, tail->features);
            break;
        case 8:
            cout << "Enter Additional Information: ";
            cin >> ws;
            getline(cin, tail->arrestInfo);
            break;
        case 9:
            int status;
            cout << "Enter Current Status:";
            cout << "\n[1] In Custody\n[2] Wanted\n[3] Missing\n[4] On Bail\n";
            cin >> status;
            removeRecord(folder, name);
            switch (status) {
                case 1:
                    tail->currentStatus = "In Custody";
                    folder = "In Custody";
                    break;
                case 2:
                    tail->currentStatus = "Wanted";
                    folder = "Wanted";
                    break;
                case 3:
                    tail->currentStatus = "Missing";
                    folder = "Missing";
                    break;
                case 4:
                    tail->currentStatus = "On Bail";
                    folder = "On Bail";
                    break;
                default:
                    cout << "\nInvalid input\n";
                    break;
            }
            addToList(folder, tail->firstName, tail->lastName, tail->reference);
            break;
        case 0:
            menu();
            return;
        default:
            cout << "Invalid input" << endl;
            break;
    }
    if (crimHead == NULL) {
        crimHead = tail;
    }
    else {
        temp = crimHead;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = tail;
    }
    ifstream all("All Records.txt");
    ofstream all2("All Records2.txt");
    string line1;
    string name1;
    while (getline(all,line1)) {
        getline(all,name1);
        if (name1.find(name) != string::npos) {
            getline(all,line1);
            getline(all,line1);
        } else {
            all2 << line1 << endl;
            all2 << name1 << endl;
        }
    }
    all.close();
    all2.close();
    ifstream finalRead2("All Records2.txt");
    ofstream finalWrite2("All Records.txt");
    string newLine1;
    while (getline(finalRead2, newLine1)) {
        finalWrite2 << newLine1 << endl;
    }
    finalRead2.close();
    finalWrite2.close();
    editTextfile(folder, name, tail);
}

void getInformation(string folder, string name, criminalRecords *tail, criminalRecords *temp) {
    ifstream record(folder+"/"+name+".txt");
    string line;
    while (getline(record, line)) {
        if (line.find("____") != string::npos) {
            record >> line >> line;
            tail->lastName = "";
            if (line.substr(line.size()-1,line.size()) == ",")
                tail->lastName = line.substr(0, line.size()-1);
            else {
                tail->lastName = tail->lastName + line + " ";
                while (line.substr(line.size()-1,line.size()) != ",") { //NAME
                    record >> line;
                    tail->lastName = tail->lastName + line + " ";
                }
                tail->lastName = tail->lastName.substr(0, tail->lastName.size()-2);
            }
            tail->firstName = "";
            record >> line;
            while (line != "ALIAS:") {                              //NAME
                tail->firstName = tail->firstName + line + " ";
                record >> line;
            }
            tail->firstName = tail->firstName.substr(0, tail->firstName.size()-1);
            record >> line;
            while (line != "REFERENCE") {                           //ALIAS
                tail->alias = line;
                record >> line;
            }
            record >> line >> line;                                 //REFERENCE
            tail->reference = line;
            record >> line >> line;
            tail->nationality = line;
            record >> line >> line;
            tail->citizen = line;
            record >> line >> line;
            tail->gender = line;
            record >> line >> line;
            tail->height = stof(line);
            record >> line >> line >> line;
            tail->weight = stof(line);
            record >> line >> line >> line >> line;
            tail->eyeColor = line;
            record >> line >> line >> line;
            tail->hairColor = line;
            record >> line >> line >> line >> line;
            tail->birthdate = "";
            while (line != "AGE:") {                                //BIRTH DATE
                tail->birthdate = tail->birthdate + line + " ";
                record >> line;
            }
            tail->birthdate = tail->birthdate.substr(0, tail->birthdate.size()-1);
            record >> line;
            tail->age = stoi(line);
            record >> line >> line >> line;
            tail->features = "";
            while (line != "INFORMATION:") {                        //FEATURES
                tail->features = tail->features + line + " ";
                record >> line;
            }
            tail->features = tail->features.substr(0, tail->features.size()-1);
            record >> line;
            tail->arrestInfo = "";
            while (line != "CURRENT") {                             //INFORMATION
                tail->arrestInfo = tail->arrestInfo + line + " ";
                record >> line;
            }
            tail->arrestInfo = tail->arrestInfo.substr(0, tail->arrestInfo.size()-1);
            record >> line >> line;
            tail->currentStatus = "";
            while (line != "POLICE") {                              //STATUS
                tail->currentStatus = tail->currentStatus + line + " ";
                record >> line;
            }
            tail->currentStatus = tail->currentStatus.substr(0, tail->currentStatus.size()-1);
        }
    }
    record.close();
}

void editTextfile(string folder, string name, criminalRecords *temp) {
    ofstream profile(folder+"/"+name+".txt");
    ifstream file("PNP Header.txt");
    string line;
    while (getline(file,line) ){
        profile << line << '\n';
    }
    file.close();
    profile << "\nNAME: \t\t" << temp->lastName + ", " + temp-> firstName << endl;
    profile << "\nALIAS: \t\t" << temp->alias << endl;
    profile << "\nREFERENCE NO: \t" << temp->reference << endl;
    profile << "\nNATIONALITY: \t" << temp->nationality << "\t\t\tCITIZEN: " << temp->citizen << endl;
    profile << "\nGENDER: \t" << temp->gender << endl;
    profile << "\nWEIGHT: \t" << temp->weight << " KG" << "\t\t\t\tHEIGHT: " << temp->height << " CM" << endl;
    profile << "\nEYE COLOR: \t" << temp->eyeColor << "\t\t\t\tHAIR COLOR: " << temp->hairColor << endl << endl;
    profile << "DATE OF BIRTH: \t" << temp->birthdate << "\t\tAGE: " << temp->age << endl << endl;
    profile << "DISTINCTIVE FEATURES:\n\t" << temp->features << endl << endl;
    profile << "INFORMATION:\n\t" << temp->arrestInfo << endl << endl;
    profile << "CURRENT STATUS:\n\t" << temp->currentStatus << endl << endl;
    ifstream accounts("Accounts.txt");
    string line1;
    string badge1;
    string policeName;
    while (getline(accounts,line)) {
        getline(accounts,badge1);
        stringstream geek(badge1);
        int x = 0;
        geek >> x;
        if (e_badgeNo == x)
            policeName = line;
        getline(accounts, line);
        getline(accounts, line);
        getline(accounts, line);
    }
    profile << "POLICE IN-CHARGE:\n\tOfficer " << policeName << endl << endl;
    accounts.close();
    profile.close();
    ofstream allRecords("All Records.txt",ios::app);
    allRecords << temp->reference << endl;
    allRecords << temp->lastName << ", " << temp->firstName << endl;
    allRecords << temp->currentStatus << endl << endl;
    allRecords.close();
}

bool checkReferenceRep(string reference) {
    ifstream file("All Records.txt");
    string line;
    while (getline(file,line)) {
        if (line == reference) {
            return true;
        }
    }
    return false;
}

void dateRecords (void) {
    while(1){
        int ch;
        cout << "\n\nView Records by Date" << endl;
        cout << "[1] View Records Today" << endl;
        cout << "[2] View Records Per Month" << endl;
        cout << "[3] View Records Per Year" << endl;
        cout << "[4] Return to Menu" << endl;
        cout << ">";
        cin >> ch;
        switch(ch){
            case 1:
                recPerDay();
                break;
            case 2:
                recPerMonth();
                break;
            case 3:
                recPerYear();
                break;
            case 4:
                menu();
                break;
            default:
                cout << "Incorrect input.";
                dateRecords();
        }
        string namesArr[1000];
        int i = 1;
        while (!names.empty()) {
            cout << "[" << i << "] " << names.top() << endl;
            namesArr[i] = names.top();
            names.pop();
            i++;
        }
        int open;
        cout << "\n[0] Return\nOpen: ";
        cin >> open;
        cout << endl;
        if (open == 0) dateRecords();
        else searchByName(namesArr[open]);
    }
}

void recPerDay(void) {
    time_t t = time(0);   // get time now
    tm* now = localtime(&t);
    cout << endl << "TODAY" << endl;
    ifstream dates("Date Records.txt");
    string line;
    string name;
    string month, day, year;
    while (getline(dates,line)) {
        getline(dates,line);
        name = line;
        dates >> month;
        dates >> day;
        dates >> year;
        if(now->tm_mon + 1 == stoi(month) and now->tm_mday == stoi(day) and now->tm_year + 1900 == stoi(year)) {
            names.push(name);
        }
        getline(dates,line);
        getline(dates,line);
    }
    dates.close();
}

void recPerMonth(void) {
    string currm;
    cout << "\nEnter Month (01-12): ";
    cin >> currm;
    ifstream dates("Date Records.txt");
    string line;
    string name;
    string month, day, year;
    while (getline(dates,line)) {
        getline(dates,line);
        name = line;
        dates >> month;
        dates >> day;
        dates >> year;
        if(currm == month) {
            names.push(name);
        }
        getline(dates,line);
        getline(dates,line);
    }
    dates.close();
}

void recPerYear(void) {
    string curry;
    cout << "\nEnter Year: ";
    cin >> curry;
    ifstream dates("Date Records.txt");
    string line;
    string name;
    string month, day, year;
    while (getline(dates,line)) {
        getline(dates,line);
        name = line;
        dates >> month;
        dates >> day;
        dates >> year;
        if(curry == year) {
            names.push(name);
        }
        getline(dates,line);
        getline(dates,line);
    }
    dates.close();
}

void getDates(void) {
    ifstream dates("Date Records.txt");
    string line;
    string name;
    string month, day, year;
    while (getline(dates,line)) {
        getline(dates,line);
        name = line;
        dates >> month;
        dates >> day;
        dates >> year;
        names.push(name);
        months.push(month);
        days.push(day);
        years.push(year);
        getline(dates,line);
        getline(dates,line);
    }
    dates.close();
}
