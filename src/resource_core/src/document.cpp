#include "document.hpp"

namespace lab5::space
{
Document::Document(const size_t id, const std::string& name, const std::string& content)
    : id(id), name(name), content(content)
{
}
} // namespace lab5::space