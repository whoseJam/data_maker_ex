#include <iostream>
#include <cassert>
#include <clocale>
#include <random>
#include <string>
#include <cwchar>
#include <vector>
#include <string>
#include <set>

using namespace std;

namespace sequence {

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<uint32_t> dis(0x00000000, 0x10FFFF);

int R(int l, int r) {
    return rand() % (r - l + 1) + l;
}

wchar_t generateRandomUnicodeChar() {
    uint32_t randomCodePoint = dis(gen);
    return static_cast<wchar_t>(randomCodePoint);
}

template<typename T>
void shuffle(vector<T>& answer) {
    for (int i = 1; i < answer.size(); i++) {
        int last = R(0, i);
        swap(answer[i], answer[last]);
    }
}
static vector<int> make(int n, int min, int max) {
    vector<int> answer;
    for (int i = 0; i < n; i++)
        answer.push_back(R(min, max));
    return answer;
}

/**
 * 构造一个元素范围为[min, max]的长度为n的元素互不相同的数组
 * @param n 数组长度
 * @param min 最小元素值
 * @param max 最大元素值
*/
vector<int> makeUnique(int n, int min, int max) {
    if ((max - min) / 5 <= n) {
        vector<int> memory{max - min + 1};
        for (int i = min; i <= max; i++)
            memory[i - min] = i;
        shuffle(memory);
        vector<int> answer;
        for (int i = 0; i < n; i++)
            answer.push_back(memory[i]);
        return answer;
    } else {
        set<int> memory;
        vector<int> answer;
        for (int i = 1; i <= n; i++) {
            int x = R(min, max);
            while (memory.find(x) != memory.end())
                x = R(min, max);
            answer.push_back(x);
        }
        return answer;
    }
}

/**
 * 构造一个长度为n的字符集范围[min, max]的字符串
 * @param n
 * @param min
 * @param max
*/
string makeString(int n, char min, char max) {
    string answer;
    for (int i = 0; i < n; i++)
        answer.push_back(R(min, max));
    return answer;
}
vector<int> makePermutation(int n) {
    vector<int> answer;
    for (int i = 1; i <= n; i++) {
        answer.push_back(i);
        int cur = i - 1;
        if (0 < cur) {
            int last = R(0, cur);
            swap(answer[last], answer[cur]);
        }
    }
    return answer;
}

}

using namespace sequence;

int main() {
    std::setlocale(LC_ALL, "en_US.UTF-8");
    cout << "wchar_t size = " << sizeof(wchar_t) << "\n";
    cout << "'a' size = " << sizeof('a') << '\n';
    cout << "'🚀' size = " << sizeof(L'🚀') << '\n';
    cout << "'🧑‍🚀' size = " << sizeof(L"🧑‍🚀") << "\n";
    std::wstring output;
    for (int i = 0; i < 10; i++) {
        wchar_t randomChar = L'🚀'; // generateRandomUnicodeChar();
        output += randomChar;
    }
    cout << output.size() << " !\n";
    wcout.imbue(locale(""));
    std::wcout << output << std::endl;

    std::wstring multiCharWStr = L"🧑‍🚀";
    wcout << "'" << multiCharWStr << "' size = " << sizeof(multiCharWStr) << ", " << multiCharWStr.size() << "\n";

    cout << "end\n";
    return 0;
}