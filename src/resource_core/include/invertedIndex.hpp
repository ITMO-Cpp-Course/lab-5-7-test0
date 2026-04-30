#pragma once
#include "document.hpp"
#include <string>
#include <unordered_map>
#include <vector>

namespace lab5::space
{
class InvertedIndex
{
  private:
    // (word: [id_doc: count])
    size_t doc_counter = 0;
    std::unordered_map<std::string, std::list<std::pair<std::uint64_t, std::uint64_t>>> dictionary;

  public:
    void add(Document&& document);
    void remove(size_t id) const;
    std::vector<size_t> search_by_word(const std::string& word) const;
    size_t count(std::string& word) const;
};
} // namespace lab5::space