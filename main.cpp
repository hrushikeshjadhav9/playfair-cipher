//
//  main.cpp
//  PlayfairCipherMyImplementation
//
//  Created by Hrushikesh Jadhav on 26/03/20.
//  Copyright © 2020 Hrushikesh Jadhav. All rights reserved.
//

#include <iostream>
#include <utility>


class Playfair
{
    private:
        std::string plaintext, key;
        int keysquare[5][5];
        char iorj;
    public:
        Playfair(std::string plaintext, std::string key)
        {
            this->plaintext = plaintext;
            if(plaintext.length() % 2 != 0)
                this->plaintext += 'z';
            this->key = key;
            
            if(charPresent('i'))
                this->iorj = 'i';
            else if (charPresent('j'))
                this->iorj = 'j';
            else
                this->iorj = 'i';
        }
    
        void display()
        {
            std::cout << "\nUpdated plaintext: " << this->plaintext << std::endl;
        }
        bool charPresent(char c)
        {
            // checks if char c is present in key
            if(this->key.find(c) != -1)
                return true;
            return false;
        }
        void generateKeySquare()
        {
            for (int i = 0; i < 26; i ++)
            {
                if(this->charPresent(char(i + 97)) || i == 8)
                    continue;
                
                else if(i == 9)
                    this->key += iorj;
                
                else
                    this->key += char(i+97);
            }
            
            // Converting string to matrix
            for(int i = 0; i < 5; i ++)
            {
                for(int j = 0; j < 5; j ++)
                {
                    keysquare[i][j] = this->key[i*5 + j];
                }
            }
        }
    
        void displayKeyMatrix()
        {
            std::cout << "\nKey matrix :\n";
            for(int i = 0; i < 5; i ++)
            {
                for(int j = 0; j < 5; j ++)
                {
                    std::cout << char(keysquare[i][j]) << " ";
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
        }
    
        std::string encrypt()
        {
            // Encrypts plaintext using key matrix
            
            int index1, index2;
            std::pair <int, int> pair1, pair2;
            
            for(int i = 0; i < plaintext.length(); i += 2)
            {
                index1 = int(key.find(plaintext[i]));
                pair1.first = index1 / 5;
                pair1.second = index1 % 5;
                index2 = int(key.find(plaintext[i+1]));
                pair2.first = index2 / 5;
                pair2.second = index2 % 5;
                
                /*
                 Encryption cases:
                    1. Same column
                    2. Same row
                    3. Other
                 */
                
                if(pair1.second == pair2.second)
                {
                    // Case 1 : Same column
                    plaintext[i] = keysquare[(pair1.first + 1) % 5][pair1.second];
                    plaintext[i+1] = keysquare[(pair2.first + 1) % 5][pair2.second];
                }
                else if(pair1.first == pair2.first)
                {
                    // Case 2 : Same row
                    plaintext[i] = keysquare[pair1.first][(pair1.second + 1) % 5];
                    plaintext[i+1] = keysquare[pair2.first][(pair2.second + 1) % 5];
                }
                else
                {
                    // Case 3 : Other
                    plaintext[i] = keysquare[pair1.first][pair2.second];
                    plaintext[i+1] = keysquare[pair2.first][pair1.second];
                }
            }
            return plaintext;
        }
    
        std::string decrypt()
        {
            // Decrypts cipher text using key matrix
            
            int index1, index2;
            std::pair <int, int> pair1, pair2;
            
            for(int i = 0; i < plaintext.length(); i += 2)
            {
                index1 = int(key.find(plaintext[i]));
                pair1.first = index1 / 5;
                pair1.second = index1 % 5;
                index2 = int(key.find(plaintext[i+1]));
                pair2.first = index2 / 5;
                pair2.second = index2 % 5;
                
                /*
                 Encryption cases:
                 1. Same column
                 2. Same row
                 3. Other
                 */
                
                if(pair1.second == pair2.second)
                {
                    // Case 1 : Same column
                    plaintext[i] = keysquare[(pair1.first + 4) % 5][pair1.second];
                    plaintext[i+1] = keysquare[(pair2.first + 4) % 5][pair2.second];
                }
                else if(pair1.first == pair2.first)
                {
                    // Case 2 : Same row
                    plaintext[i] = keysquare[pair1.first][(pair1.second + 4) % 5];
                    plaintext[i+1] = keysquare[pair2.first][(pair2.second + 4) % 5];
                }
                else
                {
                    // Case 3 : Other
                    plaintext[i] = keysquare[pair1.first][pair2.second];
                    plaintext[i+1] = keysquare[pair2.first][pair1.second];
                }
            }
            return plaintext;
        }
};

int main(int argc, const char * argv[]) {
    // insert code here...
    
    std::string plaintext, key;
    std::cout << "Enter plaintext: ";
    std::cin >> plaintext;
    std::cout << "Enter key: ";
    std::cin >> key;
    
    Playfair p(plaintext,key);
    p.display();
    p.generateKeySquare();
    p.displayKeyMatrix();
    std::cout << "After encryption:\n cipher text = " + p.encrypt() << "\n\n";
    std::cout << "After decryption:\n plaintext text = " + p.decrypt() << "\n\n";
    return 0;
}
