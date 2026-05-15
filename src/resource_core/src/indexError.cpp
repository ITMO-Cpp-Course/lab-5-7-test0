#include "indexError.hpp"

namespace lab6::space
{

IndexError::IndexError(const std::string& message) : std::runtime_error(message) {}
} // namespace lab6::space