#include "indexStore.hpp"
#include "document.hpp"
#include "invertedIndex.hpp"
#include "updateTransaction.hpp"
#include <iostream>
#include <system_error>

namespace lab6::space
{
UpdateTransaction IndexStore::startTransaction()
{
    if (isTransactionOpened)
    {
        throw IndexError{"Transaction for this index store already opened"};
    }

    isTransactionOpened = true;
    return UpdateTransaction(*this);
}

Result<void> IndexStore::add(lab5::space::Document&& document)
{
    try
    {
        index.add(document);
        return Result<void>();
    }
    catch (const std::exception& e)
    {
        return std::unexpected(IndexError{e.what()});
    }
    catch (...)
    {
        return std::unexpected(IndexError{"Unknown critical error"});
    }
}

Result<void> IndexStore::add(const lab5::space::Document& document)
{
    try
    {
        index.add(document);
        return Result<void>();
    }
    catch (const std::exception& e)
    {
        return std::unexpected(IndexError{e.what()});
    }
    catch (...)
    {
        return std::unexpected(IndexError{"Unknown critical error"});
    }
}

Result<void> IndexStore::remove(size_t id)
{
    try
    {
        index.remove(id);

        return Result<void>();
    }
    catch (const std::exception& e)
    {
        return std::unexpected(IndexError{e.what()});
    }
    catch (...)
    {
        return std::unexpected(IndexError{"Unknown critical error"});
    }
}

Result<std::vector<size_t>> IndexStore::searchByWord(const std::string& word) const
{
    try
    {
        if (word.empty())
        {
            throw std::system_error(std::make_error_code(std::errc::invalid_argument), "Empty query");
        }
        return index.searchByWord(word);
    }
    catch (const std::exception& e)
    {
        return std::unexpected(IndexError{e.what()});
    }
}

Result<std::map<size_t, size_t>> IndexStore::count(const std::string& word) const
{
    try
    {
        if (word.empty())
        {
            throw std::system_error(std::make_error_code(std::errc::invalid_argument), "Empty query");
        }
        return index.count(word);
    }
    catch (const std::exception& e)
    {
        return std::unexpected(IndexError{e.what()});
    }
}
} // namespace lab6::space