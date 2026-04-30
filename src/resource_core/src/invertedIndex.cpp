#include "invertedIndex.hpp"
#include "documentBuilder.hpp"

namespace lab5::space
{
    void InvertedIndex::add(const Document& document)
    {
      auto words = DocumentBuilder::split_by_words(DocumentBuilder::lowercase(document.getContent()));

      for (auto& [word, count] : words)
      {
        if (auto s = dictionary.find(word); s != dictionary.end())
          s->second.insert({document.getId(), count});
        else
          dictionary.insert({word, {{document.getId(), count}}});
      }
    }

    void InvertedIndex::remove(size_t id)
    {
      for (auto& l : dictionary)
        std::get<1>(l).erase(id);
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