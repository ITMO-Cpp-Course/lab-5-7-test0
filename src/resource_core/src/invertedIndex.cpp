#include "invertedIndex.hpp"
#include "documentBuilder.hpp"

namespace lab5::space
{
void InvertedIndex::add(Document&& document)
{
    const auto doc_id = document.getId();

    auto words = DocumentBuilder::split_by_words(DocumentBuilder::lowercase(std::move(document).getContent()));

    for (auto& [word, count] : words)
    {
        dictionary[word].emplace(doc_id, count);
    }
}

void InvertedIndex::remove(size_t id)
{
    for (auto& [word, docs] : dictionary)
    {
        docs.erase(id);
    }
}

std::vector<size_t> InvertedIndex::searchByWord(const std::string& word) const
{
    auto it = dictionary.find(word);

    if (it == dictionary.end())
        return {};

    std::vector<size_t> ids;
    ids.reserve(it->second.size());

    for (auto& [id, cnt] : it->second)
        ids.push_back(id);

    return ids;
}

std::map<size_t, size_t> InvertedIndex::count(const std::string& word) const
{
    auto it = dictionary.find(word);

    if (it == dictionary.end())
        return {};

    return it->second;
}
} // namespace lab5::space