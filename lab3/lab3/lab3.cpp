
#include <iostream>
#include <string>
using namespace std;


int main()
{
    string word="zayyand", buff1="", buff2=word, res="";
    int last_ind=0;

    for (int i = 0; i < word.length() - 1; i++)
    {
        if (word[i] != word[i + 1])
        {
            buff1 += word[i];
            last_ind = i;
        }
        else if (buff1.length()>0){
            
            if (buff1[buff1.length() - 1] != word[i] && i - last_ind == 1) {
                buff1 += word[i];
                last_ind = i;
            }
            
            if (buff1 < buff2)
                buff2 = buff1;
            buff1 = "";
        }
        
    }
    if (buff1 < buff2)
        buff2 = buff1 + word[word.length() - 1];
        

    if (buff2[buff2.length()-1] != word[word.length() - 1] && last_ind == word.length()-1) buff2 += word[word.length() - 1];
    if (last_ind == 0) buff2 = word[0];
    cout << buff2;
}


