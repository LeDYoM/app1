#ifndef LOG_H
#define LOG_H

#include <QDebug>

#define DEBUG(text) qDebug() << text;
#define DEBUG_IF(condition,text) if (condition) { DEBUG(text) }

#endif // LOG_H
