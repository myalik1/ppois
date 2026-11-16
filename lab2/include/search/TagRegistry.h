#pragma once

#include "../documents/Tag.h"
#include <cstddef>
#include <string>
#include <vector>

namespace docflow {

class TagRegistry {
public:
    TagRegistry(std::string registryName, std::size_t maxTagsAllowed);
    void registerTag(const Tag& tag);
    Tag findTagByName(const std::string& name) const;
    std::size_t countTags() const;

private:
    std::string registryName_;
    std::size_t maxTagsAllowed_;
    std::vector<Tag> registeredTags_;
};

}
