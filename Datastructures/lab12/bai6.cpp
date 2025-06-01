#include <iostream>
#include <vector>
#include <string>
#include <cstdint>

using namespace std;

struct CuckooMap
{
    struct Slot
    {
        uint8_t bit = 0;
        bool tag = false;
        string word;
    };

    vector<Slot> tab1, tab2;
    size_t size;
    size_t used = 0;
    static const int LIMIT = 500;
    static constexpr uint64_t P1 = 1315423911u;
    static constexpr uint64_t P2 = 1465277093u;

    CuckooMap(size_t count)
    {
        size = 1;
        while (size < count * 3)
            size <<= 1;
        tab1.resize(size);
        tab2.resize(size);
    }

    size_t hash1(const string &s) const
    {
        uint64_t h = 0;
        for (char c : s)
            h = h * P1 + static_cast<uint8_t>(c);
        return h & (size - 1);
    }

    size_t hash2(const string &s) const
    {
        uint64_t h = 0;
        for (char c : s)
            h = h * P2 + static_cast<uint8_t>(c);
        return h & (size - 1);
    }

    bool update(const string &s, uint8_t b)
    {
        size_t p1 = hash1(s);
        if (tab1[p1].tag && tab1[p1].word == s)
        {
            tab1[p1].bit |= b;
            return true;
        }
        size_t p2 = hash2(s);
        if (tab2[p2].tag && tab2[p2].word == s)
        {
            tab2[p2].bit |= b;
            return true;
        }
        return false;
    }

    void put(string key, uint8_t b)
    {
        if (update(key, b))
            return;
        for (int i = 0, flip = 0; i < LIMIT; ++i, flip ^= 1)
        {
            if (flip == 0)
            {
                size_t idx = hash1(key);
                if (!tab1[idx].tag)
                {
                    tab1[idx].tag = true;
                    tab1[idx].word = move(key);
                    tab1[idx].bit = b;
                    ++used;
                    return;
                }
                swap(key, tab1[idx].word);
                swap(b, tab1[idx].bit);
            }
            else
            {
                size_t idx = hash2(key);
                if (!tab2[idx].tag)
                {
                    tab2[idx].tag = true;
                    tab2[idx].word = move(key);
                    tab2[idx].bit = b;
                    ++used;
                    return;
                }
                swap(key, tab2[idx].word);
                swap(b, tab2[idx].bit);
            }
        }
        expand();
        put(move(key), b);
    }

    void expand()
    {
        vector<Slot> old;
        for (auto &e : tab1)
            if (e.tag)
                old.push_back(move(e));
        for (auto &e : tab2)
            if (e.tag)
                old.push_back(move(e));
        size <<= 1;
        tab1.clear();
        tab2.clear();
        tab1.resize(size);
        tab2.resize(size);
        used = 0;
        for (auto &e : old)
            put(move(e.word), e.bit);
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    CuckooMap dict(n);
    string line;
    for (int i = 0; i < n; ++i)
    {
        cin >> line;
        dict.put(move(line), 1);
    }
    for (int i = 0; i < n; ++i)
    {
        cin >> line;
        dict.put(move(line), 2);
    }
    for (int i = 0; i < n; ++i)
    {
        cin >> line;
        dict.put(move(line), 4);
    }

    long long pts[3] = {0, 0, 0};
    auto eval = [&](const CuckooMap::Slot &s)
    {
        if (!s.tag)
            return;
        int c = __builtin_popcount(s.bit);
        if (c == 1)
        {
            int p = (s.bit == 1 ? 0 : (s.bit == 2 ? 1 : 2));
            pts[p] += 3;
        }
        else if (c == 2)
        {
            for (int i = 0; i < 3; ++i)
                if (s.bit & (1 << i))
                    pts[i] += 1;
        }
    };
    for (const auto &s : dict.tab1)
        eval(s);
    for (const auto &s : dict.tab2)
        eval(s);
    cout << pts[0] << ' ' << pts[1] << ' ' << pts[2] << '\n';
    return 0;
}
