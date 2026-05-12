#pragma once
#include <string>

namespace lab5::space
{
class DocumentBuilder;
class Document
{
  private:
    friend class DocumentBuilder;
    size_t id;
    std::string name;
    std::string content;

    Document(const size_t id, const std::string& name, const std::string& content);

  public:
    const std::string& getName() const;
    const std::string& getContent() const;
    const size_t getId() const;
};
} // namespace lab5::space