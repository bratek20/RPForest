#ifndef PTR_H
#define PTR_H

#include <memory>

template<class Type, class PtrType>
class Ptr {
public:
    template <class ...Args>
    static PtrType New(Args&& ...args)
    {
        return PtrType(new Type(std::forward<Args>(args)...));
    }
};

#endif