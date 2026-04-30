#include "documentBuilder.hpp"
#include <unordered_map>

namespace lab5::space
{
Document DocumentBuilder::build(const std::string& name, const std::string& content)
{
    return Document(doc_counter++, name, content);
}

std::string DocumentBuilder::lowercase(const std::string& word)
{
    std::string result;
    result.reserve(word.size());
    for (unsigned char c : word)
    {
        result += static_cast<char>(std::tolower(c));
    }
    return result;
}

std::unordered_map<std::string, size_t> DocumentBuilder::split_by_words(const std::string& content)
{
    std::unordered_map<std::string, size_t> dictionary_word_count;
    std::string word;

    for (unsigned char c : content)
    {
        if (std::isalnum(c))
        {
            word += static_cast<char>(std::tolower(c));
        }
        else if (!word.empty())
        {
            dictionary_word_count[word]++;
            word.clear();
        }
    }
    if (!word.empty())
    {
        dictionary_word_count[word]++;
    }
    return dictionary_word_count;
}
} // namespace lab5::space