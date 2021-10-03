/*
The code in the profile.h and profile.cc files was written by:
Aditya Wani 
GVN Dinesh Kumar
*/
#ifndef profile_H_INCLUDED
#define profile_H_INCLUDED

//#include "cuda-sim/ptx_sim.h" //absolutely needed
#include <deque>
//using namespace std;
/*Added by Aditya*/
#include "cuda-sim/opcodes.h"
#include "cuda-sim/ptx_reg.h"
/*End of Added by Aditya*/

bool isRepWorthy(int op);
bool isALUiType(unsigned i_type,int op);
bool isALUfType(unsigned i_type,int op);
bool isSFUType(unsigned i_type,int op);

bool isLastInst(int op);

#define maxoowqSize 128

class opc_opr_thread{
public:
    opc_opr_thread(){
        opcode=0;
    }

    void addValues(ptx_reg_t s1,ptx_reg_t s2,ptx_reg_t s3,int op);
    bool isooEqual(opc_opr_thread o);
 

 private:    
    ptx_reg_t src1,src2,src3;//,dest;
    int opcode;   
};

class opc_opr_warp{

public:
    void add_opc_opr(ptx_reg_t s1, ptx_reg_t s2, ptx_reg_t s3, ptx_reg_t d, int op, int tid);
    opc_opr_thread* get_opc_opr_warp(){ //need to think again
        return arr;
    } 

    bool isoowEqual(opc_opr_warp o);
    opc_opr_thread arr[32]; 

};

class opc_opr_warp_queue{
private:
    std::deque<opc_opr_warp> oowq;
    int i,found;

public:
    bool inqueue(opc_opr_warp o);
    void insert(opc_opr_warp o);

};


#endif