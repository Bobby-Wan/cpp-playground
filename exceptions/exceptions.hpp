#ifndef _EXCEPTION_HEADER_INCLUDED_
#define _EXCEPTION_HEADER_INCLUDED_

#include <exception>

namespace except{
    struct key_not_found_exception: public std::exception{
        explicit key_not_found_exception();
        virtual ~key_not_found_exception() noexcept;

        const char* what() const noexcept;
    };
}
#endif  //_EXCEPTION_HEADER_INCLUDED_