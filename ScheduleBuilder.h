#pragma once

#include "Schedule.h"

class ScheduleBuilder {
private:
    Schedule schedule;
public:
    ScheduleBuilder & setWeekday(int weekday);
    ScheduleBuilder & setPairNum(int pairNum);
    ScheduleBuilder & setAudience(int audienceId, const Audience& audience);
    ScheduleBuilder & setSubject(int subjectId, const Subject& subject);
    ScheduleBuilder & addTeacher(int teacherId, const Teacher& teacher);
    ScheduleBuilder & addGroup(int groupId, const Group& group);

    Schedule getResult();
};