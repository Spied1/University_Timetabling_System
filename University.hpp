#pragma once
#include<map>
#include"TimeSlot.hpp"
#include"Course.hpp"
#include"Instructor.hpp"
#include"json.hpp"

class University
{
private:
	std::map<std::string,Course> mCourses;
	std::list<Instructor> mInstructors;
	std::vector<TimeSlot> mTimeSlots;

public:
	University() = default;

	void addCourse(const Course& temp);

	void addInstructor(const Instructor& temp);

	void addTimeSlot(const TimeSlot& temp);

	std::vector<std::pair<Instructor, std::pair<Course, TimeSlot>>> schedule();

	nlohmann::json toJson();
	
	void saveState(const std::string& filename);

	void loadState(const std::string& filename);
};