//
//  Input.cpp
//  Project3_45c
//
//  Created by artur on 11/23/18.
//  Copyright © 2018 Artur. All rights reserved.
//

#include "Input.hpp"

Input::Input()
{
    logins=0;
}


void Input::create(HashMap &h, const std::string &user, const std::string &pass)
{
    if (h.contains(user) == false)
    {
        h.add(user, pass);
        std::cout << "CREATED " << std::endl;
    }
    else
    {
        std::cout << "EXISTS " << std::endl;
    }
}

void Input::login(HashMap &h, const std::string &user, const std::string &pass)
{
    if (h.contains(user) && h.value(user) == pass)
    {
        std::cout << "SUCCEEDED" << std::endl;
        logins++;
    }
    else if(user=="")
    {
        std::cout<< "INVALID" << std::endl;
    }
    else if(h.getDeleted(user))
    {
        std::cout<<"INVALID"<<std::endl;
    }
    else
    {
        std::cout << "FAILED" << std::endl;
    }
}

void Input::remove(HashMap &h, const std::string &user)
{
    if(h.contains(user))
    {
        h.remove(user);
        logins--;
        std::cout<<"REMOVED"<<std::endl;
    }
    else
        std::cout<<"NONEXISTENT"<<std::endl;
}

void Input::clear(HashMap &h)
{
    //    h.~HashMap();
    h.clear();
    std::cout << "CLEARED" << std::endl;
    logins=0;
}
int Input::loginCount()
{
    return logins;
}


