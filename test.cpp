#include "Logger.h"
#include <thread>
#include <vector>
#include <atomic>
#include <chrono>

int main() {
    Logger& logger = Logger::getInstance();
    logger.setLogLevel(Logger::LogLevel::DEBUG);
    logger.logToFile("app.log");

    // basic sync logs
    logger.debug("dbg1");
    logger.info("info1");

    // enable async and submit many tasks from threads
    logger.enableAsync(true);
    const int N = 8;
    std::vector<std::thread> threads;
    for (int i=0;i<N;i++){
        threads.emplace_back([i](){
            Logger& l = Logger::getInstance();
            l.debug("async thread " + std::to_string(i) );
            l.info("async thread info " + std::to_string(i));
        });
    }
    for(auto &t: threads) t.join();

    // give some time for async to flush
    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    // disable async
    logger.enableAsync(false);

    logger.info("done");

    return 0;
}