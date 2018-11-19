#include "basicuserimpl.h"

const QString BasicUser::BASIC_USER_NAME = "User";

BasicUserImpl::BasicUserImpl():user(nullptr){

}


QString BasicUserImpl::getRoleName(){
    return BasicUser::BASIC_USER_NAME;
}

User* BasicUserImpl::getUser(){
    return user;
}

void BasicUserImpl::setUser(User* user){
    this->user=user;
}

QString BasicUserImpl::getUsername(){
    if(user == nullptr){
        // Throw error
        return "";
    }
    return user->getUsername();
}

QString BasicUserImpl::getPassword(){
    if(user == nullptr){
        // Throw error
        return "";
    }
    return user->getPassword();
}
