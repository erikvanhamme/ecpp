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

#include "poolallocator.h"

#include <cassert>
#include <cstddef>
#include <cstring>

ecpp::PoolAllocator::PoolAllocator(std::size_t poolSize, std::size_t blockSize, void *poolMem) {

    // The blockSize must be a multiple of 4 to not violate the alignment rules on ARM.
    assert((blockSize % 4) == 0);

    _blockSize = blockSize;

    // Here we add 1 to the blocksize, because each block carries with it 1 byte
    // of overhead to store the meta information.
    _blockCount = poolSize / (_blockSize + 1u);

    _dataMemSize = _blockSize * _blockCount;
    _metaMemSize = _blockCount;

    // In the memory region, the data memory is first, the meta memory after that.
    _dataMem = reinterpret_cast<std::uint8_t *>(poolMem);
    _metaMem = reinterpret_cast<std::uint8_t *>(reinterpret_cast<std::size_t>(poolMem) + _dataMemSize);

    // We must initialize the meta memory block to 0 for the free block locator to work.
    std::memset(_metaMem, 0u, _metaMemSize);
}

ecpp::PoolAllocator::~PoolAllocator() {
}

void *ecpp::PoolAllocator::allocate(std::size_t size) {

    auto blocksNeeded = size / _blockSize;
    if (size % _blockSize) {
        blocksNeeded++;
    }

    int firstFreeBlock = findFreeBlocks(blocksNeeded);

    if (firstFreeBlock == -1) {
        return nullptr;
    }

    _metaMem[firstFreeBlock] = blocksNeeded;

    return _dataMem + (_blockSize * firstFreeBlock);
}

void ecpp::PoolAllocator::deallocate(void *address) {

    auto min = reinterpret_cast<std::size_t>(_dataMem);
    auto max = min + _dataMemSize - _blockSize;

    auto addressNumerical = reinterpret_cast<std::size_t>(address);

    if ((min <= addressNumerical) && (addressNumerical <= max)) {

        auto block = (addressNumerical - min) / _blockSize;

        _metaMem[block] = 0;
    }
}

int ecpp::PoolAllocator::findFreeBlocks(std::size_t blocksNeeded) const {

    // Here, the first available slot of at least size bytes is located using the first-fit approach.

    std::size_t pos = 0;
    std::size_t limit = _metaMemSize - blocksNeeded;

    while (pos <= limit) {

        if (_metaMem[pos] != 0) {

            // If the meta info states that > 0 successive blocks are used, move up the position by the corresponding number of blocks.
            pos += _metaMem[pos];

        } else {

            // If the meta info states that the current block is not used, check if the next (blocksNeeded - 1) blocks are also free.
            bool free = true;
            for (std::size_t i = 1; i < blocksNeeded; ++i) {

                if (_metaMem[pos + i] != 0) {
                    free = false;
                    pos = pos + i + 1;
                    break;
                }
            }

            if (free) {
                return pos;
            }
        }
    }

    return -1;
}
