#include "updateTransaction.hpp"

namespace lab6::space
{
UpdateTransaction::UpdateTransaction(IndexStore& s) : real(s), copy(s), isInvalid(false) {}

UpdateTransaction::UpdateTransaction(UpdateTransaction&& old)
    : real(old.real), copy(old.copy), isInvalid(old.isInvalid), isCommitted(old.isCommitted)
{
    old.isInvalid = true;
}
UpdateTransaction& UpdateTransaction::operator=(UpdateTransaction&& old)
{
    real = old.real;
    copy = old.copy;
    isCommitted = old.isCommitted;
    isInvalid = old.isInvalid;

    return *this;
}

Result<void> UpdateTransaction::add(lab5::space::Document&& doc)
{
    if (isCommitted)
        return std::unexpected(IndexError{"Transaction already commited"});
    if (isInvalid)
        return std::unexpected(IndexError{"Transaction is invalid"});

    auto res = copy.add(std::move(doc));
    if (!res.has_value())
        isInvalid = true;
    return res;
}

Result<void> UpdateTransaction::add(const lab5::space::Document& doc)
{
    if (isCommitted)
        return std::unexpected(IndexError{"Transaction already commited"});
    if (isInvalid)
        return std::unexpected(IndexError{"Transaction is invalid"});

    auto res = copy.add(doc);
    if (!res.has_value())
        isInvalid = true;
    return res;
}
Result<void> UpdateTransaction::remove(size_t id)
{
    if (isCommitted)
        return std::unexpected(IndexError{"Transaction already commited"});
    if (isInvalid)
        return std::unexpected(IndexError{"Transaction is invalid"});

    auto res = copy.remove(id);
    if (!res.has_value())
        isInvalid = true;
    return res;
}
bool UpdateTransaction::commited()
{
    return isCommitted;
}
bool UpdateTransaction::valid()
{
    return !isInvalid;
}

Result<std::vector<size_t>> UpdateTransaction::searchByWord(const std::string& word)
{
    if (isCommitted)
        return std::unexpected(IndexError{"Transaction already commited"});
    if (isInvalid)
        return std::unexpected(IndexError{"Transaction is invalid"});

    auto res = copy.searchByWord(word);
    if (!res.has_value())
        isInvalid = true;
    return res;
}
Result<std::map<size_t, size_t>> UpdateTransaction::count(const std::string& word)
{
    if (isCommitted)
        return std::unexpected(IndexError{"Transaction already commited"});
    if (isInvalid)
        return std::unexpected(IndexError{"Transaction is invalid"});

    auto res = copy.count(word);
    if (!res.has_value())
        isInvalid = true;
    return res;
}
Result<void> UpdateTransaction::commit()
{
    if (isCommitted)
        return std::unexpected(IndexError{"Transaction already commited"});
    if (isInvalid)
        return std::unexpected(IndexError{"Transaction is invalid"});

    isCommitted = true;
    real = IndexStore(std::move(copy));
    real.isTransactionOpened = false;

    return Result<void>{};
}
} // namespace lab6::space