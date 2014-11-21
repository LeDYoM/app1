#ifndef CONFIG_H
#define CONFIG_H

#define USE_QT_LIB

#ifdef USE_QT_LIB

    #define APP_DEBUG

    #include <QDebug>

    #include <QList>
    template <class T>
    using List = QList<T>;

    #include <QGLShaderProgram>
    using GLShaderProgram = QGLShaderProgram;

    using String = QString;

    #include <QMatrix4x4>
    using Matrix4x4 = QMatrix4x4;

    #include <QVector3D>
    using Vector3D = QVector3D;

    #include <QQuaternion>
    using Quaternion = QQuaternion;

#endif

#define SIMPLEPROPERTYBASE(type,name,baseAccess,getterAccess,getter,setterAccess,setter)  baseAccess: \
        type name; \
    getterAccess: \
        inline type getter() const { return name; } \
    setterAccess: \
        void setter(type value) { name = value; }

#define SIMPLEPROPERTY(type,name,getter,setter) SIMPLEPROPERTYBASE(type,name,private,public,getter,public,setter)
#define SIMPLEPROTECTEDPROPERTY(type,name,getter,setter) SIMPLEPROPERTYBASE(type,name,protected,public,getter,public,setter)

#define READONLYPROPERTYBASE(type,name,baseAccess,getterAccess,getter) baseAccess: \
        type name; \
    getterAccess: \
        inline type getter() const { return name; } \

#define READONLYPROPERTY(type,name,getter) READONLYPROPERTYBASE(type,name,private,public,getter)

#endif // CONFIG_H

