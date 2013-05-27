#include <iostream>

using namespace std;

int main(){
  char c=0;
  
  FILE* proc=popen("./qemu_dummy","r+");
  
  if(proc==NULL) perror("Error opening file");
  else{
    c=fgetc(proc);
  }

  if(!c){
    cout << "No boot signal.." << endl;
    pclose(proc);
    return 777;
  }
  
  char request='a';
  
  cout << "Boot signal: '" << c << "'" << endl;
  cout << "Writing " << request << " to VM: " << endl;
  
  putc(request,proc);
  c=fgetc(proc);
  cout << "Response: " << c << endl;

  fflush(proc);
  
  while(fgetc(proc)!=EOF){}

  pclose(proc);

  cout << "Process closed" << endl;
}
