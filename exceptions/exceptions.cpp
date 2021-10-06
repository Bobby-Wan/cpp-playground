#include "exceptions.hpp"

namespace except{
        key_not_found_exception::key_not_found_exception(){}
        key_not_found_exception::~key_not_found_exception(){}
        const char* key_not_found_exception::what() const noexcept{
            return "key not found";
        }
}