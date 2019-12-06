#include "../third-party/PicoSHA2/picosha2.h"
#include <thread>
#include <cstdlib>
#include <vector>
#include <boost/log/trivial.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup.hpp>
static std::string endChar = "0000";

void hashing()
{

    while (true) 
	{
        std::string genstring = std::to_string(std::rand());
        std::string hash = picosha2::hash256_hex_string(genstring);
        std::string lastChar = hash.substr(hash.size() - endChar.size());
        if (lastChar == endChar) 
		{
            BOOST_LOG_TRIVIAL(info) << "0000  in hash '" << hash << "' of string '" << genstring << "'";
        } 
		else 
		{
            BOOST_LOG_TRIVIAL(trace) << "Hash '" << hash << "' get from string'" << genstring << "'";
        }
    }
}

void init()
{
    vel
    boost::log::register_simple_formatter_factory< boost::log::trivial::severity_level, char >("austerity");

    //Логирование
    auto ForFileLogger = boost::log::add_file_log(
            boost::log::keywords::file_name = "../logs/loggerFile_%N.log",
            boost::log::keywords::rotation_size = 10 * 1024 * 1024,
            boost::log::keywords::time_based_rotation = boost::log::sinks::file::rotation_at_time_point{0, 0, 0},
            boost::log::keywords::format = "[%TimeStamp%][%austerity%][%ThreadID%]: %Message%"
    );
    auto ForConsoleLogger = boost::log::add_console_log(
            std::cout,
            boost::log::keywords::format = "[%TimeStamp%][%austerity%][%ThreadID%]: %Message%"
    );

    //Фильтрация
    ForFileLogger->set_filter(
            boost::log::trivial::severity >= boost::log::trivial::trace
    );
    ForConsoleLogger->set_filter(
            boost::log::trivial::severity >= boost::log::trivial::info
    );

}

int main(int argc, char *argv[])
{
    srand(time(nullptr));
    init();
    boost::log::add_common_attributes();

    size_t threadAmount = 0;
    if(argc >=2) 
	{
        threadAmount = boost::lexical_cast<size_t>(argv[1]);
    }
    else 
	{
        threadAmount = boost::thread::hardware_concurrency();
    }
    BOOST_LOG_TRIVIAL(trace) << "Threads amount: " << threadAmount;

    std::vector<boost::thread> threads;
    threads.reserve(threadAmount);
    for (size_t i = 0; i < threadAmount; i++) 
	{
        threads.emplace_back(hashing);
    }

    for (boost::thread &thread : threads)
	{
        thread.join();
    }

    return 0;
}