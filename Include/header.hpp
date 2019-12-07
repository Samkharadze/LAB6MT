//Copyright 2019 CrazyOverdose

#ifndef  INCLUDE_HEADER_HPP_
#define  INCLUDE_HEADER_HPP_
#include "picosha2.hpp"
#include <string>
#include <iostream>
#include <thread>
#include <stdlib.h>
#include <random>
#include <ctime>
#include <boost/log/trivial.hpp>

class SHA256{
public:
    static void getting_a_hash() {
        for (;;) {
           const std::string end_hash = "0000";
            //случайные взодные данные
            std::mt19937 gen;
            gen.seed(time(0));
            std::string random = std::to_string(gen());

            //значение хеш-функции
            if (picosha2::hash256_hex_string(random).substr(60) == end_hash) {
                //сообщения журнала на консоли
                BOOST_LOG_TRIVIAL(info) << "Suitable SHA256(\"" << random
 << "\") = \"" << picosha2::hash256_hex_string(random) << "\";"
<< std::endl;} else {
                BOOST_LOG_TRIVIAL(info) << "Thread ID "
  << std::this_thread::get_id() << "  UNSuitable SHA256(\"" << random
 << ") = \"" << picosha2::hash256_hex_string(random) << ";" << std::endl;}
        }
    }
};
#endif // INCLUDE_HEADER_HPP_
