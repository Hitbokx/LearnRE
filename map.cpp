#include <iostream>
#include <vector>
#include <algorithm>

struct StudentGrade
{
	std::string name{};
	std::string grade{};
};

class GradeMap
{
private:
	std::vector<StudentGrade> m_map{};
	
public:
	std::string& operator[](std::string str);
};

std::string& GradeMap::operator[](std::string s_name)
{
	auto found{ std::find_if(m_map.begin(),m_map.end(),
		[&](const auto& student)
		{
			return (student.name.find(s_name) != std::string_view::npos);
			//return student.name == s_name;
		}
	) };

	if (found == m_map.end())
	{
		StudentGrade student{ s_name };
		m_map.push_back(student);
		return m_map.back().grade;
	}
	else
	{
		return (*found).grade;
	}
}

int main()
{
	GradeMap grades{};

	grades["Joe"] = 'A';
	grades["Frank"] = 'B';
	grades["Gauri"] = "A++";

	std::cout << "Joe has a grade of " << grades["Joe"] << '\n';
	std::cout << "Frank has a grade of " << grades["Frank"] << '\n';
	std::cout << "Gauri has a grade of " << grades["Gauri"] << '\n';
	
	return 0;
}
