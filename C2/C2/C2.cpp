// Старый фокусник решил передать секрет одного фокуса своему ученику.
// Фокус заключается в следующем : зритель угадывает натуральное число от 100 до 10000, затем вычитает из числа сумму его цифр.
//В полученном числе он зачёркивает любую ненулевую цифру и называет все оставшиеся цифры фокуснику.
//Выслушав названные цифры, фокусник, погодя, называет цифру, которая была зачёркнута.
// Требуется написать программу, которая, получив на вход названные цифры, выдаёт зачёркнутую зрителем цифру.
//Вход программы представлен текстовым файлом input.txt, в котором в одну строку без пробелов
//заданы называемые зрителем цифры.Выход программы представлен
//текстовым файлом output.txt, в который записывается зачёркнутая цифра.Пример:
// 12345674 -> 4

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
    string str; int sum = 0;
    ifstream input("input.txt");
    ofstream output("output.txt");
    while (!input.eof())
    {
        getline(input, str);
        for (int i = 0; i < size(str); ++i)
            sum += str[i] - 48;
        output << 9 * (sum / 9 + 1) - sum;
    }
    input.close();
    output.close();
}