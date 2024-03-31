#include <stdint.h>
#include <string>

class Convert {
public:
    static int32_t ReadInteger(const std::string &input, const std::string &filter_name);
    static float ReadFloat(const std::string &input, const std::string &filter_name);
};