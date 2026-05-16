#include "updateTransaction.hpp"

namespace lab6::space
{
UpdateTransaction::UpdateTransaction(IndexStore& s) : real(s), copy(s), isValid(true) {}

UpdateTransaction::~UpdateTransaction()
{
    close();
}

void UpdateTransaction::close()
{
    if (isValid)
    {
        isValid = false;
        real.isTransactionOpened = false;
    }
}

UpdateTransaction::UpdateTransaction(UpdateTransaction&& old) : real(old.real), copy(old.copy), isValid(old.isValid)
{
    old.isValid = false;
}
UpdateTransaction& UpdateTransaction::operator=(UpdateTransaction&& old)
{
    close();

    real = old.real;
    copy = old.copy;
    isValid = old.isValid;
    old.isValid = false;

    return *this;
}

Result<void> UpdateTransaction::add(lab5::space::Document&& doc)
{
    if (!isValid)
        return std::unexpected(IndexError{"Transaction is invalid"});

    auto res = copy.add(std::move(doc));
    if (!res.has_value())
        close();
    return res;
}

Result<void> UpdateTransaction::add(const lab5::space::Document& doc)
{
    if (!isValid)
        return std::unexpected(IndexError{"Transaction is invalid"});

    auto res = copy.add(doc);
    if (!res.has_value())
        close();
    return res;
}
Result<void> UpdateTransaction::remove(size_t id)
{
    if (!isValid)
        return std::unexpected(IndexError{"Transaction is invalid"});

    auto res = copy.remove(id);
    if (!res.has_value())
        close();
    return res;
}
bool UpdateTransaction::valid()
{
    return isValid;
}

Result<std::vector<size_t>> UpdateTransaction::searchByWord(const std::string& word)
{
    if (!isValid)
        return std::unexpected(IndexError{"Transaction is invalid"});

    auto res = copy.searchByWord(word);
    if (!res.has_value())
        close();
    return res;
}
Result<std::map<size_t, size_t>> UpdateTransaction::count(const std::string& word)
{
    if (!isValid)
        return std::unexpected(IndexError{"Transaction is invalid"});

    auto res = copy.count(word);
    if (!res.has_value())
        close();
    return res;
}
Result<void> UpdateTransaction::commit()
{
    if (!isValid)
        return std::unexpected(IndexError{"Transaction is invalid"});

    real = IndexStore(std::move(copy));

    close();

    return Result<void>{};
}
} // namespace lab6::space