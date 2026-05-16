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

    Document(size_t new_id, const std::string& new_name, const std::string& new_content);

  public:
    const std::string& getName() const;
    const std::string& getContent() const;
    size_t getId() const;
};
} // namespace lab5::space