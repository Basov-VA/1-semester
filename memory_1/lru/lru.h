#include <iostream>
#include <unordered_map>
#include <list>

template <typename K, typename V>
class LruCache {
public:
    LruCache(unsigned int size_):
            size(size_)
    {}

    void GoEnd(typename std::list<std::pair<K, V>>::iterator& it) {
        values.push_back(*it);
        values.erase(it);
        it = --values.end();
    }

    void Put(const K& it, const V& val) {
        auto iter_ = cache.find(it);
        if (iter_ == cache.end()) { // элемента нет в кеше
            if (cache.size() == size) { // удаляем ласт юзавшиеся элемент
                cache.erase(values.front().first);
                values.erase(values.begin());
            }
            values.push_back({it, val});
            cache[it] = --values.end();
        }
        else
        { // элемент есть в кеше, просто меняем местами последовательность юзания элемента
            iter_->second->second = val;
            GoEnd(iter_->second);
        }
    }

    bool Get(const K& it, V* val) {
        auto iter_ = cache.find(it);
        if (iter_ == cache.end()) {//элемента нет
            return false;
        }
        else
        {
            *val = iter_->second->second;
            GoEnd(iter_->second);
            return true;
        }
    }

private:
    std::unordered_map<K, typename std::list<std::pair<K, V>>::iterator> cache;
    std::list<std::pair<K, V>> values;
    unsigned int size;
};
