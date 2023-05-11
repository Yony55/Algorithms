// Jonathan Maya A01424137
// Programa que implementa los algoritmo de encriptacion de cesar, vigenere y OTP
#include <iostream>
#include <cstring>
using namespace std;

// Funcion que realiza el cifrado de cesar
void caesarCipher(){
    string caesarText;
    char key;
    int keyIndex;
    cout << "Ingresa el texto a cifrar: ";
    cin.ignore(1,'\n');
    getline(cin, caesarText);
    cout << "Ingrese la llave de cifrado: ";
    cin >> key;
    string result = "";

    if(isupper(key))
        keyIndex = int(key)-65;

    else
        keyIndex = int(key)-97;

    for (int i = 0; i < caesarText.length(); i++){
        if (isupper(caesarText[i])){
            if(caesarText[i] == ' '){
                result += ' ';
                continue;
        }
            result += char(int(caesarText[i] + keyIndex - 65) % 26 + 65);
        }

        else{
            if(caesarText[i] == ' '){
                result += ' ';
                continue;
            }
            result += char(int(caesarText[i]+keyIndex - 97) % 26 + 97);
        }
    
    }

    cout << "El texto cifrado es: " + result << endl;
    cout << endl;
 
}

// Funcion que realiza el cifrado vigenere
void vigenereCipher(){
    string vigenereText;
    string key;
    string vigenereTextUpper = "";
    string keyUpper = "";
    string result = "";
    cout << "Ingresa el texto a cifrar: ";
    cin.ignore(1,'\n');
    getline(cin, vigenereText);
    cout << "Ingrese la llave de cifrado: ";
    getline(cin, key);

    for (int i = 0; i < vigenereText.length(); i++){
        if(vigenereText[i] == ' '){
            vigenereTextUpper += ' ';
            continue;
        }
        vigenereTextUpper += toupper(vigenereText[i]);
    }
    for (int i = 0; i < key.length(); i++){
        if(key[i] == ' '){
            keyUpper += ' ';
            continue;
        }
        keyUpper += toupper(key[i]);
    }

    int keyIndex = 0;
    for(int i = 0; i < vigenereTextUpper.length(); i++){
        if(vigenereTextUpper[i] == ' '){
            result += ' ';
            continue;
        }
        else{
            if(keyUpper[keyIndex] == ' '){
                keyIndex++;
            }
            int keyCharIndex = int(keyUpper[keyIndex]-65);
            result += char(int(vigenereTextUpper[i] + keyCharIndex - 65) % 26 + 65);
            keyIndex++;
            if(keyIndex == keyUpper.length()){
                keyIndex = 0;
            }
        }
    }
    cout << "El texto cifrado es: " + result << endl;
    cout << endl; 
    
}

// Funcion que realiza el cifrado OTP
void OTP(){
    string result = "";
    string OTPTextUpper = "";
    string OTPText;
    string keyOTP = "";
    cout << "Ingresa el texto a cifrar: ";
    cin.ignore(1,'\n');
    getline(cin, OTPText);

    for (int i = 0; i < OTPText.length(); i++){
        if(OTPText[i] == ' '){
            OTPTextUpper += ' ';
            continue;
        }
        OTPTextUpper += toupper(OTPText[i]);
    }

    for(int i = 0; i < OTPTextUpper.length(); i++){
        if(OTPTextUpper[i] == ' '){
            result += ' ';
            keyOTP += ' ';
            continue;
        }
        else{
            int randNum = rand()%(90-65 + 1) + 65;
            keyOTP += char(randNum);
            result += char(int(OTPTextUpper[i] + randNum - 65) % 26 + 65);
        }
    }

    cout << "Palabra cifrada: " + result << endl;
    cout << "Llave de cifrado: " + keyOTP << endl;
    cout << endl;
}
 
int main(){
    int control = 0;
    while(control == 0){
        cout << "Ingrese un número para comenzar la encriptación" << endl;
        cout << "1 para Cifrado del Cesar" << endl;
        cout << "2 para el Cifrado Vigenere" << endl;
        cout << "3 para el cifrado OTP" << endl;
        cout << "4 para salir" << endl;
        int option;
        cout << "Ingrese su opción: ";
        cin >> option;
        if(option == 1){
            caesarCipher();
        }
        else if(option == 2){
            vigenereCipher();
        }
        else if(option == 3){
            OTP();
        }
        else if(option = 4){
            break;
        }
    }
    return 0;
}