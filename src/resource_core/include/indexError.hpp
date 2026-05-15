#pragma once
#include <stdexcept>
#include <string>

namespace lab6::space
{

class IndexError : public std::runtime_error
{
  public:
    explicit IndexError(const std::string& message);
};

} // namespace lab6::space