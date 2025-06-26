#include <unordered_map>
#include <vector>
#include <string>

struct SuperKey {
    std::string StrPart;
    int IntPart;
    float FloatPart;

    bool operator==(const SuperKey& rhs) const {
        return this->StrPart == rhs.StrPart && this->IntPart == rhs.IntPart && this->FloatPart == rhs.FloatPart;
    }
};


template<>
struct std::hash<SuperKey>
{
    std::size_t operator()(const SuperKey& s) const noexcept
    {
        std::size_t h1 = std::hash<std::string>{}(s.StrPart);
        return h1; // or use boost::hash_combine
    }
};
/*
 * Напишите хэш-функцию, реализовав специализацию шаблона std::hash для типа SuperKey
 * Напише функцию PopulateHashMap, которая добавляет в hashMap пары ключ-значение из данного вектора toAdd
 */
void PopulateHashMap(std::unordered_map<SuperKey, std::string>& hashMap, const std::vector<std::pair<SuperKey, std::string>>& toAdd)
{
    for (size_t i = 0; i < toAdd.size(); i++)
    {
        hashMap.insert(std::make_pair(toAdd[i].first,toAdd[i].second));
    }
}

