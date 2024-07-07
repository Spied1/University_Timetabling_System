#include"Course.hpp"
#include<iostream>

Course::Course(const std::string& courseName, const std::vector<TimeSlot>& preferredTimeSlots)
	: mCourseName(courseName),
	mPreferredTimeSlots(preferredTimeSlots)
{
}

void Course::displayInfo()
{
	std::cout << "Course name: " << mCourseName << " Prefered Times: ";
	for (const auto& x : mPreferredTimeSlots)
	{
		x.displayInfo();
	}
}

std::string Course::getName() const
{
	return mCourseName;
}

void Course::displayInfo() const
{
	std::cout << "Course name: " << mCourseName << " Prefered Times: ";
	for (const auto& x : mPreferredTimeSlots)
	{
		x.displayInfo();
	}
}

const std::vector<TimeSlot>& Course::getPreferreds()
{
	return mPreferredTimeSlots;
}

nlohmann::json Course::toJson()
{
	nlohmann::json j{};

	j["course_name"] = mCourseName;

	for (auto& x : mPreferredTimeSlots)
	{
		j["preferred_time_slot"].push_back(x.toJson());
	}

	return j;
}

Course& Course::fromJson(nlohmann::json temp)
{
	mCourseName = temp["course_name"];

	mPreferredTimeSlots.clear();

	nlohmann::json timeSlots = temp["preferred_time_slot"];

	for (nlohmann::json& x : timeSlots)
	{
		TimeSlot t;

		mPreferredTimeSlots.push_back(t.fromJson(x));
	}

	return *this;
}