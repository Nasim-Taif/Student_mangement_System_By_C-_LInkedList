#include <bits/stdc++.h>
using namespace std;

// Node Class
class Node {
public:
    int roll;
    string Name;
    string Dept;
    float Marks;
    Node* next;
};

// Stores the head of the Linked List
Node* head = nullptr;

// Map to store user credentials and roles
map<string, pair<string, string>> user_credentials; // (username, (password, role))

// Function Declarations
bool check(int x);
void Insert_Record(int roll, string Name, string Dept, float Marks);
void Search_Record(int roll);
int Delete_Record(int roll);
void Show_Record();
void save_credentials();
void load_credentials();
void save_records();
void load_records();
void Register();
bool Login(string &role);

// Check Function to check if Record Already Exists or Not
bool check(int x)
{
    if (head == nullptr)
        return false;

    Node* t = head;

    // Traverse the Linked List
    while (t != nullptr) {
        if (t->roll == x)
            return true;
        t = t->next;
    }

    return false;
}

// Function to insert the record
void Insert_Record(int roll, string Name, string Dept, float Marks)
{
    if (check(roll)) {
        cout << "Student with this record already exists\n";
        return;
    }

    // Create new Node to Insert Record
    Node* t = new Node();
    t->roll = roll;
    t->Name = Name;
    t->Dept = Dept;
    t->Marks = Marks;
    t->next = nullptr;

    // Insert at Begin
    if (head == nullptr || (head->roll >= t->roll)) {
        t->next = head;
        head = t;
    }
    // Insert at middle or End
    else {
        Node* c = head;
        while (c->next != nullptr && c->next->roll < t->roll) {
            c = c->next;
        }
        t->next = c->next;
        c->next = t;
    }

    cout << "Record Inserted Successfully\n";
    save_records();
}

// Function to search record for any students Record with roll number
void Search_Record(int roll)
{
    if (!head) {
        cout << "No such Record Available\n";
        return;
    }
    else {
        Node* p = head;
        while (p) {
            if (p->roll == roll) {
                cout << "Roll Number\t" << p->roll << endl;
                cout << "Name\t\t" << p->Name << endl;
                cout << "Department\t" << p->Dept << endl;
                cout << "CGPA \t\t" << p->Marks << endl;
                return;
            }
            p = p->next;
        }

        if (p == nullptr)
            cout << "No such Record Available\n";
    }
}

// Function to delete student record with given roll number if it exists
int Delete_Record(int roll)
{
    Node* t = head;
    Node* p = nullptr;

    // Deletion at Begin
    if (t != nullptr && t->roll == roll) {
        head = t->next;
        delete t;

        cout << "Record Deleted Successfully\n";
        save_records();
        return 0;
    }

    // Deletion Other than Begin
    while (t != nullptr && t->roll != roll) {
        p = t;
        t = t->next;
    }
    if (t == nullptr) {
        cout << "Record does not Exist\n";
        return -1;
    }
    p->next = t->next;
    delete t;
    cout << "Record Deleted Successfully\n";
    save_records();
    return 0;
}

// Function to display the Student's Record
void Show_Record()
{
    Node* p = head;
    if (p == nullptr) {
        cout << "No Record Available\n";
    }
    else {
        cout << "ID   \tName\tCourse\tCGPA \n";

        // Until p is not NULL
        while (p != nullptr) {
            cout << p->roll << "\t" << p->Name << "\t" << p->Dept << "\t" << p->Marks << endl;
            p = p->next;
        }
    }
}

// Function to save user credentials to a file
void save_credentials()
{
    ofstream outfile("credentials.txt");
    for (const auto& pair : user_credentials) {
        outfile << pair.first << " " << pair.second.first << " " << pair.second.second << endl;
    }
    outfile.close();
}

// Function to load user credentials from a file
void load_credentials()
{
    ifstream infile("credentials.txt");
    if (infile.is_open()) {
        string username, password, role;
        while (infile >> username >> password >> role) {
            user_credentials[username] = make_pair(password, role);
        }
        infile.close();
    }
}

// Function to save student records to a file
void save_records()
{
    ofstream outfile("records.txt");
    Node* p = head;
    while (p != nullptr) {
        outfile << p->roll << " " << p->Name << " " << p->Dept << " " << p->Marks << endl;
        p = p->next;
    }
    outfile.close();
}

// Function to load student records from a file
void load_records()
{
    ifstream infile("records.txt");
    if (infile.is_open()) {
        int roll;
        float marks;
        string name, dept;
        while (infile >> roll >> name >> dept >> marks) {
            Insert_Record(roll, name, dept, marks);
        }
        infile.close();
    }
}

// Function to register a new user
void Register()
{
    string username, password, role;
    cout << "\n\t\t\t\tRegistration Portal: --> \n";
    cout << "\n\t\t\t\tEnter Username: ";
    cin >> username;
    cout << "\n\t\t\t\tEnter Password: ";
    cin >> password;
    cout << "\n\t\t\t\tEnter Role (student/faculty): ";
    cin >> role;

    // Check if the username already exists
    if (user_credentials.find(username) != user_credentials.end()) {
        cout << "Username already exists. Please try a different username.\n";
    } else {
        user_credentials[username] = make_pair(password, role);
        cout << "Registration Successful.\n";
        save_credentials();
    }
}

// Function to login a user
bool Login(string &role)
{
    string username, password;
    cout << "\t\t\t\tEnter Username: ";
    cin >> username;
    cout << "\t\t\t\tEnter Password: ";
    cin >> password;

    // Check if the username exists and the password matches
    if (user_credentials.find(username) != user_credentials.end() && user_credentials[username].first == password) {
        cout << "Login Successful.\n";
        role = user_credentials[username].second;
        return true;
    } else {
        cout << "Invalid Username or Password.\n";
        return false;
    }
}

// Driver code
int main()
{
    head = nullptr;
    load_credentials();
    load_records();

    string Name, Course, role;
    int Roll;
    float Marks;

    // Menu-driven program
    while (true) {
        cout << "\n\t\t<---- Welcome to Student Record Management System ---->\n";
        cout << "\n\t\t\t\tPress\n\t\t\t\t1. to Register\n\t\t\t\t2. to Login\n\t\t\t\t3. to Exit\n";
        cout << "\n\t\t\t\tEnter your Choice: ";
        int initial_choice;
        cin >> initial_choice;

        if (initial_choice == 1) {
            Register();
        }
        else if (initial_choice == 2) {
            if (Login(role)) {
                if (role == "faculty") {
                    while (true) {
                        cout << "\n\t\t\t\tPress\n\t\t\t\t1. to create a new Record\n\t\t\t\t2. to delete a student record\n\t\t\t\t3. to Search a Student Record\n\t\t\t\t4. to view all students record\n\t\t\t\t5. to Logout\n";
                        cout << "\n\t\t\t\tEnter your Choice: ";
                        int Choice;
                        cin >> Choice;

                        if (Choice == 1) {
                            cout << "\t\t\t\tEnter Name of Student: ";
                            cin >> Name;
                            cout << "\t\t\t\tEnter ID Number of Student: ";
                            cin >> Roll;
                            cout << "\t\t\t\tEnter Course of Student: ";
                            cin >> Course;
                            cout << "\t\t\t\tCGPA of Student: ";
                            cin >> Marks;
                            Insert_Record(Roll, Name, Course, Marks);
                        }
                        else if (Choice == 2) {
                            cout << "\t\t\t\tEnter ID Number of Student whose record is to be deleted: ";
                            cin >> Roll;
                            Delete_Record(Roll);
                        }
                        else if (Choice == 3) {
                            cout << "\t\t\t\tEnter ID Number of Student whose record you want to Search: ";
                            cin >> Roll;
                            Search_Record(Roll);
                        }
                        else if (Choice == 4) {
                            Show_Record();
                        }
                        else if (Choice == 5) {
                            break;
                        }
                        else {
                            cout << "Invalid Choice. Try Again.\n";
                        }
                    }
                } else if (role == "student") {
                    while (true) {
                        cout << "\n\t\t\t\tPlease Press -->\n\n\t\t\t\t1.See Your Profile \n\t\t\t\t2. to Logout\n";
                        cout << "\nEnter your Choice: ";
                        int Choice;
                        cin >> Choice;

                        if (Choice == 1) {
                            cout << "Enter your ID Number: ";
                            cin >> Roll;
                            Search_Record(Roll);
                        }
                        else if (Choice == 2) {
                            break;
                        }
                        else {
                            cout << "Invalid Choice. Try Again.\n";
                        }
                    }
                }
            }
        }
        else if (initial_choice == 3) {
            exit(0);
        }
        else {
            cout << "Invalid Choice. Try Again.\n";
        }
    }

    return 0;
}

