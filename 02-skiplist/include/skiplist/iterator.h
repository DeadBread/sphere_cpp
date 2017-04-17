#ifndef __ITERATOR_H
#define __ITERATOR_H
#include <cassert>
#include "node.h"

/**
 * Skiplist const iterator
 */
template<class Key, class Value>
class Iterator {
private:
  Node<Key, Value> *pCurrent;

public:
  Iterator(Node<Key,Value> *p) : pCurrent(p) {}
  virtual ~Iterator() {}

  virtual const Key& key() const {
    assert(pCurrent != nullptr);
    return pCurrent->key();
  };

  virtual const Value& value() const {
    assert(pCurrent != nullptr);
    return pCurrent->value();
  };

  virtual const Value& operator*() {
    assert(pCurrent != nullptr);
    return pCurrent->value();
  };

  virtual const Value& operator->() {
    assert(pCurrent != nullptr);
    return pCurrent->value();
  };

  virtual bool operator==(const Iterator &right) const {
    return this->pCurrent == right.pCurrent;
  };

  virtual bool operator!=(const Iterator &right) const {
    return this->pCurrent != right.pCurrent;
  };


  virtual Iterator& operator=(const Iterator &right) {
  	this->pCurrent = right.pCurrent;
    return *this;
  };

  virtual Iterator& operator++() {
  	this->pCurrent = &(this->pCurrent->next());
    return *this;
  };

  //How it should be implemented for iterators?
  virtual Iterator operator++(int) {
  	auto tmp = *this;
  	this->pCurrent = &(this->pCurrent->next());
    return tmp;
  };
};

#endif // __ITERATOR_H
