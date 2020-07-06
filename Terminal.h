#pragma once

#include <istream>
#include <ostream>
#include <sstream>
#include <vector>

#include "Collection.h"
#include "UniversityObject.h"
#include "ScheduleCollection.h"
#include "ScheduleBuilder.h"

class Terminal {
private:
    std::istream & in;
    std::ostream & out;

    void sendInputError();

    void menu();
    void univerObjectMenu(const std::string& univerObjectName, Collection<UniversityObject> & collection);
    void subjects();
    void teachers();
    void audiences();
    void groups();
    void schedule();
    void searchFreeAudiences();

    Collection<Subject> subjectsCollection;
    Collection<Teacher> teachersCollection;
    Collection<Audience> audiencesCollection;
    Collection<Group> groupsCollection;

    ScheduleCollection scheduleCollection;
public:
    Terminal(std::istream & in, std::ostream & out) : in(in), out(out) {}
    void start();
};
