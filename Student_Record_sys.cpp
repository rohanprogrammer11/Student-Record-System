#include<iostream>
#include<fstream> // The #include <fstream> header in C++ is used to perform file input and output operations. It provides classes that allow your program to read from and write to files.
#include<cstring> //#include <cstring> is the C++ version of the C header <string.h>, and it provides functions for manipulating C-style strings (null-terminated character arrays).

using namespace std;

class Student{
    public:
    int roll_no;
    char name[50];
    float marks;

    void input(){
        
        std::cout << "Enter the Roll No. : ";
            cin >> roll_no;
            cin.ignore(); // To ignore the newline character left in the input buffer

        std::cout << "Enter the Name : ";
        cin.getline(name, 50); // To read a line of text including spaces

        std::cout << "Enter the Marks : ";
        cin >> marks;
    }

    void display(){

        cout << "\n Roll No. : " << roll_no;
        cout << "\n Name : " << name;
        cout << "\n Marks : " << marks;

    }
};

void addrecord(){
    Student s;

    ofstream outFile("student.dat",ios::binary | ios::app); // Open file in binary mode and append
    s.input(); // Call input method to get student details
    outFile.write(reinterpret_cast<char*>(&s), sizeof(Student));
    outFile.close(); // Close the file after writing
    cout << "\n Record Added Successfully!";
}

void displayAll(){
    Student s;
    ifstream inFile("student.dat", ios::binary); // Open file in binary mode for reading
    while (inFile.read(reinterpret_cast<char*>(&s), sizeof(Student))){
        s.display();
        cout << "\n--------------------------";
    }
    inFile.close(); // Close the file after reading
}

void searchrecord(){
    int roll;
    bool found = false;
    Student s;
    cout << "Enter Roll No. to Search : ";
    cin >> roll;
    ifstream inFile("student.dat", ios::binary); // Open file in binary mode for reading
    while (inFile.read(reinterpret_cast<char*>(&s), sizeof(Student))){
        if (s.roll_no == roll){
            s.display();
            found = true;
            break;
        }
    }

    inFile.close(); // Close the file after reading
    if(!found){
        cout << "\n Record is not found!";
    }

}

void updateRecord(){
    int roll;
    bool found = false;
    Student s;
    fstream file("student.dat", ios::binary | ios::in | ios::out);
    cout << "Enter the Roll No. to update : ";
    cin >> roll;

    while(file.read(reinterpret_cast<char*>(&s), sizeof(Student))){
        streampos pos = file.tellg();
        file.read(reinterpret_cast<char*>(&s), sizeof(Student));
        if(s.roll_no == roll){
            cout << "old Record";
            s.display();
            cout << "Enter new details : \n";
            s.input();
            file.seekp(pos);
            file.write(reinterpret_cast<char*>(&s), sizeof(Student));
            found = true;
            cout << "Record Updated.\n";
        }
    }
    file.close();
    if(!found)
        cout << "Record not found!.\n";
}

void deleteRecord(){
    int roll;
    Student s;
    ifstream inFile("student.dat", ios::binary);
    ofstream outFile("temp.dat", ios::binary);
    cout << "Enter Roll No. to detele : ";
    cin >> roll;

    bool found = false;
    while(inFile.read(reinterpret_cast<char*>(&s), sizeof(Student))){
        if(s.roll_no != roll){
            outFile.write(reinterpret_cast<char*>(&s), sizeof(Student));
        }else{
            found = true;
        }
    }
    inFile.close();
    outFile.close();
    remove("student.dat");
    rename("temp.dat","student.dat");

    if(found){
        cout << "Record Deleted.\n";
    }else{
        cout << "Record Not Found!.\n";
    }
}

int main() {
    int choice;
    do {
        cout << "\n--- Student Record System ---\n";
        cout << "1. Add Record\n";
        cout << "2. Display All Records\n";
        cout << "3. Search Record\n";
        cout << "4. Update Record\n";
        cout << "5. Delete Record\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addrecord(); break;
            case 2: displayAll(); break;
            case 3: searchrecord(); break;
            case 4: updateRecord(); break;
            case 5: deleteRecord(); break;
            case 6: cout << "Goodbye!\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 6);

    return 0;
}
