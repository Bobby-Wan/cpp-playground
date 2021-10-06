#ifndef _HASHMAP_HEADER_
#define _HASHMAP_HEADER_

#include "vector.hpp"
#include "list.hpp"
#include "../algorithms/hash.hpp"
#include "../exceptions/exceptions.hpp"

namespace ds{
    //generic hashmap with chaining
        template <class K, class V>
        class hash_map_chaining
        {
            struct pair{
                K key;
                V value;
            };

            // inline bool operator==(const pair& lhs, cosnt pair& rhs){
            //         return this.key == other.key && this->value == other.value;
            // }
        public:
            //delete

            hash_map_chaining(std::size_t size_of_table=16) : m(size_of_table),table(size_of_table){}

            void insert(const K &key, const V &value){
                size_t hash = key_to_hash(key);
                size_t position = hash_to_position(hash);

                pair p;
                p.key = hash;
                p.value = value;

                if(!table[position].is_empty()){
                    //stats
                    ++collisions;
                }

                table[position].append(p);

                //stats
                ++insertions;
            }

            bool contains(const K& key) const
            {
                size_t position = key_to_position(key);
                
                for(auto pair:table[position]){
                    if(pair.key == key_to_hash(key)){
                        return true;
                    }
                }

                return false;
            }

            V& operator[](const K& key) {
                size_t position = key_to_position(key);
                // for(auto pair:table[position]){
                //     if(pair.key == key_to_hash(key)){
                //         return pair.value;
                //     }
                // }
                for(auto b = table[position].begin();b != table[position].end();++b){
                    if((*b).key == key){
                        return (*b).value;
                    }
                }

                throw except::key_not_found_exception();
            }

            const V& operator[](const K& key)const throw(){
                size_t position = key_to_position(key);
                for(auto pair:table[position]){
                    if(pair.key == key){
                        return pair.value;
                    }
                }

                throw except::key_not_found_exception();
            }

        private:
            size_t key_to_position(const K& key)const{
                return key_to_hash(key) % m;
            }
            size_t key_to_hash(const K& key)const{
                return alg::hash::hash<K>{}(key);
            }
            size_t hash_to_position(const std::size_t i)const{
                return i % m;
            }
        private:
            //size of table;
            std::size_t m;

            size_t collisions = 0;
            size_t insertions = 0;
            // hash<K> hash_function;
            ds::vector<list<pair>> table;
        };
    
}





#endif  //_HASHMAP_HEADER_