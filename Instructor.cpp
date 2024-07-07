#include<iostream>
#include<string>
#include"Instructor.hpp"

Instructor::Instructor(std::string name):
	mName(name)
{
}

Instructor::Instructor(std::string name, std::vector<TimeSlot> Avaliability, std::vector<Course> PreferredCourses) :
	mName(name),
	mAvaliability(Avaliability),
	mPreferredCourses(PreferredCourses)
{

}

std::string Instructor::getName() const
{
	return mName;
}

void Instructor::displayInfo()
{
	std::cout << "Name: " << mName << " avaliability: \n";
	for (const auto& x : mAvaliability)
	{
		x.displayInfo();
	}

	std::cout << "Preffered Courses: \n";

	for (const auto& x : mPreferredCourses)
	{
		x.displayInfo();
	}
}

void Instructor::addCourse(const Course& temp)
{
	mPreferredCourses.push_back(temp);
}

std::vector<Course> Instructor::getCourse()
{
	return mPreferredCourses;
}

void Instructor::addAvailability(const TimeSlot& temp)
{
	mAvaliability.push_back(temp);
}

std::vector<TimeSlot>& Instructor::getTimes()
{
	return mAvaliability;
}

nlohmann::json Instructor::toJson()
{
	nlohmann::json j;
	j["name"] = mName;

	for (auto& x : mAvaliability)
	{
		j["avaliability"].push_back(x.toJson());
	}

	for (auto& x : mPreferredCourses)
	{
		j["preferred_courses"].push_back(x.toJson());
	}

	return j;
}

Instructor& Instructor::fromJson(nlohmann::json temp)
{
	mName = temp["name"];

	nlohmann::json avaliability = temp["avaliability"];

	mAvaliability.clear();
	mPreferredCourses.clear();
	for (nlohmann::json& x : avaliability)
	{
		TimeSlot t;

		mAvaliability.push_back(t.fromJson(x));
	}

	nlohmann::json preferred_courses = temp["preferred_courses"];

	for (nlohmann::json& x : preferred_courses)
	{
		Course c;

		mPreferredCourses.push_back(c.fromJson(x));
	}

	return *this;
}
