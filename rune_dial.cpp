#include <bits/stdc++.h>

std::vector<std::string> decodeRunes(std::string runes)
{

    static std::array<std::string, 8> rune_letters{
        "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz",
    };

    if (runes.size() == 0)
    {
        return {};
    }

    std::vector<std::string> subRunes{decodeRunes(runes.substr(1))};
    if (subRunes.size() == 0)
    {
        subRunes = std::vector<std::string>{""};
    }

    std::vector<std::string> res;
    for (char ch : rune_letters[runes[0] - '2'])
    {
        for (std::string s : subRunes)
        {
            res.push_back(ch + s);
        }
    }

    return res;
}

int main()
{
    for (std::string s : decodeRunes("234"))
    {
        std::cout << s << std::endl;
    }

    int a[0];
    int *p = a;

    std::cout << *p << std::endl;

    int res[3][3]{std::array<int, 3>{1, 2, 3}, std::array<int, 3>{1, 2, 3},
                  std::array<int, 3>{1, 2, 3}};
}