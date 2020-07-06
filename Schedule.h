#pragma once

#include <iostream>
#include <utility>
#include <vector>
#include <ostream>

#include "Collection.h"
#include "UniversityObject.h"

class Schedule {
private:
    int weekday{};
    int pairNum{};

    int audienceId{};
    Audience audience;

    int subjectId{};
    Subject subject;

    std::vector<int> teachersIds;
    std::vector<int> groupsIds;

    std::vector<Teacher> teachers;
    std::vector<Group> groups;
public:
    Schedule() = default;
    Schedule(const Schedule & schedule) = default;

    friend std::ostream& operator<< (std::ostream &out, const Schedule & schedule);

    void setWeekday(int weekday);
    void setPairNum(int pairNum);
    void setAudienceId(int audienceId, Audience audience);
    void setSubjectId(int subjectId, Subject subject);
    void addTeacherId(int teacherId, Teacher teacher);
    void addGroupId(int groupId, Group group);

    int getWeekday() const;
    int getPairNum() const;
    int getAudienceId() const;
    int getSubjectId() const;
    const std::vector<int> & getTeachersIds() const;
    const std::vector<int> & getGroupsIds() const;
};