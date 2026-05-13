#pragma once
#include "document.hpp"
#include "invertedIndex.hpp"
#include <expected>
#include <map>
#include <string>
#include <vector>

namespace lab6::space
{
struct IndexError
{
    std::string message;
};

template <typename T> using Result = std::expected<T, IndexError>;

class UpdateTransaction;
class IndexStore
{
  private:
    friend class UpdateTransaction;
    lab5::space::InvertedIndex index;

  public:
    IndexStore() = default;

    UpdateTransaction startTransaction();

    Result<void> add(lab5::space::Document&& doc);
    Result<void> remove(size_t id);
    Result<std::vector<size_t>> searchByWord(const std::string& word) const;
    Result<std::map<size_t, size_t>> count(const std::string& word) const;
};
} // namespace lab6::space