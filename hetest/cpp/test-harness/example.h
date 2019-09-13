#include <memory>

class foo {
public:
    foo(){}

    void bar(){ /* Does something */ }
    int num;
};

int main(){
    std::shared_ptr<foo> foo_ptr = std::make_shared<foo>();
    foo_ptr->bar(); //Works without issue
    foo_ptr->bar(); //Access violation: foo_ptr is now equal to the value stored in 'num'

    return 0;
}

