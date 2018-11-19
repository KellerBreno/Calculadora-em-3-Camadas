#include "userimpl.h"

UserImpl::UserImpl(){

}

QString UserImpl::getUsername(){
    return username;
}

void UserImpl::setUsername(QString username){
    this->username=username;
}

QString UserImpl::getPassword(){
    return password;
}

void UserImpl::setPassword(QString password){
    this->password = password;
}

void UserImpl::addRole(Role *role){
    for(auto &r:roles){
        if(r->getRoleName()==role->getRoleName()){
            return;
        }
    }
    role->setUser(this);
    roles.push_back(role);
}

Role* UserImpl::asRole(QString name){
    for(auto &role:roles){
        if(role->getRoleName()==name){
            return role;
        }
    }
    return nullptr;
}

