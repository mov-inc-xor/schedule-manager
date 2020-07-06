#include "Schedule.h"

std::ostream &operator<<(std::ostream &out, const Schedule &schedule) {
    //std::string WDS[] = {"Пн", "Вт", "Ср", "Чт", "Пт", "Сб", "Вс"};
    std::string PAIR_TIMES[] = {"08:15-09:50", "10:00-11:35", "11:45-13:20", "14:20-15:55", "16:05-17:40", "17:50-19:25"};

    //std::string wd = WDS[schedule.weekday];
    std::string pairTime = PAIR_TIMES[schedule.pairNum];

    out << pairTime << ", " << schedule.audience << ", ";

    for (const Group& group : schedule.groups) {
        out << group << " ";
    }

    out << std::endl << schedule.subject << std::endl;

    for (const Teacher& teacher : schedule.teachers) {
        out << teacher << std::endl;
    }

    return out;
}

void Schedule::setWeekday(int weekday) {
    this->weekday = weekday;
}

void Schedule::setPairNum(int pairNum) {
    this->pairNum = pairNum;
}

void Schedule::setAudienceId(int audienceId, Audience audience) {
    this->audienceId = audienceId;
    this->audience = audience;
}

void Schedule::setSubjectId(int subjectId, Subject subject) {
    this->subjectId = subjectId;
    this->subject = subject;
}

void Schedule::addTeacherId(int teacherId, Teacher teacher) {
    teachersIds.push_back(teacherId);
    teachers.push_back(teacher);
}

void Schedule::addGroupId(int groupId, Group group) {
    groupsIds.push_back(groupId);
    groups.push_back(group);
}

int Schedule::getWeekday() const {
    return weekday;
}

int Schedule::getPairNum() const {
    return pairNum;
}

int Schedule::getAudienceId() const {
    return audienceId;
}

int Schedule::getSubjectId() const {
    return subjectId;
}

const std::vector<int> &Schedule::getTeachersIds() const {
    return teachersIds;
}

const std::vector<int> &Schedule::getGroupsIds() const {
    return groupsIds;
}
