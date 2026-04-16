#include <iostream>
#include <string>

using namespace std;

struct Student {
    string name;
    string* mentors;
    int numMentors;
    int priority;

    Student(string n, string* m, int num, int p = 0)
        : name(n), mentors(m), numMentors(num), priority(p) {}

    static bool compare(const Student& a, const Student& b) {
        return a.priority > b.priority;
    }
};

struct Mentor {
    string name;
    string* students;
    int numStudents;
    int slots;

    Mentor(string n, string* s, int num, int sl)
        : name(n), students(s), numStudents(num), slots(sl) {}
};

int getStudentPriority(const Student& student, Mentor* mentors, int numMentors) {
    int score = 0;
    for (int i = 0; i < numMentors; ++i) {
        for (int j = 0; j < student.numMentors; ++j) {
            if (student.mentors[j] == mentors[i].name) {
                score += (student.numMentors - j); 
                break;
            }
        }
    }
    return score;
}

int getMentorPriority(const Mentor& mentor, const Student& student) {
    for (int i = 0; i < mentor.numStudents; ++i) {
        if (mentor.students[i] == student.name) {
            return (mentor.numStudents - i);
        }
    }
    return 0; 
}

void swap(Student& a, Student& b) {
    Student temp = a;
    a = b;
    b = temp;
}

void quickSort(Student* students, int left, int right) {
    if (left >= right) return;
    
    int pivot = left + (right - left) / 2;
    swap(students[left], students[pivot]);
    
    int i = left + 1, j = right;
    
    while (i <= j) {
        while (i <= j && Student::compare(students[i], students[left])) i++;
        while (i <= j && Student::compare(students[left], students[j])) j--;
        
        if (i <= j) {
            swap(students[i], students[j]);
            i++;
            j--;
        }
    }
    swap(students[left], students[j]);
    
    quickSort(students, left, j);
    quickSort(students, i, right);
}

void sortStudents(Student* students, int numStudents) {
    quickSort(students, 0, numStudents - 1);
}

void assign(Student* students, int numStudents, Mentor* mentors, int numMentors) {
    for (int i = 0; i < numStudents; ++i) {
        students[i].priority = getStudentPriority(students[i], mentors, numMentors);
    }

    sortStudents(students, numStudents); 

    for (int i = 0; i < numStudents; ++i) {
        Student& currentStudent = students[i];

       
        for (int j = 0; j < currentStudent.numMentors - 1; ++j) {
            for (int k = 0; k < currentStudent.numMentors - j - 1; ++k) {
                string mentorA = currentStudent.mentors[k];
                string mentorB = currentStudent.mentors[k + 1];
                int priorityA = 0;
                int priorityB = 0;
                for (int m = 0; m < numMentors; ++m) {
                    if (mentors[m].name == mentorA) 
                        priorityA = getMentorPriority(mentors[m], currentStudent);
                    if (mentors[m].name == mentorB) 
                        priorityB = getMentorPriority(mentors[m], currentStudent);
                }
                if (priorityA < priorityB) {
                    swap(currentStudent.mentors[k], currentStudent.mentors[k + 1]);
                }
            }
        }

       
        for (int j = 0; j < currentStudent.numMentors; ++j) {
            for (int k = 0; k < numMentors; ++k) {
                if (mentors[k].name == currentStudent.mentors[j] && mentors[k].slots > 0) {
                    cout << currentStudent.name << " assigned to " << mentors[k].name << endl;
                    mentors[k].slots--;
                    goto nextStudent; 
                }
            }
        }

        cout << currentStudent.name << " not assigned" << endl;

    nextStudent: ;
    }
}

int main() {

	Student students[3] = {
	    Student("Student1", new string[3]{"MentorA", "MentorC", "MentorB"}, 3),
	    Student("Student2", new string[3]{"MentorA", "MentorC", "MentorB"}, 3),
	    Student("Student3", new string[3]{"MentorA", "MentorC", "MentorB"}, 3)
	};
	
	Mentor mentors[3] = {
	    Mentor("MentorA", new string[3]{"Student3", "Student1", "Student2"}, 3, 1),
	    Mentor("MentorB", new string[3]{"Student1", "Student3", "Student2"}, 3, 1),
	    Mentor("MentorC", new string[3]{"Student2", "Student1", "Student3"}, 3, 1)
	};

    assign(students, 3, mentors, 3);

    for (int i = 0; i < 3; ++i) {
        delete[] students[i].mentors;
        delete[] mentors[i].students;
    }

    return 0;
}
