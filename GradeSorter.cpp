#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

struct Student
{
	std::string name{};
	int grades{};
};

using vectorArray = std::vector<Student>;

int getInput()
{
	std::cout << "Please enter the number of students you want: ";
	int input{};
	std::cin >> input;
	return input;
}

std::vector<int> returnGrades(const vectorArray& students, int numStudents)
{
	std::vector<int> studentGrades(numStudents);

	for (int i{ 0 }; Student student : students)
	{
		studentGrades[i] = { student.grades };
		++i;
	}
	return studentGrades;
}

int main()
{
	int numStudents{ getInput() };
	std::vector<Student> students{ static_cast<size_t>(numStudents) };
	std::cout << '\n';

	for (int i{ 0 }; Student student : students)
	{
		std::cout << "Please enter the name of a student: ";
		std::cin >> student.name;

		std::cout << "Please enter his grades: ";
		std::cin >> student.grades;
		std::cout << '\n';

		students[i] = { student.name, student.grades };
		++i;
	}

	std::vector<int> studentGrades{ returnGrades(students, numStudents) };

	std::sort(std::rbegin(studentGrades), std::rend(studentGrades));

	for (int i{ 0 }; Student student : students)
	{
		for (Student student : students)
		{
			if (student.grades == studentGrades[i])
			{
				std::cout << student.name << " got a grade of " << studentGrades[i] << '\n';
			}
		}
		++i;
	}

	return 0;
}