#ifndef EXERCISE_H
#define EXERCISE_H

#include <QString>

class Exercise {
private:
    QString name;
    QString description;
    int baseTimeSeconds;

public:
    Exercise(QString n, QString desc, int time)
        : name(n), description(desc), baseTimeSeconds(time) {}

    QString getName() const { return name; }
    QString getDescription() const { return description; }
    int getBaseTime() const { return baseTimeSeconds; }
};

#endif // EXERCISE_H
