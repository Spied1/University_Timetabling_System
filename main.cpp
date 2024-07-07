#include <iostream>
#include "TimeSlot.hpp"
#include "Course.hpp"
#include "Instructor.hpp"
#include "University.hpp"
#include "json.hpp"

bool test_1()
{
    University uni;

    TimeSlot slot1("Monday", "09:00", "10:00");
    TimeSlot slot2("Monday", "10:00", "11:00");
    TimeSlot slot3("Tuesday", "09:00", "10:00");

    uni.addTimeSlot(slot1);
    uni.addTimeSlot(slot2);
    uni.addTimeSlot(slot3);

    std::vector<TimeSlot> preferredTimes1 = { slot1, slot2 };
    std::vector<TimeSlot> preferredTimes2 = { slot2, slot3 };

    Course course1("Math", preferredTimes1);
    Course course2("Physics", preferredTimes2);

    uni.addCourse(course1);
    uni.addCourse(course2);

    Instructor instructor1("Dr. Smith");
    instructor1.addAvailability(slot1);
    instructor1.addAvailability(slot2);
    instructor1.addCourse(course1);

    Instructor instructor2("Dr. Johnson");
    instructor2.addAvailability(slot2);
    instructor2.addAvailability(slot3);
    instructor2.addCourse(course2);

    uni.addInstructor(instructor1);
    uni.addInstructor(instructor2);

    std::vector<std::pair<Instructor, std::pair<Course, TimeSlot>>> schedule = uni.schedule();

    
    for (const auto& pair : schedule) {
        std::cout << "Instructor: " << pair.first.getName() << " will teach Course: " << pair.second.first.getName() << " at time: ";
        pair.second.second.displayInfo();
    }
    

    if (schedule.size() == 2)
    {
        std::cout << "Test 1 complete" << "\n" << "\n";
        return true;
    }

    std::cout << "Test 1 incomplete" << "\n" << "\n";
    return false;
}

bool test_2()
{
    std::string filename = "university_state.json";
    TimeSlot first("Monday", "11:00", "14:00");
    TimeSlot second("Sunday", "19:00", "21:00");
    TimeSlot third("Sumday", "11:33", "22:22");

    Course f("math", { first,second,third });

    Course s;
    s.fromJson(f.toJson());

    Instructor fil("Dr. Smith", { first,second,third }, { f,s });

    Instructor til;
    til.fromJson(fil.toJson());

    University fe;

    fe.addCourse(f);
    fe.addCourse(s);

    fe.addInstructor(fil);
    fe.addInstructor(til);

    fe.addTimeSlot(first);
    fe.addTimeSlot(second);
    fe.addTimeSlot(third);

    University lf;

    fe.saveState(filename);

    lf.loadState(filename);

    //std::cout << fe.toJson() << std::endl << std::endl;

    //std::cout << lf.toJson();

    if (fe.toJson() == lf.toJson())
    {
        std::cout << "Test 2 complete" << "\n" << "\n";
        return true;
    }

    std::cout << "Test 2 incomplete" << "\n" << "\n";
    return false;
}

int main() {

    if (test_1() == true && test_2() == true)
    {
        std::cout << "all tests complete" << "\n";
    }
    
    return 0;
}
