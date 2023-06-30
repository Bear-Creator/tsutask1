#include<iostream>
#include<fstream>
#include<algorithm>

using namespace std;
char c;
int RecordLength, Shift, txtlen;
string text;

string sdvig(string s, int shift)
{
    if (shift>0)  rotate(s.begin(),s.begin()+(s.length()-shift),s.end());
    else rotate(s.begin(),s.begin()+(abs(shift)),s.end());
    return s;
};

string encrypt(string text, int Shift)
{   
    string out, rslt = "";
    int k, sim;
    int ost = 0;
    txtlen = text.length();
    for (int i = 0; i < txtlen; i++)
    {   
        sim = (int)text[i];
        k = 128;
        while (k>=1) {
            out += to_string(sim/k);
            sim %= k;
            k /= 2;
        };

        
        ost++;
        if (ost == RecordLength)
        {
            ost = 0;
            rslt += sdvig(out, Shift);
            out = "";
        }
    }

    return rslt;
}

string decrypt(string text, int Shift)
{   
    string s, out = "";
    int nom, pow2;
    Shift *= -1;
    txtlen = text.length();
    for (int i=0; i < txtlen/(RecordLength*8); i++)
    {   
        s = sdvig(text.substr(i*RecordLength*8, RecordLength*8), Shift);
        for (int k=0; k < RecordLength; k++)
        {   
            nom = 0;
            pow2=1;
            for (int j=7;j>-1;j--)
            {
                if (s[k*8 + j]=='1') nom+=pow2;
                pow2*=2;
            }
            out+=(char) nom;
        }
    }
    return out;
}

int main()
{
    ifstream in("input.txt");
    in>>RecordLength;
    in>>Shift;
    in>>text;
    txtlen = text.length();
    if (txtlen%RecordLength !=0) 
        for (int i = 0; i < (RecordLength - (txtlen%RecordLength)); i++) text+=" ";
    text = encrypt(text, Shift);
    for (int i=0; i<txtlen*8; i++)
    {
        if (i % (RecordLength*8) ==0) cout << " "; 
        cout << text[i];
    }
    cout << endl;
    text = decrypt(text, Shift);
    cout << text << endl;
    return 0;
}
