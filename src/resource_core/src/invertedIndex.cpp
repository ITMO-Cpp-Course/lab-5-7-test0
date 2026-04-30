#include "invertedIndex.hpp"
#include "documentBuilder.hpp"

namespace lab5::space
{
    void InvertedIndex::add(const Document& document)
    {
      DocumentBuilder builder;

      auto words = builder.split_by_words(builder.lowercase(document.getContent()));

      for (auto& w : words)
      {
        if (auto s = dictionary.find(std::get<0>(w)); s != dictionary.end())
          s->second.push_back({document.getId(), std::get<1>(w)});
        else
          dictionary.insert({std::get<0>(w), {document.getId(), std::get<1>(w)}});
      }
    }

    void InvertedIndex::remove(size_t id)
    {

    }
    
    std::vector<size_t> InvertedIndex::searchByWord(const std::string& word) const
    {
      return {};
    }
    size_t InvertedIndex::count(std::string& word) const
    {
      return 0;
    }
} // namespace lab5::space