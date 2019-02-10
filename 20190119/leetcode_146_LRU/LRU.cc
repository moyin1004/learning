/// @file    LRU.cc
/// @data    2019-01-21 12:08:43

#if 0
//44ms version

auto desyncio = []()  //这是关键，虽然不知道啥意思
{
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

struct CacheNode {
    int key;
    int value;
    CacheNode *next;
    CacheNode *pre;
    CacheNode(int k, int v): key(k), value(v){}
};

class List {
public:
    List()
    : _head(new CacheNode(0, 0))
    , _tail(_head)
    , _size(0)
    {
        _head->next = _head->pre = _head;
    }

    void push_back(int key, int value) {
        CacheNode *p = new CacheNode(key, value);
        p->next = _head;
        p->pre = _tail;
        _tail->next = p;
        _head->pre = p;
        _size++;
        _tail = _tail->next;
    }

    void to_back(CacheNode *n) {
        if(n != _tail) {
            n->pre->next = n->next;
            n->next->pre = n->pre;
            n->next = _head;
            n->pre = _tail;
            _tail->next = n;
            _head->pre = n;
            _tail = n;
        }
    }

    void erase(CacheNode *n) {
        n->next->pre = n->pre;
        n->pre->next = n->next;
        _tail = _head->pre;
        _size--;
        delete n;
    }

    ~List() {
        _head = _head->next;
        while (_head != _tail) {
            delete _head->pre;
            _head = _head->next;
        }
        delete _head;
    }

    CacheNode *_head;
    CacheNode *_tail;
    int _size;
};



class LRUCache {
public:
    LRUCache(int capacity) 
    : _cap(capacity)
    , _size(0)
    {}

    int get(int key) {
        auto itnode = _node.find(key);
        if (itnode == _node.end()) return -1;

        _cachelist.to_back(itnode->second);
        itnode->second = _cachelist._tail;
        return _cachelist._tail->value;
    }

    void put(int key, int value) {
        auto itnode = _node.find(key);
        if (itnode == _node.end()) {
            if(_size == _cap) {
                _node.erase(_cachelist._head->next->key);
                _cachelist.erase(_cachelist._head->next);
                --_size;
            }
            _cachelist.push_back(key, value);
            _node[key] = _cachelist._tail;
            ++_size;
            return ;
        }

        _cachelist.to_back(itnode->second);
        _cachelist._tail->value = value;
        itnode->second = _cachelist._tail;
    }
private:
    List _cachelist;
    std::unordered_map<int, CacheNode *> _node;
    int _cap;
    int _size;
};
#endif

#if 0
//88ms version

class LRUCache {
public:
    LRUCache(int capacity) 
    : _cap(capacity)
    , _size(0)
    {}

    int get(int key) {
        if (_node.find(key) == _node.end())
            return -1;
        else {
            int value = _node[key]->value;
            _cachelist.erase(_node[key]);
            _cachelist.push_back(CacheNode(key, value));
            auto it = _cachelist.end();
            _node[key] = --it;
            return value;
        }
    }

    void put(int key, int value) {
        auto it = _cachelist.end();
        if (_node.find(key) != _node.end()) {
            _cachelist.erase(_node[key]);
            _cachelist.push_back(CacheNode(key, value));
            it = _cachelist.end();
            _node[key] = --it;
        }
        else {
            if(_size == _cap) {
                _node.erase(_cachelist.begin()->key);
                _cachelist.pop_front();
                _cachelist.push_back(CacheNode(key, value));
                it = _cachelist.end();
                _node[key] = --it;
            }
            else {
                _cachelist.push_back(CacheNode(key, value));
                it = _cachelist.end();
                _node[key] = --it;
                ++_size;
            }
        }
    }
private:
    struct CacheNode {
        int key;
        int value;
        CacheNode(int k, int v): key(k), value(v){}
    };
    std::list<CacheNode> _cachelist;
    std::unordered_map<int, list<CacheNode>::iterator> _node;
    int _cap;
    int _size;
};

#endif
