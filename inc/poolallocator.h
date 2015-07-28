/*
 * Copyright 2015 Erik Van Hamme
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef POOLALLOCATOR_H
#define POOLALLOCATOR_H

#include "allocator.h"

#include <cstddef>
#include <cstdint>

namespace ecpp {

class PoolAllocator : public Allocator {
public:
    PoolAllocator(std::size_t poolSize, std::size_t blockSize, void *poolMem);
    virtual ~PoolAllocator();

    virtual void *allocate(std::size_t size) override;
    virtual void deallocate(void *address) override;

private:
    int findFreeBlocks(std::size_t blocksNeeded) const;

    std::uint8_t *_dataMem;
    std::uint8_t *_metaMem;
    std::size_t _blockCount;
    std::size_t _blockSize;
    std::size_t _dataMemSize;
    std::size_t _metaMemSize;
};

}

#endif // POOLALLOCATOR_H
