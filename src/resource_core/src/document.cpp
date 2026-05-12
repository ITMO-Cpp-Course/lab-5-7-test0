#include "document.hpp"

namespace lab5::space
{
Document::Document(size_t new_id, const std::string& new_name, const std::string& new_content)
    : id(new_id), name(new_name), content(new_content)
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
size_t Document::getId() const
{
    return id;
}
} // namespace lab5::space