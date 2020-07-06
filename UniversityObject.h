#pragma once

#include <string>
#include <utility>

class UniversityObject {
private:
    std::string name;
public:
    UniversityObject() : name("-") {}
    explicit UniversityObject(std::string name) : name(std::move(name)) {}
    UniversityObject(const UniversityObject & uo) = default;

    std::string getName() {
        return name;
    }

    friend std::ostream& operator<< (std::ostream &out, const UniversityObject & uo) {
        out << uo.name;
        return out;
    }
};

typedef UniversityObject Subject;
typedef UniversityObject Teacher;
typedef UniversityObject Audience;
typedef UniversityObject Group;