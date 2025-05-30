#ifndef ITEM_H
#define ITEM_H

#include <cstring>

#ifndef KEYSZ
#define KEYSZ 6 
#endif

#ifndef PLSZ
#define PLSZ 10
#endif

class Item {
public:
    char key[KEYSZ];
    char payload[PLSZ];

    bool operator<(const Item &outro) const {
        return strcmp(key, outro.key) < 0;
    }

    bool operator>(const Item &outro) const {
        return std::strcmp(this->key, outro.key) > 0;
    }

};

#endif
