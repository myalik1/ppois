#include "../../include/search/TagRegistry.h"
#include "../../include/exceptions/WorkflowExceptions.h"

namespace docflow {

TagRegistry::TagRegistry(std::string registryName, std::size_t maxTagsAllowed)
    : registryName_(std::move(registryName)), maxTagsAllowed_(maxTagsAllowed) {}

void TagRegistry::registerTag(const Tag& tag) {
    if (registeredTags_.size() >= maxTagsAllowed_) {
        throw StorageCapacityExceededException("Tag registry capacity reached");
    }
    registeredTags_.push_back(tag);
}

Tag TagRegistry::findTagByName(const std::string& name) const {
    for (const auto& tag : registeredTags_) {
        if (tag.getTagName() == name) {
            return tag;
        }
    }
    throw DocumentNotFoundException("Tag not found in registry");
}

std::size_t TagRegistry::countTags() const {
    return registeredTags_.size();
}

}
