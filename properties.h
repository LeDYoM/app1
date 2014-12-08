#ifndef PROPERTIES_H
#define PROPERTIES_H

#define DEF_PROPERTY(type,member,base) \
    public: \
        inline type get##base() const { return member; } \
        inline void set##base(type value) { if (value != member) { member = value; } } \
    private: \
        type member;

//Q_PROPERTY(type member READ get##base WRITE set##base)

#endif // PROPERTIES_H
