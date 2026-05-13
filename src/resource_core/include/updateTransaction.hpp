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
    IndexStore& store;
    bool committed = false;

  public:
    explicit UpdateTransaction(IndexStore& s);

    UpdateTransaction& get()
    {
        return *this;
    }

    void add(lab5::space::Document&& doc);
    void remove(size_t id);
    Result<void> commit();
};
} // namespace lab6::space