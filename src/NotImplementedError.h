#ifndef LOGIC_SOLVER_NOTIMPLEMENTEDERROR_H
#define LOGIC_SOLVER_NOTIMPLEMENTEDERROR_H

#include <stdexcept>

class NotImplementedError : std::logic_error {
public:
    explicit NotImplementedError(const std::string &message) : std::logic_error("Feature not implemented: " + message) {}
};


#endif //LOGIC_SOLVER_NOTIMPLEMENTEDERROR_H
