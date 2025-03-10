#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib> // For system("cls")

using namespace std;

class Student {
    int rollno;
    string name;
    int p_marks, c_marks, m_marks, e_marks, cs_marks;
    float per;
    char grade;

    void calculate() {
        per = (p_marks + c_marks + m_marks + e_marks + cs_marks) / 5.0;
        if (per >= 60) grade = 'A';
        else if (per >= 50) grade = 'B';
        else if (per >= 33) grade = 'C';
        else grade = 'F';
    }

public:
    void getData() {
        cout << "\nEnter roll number of student: ";
        cin >> rollno;
        cout << "Enter the Name of student: ";
        cin.ignore();  // To ignore any extra newline character
        getline(cin, name);
        cout << "Enter marks in Physics: ";
        cin >> p_marks;
        cout << "Enter marks in Chemistry: ";
        cin >> c_marks;
        cout << "Enter marks in Mathematics: ";
        cin >> m_marks;
        cout << "Enter marks in English: ";
        cin >> e_marks;
        cout << "Enter marks in Computer Science: ";
        cin >> cs_marks;

        calculate();
    }

    void showData() const {
        cout << "\nRoll No: " << rollno;
        cout << "\nName: " << name;
        cout << "\nMarks in Physics: " << p_marks;
        cout << "\nMarks in Chemistry: " << c_marks;
        cout << "\nMarks in Mathematics: " << m_marks;
        cout << "\nMarks in English: " << e_marks;
        cout << "\nMarks in Computer Science: " << cs_marks;
        cout << "\nPercentage: " << fixed << setprecision(2) << per;
        cout << "\nGrade: " << grade << endl;
    }

    void showTabular() const {
        cout << rollno << setw(12) << name << setw(10) << p_marks
             << setw(10) << c_marks << setw(10) << m_marks
             << setw(10) << e_marks << setw(10) << cs_marks
             << setw(10) << fixed << setprecision(2) << per
             << setw(10) << grade << endl;
    }

    int getRollNo() const {
        return rollno;
    }
};

// File stream and global student object
fstream fp;
Student st;

void writeStudent() {
    fp.open("student.dat", ios::out | ios::app);
    st.getData();
    fp.write((char*)&st, sizeof(Student));
    fp.close();
    cout << "\nStudent record has been created.\n";
}

void displayAll() {
    system("cls");
    cout << "\n\n\n\t\tDISPLAY ALL RECORDS\n\n";
    fp.open("student.dat", ios::in);
    while (fp.read((char*)&st, sizeof(Student))) {
        st.showData();
        cout << "\n====================================\n";
    }
    fp.close();
}

void displaySpecific(int rollno) {
    bool found = false;
    fp.open("student.dat", ios::in);
    while (fp.read((char*)&st, sizeof(Student))) {
        if (st.getRollNo() == rollno) {
            system("cls");
            st.showData();
            found = true;
            break;
        }
    }
    fp.close();
    if (!found) {
        cout << "\nRecord not found.\n";
    }
}

void modifyStudent() {
    int rollno;
    bool found = false;
    cout << "\nEnter roll number to modify: ";
    cin >> rollno;
    fp.open("student.dat", ios::in | ios::out);
    while (fp.read((char*)&st, sizeof(Student))) {
        if (st.getRollNo() == rollno) {
            system("cls");
            st.showData();
            cout << "\nEnter new details:\n";
            st.getData();
            long pos = -1 * sizeof(Student);
            fp.seekp(pos, ios::cur);
            fp.write((char*)&st, sizeof(Student));
            cout << "\nRecord updated successfully.\n";
            found = true;
            break;
        }
    }
    fp.close();
    if (!found) {
        cout << "\nRecord not found.\n";
    }
}

void deleteStudent() {
    int rollno;
    cout << "\nEnter roll number to delete: ";
    cin >> rollno;
    fp.open("student.dat", ios::in);
    fstream tempFile;
    tempFile.open("temp.dat", ios::out);
    bool found = false;
    while (fp.read((char*)&st, sizeof(Student))) {
        if (st.getRollNo() != rollno) {
            tempFile.write((char*)&st, sizeof(Student));
        } else {
            found = true;
        }
    }
    fp.close();
    tempFile.close();
    remove("student.dat");
    rename("temp.dat", "student.dat");
    if (found) {
        cout << "\nRecord deleted successfully.\n";
    } else {
        cout << "\nRecord not found.\n";
    }
}

void classResult() {
    system("cls");
    fp.open("student.dat", ios::in);
    if (!fp) {
        cout << "ERROR! File could not be opened.\n";
        exit(0);
    }
    cout << "\n\n\t\tALL STUDENTS RESULT\n\n";
    cout << "====================================================\n";
    cout << "Roll No. Name        P   C   M   E   CS   %age Grade\n";
    cout << "====================================================\n";
    while (fp.read((char*)&st, sizeof(Student))) {
        st.showTabular();
    }
    fp.close();
}

void resultMenu() {
    int choice, rollno;
    system("cls");
    cout << "\nRESULT MENU\n";
    cout << "1. Class Result\n";
    cout << "2. Student Report Card\n";
    cout << "3. Back to Main Menu\n";
    cout << "Enter your choice: ";
    cin >> choice;
    switch (choice) {
        case 1: classResult(); break;
        case 2:
            cout << "\nEnter Roll Number: ";
            cin >> rollno;
            displaySpecific(rollno);
            break;
        case 3: return;
        default: cout << "Invalid choice.\n";
    }
}

void entryMenu() {
    char choice;
    system("cls");
    cout << "\nENTRY MENU\n";
    cout << "1. Create Student Record\n";
    cout << "2. Display All Students Records\n";
    cout << "3. Search Student Record\n";
    cout << "4. Modify Student Record\n";
    cout << "5. Delete Student Record\n";
    cout << "6. Back to Main Menu\n";
    cout << "Enter your choice: ";
    cin >> choice;
    switch (choice) {
        case '1': writeStudent(); break;
        case '2': displayAll(); break;
        case '3': {
            int rollno;
            cout << "\nEnter Roll Number: ";
            cin >> rollno;
            displaySpecific(rollno);
            break;
        }
        case '4': modifyStudent(); break;
        case '5': deleteStudent(); break;
        case '6': return;
        default: cout << "Invalid choice.\n";
    }
}

void intro() {
    system("cls");
    cout << "STUDENT REPORT CARD SYSTEM\n";
    cout << "Project\n";
    cout << "Developed by: CodeWithC\n";
    cin.get();  // To wait for a key press
}

int main() {
    char choice;
    intro();
    do {
        system("cls");
        cout << "\nMAIN MENU\n";
        cout << "1. RESULT MENU\n";
        cout << "2. ENTRY/EDIT MENU\n";
        cout << "3. EXIT\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case '1': resultMenu(); break;
            case '2': entryMenu(); break;
            case '3': exit(0);
            default: cout << "Invalid choice.\n";
        }
    } while (choice != '3');
    return 0;
}




// --------------------------------------------------or--------------------------------------------------or---------------------------------------------


// //***************************************************************
// //                   HEADER FILE USED IN PROJECT
// //****************************************************************

// #include<conio.h>
// #include<stdio.h>
// #include<process.h>
// #include<fstream.h>
// #include<iomanip.h>

// //***************************************************************
// //                   CLASS USED IN PROJECT
// //****************************************************************

// class student
// {
//     int rollno;
//     char name[50];
//     int p_marks,c_marks,m_marks,e_marks,cs_marks;
//     float per;
//     char grade;
//     int std;
//     void calculate()
//     {
//         per=(p_marks+c_marks+m_marks+e_marks+cs_marks)/5.0;
//         if(per>=60)
//             grade='A';
//         else if(per>=50 && per<60)
//             grade='B';
//         else if(per>=33 && per<50)
//             grade='C';
//         else
//             grade='F';
//     }
// public:
//     void getdata()
//     {
//         cout<<"\nEnter The roll number of student ";
//         cin>>rollno;
//         cout<<"\n\nEnter The Name of student ";
//         gets(name);
//         cout<<"\nEnter The marks in physics out of 100 : ";
//         cin>>p_marks;
//         cout<<"\nEnter The marks in chemistry out of 100 : ";
//         cin>>c_marks;
//         cout<<"\nEnter The marks in maths out of 100 : ";
//         cin>>m_marks;
//         cout<<"\nEnter The marks in english out of 100 : ";
//         cin>>e_marks;
//         cout<<"\nEnter The marks in computer science out of 100 : ";
//         cin>>cs_marks;
//         calculate();
//     }

//     void showdata()
//     {
//         cout<<"\nRoll number of student : "<<rollno;
//         cout<<"\nName of student : "<<name;
//         cout<<"\nMarks in Physics : "<<p_marks;
//         cout<<"\nMarks in Chemistry : "<<c_marks;
//         cout<<"\nMarks in Maths : "<<m_marks;
//         cout<<"\nMarks in English : "<<e_marks;
//         cout<<"\nMarks in Computer Science :"<<cs_marks;
//         cout<<"\nPercentage of student is  :"<<setprecision(2)<<per;
//         cout<<"\nGrade of student is :"<<grade;
//     }

//     void show_tabular()
//     {
//         cout<<rollno<<setw(12)<<name<<setw(10)<<p_marks<<setw(3)<<c_marks<<setw(3)<<m_marks<<setw(3)<<e_marks<<setw(3)<<cs_marks<<setw(6)<<setprecision(3)<<per<<"   "<<grade<<endl;
//     }

//     int  retrollno()
//     {
//         return rollno;
//     }

// };         //class ends here



// //***************************************************************
// //      global declaration for stream object, object
// //****************************************************************

// fstream fp;
// student st;

// //***************************************************************
// //      function to write in file
// //****************************************************************

// void write_student()
// {
//     fp.open("student.dat",ios::out|ios::app);
//     st.getdata();
//     fp.write((char*)&st,sizeof(student));
//     fp.close();
//     cout<<"\n\nstudent record Has Been Created ";
//     getch();
// }


// //***************************************************************
// //      function to read all records from file
// //****************************************************************


// void display_all()
// {
//     clrscr();
//     cout<<"\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
//     fp.open("student.dat",ios::in);
//     while(fp.read((char*)&st,sizeof(student)))
//     {
//         st.showdata();
//         cout<<"\n\n====================================\n";
//         getch();
//     }
//     fp.close();
//     getch();
// }


// //***************************************************************
// //      function to read specific record from file
// //****************************************************************


// void display_sp(int n)
// {
//     int flag=0;
//     fp.open("student.dat",ios::in);
//     while(fp.read((char*)&st,sizeof(student)))
//     {
//         if(st.retrollno()==n)
//         {
//             clrscr();
//             st.showdata();
//             flag=1;
//         }
//     }
//     fp.close();
//     if(flag==0)
//         cout<<"\n\nrecord not exist";
//     getch();
// }


// //***************************************************************
// //      function to modify record of file
// //****************************************************************


// void modify_student()
// {
//     int no,found=0;
//     clrscr();
//     cout<<"\n\n\tTo Modify ";
//     cout<<"\n\n\tPlease Enter The roll number of student";
//     cin>>no;
//     fp.open("student.dat",ios::in|ios::out);
//     while(fp.read((char*)&st,sizeof(student)) && found==0)
//     {
//         if(st.retrollno()==no)
//         {
//             st.showdata();
//             cout<<"\nPlease Enter The New Details of student"<<endl;
//             st.getdata();
//             int pos=-1*sizeof(st);
//             fp.seekp(pos,ios::cur);
//             fp.write((char*)&st,sizeof(student));
//             cout<<"\n\n\t Record Updated";
//             found=1;
//         }
//     }
//     fp.close();
//     if(found==0)
//         cout<<"\n\n Record Not Found ";
//     getch();
// }


// //***************************************************************
// //      function to delete record of file
// //****************************************************************


// void delete_student()
// {
//     int no;
//     clrscr();
//     cout<<"\n\n\n\tDelete Record";
//     cout<<"\n\nPlease Enter The roll number of student You Want To Delete";
//     cin>>no;
//     fp.open("student.dat",ios::in|ios::out);
//     fstream fp2;
//     fp2.open("Temp.dat",ios::out);
//     fp.seekg(0,ios::beg);
//     while(fp.read((char*)&st,sizeof(student)))
//     {
//         if(st.retrollno()!=no)
//         {
//             fp2.write((char*)&st,sizeof(student));
//         }
//     }
//     fp2.close();
//     fp.close();
//     remove("student.dat");
//     rename("Temp.dat","student.dat");
//     cout<<"\n\n\tRecord Deleted ..";
//     getch();
// }


// //***************************************************************
// //      function to display all students grade report
// //****************************************************************

// void class_result()
// {
//     clrscr();
//     fp.open("student.dat",ios::in);
//     if(!fp)
//     {
//         cout<<"ERROR!!! FILE COULD NOT BE OPEN\n\n\n Go To Entry Menu to create File";
//         cout<<"\n\n\n Program is closing ....";
//         getch();
//         exit(0);
//     }

//     cout<<"\n\n\t\tALL STUDENTS RESULT \n\n";
//     cout<<"====================================================\n";
//     cout<<"Roll No. Name          P  C  M  E  CS  %age Grade\n";
//     cout<<"====================================================\n";

//     while(fp.read((char*)&st,sizeof(student)))
//     {
//         st.show_tabular();
//     }
//     fp.close();
//     getch();
// }




// //***************************************************************
// //      function to display result menu
// //****************************************************************

// void result()
// {
//     int ans,rno;
//     char ch;
//     clrscr();
//     cout<<"\n\n\nRESULT MENU";
//     cout<<"\n\n\n1. Class Result\n\n2. Student Report Card\n\n3.Back to Main Menu";
//     cout<<"\n\n\nEnter Choice (1/2)? ";
//     cin>>ans;
//     switch(ans)
//     {
//     case 1 :
//         class_result();
//         break;
//     case 2 :
//     {
//         do
//         {
//             clrscr();
//             char ans;
//             cout<<"\n\nEnter Roll Number Of Student : ";
//             cin>>rno;
//             display_sp(rno);
//             cout<<"\n\nDo you want to See More Result (y/n)?";
//             cin>>ans;
//         }
//         while(ans=='y'||ans=='Y');

//         break;
//     }
//     case 3:
//         break;
//     default:
//         cout<<"\a";
//     }
// }

// //***************************************************************
// //      INTRODUCTION FUNCTION
// //****************************************************************

// void intro()
// {
//     clrscr();
//     gotoxy(35,11);
//     cout<<"STUDENT";
//     gotoxy(33,14);
//     cout<<"REPORT CARD";
//     gotoxy(35,17);
//     cout<<"PROJECT";
//     cout<<"\n\nMADE BY : Code With C";
//     cout<<"\n\nCONTACT : codewithc.com";
//     getch();

// }




// //***************************************************************
// //      ENTRY / EDIT MENU FUNCTION
// //****************************************************************
// void entry_menu()
// {
//     clrscr();
//     char ch2;
//     cout<<"\n\n\n\tENTRY MENU";
//     cout<<"\n\n\t1.CREATE STUDENT RECORD";
//     cout<<"\n\n\t2.DISPLAY ALL STUDENTS RECORDS";
//     cout<<"\n\n\t3.SEARCH STUDENT RECORD ";
//     cout<<"\n\n\t4.MODIFY STUDENT RECORD";
//     cout<<"\n\n\t5.DELETE STUDENT RECORD";
//     cout<<"\n\n\t6.BACK TO MAIN MENU";
//     cout<<"\n\n\tPlease Enter Your Choice (1-6) ";
//     ch2=getche();
//     switch(ch2)
//     {
//     case '1':
//         clrscr();
//         write_student();
//         break;
//     case '2':
//         display_all();
//         break;
//     case '3':
//         int num;
//         clrscr();
//         cout<<"\n\n\tPlease Enter The roll number ";
//         cin>>num;
//         display_sp(num);
//         break;
//     case '4':
//         modify_student();
//         break;
//     case '5':
//         delete_student();
//         break;
//     case '6':
//         break;
//     default:
//         cout<<"\a";
//         entry_menu();
//     }
// }


// //***************************************************************
// //      THE MAIN FUNCTION OF PROGRAM
// //****************************************************************


// void main()
// {
//     char ch;
//     intro();
//     do
//     {
//         clrscr();
//         cout<<"\n\n\n\tMAIN MENU";
//         cout<<"\n\n\t01. RESULT MENU";
//         cout<<"\n\n\t02. ENTRY/EDIT MENU";
//         cout<<"\n\n\t03. EXIT";
//         cout<<"\n\n\tPlease Select Your Option (1-3) ";
//         ch=getche();
//         switch(ch)
//         {
//         case '1':
//             clrscr();
//             result();
//             break;
//         case '2':
//             entry_menu();
//             break;
//         case '3':
//             exit(0);
//         default :
//             cout<<"\a";
//         }
//     }
//     while(ch!='3');
// }

// //***************************************************************
// //                      END OF PROJECT
// //***************************************************************
