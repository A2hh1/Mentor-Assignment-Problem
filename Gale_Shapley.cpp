#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Student {
    string name;
    vector<string> mentors;
    int nextProposal;

    Student(string n, vector<string> m)
        : name(n), mentors(m), nextProposal(0) {}
};

struct Mentor {
    string name;
    vector<string> students;
    int currentStudent; // index of assigned student

    Mentor(string n, vector<string> s)
        : name(n), students(s), currentStudent(-1) {}
};

// Check if mentor prefers s1 over s2
bool prefers(Mentor& mentor, string s1, string s2) {
    for (int i = 0; i < mentor.students.size(); i++) {
        if (mentor.students[i] == s1) return true;
        if (mentor.students[i] == s2) return false;
    }
    return false;
}

void stableMatching(vector<Student>& students, vector<Mentor>& mentors) {
    int n = students.size();
    int m = mentors.size();

    while (true) {
        bool foundFree = false;

        for (int i = 0; i < n; i++) {
            // check if student is already assigned
            bool isFree = true;
            for (int j = 0; j < m; j++) {
                if (mentors[j].currentStudent == i) {
                    isFree = false;
                    break;
                }
            }

            if (!isFree) continue;

            if (students[i].nextProposal >= students[i].mentors.size())
                continue;

            foundFree = true;

            string mentorName = students[i].mentors[students[i].nextProposal++];

            for (int j = 0; j < m; j++) {
                if (mentors[j].name == mentorName) {

                    if (mentors[j].currentStudent == -1) {
                        mentors[j].currentStudent = i;
                    } else {
                        int other = mentors[j].currentStudent;

                        if (prefers(mentors[j], students[i].name, students[other].name)) {
                            mentors[j].currentStudent = i;
                        }
                    }
                    break;
                }
            }
        }

        if (!foundFree) break;
    }

    // Print results
    cout << "\nFinal Matching:\n";
    for (int j = 0; j < m; j++) {
        if (mentors[j].currentStudent != -1) {
            cout << students[mentors[j].currentStudent].name
                 << " -> " << mentors[j].name << endl;
        }
    }
}

int main() {
    vector<Student> students = {
        Student("Student1", {"MentorA", "MentorB", "MentorC"}),
        Student("Student2", {"MentorA", "MentorB", "MentorC"}),
        Student("Student3", {"MentorA", "MentorB", "MentorC"})
    };

    vector<Mentor> mentors = {
        Mentor("MentorA", {"Student3", "Student1", "Student2"}),
        Mentor("MentorC", {"Student1", "Student3", "Student2"}),
        Mentor("MentorB", {"Student2", "Student1", "Student3"})
    };

    stableMatching(students, mentors);

    return 0;
}
