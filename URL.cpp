#include<iostream>
#include<string>
#include<vector>
using namespace std;

const string code= "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

string encoded;
string decoded;

string flag ="9";

void append(const int& b) {
	if (b > 61) {
		encoded += code[b-61];
	}
	else
		encoded += code[b];
	
}

 void base62(string s) {
	int b;
	encoded ="";
	for(int i=0;i<s.length();i+=3)
	{
		b = (s[i] & 0xFC) >> 2;
		append(b);

		b = (s[i] & 0x03) << 4;

		if (i + 1 < s.length())
		{
			b |= (s[i + 1] & 0xF0) >> 4;
			append(b);

			b = (s[i + 1] & 0x0F) << 2;
			if (i + 2 < s.length())
			{
				b |= (s[i + 2] & 0xC0) >> 6;
				append(b);

				b = s[i + 2] & 0x3F;
				append(b);
			}
			else
				append(b);

		}
		else
			append(b);
	}
}

 void decode62(string encoded) {
	 int m = 0;
	 int unit[4];
	 int b = 0;
	 vector<int>ch;
	 for (int i = 0; i < encoded.length(); i++) {
		 unit[m] = code.find(encoded[i]);
		 m++;
		 if (m == 4)
		 {
			 b = unit[0] << 2 | unit[1] >> 4;
			 ch.push_back(b);
			// cout << b;
			 b = (unit[1] << 4 | unit[2] >> 2)& 0xFF;
			 ch.push_back(b);
			 b = (unit[2] << 6 | unit[3]) &0xFF;
			 ch.push_back(b);
			 m = 0;

		 }
		 
	}

	 if (m != 0) {
		 if (m == 1) {
			 b = unit[0] >> 2;
			 ch.push_back(b);
		 }
		 if (m == 2)
		 {
			 b = unit[0] << 2 | unit[1] >> 4;
			 ch.push_back(b);
		 }
		 if (m == 3) {
			 b = unit[0] << 2 | unit[1] >> 4;
			 ch.push_back(b);
			 b = (unit[1] << 4 | unit[2] >> 2)& 0xFF;
			 ch.push_back(b);
		 }
	 }

	 for (auto el : ch)
		 decoded += el;

 }


int main() {
	string s;
	cin >> s;
	base62(s);
	cout << encoded<<"\n";
	decode62(encoded);
	cout << decoded;
	return 0;
	
}