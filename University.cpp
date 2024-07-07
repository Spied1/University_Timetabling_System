#include<iostream>
#include<fstream>
#include"University.hpp"

void University::addCourse(const Course& temp)
{
	mCourses[temp.getName()] = temp;
}

void University::addInstructor(const Instructor& temp)
{
	mInstructors.push_back(temp);
}

void University::addTimeSlot(const TimeSlot& temp)
{
	mTimeSlots.push_back(temp);
}

std::vector<std::pair<Instructor, std::pair<Course, TimeSlot>>> University::schedule()
{
    std::vector<std::pair<Instructor, std::pair<Course,TimeSlot>>> scheduled;
    std::vector<TimeSlot> availableTimeSlots = mTimeSlots;

    for (auto& inst : mInstructors)
    {
        std::vector<TimeSlot> instructorAvailability = inst.getTimes();
        std::vector<Course> instructorPreferredCourses = inst.getCourse();

        for (const auto& course : instructorPreferredCourses) 
        {
            auto courseIt = mCourses.find(course.getName());

            if (courseIt != mCourses.end()) 
            {
                std::vector<TimeSlot> coursePreferredTimes = courseIt->second.getPreferreds();

                for (const auto& courseTime : coursePreferredTimes) 
                {
                    auto instructorTimeIt = std::find(instructorAvailability.begin(), instructorAvailability.end(), courseTime);

                    if (instructorTimeIt != instructorAvailability.end()) 
                    {
                        auto timeSlotIt = std::find(availableTimeSlots.begin(), availableTimeSlots.end(), courseTime);

                        if (timeSlotIt != availableTimeSlots.end()) 
                        {
                            std::pair<Instructor, std::pair<Course, TimeSlot>> scheduledPair = { inst,  { courseIt->second, *timeSlotIt } };
                            scheduled.push_back(scheduledPair);
                            availableTimeSlots.erase(timeSlotIt);
                            break;
                        }
                    }
                }
            }
        }
    }

    return scheduled;
}

nlohmann::json University::toJson()
{
    nlohmann::json j;

    for (auto& x : mCourses)
    {
        j["courses"].push_back(x.second.toJson());
    }

    for (auto& x : mInstructors)
    {
        j["instructors"].push_back(x.toJson());
    }

    for (auto& x : mTimeSlots)
    {
        j["time_slots"].push_back(x.toJson());
    }

    return j;
}

void University::saveState(const std::string& filename)
{
    nlohmann::json j = toJson();

    std::ofstream file(filename);

    if (file.is_open())
    {
        file << j.dump(4);
        file.close();
    }

    else
    {
        throw std::runtime_error("Unable to open file for writing");
    }
}

void University::loadState(const std::string& filename)
{
    std::ifstream file(filename);
    nlohmann::json js;
    if (file.is_open())
    {
        file >> js;
        file.close();
    }
    else
    {
        throw std::runtime_error("Unable to open file for reading");
    }

    mCourses.clear();
    mInstructors.clear();
    mTimeSlots.clear();

    nlohmann::json courses = js["courses"];

    for (nlohmann::json& x : courses)
    {
        Course c;

        mCourses[c.fromJson(x).getName()] = c;
    }

    nlohmann::json instructors = js["instructors"];

    for (nlohmann::json& x : instructors)
    {
        Instructor i;

        mInstructors.push_back(i.fromJson(x));
    }

    nlohmann::json time_slots = js["time_slots"];

    for (nlohmann::json& x : time_slots)
    {
        TimeSlot t;

        mTimeSlots.push_back(t.fromJson(x));
    }
}