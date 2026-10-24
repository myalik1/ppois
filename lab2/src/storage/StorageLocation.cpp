#include "../../include/storage/StorageLocation.h"
#include "../../include/exceptions/WorkflowExceptions.h"

namespace docflow {

StorageLocation::StorageLocation(
    std::string id, std::string rootPath, std::size_t capacity, std::size_t used)
    : locationId_(std::move(id)),
      rootPath_(std::move(rootPath)),
      capacityBytes_(capacity),
      usedBytes_(used) {}

void StorageLocation::allocateSpace(std::size_t bytes) {
    if (bytes == 0 || usedBytes_ + bytes > capacityBytes_) {
        throw StorageCapacityExceededException("Not enough storage capacity");
    }
    usedBytes_ += bytes;
}

void StorageLocation::releaseSpace(std::size_t bytes) {
    if (bytes > usedBytes_) {
        usedBytes_ = 0;
        return;
    }
    usedBytes_ -= bytes;
}

std::size_t StorageLocation::getAvailableBytes() const {
    return capacityBytes_ - usedBytes_;
}

}
