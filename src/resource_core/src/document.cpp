#include "document.hpp"

namespace lab5::space
{
Document::Document(const size_t id, const std::string& name, const std::string& content)
    : id(id), name(name), content(content)
{
}

const std::string& Document::getName() const
{
  return name;
}
const std::string& Document::getContent() const
{
  return content;
}
const size_t Document::getId() const
{
  return id;
}
} // namespace lab5::space