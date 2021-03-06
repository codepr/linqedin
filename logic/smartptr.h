#ifndef SMARTPTR_H
#define SMARTPTR_H

template <class T>
class SmartPtr {
private:
    T* _ptr;
public:
    SmartPtr();
    SmartPtr(T*);
    SmartPtr(const SmartPtr&);
    ~SmartPtr();
    SmartPtr& operator=(const SmartPtr&);
    T& operator*() const;
    T* operator->() const;
    bool operator==(const SmartPtr&) const;
    bool operator!=(const SmartPtr&) const;
};

#include "smartptr.cpp"
#endif
