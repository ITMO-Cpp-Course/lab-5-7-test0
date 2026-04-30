#pragma once
#include "document.hpp"
#include <string>
#include <vector>

namespace lab5::space
{
class DocumentBuilder
{
  public:
    Document build(const size_t id, const std::string& name, const std::string& content);

    std::string lowercase(const std::string& word) const;
    std::vector<std::string> split_by_words(const std::string& content) const;
};
} // namespace lab5::space