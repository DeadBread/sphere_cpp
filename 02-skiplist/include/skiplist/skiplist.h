#ifndef __SKIPLIST_H
#define __SKIPLIST_H
#include <functional>
#include <ctime>
#include <cstdlib>
#include <list>
#include "node.h"
#include "iterator.h"

/**
 * Skiplist interface
 */
template<class Key, class Value, size_t MAXHEIGHT, class Compare = std::less<Key>>
class SkipList {
private:
  Node<Key, Value> *pHead;
  Node<Key, Value> *pTail;

  IndexNode<Key, Value> *pTailIdx;
  IndexNode<Key, Value> *aHeadIdx[MAXHEIGHT];

public:
  /**
   * Creates new empty skiplist
   */
  SkipList() {
    pHead   = new DataNode<Key, Value>(nullptr, nullptr);
    pTail   = new DataNode<Key, Value>(nullptr, nullptr);

    Node<Key, Value> *prev = pHead;
    pTailIdx = new IndexNode<Key, Value>(pTail, pTail);
    for (int i=0; i < MAXHEIGHT; i++) {
      aHeadIdx[i] = new IndexNode<Key, Value>(prev, pHead);
      aHeadIdx[i]->next(pTailIdx);
      prev = aHeadIdx[i];
    }
  }

  /**
   * Disable copy constructor
   */
  SkipList(const SkipList& that) = delete;


  /**
   * Destructor
   */
  virtual ~SkipList() {
    delete pTailIdx;
    for (int i=0; i < MAXHEIGHT; i++) {
      delete aHeadIdx[i];
    }

    delete pHead;
    delete pTail;
  };

  /**
   * Assign new value for the key. If a such key already has
   * assosiation then old value returns, otherwise nullptr
   *
   * @param key key to be assigned with value
   * @param value to be added
   * @return old value for the given key or nullptr
   */

  Node<Key,Value>* insert_after_data(Node<Key,Value>& after, const Key& key, const Value& value) {
    DataNode<Key,Value> * old_next = dynamic_cast<DataNode<Key,Value> *> ( &after.next() );
    DataNode<Key,Value> * new_next = new DataNode<Key,Value> (&key, &value);
    (dynamic_cast<DataNode<Key,Value> &>(after)).next(new_next);
    new_next->next(old_next);
    return new_next;
  };

  Node<Key,Value>* insert_after_index(Node<Key,Value>& after, Node<Key,Value> *down, Node<Key,Value> *root) {
    IndexNode<Key,Value> * old_next = dynamic_cast<IndexNode<Key,Value> *> ( &after.next() );
    IndexNode<Key,Value> * new_next = new IndexNode<Key,Value> (down, root);
    (dynamic_cast<IndexNode<Key,Value> &>(after)).next(new_next);
    new_next->next(old_next);
    return new_next;
  };

  //what kind of const could've been here!?
  virtual Value* Put(const Key& key, const Value& value) {
    srand(time(0));

    //finding the element. If it exists - deleting it
    Value *find = Get(key);
    if (find != nullptr)
      this->Delete(key);

    std::list<Node<Key,Value> *> before_insert;

    Node<Key, Value> &cur = *aHeadIdx[MAXHEIGHT - 1];
    int cur_level = MAXHEIGHT;

    //finding the proper place for the new element and saving the upper level positions.
    while (cur_level >= 0) {
      while ((cur.next()).key() <= key)
        cur = cur.next();

      if (cur_level > 0) {
        before_insert.push_front (&cur);
        cur = (dynamic_cast<IndexNode<Key,Value> &>(cur)).down();
        cur_level --;
      }
    }
    
    Node<Key,Value>* new_root = insert_after_data(cur, key, value);
    Node<Key,Value>* new_down = new_root;
    int coin = rand() % 2; //coin

    auto iter = before_insert.begin();
    while ((iter != before_insert.end()) && coin) {
      new_down = insert_after_index(*(*iter), new_down, new_root);
      coin = rand() % 2;
      iter ++;
    }

    return find;

    // Node<Key, Value> &cur = *aHeadIdx[MAXHEIGHT - 1];

    // while(cur.key() <= key) {
    //   cur = cur.next();
    // }

    // std::vector<IndexNode<Key,Value> *> to_add(MAXHEIGHT);

    // int cur_level = MAXHEIGHT;

    // while (cur_level > 0) {
    //   while ((cur.next()).key() <= key)
    //     cur = cur.next();

    //   cur = (dynamic_cast<IndexNode<Key,Value> &>(cur)).down();
    //   cur_level --;
    // }

    // while ((cur.next()).key() <= key)
    //   cur = cur.next();

    // if (cur.key() == key) {
    //   Value* ret = const_cast<Value *> (&cur.value());
    //   DataNode<Key, Value> *tmp_next = &cur.next();
    //   cur = DataNode<Key, Value> (key, value);
    //   cur.next(tmp_next);
    //   return ret;
    // }
    // else {

    //   return nullptr;
    // }


  };

  /**
   * Put value only if there is no assosiation with key in
   * the list and returns nullptr
   *
   * If there is an established assosiation with the key already
   * method doesn't nothing and returns existing value
   *
   * @param key key to be assigned with value
   * @param value to be added
   * @return existing value for the given key or nullptr
   */
  virtual Value* PutIfAbsent(const Key& key, const Value& value) {
    return nullptr;
  };

  /**
   * Returns value assigned for the given key or nullptr
   * if there is no established assosiation with the given key
   *
   * @param key to find
   * @return value assosiated with given key or nullptr
   */
  virtual Value* Get(const Key& key) const {
    Node<Key, Value> &cur = *aHeadIdx[MAXHEIGHT - 1];
    int cur_level = MAXHEIGHT;

    while (cur_level >= 0) {
      while ((cur.next()).key() <= key)
        cur = cur.next();

      if (cur_level > 0) {
        cur = (dynamic_cast<IndexNode<Key,Value> &>(cur)).down();
        cur_level --;
      }
    }

    if (cur.key() == key)
      return const_cast<Value*> (&cur.value());

    return nullptr;
  };

  /**
   * Remove given key from the skpiplist and returns value
   * it has or nullptr in case if key wasn't assosiated with
   * any value
   *
   * @param key to be added
   * @return value for the removed key or nullptr
   */
  virtual Value* Delete(const Key& key) {
    Node<Key, Value> &cur = *aHeadIdx[MAXHEIGHT - 1];
    int cur_level = MAXHEIGHT;

    //deleting from higher levels
    while (cur_level > 0) {
      while ((cur.next()).key() < key)
        cur = cur.next();
      if (cur.next().key() == key) {

        //two awesome lines!
        //did u mean this to work like that?
        IndexNode<Key, Value> * new_next = dynamic_cast<IndexNode<Key, Value> *>(& (cur.next().next()));
        dynamic_cast<IndexNode<Key, Value> &>(cur).next(new_next);
      }
    }

    //deleting from the first level
    cur = *pHead;
    while ((cur.next()).key() < key)
        cur = cur.next();
      if (cur.next().key() == key) {
        DataNode<Key, Value> * new_next = dynamic_cast<DataNode<Key, Value> *>(& (cur.next().next()));
        dynamic_cast<DataNode<Key, Value> &>(cur).next(new_next);
      }


    return nullptr;
  };

  /**
   * Same as Get
   */
  virtual const Value* operator[](const Key& key) {
    return nullptr;
  };

  /**
   * Return iterator onto very first key in the skiplist
   */
  virtual Iterator<Key, Value> cbegin() const {
    return Iterator<Key,Value>(pTail);
  };

  /**
   * Returns iterator to the first key that is greater or equals to
   * the given key
   */
  virtual Iterator<Key, Value> cfind(const Key &min) const {
    return Iterator<Key,Value>(pTail);
  };

  /**
   * Returns iterator on the skiplist tail
   */
  virtual Iterator<Key, Value> cend() const {
    return Iterator<Key,Value>(pTail);
  };
};
#endif // __SKIPLIST_H
