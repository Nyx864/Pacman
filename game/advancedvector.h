#ifndef ADVANCEDVECTOR_H
#define ADVANCEDVECTOR_H

#include <QVector>

template <class T>
class AdvancedVector: public QVector<T>
{
public:
    T& operator[] (int index)
    {
        if (index < 0)
            index += this->size();
        if (index >= this->size())
            index -= this->size();
        return this->data()[index];
    }

    const T operator[] (int index) const
    {
        if (index < 0)
            index += this->size();
        if (index >= this->size())
            index -= this->size();
        return this->data()[index];
    }
};

#endif // ADVANCEDVECTOR_H
