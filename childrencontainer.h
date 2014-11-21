#ifndef CHILDRENCONTAINER_H
#define CHILDRENCONTAINER_H

#include <QList>

template <class T>
class ChildrenContainer
{
public:
    explicit ChildrenContainer() {}

protected:
    QList<T*> _children;
};

#endif // CHILDRENCONTAINER_H
