#include "Terminal.h"

void Terminal::sendInputError() {
    out << "Введена неверная команда" << std::endl;
}

void Terminal::menu() {
    out << "Вы в главном меню. Введите номер пункта для перехода к следующему меню:" << std::endl;
    out << "1. Предметы" << std::endl;
    out << "2. Преподаватели" << std::endl;
    out << "3. Аудитории" << std::endl;
    out << "4. Группы" << std::endl;
    out << "5. Расписание" << std::endl;
    out << "6. Поиск свободных аудиторий" << std::endl;

    std::string selectedState;
    in >> selectedState;

    if (selectedState == "1") {
        subjects();
    } else if (selectedState == "2") {
        teachers();
    } else if (selectedState == "3") {
        audiences();
    } else if (selectedState == "4") {
        groups();
    } else if (selectedState == "5") {
        schedule();
    } else if (selectedState == "6") {
        searchFreeAudiences();
    } else {
        sendInputError();
        menu();
    }
}

void Terminal::univerObjectMenu(const std::string& univerObjectName, Collection<UniversityObject> & collection) {
    out << "<МЕНЮ \"" << univerObjectName << "\">" << std::endl;
    out << "Список:" << std::endl;

    if (collection.empty()) {
        out << "ПУСТО" << std::endl;
    } else {
        collection.print(out);
    }

    out << "Выберите действие:" << std::endl;
    out << "1. Добавить" << std::endl;
    out << "2. Удалить" << std::endl;
    out << "3. Главное меню" << std::endl;

    std::string cmd;
    in >> cmd;

    if (cmd == "1") {
        out << "Введите имя:" << std::endl;
        std::string objectName;
        in.get();
        std::getline(in, objectName);
        collection.add(UniversityObject(objectName));
        out << objectName << " успешно добавлен." << std::endl;
        univerObjectMenu(univerObjectName, collection);
    } else if (cmd == "2") {
        out << "Введите ID:" << std::endl;
        int objectId;
        in >> objectId;
        if (collection.has(objectId)) {
            std::string objectName = collection.find(objectId).getName();
            collection.remove(objectId);
            out << objectName << " успешно удален." << std::endl;
        } else {
            out << "Объекта с указанным ID не существует." << std::endl;
        }
        univerObjectMenu(univerObjectName, collection);
    } else if (cmd == "3") {
        menu();
    } else {
        sendInputError();
        univerObjectMenu(univerObjectName, collection);
    }
}

void Terminal::subjects() {
    return univerObjectMenu("Предметы", subjectsCollection);
}

void Terminal::teachers() {
    return univerObjectMenu("Преподаватели", teachersCollection);
}

void Terminal::audiences() {
    return univerObjectMenu("Аудитории", audiencesCollection);
}

void Terminal::groups() {
    return univerObjectMenu("Группы", groupsCollection);
}

void Terminal::schedule() {
    out << "<МЕНЮ \"Расписание\">" << std::endl;
    out << "Список:" << std::endl;

    if (scheduleCollection.empty()) {
        out << "ПУСТО" << std::endl;
    } else {
        scheduleCollection.print(out);
    }

    out << "Выберите действие:" << std::endl;
    out << "1. Добавить" << std::endl;
    out << "2. Удалить" << std::endl;
    out << "3. Показать расписание группы" << std::endl;
    out << "4. Показать расписание преподавателя" << std::endl;
    out << "5. Главное меню" << std::endl;

    std::string cmd;
    in >> cmd;

    if (cmd == "1") {
        ScheduleBuilder scheduleBuilder;

        out << "Введите через пробел:" << std::endl <<
               " - номер дня недели(0 - пн, 6 - вс), " << std::endl <<
               " - номер пары(0 - 8:15-9:50, 5 - 17:50-19:25), " << std::endl <<
               " - ID аудитории" << std::endl <<
               " - ID предмета" << std::endl;

        int weekday, pairNum, audId, subjectId;
        in >> weekday >> pairNum >> audId >> subjectId;

        scheduleBuilder.setWeekday(weekday)
                .setPairNum(pairNum)
                .setAudience(audId, audiencesCollection.find(audId))
                .setSubject(subjectId, subjectsCollection.find(subjectId));

        out << "Перечислите через пробел ID преподаватей, которые будут вести занятие:" << std::endl;

        in.get();

        std::string tIdsStr;
        std::getline(in, tIdsStr);
        int tId;
        std::stringstream ss(tIdsStr);
        while (ss >> tId) {
            scheduleBuilder.addTeacher(tId, teachersCollection.find(tId));
        }

        out << "Перечислите через пробел ID групп, для которых состоится занятие:" << std::endl;

        std::string groupsIdsStr;
        std::getline(in, groupsIdsStr);
        int groupId;
        ss = std::stringstream(groupsIdsStr);
        while (ss >> groupId) {
            scheduleBuilder.addGroup(groupId, groupsCollection.find(groupId));
        }

        Schedule result = scheduleBuilder.getResult();
        ScheduleCollection::CollisionStatus collisionStatus = scheduleCollection.collision(result);
        scheduleCollection.add(result);

        switch (collisionStatus) {
            case ScheduleCollection::NO_PROBLEM:
                out << "Данные о расписании успешно добавлены." << std::endl;
                break;
            case ScheduleCollection::AUDIENCE_COLLISION:
                out << "Ошибка! Найдена коллизия с аудиториями." << std::endl;
                break;
            case ScheduleCollection::TEACHER_COLLISION:
                out << "Ошибка! Найдена коллизия с преподавателями." << std::endl;
                break;
            case ScheduleCollection::GROUP_COLLISION:
                out << "Ошибка! Найдена коллизия с группами." << std::endl;
                break;
        }

        return schedule();
    } else if (cmd == "2") {
        out << "Введите ID расписания:" << std::endl;
        int scheduleId;
        in >> scheduleId;
        scheduleCollection.remove(scheduleId);
        out << "Данные о расписании успешно удалены." << std::endl;
        return schedule();
    } else if (cmd == "3") {
        out << "Введите ID группы:" << std::endl;
        int id;
        in >> id;
        out << "Расписание группы:" << std::endl;
        scheduleCollection.printWeekSchedule(out, ScheduleCollection::TEACHER, id);
        return schedule();
    } else if (cmd == "4") {
        out << "Введите ID преподавателя:" << std::endl;
        int id;
        in >> id;
        out << "Расписание преподавателя:" << std::endl;
        scheduleCollection.printWeekSchedule(out, ScheduleCollection::TEACHER, id);
        return schedule();
    } else if (cmd == "5") {
        return menu();
    } else {
        sendInputError();
        return schedule();
    }
}

void Terminal::searchFreeAudiences() {
    out << "Введите через пробел интересующий день недели(0 - пн, 6 - вс) и номер пары по расписанию(0 - 08:15-09:50, 5 - 17:50-19:25):" << std::endl;

    int weekday, pairNum;
    in >> weekday >> pairNum;

    std::vector<Audience> freeAudiences = scheduleCollection.getFreeAudiences(weekday, pairNum, audiencesCollection);

    if (freeAudiences.empty()) {
        out << "Свободных аудиторий не найдено." << std::endl;
    } else {
        out << "Найдены следующие аудитории:" << std::endl;

        for (const auto& audience : freeAudiences) {
            out << audience << std::endl;
        }
    }

    menu();
}

void Terminal::start() {
    menu();
}
