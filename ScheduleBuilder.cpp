#include "ScheduleBuilder.h"

ScheduleBuilder &ScheduleBuilder::setWeekday(int weekday) {
    schedule.setWeekday(weekday);
    return *this;
}

ScheduleBuilder &ScheduleBuilder::setPairNum(int pairNum) {
    schedule.setPairNum(pairNum);
    return *this;
}

ScheduleBuilder &ScheduleBuilder::setAudience(int audienceId, const Audience& audience) {
    schedule.setAudienceId(audienceId, audience);
    return *this;
}

ScheduleBuilder &ScheduleBuilder::setSubject(int subjectId, const Subject& subject) {
    schedule.setSubjectId(subjectId, subject);
    return *this;
}

ScheduleBuilder &ScheduleBuilder::addTeacher(int teacherId, const Teacher& teacher) {
    schedule.addTeacherId(teacherId, teacher);
    return *this;
}

ScheduleBuilder &ScheduleBuilder::addGroup(int groupId, const Group& group) {
    schedule.addGroupId(groupId, group);
    return *this;
}

Schedule ScheduleBuilder::getResult() {
    return schedule;
}
