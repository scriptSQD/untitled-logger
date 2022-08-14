#include <Timestamper.hpp>

std::string Timestamper::GetCurrent() {
    auto time = std::time(nullptr);
    auto local(localtime(&time));

    std::stringstream ss;
    std::string timestamp;

    ss << std::put_time(local, "%F, %T");
    timestamp = "[" + ss.str() + "]";

    return timestamp;
}
