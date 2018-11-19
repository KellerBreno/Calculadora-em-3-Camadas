#include "adminuserimpl.h"

const QString AdminUser::ADMIN_USER_NAME = "Admin";

AdminUserImpl::AdminUserImpl():user(nullptr){

}

QString AdminUserImpl::getUsername(){
    if(user == nullptr){
        // Throw error
        return "";
    }
    return user->getUsername();
}

QString AdminUserImpl::getRoleName(){
    return AdminUser::ADMIN_USER_NAME;
}

User* AdminUserImpl::getUser(){
    return user;
}

void AdminUserImpl::setUser(User* user){
    this->user = user;
}
