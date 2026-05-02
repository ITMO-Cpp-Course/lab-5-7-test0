#pragma once
#include "document.hpp"
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

namespace lab5::space
{
class InvertedIndex
{
  private:
    // (word: [id_doc: count])
    std::unordered_map<std::string, std::map<size_t, size_t>> dictionary;

  public:
    void add(const Document& document);
    void remove(size_t id);
    std::vector<size_t> searchByWord(const std::string& word) const;
    std::map<size_t, size_t> count(const std::string& word) const;
};
} // namespace lab5::space