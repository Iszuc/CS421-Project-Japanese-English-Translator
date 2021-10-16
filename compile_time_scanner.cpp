#include <iostream>
#include <array>
#include <utility>
#include <string>
using namespace std;

template<unsigned int>
auto table = 0;

constexpr pair<char,unsigned int> Trs(const char& c, const unsigned int& i)
{
  return pair(c,i);
}

template<>
constexpr array table<1>
{
  Trs('a', 2),
  Trs('b', 3),
  Trs('c', 4)
};

template<>
constexpr array table<2>
{
  Trs('d', 1)
};

template<>
constexpr array table<3>
{
  Trs('d', 0)
};

template<>
constexpr array table<4>
{
  Trs('d', 0)
};

template<unsigned int id>
bool scan(const string& s, const unsigned int& i);

template<unsigned int id, unsigned int begin, unsigned int end>
inline bool scan(const string& s, const unsigned int& i)
{
  constexpr unsigned int index = (begin + end) / 2;

  if constexpr(begin == end)
  {
    return false;
  }
  else if(table<id>[index].first < s[i])
  {
    return scan<id, index + 1, end>(s,i);
  }
  else if(table<id>[index].first > s[i])
  {
    return scan<id, begin, index>(s,i);
  }
  else if constexpr(table<id>[index].second == 0)
  {
    return true;
  }
  else
  {
    return scan<table<id>[index].second>(s, i+1);
  }
}

template<unsigned int id>
bool scan(const string& s, const unsigned int& i)
{
  return scan<id, 0, table<id>.size()>(s,i);
}

bool scan(const string& s)
{
  return scan<1>(s,0);
}

int main()
{
  cout << scan("ad") << endl;
  cout << scan("ab") << endl;
  cout << scan("bd") << endl;
  cout << scan("adbd") << endl;
  cout << scan("adb") << endl;
  return 0;
}
