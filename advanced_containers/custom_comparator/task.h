#include <map>
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

bool operator <(const SuperKey& lhs, const SuperKey& rhs)
{
    if(lhs.StrPart < rhs.StrPart)
    {
        return true;
    }
    if(lhs.StrPart == rhs.StrPart && lhs.IntPart < rhs.IntPart)
    {
        return true;
    }
    if(lhs.StrPart == rhs.StrPart && lhs.IntPart == rhs.IntPart && lhs.FloatPart < rhs.FloatPart)
    {
        return true;
    }
    return false;
}

/*
 * Напишите реализацию оператора < для типа SuperKey, чтобы ключи типа SuperKey можно было использовать в map.
 * Порядок должен быть таким, чтобы все ключи с одинаковым значением поля StrPart шли друг за другом без пропусков.
 * Напишите функцию PopulateMap, которая добавляет в map пары ключ-значение из данного вектора toAdd
 */
void PopulateMap(
    std::map<SuperKey, std::string>& map,
    const std::vector<std::pair<SuperKey, std::string>>& toAdd){
        for (size_t i = 0; i < toAdd.size(); i++)
        {
            map.insert(std::make_pair(toAdd[i].first,toAdd[i].second));
        }
    }
