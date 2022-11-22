#ifndef HASHES
#define HASHES

#include <vector>
#include <unordered_set>

namespace std {
    template<typename T>
    inline void hash_combine(std::size_t& seed, const T& v)
	{
		std::hash<T> hasher;
		seed ^= hasher(v) + 0x9e3779b9 + (seed<<6) + (seed>>2);
	}

    template <>
    struct hash<pair<unsigned int, unsigned int>> {
        size_t operator()(const pair<unsigned int, unsigned int>& p) const
        {
            auto hash1 = hash<unsigned int>{}(p.first);
            auto hash2 = hash<unsigned int>{}(p.second);
    
            if (hash1 != hash2) {
                return hash1 ^ (hash2 << 1);             
            }
            
            // If hash1 == hash2, their XOR is zero.
            return hash1;
        }
    };

    template <>
    struct hash<pair<unsigned int*, unsigned int*>> {
        size_t operator()(const pair<unsigned int*, unsigned int*>& p) const
        {
            auto hash1 = hash<unsigned int*>{}(p.first);
            auto hash2 = hash<unsigned int*>{}(p.second);
    
            if (hash1 != hash2) {
                return hash1 ^ (hash2 << 1);             
            }
            
            // If hash1 == hash2, their XOR is zero.
            return hash1;
        }
    };

    template <>
    struct hash<unordered_set<unsigned int>> {
        auto operator()(const unordered_set<unsigned int>& vec) const -> size_t {
            std::size_t seed = vec.size();
            for (auto x : vec) {
                x = ((x >> 16) ^ x) * 0x45d9f3b;
                x = ((x >> 16) ^ x) * 0x45d9f3b;
                x = (x >> 16) ^ x;
                seed ^= x + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            }
            return seed;
        }
    };

    template <>
    struct hash<vector<unsigned int>> {
        auto operator()(const vector<unsigned int>& vec) const -> size_t {
            std::size_t seed = vec.size();
            for (auto x : vec) {
                x = ((x >> 16) ^ x) * 0x45d9f3b;
                x = ((x >> 16) ^ x) * 0x45d9f3b;
                x = (x >> 16) ^ x;
                seed ^= x + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            }
            return seed;
        }
    };

	template<typename T1, typename T2>
	struct hash<std::pair<T1, T2>> {
		std::size_t operator()(std::pair<T1, T2> const &p) const {
		std::size_t seed1(0);
		std::hash_combine(seed1, p.first);
		std::hash_combine(seed1, p.second);

		std::size_t seed2(0);
		std::hash_combine(seed2, p.second);
		std::hash_combine(seed2, p.first);

		return std::min(seed1, seed2);
		}
	};
};

#endif
