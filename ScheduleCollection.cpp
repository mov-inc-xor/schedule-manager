#include "ScheduleCollection.h"

ScheduleCollection::CollisionStatus ScheduleCollection::collision(const Schedule &schedule) {
    for (const auto & p : items) {
        Schedule itSchedule = p.second;

        if (schedule.getWeekday() == itSchedule.getWeekday() &&
            schedule.getPairNum() == itSchedule.getPairNum()) {

            if (schedule.getAudienceId() == itSchedule.getAudienceId()) {
                return AUDIENCE_COLLISION;
            }

            for (int ts1Id : schedule.getTeachersIds()) {
                for (int ts2Id : itSchedule.getTeachersIds()) {
                    if (ts1Id == ts2Id) {
                        return TEACHER_COLLISION;
                    }
                }
            }

            for (int gs1Id : schedule.getGroupsIds()) {
                for (int gs2Id : itSchedule.getGroupsIds()) {
                    if (gs1Id == gs2Id) {
                        return GROUP_COLLISION;
                    }
                }
            }
        }
    }

    return NO_PROBLEM;
}

int ScheduleCollection::add(const Schedule &schedule) {
    CollisionStatus status = collision(schedule);
    if (status == NO_PROBLEM) {
        return Collection::add(schedule);
    }
    return -1;
}

std::vector<Audience> ScheduleCollection::getFreeAudiences(int weekday, int pairNum, const Collection<Audience>& audiencesCollection) {
    std::vector<std::pair<int, Audience>> freeAudiences;

    for (const auto & pair : audiencesCollection.getItems()) {
        freeAudiences.emplace_back(pair.first, pair.second);
    }

    for (auto & freeAudience : freeAudiences) {
        for (const auto & p : items) {
            Schedule schedule = p.second;
            if (schedule.getWeekday() == weekday &&
                schedule.getPairNum() == pairNum &&
                schedule.getAudienceId() == freeAudience.first) {
                freeAudience.first = -1;
            }
        }
    }

    std::vector<Audience> result;

    for (auto & freeAudience : freeAudiences) {
        if (freeAudience.first != -1) {
            result.push_back(freeAudience.second);
        }
    }

    return result;
}

void ScheduleCollection::printWeekSchedule(std::ostream & out, ScheduleType scheduleType, int id) {
    const std::map<int, Schedule> & scheduleItems = items;
    std::array WDS = {"Понедельник", "Вторник", "Среда", "Четверг", "Пятница", "Суббота", "Воскресенье"};

    int weekdayNum = 0;
    for (std::string weekday : WDS) {
        out << weekday << ':' << std::endl;

        bool has = false;

        for (const auto& scheduleItem : scheduleItems) {
            Schedule schedule = scheduleItem.second;
            if (schedule.getWeekday() == weekdayNum) {
                if (scheduleType == TEACHER) {
                    for (int teacherId : schedule.getTeachersIds()) {
                        if (teacherId == id) {
                            has = true;
                            out << schedule << std::endl;
                        }
                    }
                } else {
                    for (int groupId : schedule.getGroupsIds()) {
                        if (groupId == id) {
                            has = true;
                            out << schedule << std::endl;
                        }
                    }
                }

            }
        }

        if (!has) {
            out << "НЕТ ЗАНЯТИЙ" << std::endl;
        }

        out << std::endl;

        weekdayNum++;
    }

}
