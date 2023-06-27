// Section 19
// Challenge 2
// Automated Grader
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>

using namespace std;

class Student{
    public:
        std::string name;
        std::string answers;
        int score;
};

void print_dotted_line(int total_width){
    std::cout << std::setw(total_width) << std::setfill('-') << "" << std::endl;
    std::cout << std::setfill(' ');
}

int main() {
    
    std::ifstream responses;
    // responses.open("responses.txt"); // for debug
    responses.open("Section19Challenge/Challenge2/responses.txt"); // for regular build

    if (!responses){
        std::cerr << "Problem opening file" << std::endl;
        return 1; // exit the program (main)
    }

    // Extract answer key
    std::string answer_key {};
    responses >> answer_key;

    std::vector<Student> students;
    while (!responses.eof()){
        Student temp;
        responses >> temp.name;
        responses >> temp.answers;

        temp.score = 0;

        for(size_t idx = 0; idx < temp.answers.length(); idx++){
            if (temp.answers[idx] == answer_key[idx]){
                temp.score++;
            }
        }

        students.push_back(temp);
    }

    responses.close();

    const int student_with = 10;
    const int score_width = 8;
    const int total_width {student_with + score_width};

    // header
    std::cout << std::endl;
    std::cout << std::setw(student_with) << std::left << "Name";
    std::cout << std::setw(score_width) << std::right << "Score" << std::endl;
    print_dotted_line(total_width);

    // body
    double total_score {0};
    for (auto student : students){
        total_score += student.score;

        std::cout << std::setw(student_with) << std::left << student.name;
        std::cout << std::setw(score_width) << std::right << student.score;
        std::cout << std::endl;
    }

    double average_score {total_score/students.size()};

    // Footer
    print_dotted_line(total_width);
    std::cout << std::setw(student_with) << std::left << "Average";
    std::cout << std::setw(score_width) << std::right << std::setprecision(3) 
              << average_score << std::endl;

    



    return 0;
}

