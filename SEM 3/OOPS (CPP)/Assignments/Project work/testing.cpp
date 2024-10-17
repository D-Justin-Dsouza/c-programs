/*#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

class Subject {
public:
    string name;
    int marks;
    int credits;

    Subject() : marks(0), credits(0) {}
};

class Semester {
public:
    Subject subjects[10];  // Maximum of 10 subjects per semester
    int numSubjects;

    Semester() : numSubjects(0) {}

    void addSubject(const string& name, int marks, int credits) {
        if (numSubjects < 10) {
            subjects[numSubjects].name = name;
            subjects[numSubjects].marks = marks;
            subjects[numSubjects].credits = credits;
            numSubjects++;
        } else {
            cout << "Cannot add more subjects, maximum limit reached." << endl;
        }
    }

    double calculateCGPA() {
        double totalPoints = 0.0;
        int totalCredits = 0;

        for (int i = 0; i < numSubjects; i++) {
            double gradePoint = calculateGradePoint(subjects[i].marks);
            totalPoints += gradePoint * subjects[i].credits;
            totalCredits += subjects[i].credits;
        }

        return (totalCredits > 0) ? (totalPoints / totalCredits) : 0.0;
    }

    double calculateGradePoint(int marks) {
        if (marks >= 90) return 10.0;  // A+
        if (marks >= 80) return 9.0;   // A
        if (marks >= 70) return 8.0;   // B+
        if (marks >= 60) return 7.0;   // B
        if (marks >= 50) return 6.0;   // C
        if (marks >= 40) return 5.0;   // D
        return 0.0;  // F
    }
};

class StudentResult {
public:
    string sname, rno, branch;
    Semester semesters[2];  // Only 2 semesters as per the current design

    void getDetailsAndMarks() {
        cout << "Enter student name: ";
        cin.ignore(); // Ignore newline
        getline(cin, sname);
        cout << "Enter roll number: ";
        getline(cin, rno);
        cout << "Enter branch: ";
        getline(cin, branch);

        for (int i = 0; i < 2; i++) {
            cout << "Enter number of subjects for semester " << (i + 1) << ": ";
            int numSubjects;
            cin >> numSubjects;

            for (int j = 0; j < numSubjects; j++) {
                string subjectName;
                int marks, credits;

                cout << "Enter subject name: ";
                cin >> subjectName;
                cout << "Enter marks: ";
                cin >> marks;
                cout << "Enter credits: ";
                cin >> credits;

                semesters[i].addSubject(subjectName, marks, credits);
            }
        }
    }

    void display() {
        cout << "Name: " << sname << "\nRoll No: " << rno << endl;
        if (!branch.empty()) {
            cout << "Branch: " << branch << endl;
        }

        for (int i = 0; i < 2; i++) {
            cout << "Semester " << (i + 1) << ":\n";
            for (int j = 0; j < semesters[i].numSubjects; j++) {
                cout << "  Subject: " << semesters[i].subjects[j].name
                     << ", Marks: " << semesters[i].subjects[j].marks
                     << ", Credits: " << semesters[i].subjects[j].credits << endl;
            }
            double cgpa = semesters[i].calculateCGPA();
            cout << "  CGPA: " << fixed << setprecision(2) << cgpa << endl;
        }
    }

    void saveToFile() {
        string filename = rno + ".txt";
        ofstream outFile(filename);
        if (outFile.is_open()) {
            out
            outFile << sname << endl;
            outFile << rno << endl;
            outFile << branch << endl;
            for (int i = 0; i < 2; i++) {
                outFile << semesters[i].numSubjects << endl;
                for (int j = 0; j < semesters[i].numSubjects; j++) {
                    outFile << semesters[i].subjects[j].name << " "
                            << semesters[i].subjects[j].marks << " "
                            << semesters[i].subjects[j].credits << endl;
                }
            }
            outFile.close();
            cout << "Result saved in file: " << filename << endl;
        } else {
            cout << "Error opening file!" << endl;
        }
    }

    void loadFromFile(const string& roll_no) {
        string filename = roll_no + ".txt";
        ifstream inFile(filename);
        if (inFile.is_open()) {
            getline(inFile, sname);
            getline(inFile, rno);
            getline(inFile, branch);
            for (int i = 0; i < 2; i++) {
                inFile >> semesters[i].numSubjects;
                inFile.ignore();
                for (int j = 0; j < semesters[i].numSubjects; j++) {
                    inFile >> semesters[i].subjects[j].name
                           >> semesters[i].subjects[j].marks
                           >> semesters[i].subjects[j].credits;
                }
            }
            inFile.close();
        } else {
            cout << "Error opening file!" << endl;
        }
    }

    void appendBranchToFile() {
        cout << "Enter branch: ";
        cin.ignore();
        getline(cin, branch);
        string filename = rno + ".txt";
        ofstream outFile(filename, ios::app);
        if (outFile.is_open()) {
            outFile << branch << endl;
            outFile.close();
            cout << "Branch appended to file: " << filename << endl;
        } else {
            cout << "Error opening file!" << endl;
        }
    }

    void editMarks(const string& roll_no) {
        loadFromFile(roll_no);
        for (int i = 0; i < 2; i++) {
            cout << "Enter marks for semester " << (i + 1) << ":\n";
            for (int j = 0; j < semesters[i].numSubjects; j++) {
                cout << "  Subject: " << semesters[i].subjects[j].name << " ";
                cin >> semesters[i].subjects[j].marks;
            }
        }
        saveToFile();
        cout << "Marks updated for roll number " << roll_no << endl;
    }

    void calculateAndDisplayCGPA(int semesterNumber) {
        if (semesterNumber < 1 || semesterNumber > 2) {
            cout << "Invalid semester number! Please enter 1 or 2." << endl;
            return;
        }
        double cgpa = semesters[semesterNumber - 1].calculateCGPA();
        cout << "CGPA for semester " << semesterNumber << " is: "
              << fixed << setprecision(2) << cgpa << endl;
    }
};

void menu() {
    cout << "\nExamination Result System Menu:";
    cout << "\n1. Enter result details and display";
    cout << "\n2. Edit marks of a student and display";
    cout << "\n3. Append branch to result file and display";
    cout << "\n4. Calculate CGPA for a semester";
    cout << "\n5. Exit\n";
}

int main() {
    StudentResult sr;
    int choice, semesterNumber;

    while (true) {
        menu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                sr.getDetailsAndMarks();
                sr.saveToFile();
                sr.display();
                break;
            case 2:
                cout << "Enter roll number to edit marks: ";
                cin >> sr.rno;
                sr.editMarks(sr.rno);
                sr.display();
                break;
            case 3:
                cout << "Enter roll number to append branch: ";
                cin >> sr.rno;
                sr.loadFromFile(sr.rno);
                sr.appendBranchToFile();
                sr.display();
                break;
            case 4:
                cout << "Enter semester number (1-2): ";
                cin >> semesterNumber;
                sr.loadFromFile(sr.rno);
                sr.calculateAndDisplayCGPA(semesterNumber);
                break;
            case 5:
                cout << "Exiting..." << endl;
                return 0;
            default:
                cout << "Invalid choice!" << endl;
        }
    }
    return 0;
}
*/
// i want a admin and Faculty , i want admin to have powers of setting no of subejcts , name ,credits, while faculty can enter the students marks
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

class SubjectsAdmin{
    
};