#include <iomanip>
#include <iostream>
#include "string"
#include "HashMap.hpp"
#include <sstream>
#include "Input.hpp"



int main()
{
    HashMap h1;
    Input h2;
    std::string login;
    std::string pass;
    std::string input;
    std::string wholeLine;
    bool debug = false;
    
    do
    {
        login = "";
        pass = "";
        input = "";
        wholeLine="";
        
        getline(std::cin, wholeLine);
        std::stringstream in(wholeLine);
        in >> input;
        in >> login;
        in >> pass;
        
        if (input == "CREATE" && pass != "" && login != "")
        {
            h2.create(h1, login, pass);
        }
        else if(input == "LOGIN" && login == "COUNT" && debug==false)
        {
            std::cout <<"INVALID" << std::endl;
        }
        else if (input == "LOGIN" && login == "COUNT" && debug==true)
        {
            std::cout << h2.loginCount() << std::endl;
        }
        else if (input == "LOGIN")
        {
            h2.login(h1, login, pass);
        }
        else if (input == "CLEAR")
        {
            h2.clear(h1);
        }
        else if (input == "QUIT")
        {
            std::cout << "GOODBYE"<< std::endl;
        }
        else if(input=="REMOVE")
        {
            h2.remove(h1, login);
        }
        else if (input == "BUCKET"&& login == "COUNT" && debug==true)
        {
            std::cout << h1.bucketCount() << std::endl;
            //      std::cout<<h1.size()<<std::endl;
        }
        else if (input == "LOAD"&&login == "FACTOR" && debug == true)
        {
            std::cout << std::setprecision(1)<< h1.loadFactor() << std::endl;
        }
        else if (input == "DEBUG"&& login == "ON")
        {
            if (debug==false)
            {
                debug = true;
                std::cout << "ON NOW" << std::endl;
            }
            else if (debug==true)
            {
                std::cout << "ON ALREADY" << std::endl;
            }
        }
        else if (input == "DEBUG"&& login == "OFF")
        {
            if (debug==true)
            {
                debug = false;
                std::cout << "OFF NOW" << std::endl;
            }
            else if (debug == false)
            {
                std::cout << "OFF ALREADY" << std::endl;
            }
            
        }
        else if (input == "MAX" && login == "BUCKET" && pass == "SIZE" && debug ==true)
        {
            std::cout << h1.maxBucketSize() << std::endl;
        }
        else
        {
            std::cout << "INVALID" << std::endl;
        }
    } while (input != "QUIT");
    
    
    
    return 0;
}

