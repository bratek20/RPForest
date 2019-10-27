#ifndef SYMBOL_H
#define SYMBOL_H

#include "ProcessContext.h"

#include <memory>
#include <vector>


class Symbol;
using SymbolPtr = std::shared_ptr<Symbol>;

class Symbol : public std::enable_shared_from_this<Symbol> {
public:
    template <class T, class ...Args>
    static SymbolPtr S(Args&& ...args)
    {
        return SymbolPtr(new T(std::forward<Args>(args)...));
    }

    virtual ~Symbol(){}

    virtual std::vector<SymbolPtr> produce() {
        return {shared_from_this()};
    }

    virtual void process(ProcessContext&) {

    }

    virtual std::string toString() = 0;

};

#endif