#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include <cctype>

using namespace std;

// Structure to store student details
struct Student {
    string name;
    string rollNumber;
    string branch;
    double cgpa;
    int backlogs;
    bool isEligible;
    string rejectionReason;
};

// Class to manage the placement eligibility logic
class PlacementChecker {
private:
    // Criteria Constants
    const double MIN_CGPA = 7.0;
    const int MAX_BACKLOGS = 0;

    // Helper function to check if branch is allowed
    bool isBranchAllowed(const string& branch) {
        // Allowing standard engineering branches
        return (branch == "CSE" || branch == "IT" || branch == "ECE" || branch == "EEE");
    }

public:
    // Function to check eligibility
    void evaluateEligibility(Student& s) {
        if (s.cgpa < MIN_CGPA) {
            s.isEligible = false;
            s.rejectionReason = "CGPA is below 7.0";
        } 
        else if (s.backlogs > MAX_BACKLOGS) {
            s.isEligible = false;
            s.rejectionReason = "Active backlogs exceed 0";
        } 
        else if (!isBranchAllowed(s.branch)) {
            s.isEligible = false;
            s.rejectionReason = "Branch (" + s.branch + ") not eligible for this drive";
        } 
        else {
            s.isEligible = true;
            s.rejectionReason = "Meets all criteria";
        }
    }

    // Function to display the eligibility results report
    void displayReport(const vector<Student>& students) {
        cout << "\n===================================================================================\n";
        cout << setw(15) << left << "Roll No"
             << setw(15) << left << "Name"
             << setw(10) << left << "Branch"
             << setw(8) << left << "CGPA"
             << setw(10) << left << "Status"
             << "Remarks/Reason\n";
        cout << "===================================================================================\n";

        for (size_t i = 0; i < students.size(); i++) {
            const Student& s = students[i];

            cout << setw(15) << left << s.rollNumber
                 << setw(15) << left << s.name
                 << setw(10) << left << s.branch
                 << setw(8) << left << fixed << setprecision(2) << s.cgpa;

            if (s.isEligible) {
                cout << setw(10) << left << "ELIGIBLE"
                     << s.rejectionReason << "\n";
            } 
            else {
                cout << setw(10) << left << "NOT ELIGIBLE"
                     << s.rejectionReason << "\n";
            }
        }

        cout << "===================================================================================\n";
    }
};

int main() {
    PlacementChecker checker;
    vector<Student> studentList;
    int numStudents;

    cout << "=== Welcome to the Placement Eligibility Checker App ===\n\n";
    cout << "Enter the number of students to evaluate: ";

    if (!(cin >> numStudents)) {
        cout << "Invalid input. Exiting program.\n";
        return 1;
    }

    // Process each student
    for (int i = 0; i < numStudents; i++) {
        Student s;

        cout << "\n--- Entering Details for Student " << (i + 1) << " ---\n";

        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, s.name);

        cout << "Enter Roll Number: ";
        cin >> s.rollNumber;

        cout << "Enter Branch (e.g., CSE, IT, ECE, EEE, MECH): ";
        cin >> s.branch;

        // Convert branch to uppercase for uniformity
        for (size_t j = 0; j < s.branch.length(); j++) {
            s.branch[j] = static_cast<char>(
                toupper(static_cast<unsigned char>(s.branch[j]))
            );
        }

        cout << "Enter current CGPA: ";
        cin >> s.cgpa;

        cout << "Enter number of active backlogs: ";
        cin >> s.backlogs;

        // Evaluate eligibility
        checker.evaluateEligibility(s);

        // Add to list
        studentList.push_back(s);
    }

    // Generate Final Dashboard Report
    checker.displayReport(studentList);

    return 0;
}
