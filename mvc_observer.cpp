// main.cpp
#include < iostream>

#include "observer.hpp"

class model : public subject< model>
{
public:
 model()
 {
  std::cout << "model constructed\n";
 }

 void modify_model()
 {
  this-> notify_all();
 }
};

class view : public observer< view, model>, public subject< view>
{
public:
 void do_observe(model& m)
 {
  std::cout << "view observed the model" < < std::endl;
 }
};

class controller : public observer< controller, model>, public observer< controller, view>
{
public:
 void do_observe(model& m)
 {
  std::cout << "controller observed the model" << std::endl;
 }

 void do_observe(view& v)
 {
  std::cout << "controller observed the view" << std::endl;
 }

};

int main()
{
 model m;
 controller c;
 view v;

 m.add_observer(v);
 m.add_observer(c);

 v.add_observer(c);

 // when the model is modified all its observers will be notified
 m.modify_model();

 return 0;
}
