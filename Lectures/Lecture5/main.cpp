#include <iostream>
#include <zconf.h>

using namespace std;
int main() {
    int i;
    for(i= 0; i< 3; i++) {
        cout<<"FORK: "<<fork()<<" ";
        cout<<i<<"\n";
    }
}