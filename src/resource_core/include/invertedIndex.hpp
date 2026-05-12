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
    using word_t = std::string;
    using doc_id_t = size_t;
    using count_t = size_t;

    // (word: [id_doc: count])
    std::unordered_map<word_t, std::map<doc_id_t, count_t>> dictionary;

  public:
    void add(Document&& document);
    void remove(size_t id);
    std::vector<size_t> searchByWord(const std::string& word) const;
    std::map<size_t, size_t> count(const std::string& word) const;
};
} // namespace lab5::space