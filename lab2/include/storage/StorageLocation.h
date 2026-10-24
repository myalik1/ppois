#pragma once

#include <cstddef>
#include <string>

namespace docflow {

class StorageLocation {
public:
    StorageLocation(std::string id, std::string rootPath, std::size_t capacity, std::size_t used);
    void allocateSpace(std::size_t bytes);
    void releaseSpace(std::size_t bytes);
    std::size_t getAvailableBytes() const;

private:
    std::string locationId_;
    std::string rootPath_;
    std::size_t capacityBytes_;
    std::size_t usedBytes_;
};

}
