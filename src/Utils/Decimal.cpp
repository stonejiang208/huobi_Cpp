/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "Huobi/Decimal.h"

namespace Huobi {

    std::ostream & operator<<(std::ostream &out, const Decimal& obj) {
        out << obj.toString();
        return out;
    }

    std::istream & operator>>(std::istream &in, Decimal& obj) {
        std::string str;
        in >> str;
        obj = Decimal(str.c_str());
        return in;
    }
}
