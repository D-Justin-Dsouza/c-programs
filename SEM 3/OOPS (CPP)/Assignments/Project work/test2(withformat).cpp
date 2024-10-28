#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

// Base class to handle marks
class Marks {
public:
    float course_mark[3];  // Array to hold marks for theory, IT, and term work
    string type_of_marks[3] = {"Theory", "IT", "Term Work"};
    float total_max_marks;  // Maximum total marks for the subject

    void input_marks() {
        cout << "Enter the maximum total marks for the subject: ";
        cin >> total_max_marks;

        float total_marks_obtained = 0;
        for (int i = 0; i < 3; i++) {
            cout << "Enter marks obtained in " << type_of_marks[i] << ": ";
            cin >> course_mark[i];
            total_marks_obtained += course_mark[i];
        }

        while (total_marks_obtained > total_max_marks) {
            cout << "Invalid! The total marks cannot exceed " << total_max_marks << ". Enter again:\n";
            total_marks_obtained = 0;
            for (int i = 0; i < 3; i++) {
                cout << "Enter marks obtained in " << type_of_marks[i] << ": ";
                cin >> course_mark[i];
                total_marks_obtained += course_mark[i];
            }
        }
    }

    float getTotalMarksObtained() const {
        float total_obtained = 0;
        for (int i = 0; i < 3; i++) {
            total_obtained += course_mark[i];
        }
        return total_obtained;
    }
};

// Class for subjects, inherits from Marks
class Subject : public Marks {
public:
    string name;
    string code;
    int credits;
    char grade;

    Subject() : credits(0), name("undefined"), code("undefined") {}

    void inputSubject() {
        cout << "Enter course name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter course code: ";
        getline(cin, code);
        cout << "Enter credits for the subject: ";
        cin >> credits;
        input_marks();
    }
};

// Class to represent a semester
class Semester {
public:
    int subjectCount;
    string semesterName;
    Subject subjects[10];  // Assuming a maximum of 10 subjects per semester

    Semester() : subjectCount(0) {}

    void inputSemesterDetails(const string& semName) {
        semesterName = semName;
        cout << "Enter number of subjects in " << semName << ": ";
        cin >> subjectCount;
        for (int i = 0; i < subjectCount; i++) {
            cout << "\nEntering details for subject " << (i + 1) << ":\n";
            subjects[i].inputSubject();
        }
    }

    double calculateCGPA() const {
        double totalPoints = 0.0;
        int totalCredits = 0;

        for (int i = 0; i < subjectCount; i++) {
            double gradePoint = subjects[i].getTotalMarksObtained() / subjects[i].total_max_marks * 10; // Simplified CGPA logic
            totalPoints += gradePoint * subjects[i].credits;
            totalCredits += subjects[i].credits;
        }

        return (totalCredits > 0) ? (totalPoints / totalCredits) : 0.0;
    }
};

// Class to handle student result
class StudentResult {
public:
    string studentName, rollNo, branch;
    int semesterCount;
    Semester semesters[2];  // Assuming two semesters per academic year

    StudentResult() : semesterCount(2) {}

    void inputStudentDetails() {
        cout << "Enter student name: ";
        cin.ignore();
        getline(cin, studentName);
        cout << "Enter roll number: ";
        getline(cin, rollNo);
        cout << "Enter branch: ";
        getline(cin, branch);
    }

    void inputSemesterDetails() {
        for (int i = 0; i < semesterCount; i++) {
            semesters[i].inputSemesterDetails("Semester " + to_string(i + 1));
        }
    }

    void displayStudentDetails() const {
        string markArr[10] = {"Credit", "Theory", "IT", "Termwork", "Theory total", "Practical", "Oral", "Total", "Grade", "Grade Point"};

        cout << setw(200) << setfill('_') << "" << endl; // line
        cout << setfill(' ') << "|" << setw(108) << "\e[1mGovernment of Goa\e[0m" << setw(99) << "|" << endl; //text middle
        cout << "|" << setw(199) << "|" << endl; //free
        cout << setfill(' ') << "|" << setw(113) << "\e[1mGoa College Of Engineering\e[0m" << setw(94) << "|" << endl; //text middle
        cout << setfill(' ') << "|" << setw(110) << "\e[1mFarmaguddi Ponda Goa\e[0m" << setw(97) << "|" << endl; //text middle
        cout << setw(200) << setfill('_') << "" << endl; //line
        cout << setfill(' ') << "|" << setw(118) << "\e[1mNov-Dec 2023 Examination: Semester 1\e[0m" << setw(89) << "|" << endl; //text middle
        cout << "|" << setw(6) << left << "\e[1mName: \e[0m" << setw(192) << left << studentName << "|" << endl; // free
        cout << "|" << setw(13) << left << "\e[1mRoll Number: \e[0m" << setw(185) << left << rollNo << "|" << endl; // free
        cout << "|" << setw(9) << left << "\e[1mBranch: \e[0m" << setw(189) << left << branch << "|" << endl; // free
        cout << setw(200) << setfill('_') << "" << endl; // line

        cout.fill(' ');
        cout << "|" << setw(17) << left << "Code" << "|" << setw(50) << left << "Course" << "|"; // free

        for (string i : markArr) cout << setw(12) << left << i << "|"; 
        cout << endl;
        cout << setw(200) << setfill('_') << "" << endl; // line

        for (int i = 0; i < 10; i++) { // Assuming max 10 subjects
            cout.fill(' ');
            if (i < semesters[0].subjectCount) { // Display subjects from the first semester
                cout << "|" << setw(17) << left << semesters[0].subjects[i].code << "|"
                     << setw(50) << left << semesters[0].subjects[i].name << "|"; // free
                for (int j = 0; j < 8; j++){
                    if(j==0) cout << setw(7) << right << semesters[0].subjects[i].credits << setw(5) << "" << "|"; 
                    cout << setw(7) << right << semesters[0].subjects[i].course_mark[j] << setw(5) << "" << "|"; 
                }
                cout << setw(7) << right << semesters[0].subjects[i].grade << setw(5) << "" << "|"
                     << setw(7) << right << semesters[0].subjects[i].credits << setw(5) << "" << "|" << endl;
                cout << setw(200) << setfill('_') << "" << endl; // line
            }
        }

        double overallCGPA = 0;
        for (int i = 0; i < semesterCount; i++) {
            overallCGPA += semesters[i].calculateCGPA();
        }

        cout.fill(' ');
        cout << "|" << setw(30) << right << "Earned Credits: " << setw(10) << left << semesters[0].subjects[0].credits 
             << setw(30) << right << "SGPA: " << setw(10) << left << overallCGPA 
             << setw(30) << right << "Status: " << setw(10) << left << "Completed" << setw(78) << "" << "|" << endl;
        cout << setw(200) << setfill('_') << "" << endl; // line
    }

    void saveToFile() const {
        string filename = rollNo + ".txt";
        ofstream file(filename);
        if (!file.is_open()) {
            cout << "Error opening file!" << endl;
            return;
        }
        file << studentName << endl;
        file << rollNo << endl;
        file << branch << endl;
        for (int i = 0; i < semesterCount; i++) {
            file << semesters[i].semesterName << endl;
            file << semesters[i].subjectCount << endl;
            for (int j = 0; j < semesters[i].subjectCount; j++) {
                file << semesters[i].subjects[j].name << " " << semesters[i].subjects[j].code << " ";
                for (int k = 0; k < 3; k++) {
                    file << semesters[i].subjects[j].course_mark[k] << " ";
                }
                file << semesters[i].subjects[j].grade << endl;
            }
        }
        file.close();
        cout << "Result details saved to file: " << filename << endl;
    }
};

int main() {
    StudentResult student;
    student.inputStudentDetails();
    student.inputSemesterDetails();
    student.displayStudentDetails();
    student.saveToFile();
    return 0;
}
