/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SymbolUtils.h
 * Author: yuanxueqi
 *
 * Created on 2019年10月17日, 下午8:49
 */

#ifndef SYMBOLUTILS_H
#define SYMBOLUTILS_H

namespace Huobi {

    class SymbolUtils {
    public:

        static std::list<std::string> parseSymbols(const char* symbols) {

            std::string input(symbols);
            std::list<std::string> res;
            std::stringstream ss(input);
            std::string temp;
            while (std::getline(ss, temp, ',')) {
                InputChecker::checker()->checkSymbol(temp);
                res.push_back(temp);
            }
            return res;
        }

    };

}

#endif /* SYMBOLUTILS_H */

