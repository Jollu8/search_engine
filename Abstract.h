//
// Created by Jollu Emil on 08.09.2023.
//

#pragma once

#include "Answer.h"


class Abstract {
public:
    virtual ~Abstract() {}

    virtual Answer sent_answer() = 0;
    virtual  void print() const = 0;
};