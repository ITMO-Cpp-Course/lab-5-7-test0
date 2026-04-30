#pragma once
#include <string>

namespace lab5::space
{
class Document
{
  private:
    size_t id;
    std::string name;
    std::string content;

  public:
    Document(const size_t id, const std::string& name, const std::string& content);

    const std::string& getName() const;
    const std::string& getContent() const;
    const size_t getId() const;
};
} // namespace lab5::space