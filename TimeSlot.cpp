#include"TimeSlot.hpp"
#include<iostream>
#include<string>

TimeSlot::TimeSlot(std::string day, std::string startTime, std::string endTime) :
	mDay(day),
	mStartTime(startTime),
	mEndTime(endTime)
{
}

void TimeSlot::displayInfo() const
{
	std::cout << "day: " << mDay << " starting: " << mStartTime << " ending: " << mEndTime << "\n";
}

std::string TimeSlot::getDay() const
{
	return mDay;
}

std::string TimeSlot::getStartTime() const
{
	return mStartTime;
}

std::string TimeSlot::getEndTime() const
{
	return mEndTime;
}

bool TimeSlot::operator<(const TimeSlot& other) const 
{
	if (mDay < other.mDay) return true;
	if (mDay > other.mDay) return false;
	if (mStartTime < other.mStartTime) return true;
	if (mStartTime > other.mStartTime) return false;
	return mEndTime < other.mEndTime;
}

bool TimeSlot::operator==(const TimeSlot& other) const 
{
	return (mDay == other.mDay) &&
		(mStartTime == other.mStartTime) &&
		(mEndTime == other.mEndTime);
}

nlohmann::json TimeSlot::toJson()
{
	nlohmann::json j{};

	j["day"] = mDay;
	j["start_time"] = mStartTime;
	j["end_time"] = mEndTime;

	return j;
}

TimeSlot& TimeSlot::fromJson(nlohmann::json temp)
{
	mDay = temp["day"];
	mStartTime = temp["start_time"];
	mEndTime = temp["end_time"];

	return *this;
}