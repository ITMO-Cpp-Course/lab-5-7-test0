#pragma once
#include "document.hpp"
#include "indexStore.hpp"
#include "invertedIndex.hpp"
#include <expected>
#include <map>
#include <string>
#include <vector>

namespace lab6::space
{
class UpdateTransaction
{
  private:
    IndexStore& real; // old version of index
    IndexStore copy;
    bool isCommitted = false;
    bool isInvalid = true;

  public:
    explicit UpdateTransaction(IndexStore& s);

    UpdateTransaction& operator=(const UpdateTransaction&) = delete;
    UpdateTransaction(const UpdateTransaction&) = delete;

    UpdateTransaction(UpdateTransaction&& old);
    UpdateTransaction& operator=(UpdateTransaction&& old);

    Result<void> add(lab5::space::Document&& doc);
    Result<void> add(const lab5::space::Document& doc);
    Result<void> remove(size_t id);
    Result<std::vector<size_t>> searchByWord(const std::string& word);
    Result<std::map<size_t, size_t>> count(const std::string& word);
    Result<void> commit();
    bool commited();
    bool valid();
};
} // namespace lab6::space