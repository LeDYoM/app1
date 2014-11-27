#ifndef PROPERTIES_H
#define PROPERTIES_H

#include <QtCore>

#define DEF_PROPERTY(type,member,base) Q_PROPERTY(type member READ get##base WRITE set##base) \
    public: \
        inline type get##base() const { return member; } \
        inline void set##base(type value) { if (value != member) { member = value; } } \
    private: \
        type member;


#endif // PROPERTIES_H
