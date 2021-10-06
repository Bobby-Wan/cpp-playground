#include <cstddef>
#include "../data_structures/vector.hpp"

namespace alg
{
    namespace hash
    {
        // typedef size_t size_type;

        struct DummyHashableClass
        {
            DummyHashableClass(std::size_t id) : id(id){};

            std::size_t get_id() const
            {
                return id;
            }

        private:
            std::size_t id;
        };

        std::size_t generate_key(const DummyHashableClass& dhc)
        {
            return dhc.get_id();
        }

        template <class T>
        class hash
        {
            public:
            std::size_t operator()(const T& t) const noexcept;
        };

        //template specialization
        template <>
        class hash<int>{
            public:
            std::size_t operator()(const int& i) const noexcept{
                return static_cast<std::size_t>(i);
            }
        };

        template <>
        class hash<DummyHashableClass>{
            std::size_t operator()(const DummyHashableClass& dummy) const noexcept{
                return dummy.get_id();
            }
        };
    }

}