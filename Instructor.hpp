#pragma once
#include<string>
#include<vector>
#include"TimeSlot.hpp"
#include"Course.hpp"
#include"json.hpp"

class Instructor
{
private:
	std::string mName;
	std::vector<TimeSlot> mAvaliability;
	std::vector<Course> mPreferredCourses;

public:
	Instructor() = default;

	Instructor(std::string name);

	Instructor(std::string name, std::vector<TimeSlot> Avaliability, std::vector<Course> PreferredCourses);

	std::string getName() const;

	void displayInfo();

	void addCourse(const Course& temp);

	std::vector<Course> getCourse();

	void addAvailability(const TimeSlot& temp);

	std::vector<TimeSlot>& getTimes();

	nlohmann::json toJson();

	Instructor& fromJson(nlohmann::json temp);
};