#include <iostream>
#include <string_view>
#include <vector>
#include <functional>

class Patient;

class Doctor
{
private:
	std::string_view m_name{};
	std::vector<std::reference_wrapper<const Patient>> m_patient{};

public:
	Doctor(std::string_view name):m_name{name}{}

	void addPatient(Patient& patient);

	friend std::ostream& operator<< (std::ostream& out, const Doctor& doctor);
	std::string_view getName() const { return m_name; }
};

class Patient
{
private:
	std::string_view m_name{};
	std::vector<std::reference_wrapper<const Doctor>> m_doctor{};

	void addDoctor(const Doctor& doctor)
	{
		m_doctor.push_back(doctor);
	}

public:
	Patient(std::string_view name) :m_name{ name } {}

	friend void Doctor::addPatient(Patient& patient);

	friend std::ostream& operator<< (std::ostream& out, const Patient& patient);
	std::string_view getName() const { return m_name; }
};

void Doctor::addPatient(Patient& patient)
{
	m_patient.push_back(patient);
	patient.m_doctor.push_back(*this);
}

std::ostream& operator<< (std::ostream& out, const Doctor& doctor)
{
	if (doctor.m_patient.empty())
	{
		out << doctor.m_name << " has no patients right now.";
		return out;
	}
	out << doctor.m_name << " is seeing patients: ";
	for (const auto& patient : doctor.m_patient)
		out << patient.get().getName() << ' ';

	return out;
}

std::ostream& operator<< (std::ostream& out, const Patient& patient)
{
	if (patient.m_doctor.empty())
	{
		out << patient.m_name << " has no doctors right now.";
		return out;
	}
	out << patient.m_name << " is seeing doctors: ";
	for (const auto& doctor : patient.m_doctor)
		out << doctor.get().getName() << ' ';

	return out;
}

int main()
{
	// Create a Patient outside the scope of the Doctor
	Patient dave{ "Dave" };
	Patient frank{ "Frank" };
	Patient betsy{ "Betsy" };

	Doctor james{ "James" };
	Doctor scott{ "Scott" };
	Doctor jessi{ "Jessica" };

	james.addPatient(dave);

	scott.addPatient(dave);
	scott.addPatient(betsy);

	std::cout << james << '\n';
	std::cout << scott << '\n';
	std::cout << dave << '\n';
	std::cout << frank << '\n';
	std::cout << betsy << '\n';
	std::cout << jessi << '\n';

	return 0;
}