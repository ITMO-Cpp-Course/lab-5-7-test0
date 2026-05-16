#pragma once
#include "document.hpp"
#include <string>
#include <unordered_map>

namespace lab5::space
{
class DocumentBuilder
{
  private:
    inline static size_t doc_counter = 0;

  public:
    DocumentBuilder() = delete;

    static Document build(const std::string& name, const std::string& content);

    static std::string lowercase(const std::string& word);
    static std::unordered_map<std::string, size_t> split_by_words(const std::string& content);
};
} // namespace lab5::space