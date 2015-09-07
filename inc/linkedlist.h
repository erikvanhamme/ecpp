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

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "allocator.h"

#include <cstddef>

namespace ecpp {
namespace mem {

// This prototype is required to make sure LinkedList can be used in the definition of LinkedListIterator.
template <typename T>
class LinkedList;

// This prototype is required to make sure LinkedListIterator can be used in the definition of LinkedListEntry.
template <typename T>
class LinkedListIterator;

// This prototype is required to make sure ConstLinkedListIterator can be used in the definition of LinkedListEntry.
template <typename T>
class ConstLinkedListIterator;

template <typename T>
class LinkedListEntry {
public:
    static constexpr std::size_t LINKED_LIST_ENTRY_SIZE = sizeof(LinkedListEntry<T>);

    LinkedListEntry(T item) : _item(item), _next(nullptr), _previous(nullptr) {
    }

private:
    T _item;
    LinkedListEntry *_next;
    LinkedListEntry *_previous;

    friend class LinkedListIterator<T>;
    friend class ConstLinkedListIterator<T>;
};

template <typename T>
class LinkedListIterator {
public:
    LinkedListIterator(LinkedList<T> &list, LinkedListEntry<T> *entry) : _list(list), _entry(entry) {
    }

    bool insertAfter(T item) {

        // This protects against calling insertAfter on null iterator of the linked list.
        if ((_entry == nullptr) && (_list._head != nullptr)) {
            return false;
        }

        // make the new entry
        LinkedListEntry<T> *newEntry = makeEntry(item);
        if (newEntry == nullptr) {
            return false;
        }

        // handle linking
        if (_entry != nullptr) {

            /*
             * This branch deals with updating a non-empty list.
             */

            newEntry->_previous = _entry;

            if (_entry->_next != nullptr) {
                _entry->_next->_previous = newEntry;
            } else {
                // If there was no next entry, we have added at the end of the list and we must update the tail.
                _list._tail = newEntry;
            }

            _entry->_next = newEntry;

        } else {

            /*
             * This branch deals with starting an empty list.
             */

            _list._head = newEntry;
            _list._tail = newEntry;
        }

        // Point to the newly created entry.
        _entry = newEntry;

        _list._size++;

        return true;
    }

    bool insertBefore(T item) {

        // This protects against calling insertAfter on null iterator of the linked list.
        if ((_entry == nullptr) && (_list._head != nullptr)) {
            return false;
        }

        // make the new entry
        LinkedListEntry<T> *newEntry = makeEntry(item);
        if (newEntry == nullptr) {
            return false;
        }

        // handle linking
        if (_entry != nullptr) {

            /*
             * This branch deals with updating a non-empty list.
             */

            newEntry->_next = _entry;

            if (_entry->_previous != nullptr) {
                _entry->_previous->_next = newEntry;
            } else {
                // If there was no previous entry, we have inserted at the start of the list and must update the head.
                _list._head = newEntry;
            }

            _entry->_previous = newEntry;

        } else {

            /*
             * This branch deals with starting an empty list.
             */

            _list._head = newEntry;
            _list._tail = newEntry;
        }

        // Point to the newly created entry.
        _entry = newEntry;

        _list._size++;

        return true;
    }

    bool remove() {

        if (_entry == nullptr) {
            return false;
        }

        // Find out what to do.
        bool hasPrevious = _entry->_previous != nullptr;
        bool hasNext = _entry->_next != nullptr;

        if ((hasPrevious == true) && (hasNext == true)) {

            // Both next and previous are present, link together.
            _entry->_previous->_next = _entry->_next;
            _entry->_next->_previous = _entry->_previous;

        } else if (hasPrevious == true) {

            // Only previous is present, link _previous->_next to nullptr. We must also adjust the tail of the list.
            _entry->_previous->_next = nullptr;
            _list._tail = _entry->_previous;

        } else if (hasNext == true) {

            // Only next is present, link _next->_previous to nullptr. We must also adjust the head of the list.
            _entry->_next->_previous = nullptr;
            _list._head = _entry->_next;
        }

        // De-allocate the entry and point to the next entry if there is one.
        LinkedListEntry<T> *target = (hasNext == true) ? _entry->_next : nullptr;
        _list._allocator.deallocate(_entry);
        _entry = target;
        --_list._size;

        return true;
    }

    LinkedListIterator<T> &operator ++() {
        if (_entry != nullptr) {
            _entry = _entry->_next;
        }
        return *this;
    }

    LinkedListIterator<T> &operator --() {
        if (_entry != nullptr) {
            _entry = _entry->_previous;
        }
        return *this;
    }

    bool operator !=(const LinkedListIterator<T> &other) const {
        if (other._entry != nullptr) {
            return _entry != other._entry->_next;
        } else {
            return _entry != other._entry;
        }
    }

    T operator *() {
        if (_entry == nullptr) {
            return T();
        } else {
            return _entry->_item;
        }
    }

private:
    LinkedListEntry<T> *makeEntry(T item) {

        // Allocate memory for the new entry instance.
        void * mem = _list._allocator.allocate(LinkedListEntry<T>::LINKED_LIST_ENTRY_SIZE);

        // If no memory available return the nullptr.
        if (mem == nullptr) {
            return nullptr;
        }

        // Call constructor for new entry by using placement new.
        LinkedListEntry<T> *newEntry = new (mem) LinkedListEntry<T>(item);

        return newEntry;
    }

    LinkedList<T> &_list;
    LinkedListEntry<T> *_entry;
};

template <typename T>
class ConstLinkedListIterator {
public:
    ConstLinkedListIterator(LinkedListEntry<T> *entry) : _entry(entry) {
    }

    ConstLinkedListIterator<T> &operator ++() {
        if (_entry != nullptr) {
            _entry = _entry->_next;
        }
        return *this;
    }

    ConstLinkedListIterator<T> &operator --() {
        if (_entry != nullptr) {
            _entry = _entry->_previous;
        }
        return *this;
    }

    bool operator !=(const ConstLinkedListIterator<T> &other) const {
        if (other._entry != nullptr) {
            return _entry != other._entry->_next;
        } else {
            return _entry != other._entry;
        }
    }

    const T operator *() const {
        if (_entry == nullptr) {
            return T();
        } else {
            return _entry->_item;
        }
    }

private:
    LinkedListEntry<T> *_entry;
};

template <typename T>
class LinkedList {
public:
    LinkedList(Allocator &allocator) : _allocator(allocator), _head(nullptr), _tail(nullptr), _size(0) {
    }

    std::size_t size() const {
        return _size;
    }

    bool append(T item) {
        return end().insertAfter(item);
    }

    bool prepend(T item) {
        return begin().insertBefore(item);
    }

    const T at(const std::size_t pos) const {
        if (pos >= size()) {
            return T();
        } else {
            auto it = begin();
            for (std::size_t i = 0; i < pos; ++i) {
                ++it;
            }
            return *it;
        }
    }

    void clear() {
        while(_size != 0) {
            begin().remove();
        }
    }

    bool swap(const std::size_t fromPos, const std::size_t toPos) {
        (void) fromPos;
        (void) toPos;
        // TODO: Implement me.
        return false;
    }

    // TODO: Add sort function that takes a lambda function as argument to sort the list.

    LinkedListIterator<T> begin() {
        return LinkedListIterator<T>(*this, _head);
    }

    ConstLinkedListIterator<T> begin() const {
        return ConstLinkedListIterator<T>(_head);
    }

    LinkedListIterator<T> end() {
        return LinkedListIterator<T>(*this, _tail);
    }

    ConstLinkedListIterator<T> end() const {
        return ConstLinkedListIterator<T>(_tail);
    }

private:
    Allocator &_allocator;
    LinkedListEntry<T> *_head;
    LinkedListEntry<T> *_tail;
    std::size_t _size;

    // LinkedListIterator<T> needs access to _size, _head, _tail and _allocator
    friend class LinkedListIterator<T>;
};

}
}

#endif // LINKEDLIST_H
