# Менеджер расписания
Менеджер расписания учебного заведения, написанный в рамках прохождения курса "Объектно ориентированное программирование"

## Задание
Система обеспечивает составление расписания некоторого учебного заведения,
внесение в него изменений, выдачу полного расписания и дополнительной
информации (например, по итоговому расписанию составляется расписание
указанной группы или указанного преподавателя на заданный день или неделю).
В расписании фиксируются время и место проведения занятия, предмет и
преподаватель, проводящий занятие, а также номер группы, для которой это
занятие проводится. Некоторые занятия проводятся для нескольких групп: потока
или всего курса. Расписание не должно содержать коллизий (например, разные
занятия не должны пересекаться друг с другом по месту и времени их проведения,
один преподаватель не может вести одновременно два разных занятия, в одно и
то же время, у одной и той же группы не допускается одновременно два
различных занятия и т. д.). Система по требованию пользователя должна
осуществлять поиск свободных аудиторий на заданную дату и время.
## Введение
В качестве интерфейса будет выступать консоль. Для этого реализуем класс
Terminal, который будет по выбору пользователя печатать в консоль требуемое
меню и выбор следующего действия. Для представления сущностей «Предмет»,
«Преподаватель», «Аудитория», «Группа» реализуем класс UniversityObject,
объекты которого можно выводить в std::ostream. Для их хранения служит
шаблонный класс Collection, который каждому хранящемуся объекту присваивает
ID и может выводить на консоль все его содержимые объекты.
В самом начале необходимо в работающей программе добавить все
использующиеся в дальнейшем предметы, аудитории, группы и преподавателей.
Расписание добавляется записями, каждая из которых представляет собой день
недели (число от 0 (пн) до 6(вс)), номер пары (число от 0 (08:15-09:50) до 5 (17:50-
19:25)), ID аудитории, ID предмета, список ID преподавателей и список ID групп,
разделенных через пробел. Каждый раз при переходе в соответствующее меню
выводится список сущностей (предметы, аудитории, преподаватели и т.
д.) вместе
с их ID, поэтому можно удобно и без ошибок удалять их или создавать расписание.
Для поиска свободных аудиторий необходимо ввести день недели (число от
0 (пн) до 6(вс)) и номер пары (число от 0 (08:15-09:50) до 5 (17:50-19:25)).

При добавлении нового расписания проходит проверка на коллизии и в
случае обнаружения выводится сообщение о конфликте (коллизия с аудиторией,
преподавателем или группой).
Для создания объекта класса Schedule (расписание) использован паттерн
«Builder».
## Диаграмма классов
![Диаграмма классов](https://i.imgur.com/Z79DupM.png)
## Объектная модель
![Объектная модель](https://i.imgur.com/xZrOWZH.png)
