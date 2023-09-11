//
// Created by Jollu Emil on 08.09.2023.
//

#pragma once

#include "../utilites/Answer.h"


class Abstract {
public:
    virtual ~Abstract() {}

    virtual Answer sent_answer_to_convert_JSON() = 0;

#ifdef NDEBUG
    virtual  void print() const = 0;
#endif
};