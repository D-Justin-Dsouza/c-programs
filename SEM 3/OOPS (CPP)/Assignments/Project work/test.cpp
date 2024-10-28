/*#include <iostream>
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
*/
//new change
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

    // Input marks for the subject and ask for maximum total marks
    void input_marks() {
        cout << "Enter the maximum total marks for the subject: ";
        cin >> total_max_marks;

        float total_marks_obtained = 0;
        for (int i = 0; i < 3; i++) {
            cout << "Enter marks obtained in " << type_of_marks[i] << ": ";
            cin >> course_mark[i];
            total_marks_obtained += course_mark[i];
        }

        // Validate that total marks do not exceed the maximum
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

    // Display the marks
    void display_marks() const {
        cout << "Total Maximum Marks: " << total_max_marks << endl;
        float total_obtained = 0;
        for (int i = 0; i < 3; i++) {
            cout << "Marks for " << type_of_marks[i] << ": " << course_mark[i] << endl;
            total_obtained += course_mark[i];
        }
        cout << "Total Marks Obtained: " << total_obtained << " / " << total_max_marks << endl;
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

    Subject() : credits(0), name("undefined"), code("undefined") {}

    // Input subject details including marks
    void inputSubject() {
        cout << "Enter course name: ";
        cin.ignore();  // To handle any leftover newline characters
        getline(cin, name);
        cout << "Enter course code: ";
        getline(cin, code);
        cout << "Enter credits for the subject: ";
        cin >> credits;
        input_marks();  // Marks input from the Marks class
    }

    void displaySubject() const {
        cout << "Subject: " << name << " (Code: " << code << ")" << endl;
        display_marks();
        cout << "Credits: " << credits << endl;
    }
};

// Class to represent a semester, inherits from Subject
class Semester : public Subject {
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

    void displaySemester() const {
        cout << "Semester: " << semesterName << endl;
        for (int i = 0; i < subjectCount; i++) {
            subjects[i].displaySubject();
        }
    }

    double calculateGradePoint(float marks) const {
        if (marks >= 90) return 10.0;  // A+
        if (marks >= 80) return 9.0;   // A
        if (marks >= 70) return 8.0;   // B+
        if (marks >= 60) return 7.0;   // B
        if (marks >= 50) return 6.0;   // C
        if (marks >= 40) return 5.0;   // D
        return 0.0;  // F
    }

    double calculateCGPA() const {
        double totalPoints = 0.0;
        int totalCredits = 0;

        for (int i = 0; i < subjectCount; i++) {
            double gradePoint = calculateGradePoint(subjects[i].getTotalMarksObtained());
            totalPoints += gradePoint * subjects[i].credits;
            totalCredits += subjects[i].credits;
        }

        return (totalCredits > 0) ? (totalPoints / totalCredits) : 0.0;
    }
};

// Class to handle student result, inherits from Semester
class StudentResult : public Semester {
public:
    string studentName, rollNo, branch;

    void inputStudentDetails() {
        cout << "Enter student name: ";
        cin.ignore();
        getline(cin, studentName);
        cout << "Enter roll number: ";
        getline(cin, rollNo);
        cout << "Enter branch: ";
        getline(cin, branch);
    }

    void displayStudentDetails() const {
        cout << "Name: " << studentName << "\nRoll No: " << rollNo << "\nBranch: " << branch << endl;
        displaySemester();  // Display semester and subject details
        cout << "CGPA: " << fixed << setprecision(2) << calculateCGPA() << endl;
    }
    void saveToFile() const {
        // string filename = rollNo + ".txt";
        // ofstream outFile(filename);
        // if (outFile.is_open()) {
        //     outFile << studentName << endl;
        //     outFile << rollNo << endl;
        //     outFile << branch << endl;
            
        //     // Save both semesters
        //     outFile << "Semester 1: " << endl;
        //     outFile << subjectCount << endl;  // Subject count for Semester 1
        //     for (int i = 0; i < subjectCount; i++) {
        //         outFile << subjects[i].name << " " << subjects[i].code << " ";
        //         for (int k = 0; k < 3; k++) {
        //             outFile << subjects[i].course_mark[k] << " ";
        //         }
        //         outFile << subjects[i].total_max_marks << " " << subjects[i].credits << endl;
        //     }
        //     outFile.close();
        //     cout << "Result saved in file: " << filename << endl;
        // } else {
        //     cout << "Error opening file!" << endl;
        // }
        //adujust the code for two cases, one for semester 1 ,where the file is created and fresh data is written including student details and semester 1 marks ,and for semester 2 where the file is appended and semester 2 data is written
        string filename = rollNo + ".txt";
        fstream file(filename, ios::out | ios::app);
        if(file.seekp(0, ios::end).tellp() == 0){
            file << studentName << endl;
            file << rollNo << endl;
            file << branch << endl;
        }
        file << semesterName << endl;
        file << subjectCount << endl;
        for (int i = 0; i < subjectCount; i++) {
            file << subjects[i].name << " " << subjects[i].code << " ";
            for (int k = 0; k < 3; k++) {
                file << subjects[i].course_mark[k] << " ";
            }
            file << subjects[i].total_max_marks << " " << subjects[i].credits << endl;
        }
    }

    void loadFromFile(string &rollNo) {
        string filename = rollNo + ".txt";
        fstream file(filename, ios::in | ios::binary);
        if (!file.is_open()) {
            cout << "Error opening file!" << endl;
            return;
        }
        getline(file, studentName);
        getline(file, rollNo);
        getline(file, branch);
        getline(file, semesterName);
        file >> subjectCount;
        file.ignore();
        for (int i = 0; i < subjectCount; i++) {
            getline(file, subjects[i].name, ' ');
            file >> subjects[i].code;
            for (int k = 0; k < 3; k++) {
                file >> subjects[i].course_mark[k];
            }
            file >> subjects[i].total_max_marks >> subjects[i].credits;
        }
        file.close();
    }

   /* void editMarks(string &roll_no) {
        string filename = roll_no + ".txt";
        fstream file(filename, ios::in | ios::out);

        if (!file.is_open()) {
            cout << "Error opening file!" << endl;
            return;
        }

        // Load the student details into memory
        loadFromFile(roll_no);

        // Ask user for the subject name to update marks
        string up_sub_name;
        int new_marks;
        cout << "Enter the subject name to update: ";
        cin.ignore();
        getline(cin, up_sub_name);  // Fixes issue with spaces and newlines

        bool subject_found = false;
        for (int i = 0; i < subjectCount; i++) {
            if (up_sub_name == subjects[i].name) {
                cout << "Enter the updated marks: ";
                cin >> new_marks;
                subjects[i].course_mark[0] = new_marks;  // Update only the first mark as an example
                subject_found = true;
                break;
            }
        }

        if (!subject_found) {
            cout << "Subject not found!" << endl;
        } else {
            cout << "Marks updated successfully for subject " << up_sub_name << endl;
            saveToFile();  // Save updated details back to file
        }

        file.close();
    }*/
    void editMarks(string &roll_no) {
        string filename = roll_no + ".txt";
        fstream file(filename, ios::in | ios::out);

        if (!file.is_open()) {
            cout << "Error opening file!" << endl;
            return;
        }

        // Load the student details into memory
        loadFromFile(roll_no);

        // Ask user for the subject name to update marks
        string up_sub_name;
        cout << "Enter the subject name to update: ";
        cin.ignore();
        getline(cin, up_sub_name);  // Capture the full subject name

        bool subject_found = false;
        // Search through all semesters and subjects
        for (int sem = 0; sem < semesterCount; sem++) {
            for (int i = 0; i < semesters[sem].subjectCount; i++) {
                // Remove any trailing or leading spaces for accurate comparison
                if (trim(semesters[sem].subjects[i].name) == trim(up_sub_name)) {
                    cout << "Enter updated marks for " << semesters[sem].subjects[i].name << ":\n";
                    for (int k = 0; k < 3; k++) {
                        cout << type_of_marks[k] << ": ";
                        cin >> semesters[sem].subjects[i].course_mark[k];
                    }
                    subject_found = true;
                    break;  // Exit loop once subject is found and updated
                }
            }
            if (subject_found) {
                break;  // No need to search further if subject is already found
            }
        }

        if (!subject_found) {
            cout << "Subject not found!" << endl;
        } else {
            cout << "Marks updated successfully for subject " << up_sub_name << endl;
            // Save the updated details back to the file
            saveToFile();
        }

        file.close();
    }

    void appendBranchToFile() {
        string filename = rollNo + ".txt";
        fstream file(filename, ios::in | ios::out);

        if (!file.is_open()) {
            cout << "Error opening file!" << endl;
            return;
        }

        // Move the pointer to the end of the file for appending
        file.seekp(0, ios::end);
        file << "\nBranch: " << branch << endl;

        file.close();
        cout << "Branch appended to file: " << filename << endl;
    }
    void displayStudentDetailsFromFile() const {
        string filename = rollNo + ".txt";
        ifstream inFile(filename);

        if (inFile.is_open()) {
            string line;
            // Display the contents of the file
            while (getline(inFile, line)) {
                cout << line << endl;
            }
            inFile.close();
        } else {
            cout << "Error opening file!" << endl;
        }
    }
};

int main() {
    StudentResult sr;
    string rollNo;
    int choice;

    while (true) {
        cout << "\nExamination Result System Menu:";
        cout << "\n1. Enter result details and display";
        cout << "\n2. Edit marks of a student and display";
        cout << "\n3. Append branch to result file and display";
        cout << "\n0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                sr.inputStudentDetails();
                sr.inputSemesterDetails("Semester 1");
                sr.saveToFile(); 
                sr.inputSemesterDetails("Semester 2");
                sr.saveToFile();  // Save to file after entering details
                sr.displayStudentDetails();  // Display details directly
                break;            
            case 2:
                cout << "Enter roll number to edit marks: ";
                cin >> rollNo;
                sr.editMarks(rollNo);  // Edit marks for the student
                sr.displayStudentDetails();  // Display updated details
                break;
            case 3:
                cout << "Enter roll number to append branch: ";
                cin >> sr.rollNo;
                sr.loadFromFile(sr.rollNo);  // Load student details from file
                sr.appendBranchToFile();  // Append branch
                sr.displayStudentDetails();  // Display updated details
                break;
            case 0:
                return 0;  // Exit the program
            default:
                cout << "Invalid choice! Try again.\n";
        }
    }

    return 0;
}