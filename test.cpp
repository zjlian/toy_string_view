#include "string_view.hpp"

#include <iostream>
#include <string>

int main(int, char **)
{
    std::string std_string = "string";

    toy::StringView sv = std_string;

    constexpr toy::StringView static_sv = "static_sv";
}
