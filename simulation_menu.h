const std::string menu_header=" \n"
" S I M U L A T I O N   M A N A G E R \n"
" =================================== \n\n";

const std::string menu_selections="\n"
"1 : Interact with a VM \n"
"2 : Boot more VM's \n"
"3 : Sample random response times\n" 
"q : Quit \n"
"\n";

void print_menu(int vmCount){
  std::cout << menu_header;
  std::cout << vmCount << " VM's currently booted" << std::endl;
  std::cout << menu_selections;
  std::cout << "#> ";
}
