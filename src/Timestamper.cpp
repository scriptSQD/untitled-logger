#include <Timestamper.hpp>

std::string Timestamper::GetCurrent() {
    time_t time = std::time(nullptr);
    struct tm *local = std::localtime(&time);

    std::stringstream ss;
    std::string timestamp;

    ss << std::put_time(local, "%Y/%m/%d, %H:%M:%S");
    timestamp = "[" + ss.str() + "]";
    ss.str(std::string());

    return timestamp;
}
