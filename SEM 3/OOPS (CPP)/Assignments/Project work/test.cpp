#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

class Marks {
public:
    string type_of_marks[4] = {"theory", "IT", "term_work", "theory_total"};
    float course_mark[4];  // Array to hold marks for each component

    void input_marks() {
        for (int i = 0; i < 4; i++) {
            cout << "Enter " << type_of_marks[i] << " : ";
            cin >> course_mark[i];
        }
    }

    void display_marks() {
        for (int i = 0; i < 4; i++) {
            cout << "Marks for " << type_of_marks[i] << ": " << course_mark[i] << endl;
        }
    }

    float getTheoryTotal() const {
        return course_mark[3];  // Assuming the "theory_total" is stored at index 3
    }
};

class Subject {
public:
    string name;
    Marks marks;  // Containership
    int credits;
    string code;

    Subject() : credits(0), name("undefined"), code("undefined") {}
};

class Semester {
public:
    Subject subjects[10];  // Maximum of 10 subjects per semester
    int numSubjects;

    Semester() : numSubjects(0) {}

    void addSubject(const string& name, int credits) {
        if (numSubjects < 10) {
            subjects[numSubjects].name = name;
            subjects[numSubjects].marks.input_marks();
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
            double gradePoint;
            if(subjects[i].credits==4){
            gradePoint = calculateGradePoint(subjects[i].marks.getTheoryTotal()*(4/5));
            }
            else{
                gradePoint = calculateGradePoint(subjects[i].marks.getTheoryTotal());
                }
            totalPoints += gradePoint * subjects[i].credits;
            totalCredits += subjects[i].credits;
        }

        return (totalCredits > 0) ? (totalPoints / totalCredits) : 0.0;
    }

    double calculateGradePoint(float marks) {
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
        cin.ignore();
        getline(cin, sname);
        cout << "Enter roll number: ";
        getline(cin, rno);

        for (int i = 0; i < 2; i++) {
            cout << "Enter number of subjects for semester " << (i + 1) << ": ";
            int numSubjects;
            cin >> numSubjects;

            for (int j = 0; j < numSubjects; j++) {
                string subjectName;
                int credits;

                cout << "Enter subject name: ";
                cin >> subjectName;

                cout << "Enter credits: ";
                cin >> credits;

                semesters[i].addSubject(subjectName, credits);
            }
        }
    }

    void display() {
        cout << "Name: " << sname << "\nRoll No: " << rno << endl;
        if (!branch.empty()) {
            cout << "Branch: " << branch << endl;
        }

        for (int i = 0; i < 2; i++) {
            cout << "\n\nSemester " << (i + 1) << ":\n\n";
            for (int j = 0; j < semesters[i].numSubjects; j++) {
                cout << "  Subject: " << semesters[i].subjects[j].name<<endl;
                semesters[i].subjects[j].marks.display_marks();
                cout << "Credits: " << semesters[i].subjects[j].credits << endl;
            }
            double cgpa = semesters[i].calculateCGPA();
            cout << "CGPA: " << fixed << setprecision(2) << cgpa << endl;
        }
    }

    void saveToFile() {
        string filename = rno + ".txt";
        ofstream outFile(filename);
        if (outFile.is_open()) {
            outFile << sname << endl;
            outFile << rno << endl;
            outFile << branch << endl;
            for (int i = 0; i < 2; i++) {
                outFile << semesters[i].numSubjects << endl;
                for (int j = 0; j < semesters[i].numSubjects; j++) {
                    outFile << semesters[i].subjects[j].name << " ";
                    for (int k = 0; k < 4; k++) {
                        outFile << semesters[i].subjects[j].marks.course_mark[k] << " ";
                    }
                    outFile << semesters[i].subjects[j].credits << endl;
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
                    inFile >> semesters[i].subjects[j].name;
                    for (int k = 0; k < 4; k++) {
                        inFile >> semesters[i].subjects[j].marks.course_mark[k];
                    }
                    inFile >> semesters[i].subjects[j].credits;
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
        string up_sub_name;
        int up_sem, up_mrks, i;
        cout << "Enter the semester : ";
        cin >> up_sem;
        cout << "Enter the subject name : ";
        cin >> up_sub_name;
        cout << "\nEnter the updated marks in " << up_sub_name << " : ";
        cin >> up_mrks;
        for (i = 0; i < semesters[up_sem - 1].numSubjects; i++) {
            if (up_sub_name == semesters[up_sem - 1].subjects[i].name) {
                semesters[up_sem - 1].subjects[i].marks.course_mark[3] = up_mrks;  // Updating theory_total
            }
        }
        saveToFile();
        cout << "Marks updated for roll number " << roll_no << endl;
    }
};

void menu() {
    cout << "\nExamination Result System Menu:";
    cout << "\n1. Enter result details and display";
    cout << "\n2. Edit marks of a student and display";
    cout << "\n3. Append branch to result file and display";
    cout << "\n0. Exit\n";
}

int main() {
    StudentResult sr;
    int choice;

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
            case 0:
                cout << "Exiting..." << endl;
                return 0;
            default:
                cout << "Invalid choice!" << endl;
        }
    }
    return 0;
}
