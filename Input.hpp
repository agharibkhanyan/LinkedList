//
//  Input.hpp
//  Project3_45c
//
//  Created by artur on 11/23/18.
//  Copyright © 2018 Artur. All rights reserved.
//

#ifndef Input_hpp
#define Input_hpp

#include <stdio.h>
#include "HashMap.hpp"

class Input
{
    
public:
    Input();
    void create(HashMap &h,const std::string &user,const std::string &pass);
    void login(HashMap &h,const std::string &user,const std::string &pass);
    void remove(HashMap &h,const std::string &user);
    void clear(HashMap &h);
    int loginCount();
private:
    int logins;
};
#endif /* Input_hpp */


