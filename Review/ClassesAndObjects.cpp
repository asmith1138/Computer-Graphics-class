#include "person.h"
#include "Tweeter.h"
#include <iostream>
#include "status.h"
using std::cout;
using std::endl;

//only include stuff once
#pragma once
//remove all namespacey stuff
//using namespace std;
int main(){
    Person p1("Kate","Beckensale",23542);
    {
        Tweeter p2("Natalie","Portman",2342,"@natport");
    }
    std::string name = p1.getName();
    cout << "The end" << endl;
    //int i = p1.arbitrarynumber;

    Status s = Pending;
    s= Approved;

    FileError fe = FileError::notfound;
    fe = FileError::ok;
    NetworkError ne = NetworkError::disconnected;
    ne=NetworkError::ok;
}