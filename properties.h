#ifndef PROPERTIES_H
#define PROPERTIES_H

#include <QtCore>
#define DEF_Q_PROPERTY_READONLY(type,member) Q_PROPERTY(type member READ get_##member FINAL) \
    public: \
        inline type get_##member() const { return member; } \
    private: \
        type member;

#define DEF_Q_PROPERTY(type,member) Q_PROPERTY(type member READ get_##member WRITE set_##member NOTIFY member##Changed) \
    public: \
        inline type get_##member() const { return member; } \
        inline void set_##member(type value) { if (value != member) { member = value; Q_EMIT member##Changed(value); } } \
        Q_SIGNAL void member##Changed(type newVal); \
    private: \
        type member;

#define DEF_Q_PROPERTY_W_DEFAULT(type,member,default_) Q_PROPERTY(type member READ get_##member WRITE set_##member NOTIFY member##Changed) \
    public: \
        inline type get_##member() const { return member; } \
        inline void set_##member(type value) { if (value != member) { member = value; Q_EMIT member##Changed(value); } } \
        Q_SIGNAL void member##Changed(type newVal); \
    private: \
        type member = default_;

#define DEF_Q_PROPERTY_READONLY_W_DEFAULT(type,member,default_) Q_PROPERTY(type member READ get_##member FINAL) \
    public: \
        inline type get_##member() const { return member; } \
    private: \
        type member = default_;

#endif // PROPERTIES_H
