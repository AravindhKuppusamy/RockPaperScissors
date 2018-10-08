#ifndef ROCKPAPERSCISSORS_WOOLIE_EXCEPTION_H
#define ROCKPAPERSCISSORS_WOOLIE_EXCEPTION_H

#include <stdexcept>

class WoolieException : public std::runtime_error {
public:
    /**
     * Construct this exception.
     *
     * @param msg the exception message
     */
    WoolieException(const std::string& msg) : runtime_error(msg.c_str()) {}

    /**
     * Get a string containing information about the exception.
     *
     * @return exception message
     */
    virtual const char* what() const throw() {
        return std::runtime_error::what();
    }
};

#endif //ROCKPAPERSCISSORS_WOOLIE_EXCEPTION_H
