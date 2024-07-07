#pragma once
#include<string>
#include"json.hpp"

class TimeSlot
{
private:
	std::string mDay;
	std::string mStartTime;
	std::string mEndTime;

public:
	TimeSlot() = default;

	TimeSlot(std::string day, std::string startTime, std::string endTime);

	void displayInfo() const;

	std::string getDay() const;

	std::string getStartTime() const;

	std::string getEndTime() const;

	bool operator<(const TimeSlot& other) const;

	bool operator==(const TimeSlot& other) const;

	nlohmann::json toJson();

	TimeSlot& fromJson(nlohmann::json temp);
};