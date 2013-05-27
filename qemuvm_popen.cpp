#include "qemuvm_popen.h"
#include "QDataStream"

qemuVm_popen::qemuVm_popen(QObject *parent):
    microMachine(),boot_char('!'),proc(0),
    //command("qemu-system-i386 -hda ../microMachines_experimental_clean/microMachine.hda --nographic")
    command("./qemu_dummy")
{}

qemuVm_popen::~qemuVm_popen(){
    halt();
}

void qemuVm_popen::boot(){
    proc=popen(command,"r+");
}


void qemuVm_popen::halt(){
    pclose(proc);
}

QString qemuVm_popen::readAll(){
    return QString("Not implemented");
}

void qemuVm_popen::write(const char *s){
    fputs(s,proc);
}

response qemuVm_popen::processRequest(const char* req){
    return response("Not implemented");
}

response qemuVm_popen::processRequest_timed(const char* req,QTime& t){
    return response("Not implemented");
}

void qemuVm_popen::firstByteRecieved(){

}
