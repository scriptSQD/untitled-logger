#include <Timestamper.hpp>

std::string Timestamper::GetCurrent() {
    auto time = std::time(nullptr);
    auto local = std::localtime(&time);

    std::stringstream ss;
    std::string timestamp;

    ss << std::put_time(local, "%Y/%m/%d, %H:%M:%S");
    timestamp = "[" + ss.str() + "]";

    delete local;

    return timestamp;
}
