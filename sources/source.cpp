// Copyright 2018 Your Name <your_email>

#include <header.hpp>
#include <boost/lexical_cast.hpp>
#include <thread>
#include <ctime>
#include <boost/log/utility/setup.hpp>
#include <vector>
int main(int argc, char*argv[])
{
    srand(time(NULL));
    //size_t count_threads = thread::hardware_concurrency();
    size_t count_threads = 2;
    if (argc > 1)
        count_threads =
boost::lexical_cast<size_t>(argv[1]);
//преобразование в size_t
    boost::log::add_file_log("Log.log");//вывод в файл
    boost::log::add_console_log(std::cout);//вывод в консоль
    std::vector<std::thread> threads;
    for (size_t i = 0; i < count_threads; ++i)
    threads.emplace_back(SHA256::getting_a_hash);
//создает объект (а не копию) в конце вектора
for (std::thread& thread : threads)
        thread.join();
}
