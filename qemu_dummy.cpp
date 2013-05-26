#include <iostream>

using namespace std;

void work(){
  for(int i=0;i<200000000;i++){
    if(false){
      cout << "No way: " << i << endl;
    }
  }
  return;
}

int main(){
  
  sleep(1);
  cout << "!";

  char c;
  while(true){

    cin >> c;
    work();
    cout <<++c;
  }

}


