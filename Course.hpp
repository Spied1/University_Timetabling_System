#pragma once
#include<string>
#include<vector>
#include"TimeSlot.hpp"

class Course
{
private:
	std::string mCourseName;
	std::vector<TimeSlot> mPreferredTimeSlots;

public:
	Course() = default;

	Course(const std::string& courseName, const std::vector<TimeSlot>& preferredTimeSlots);

	std::string getName() const;

	void displayInfo();

	void displayInfo() const;

	const std::vector<TimeSlot>& getPreferreds();

	nlohmann::json toJson();
	
	Course& fromJson(nlohmann::json temp);
};