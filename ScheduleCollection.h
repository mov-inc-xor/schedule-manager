#pragma once

#include "Collection.h"
#include "Schedule.h"

class ScheduleCollection : public Collection<Schedule> {
public:
    enum CollisionStatus {NO_PROBLEM, AUDIENCE_COLLISION, TEACHER_COLLISION, GROUP_COLLISION};
    enum ScheduleType {TEACHER, GROUP};

    CollisionStatus collision(const Schedule& schedule);
    int add(const Schedule& schedule) override;
    std::vector<Audience> getFreeAudiences(int weekday, int pairNum, const Collection<Audience>& audiencesCollection);
    void printWeekSchedule(std::ostream & out, ScheduleType scheduleType, int id);
};
