/*
Every thing in this header file is added by Aditya
*/

#include "ptx_sim.h"

class opc_opr_thread{
public:
    opc_opr_thread(){
        opcode=0;
    }

    
    void addValues(ptx_reg_t s1,ptx_reg_t s2,ptx_reg_t s3,ptx_reg_t d,int op){
        src1=s1;
        src2=s2;
        src3=s3;
        dest=d;
        opcode=op;
    }

    bool isooEqual(opc_opr_thread o){
        return ((opcode==o.opcode) && src1.isEqual(o.src1) && src2.isEqual(o.src2) && src3.isEqual(o.src3) && dest.isEqual(o.dest));
    }

 private:    
    ptx_reg_t src1,src2,src3,dest;
    int opcode;   
};

class opc_opr_warp{

public:
    void add_opc_opr(ptx_reg_t s1, ptx_reg_t s2, ptx_reg_t s3, ptx_reg_t d, int op, int tid){
        arr[tid].addValues(s1,s2,s3,d,op);
    }

    opc_opr_thread* get_opc_opr_warp(){ //need to think again
        return arr;
    } 

    bool isoowEqual(opc_opr_warp o){
        for(int i=0;i<32;i++){
            if(!(arr[i].isooEqual(o.arr[i]))) return false;
        }
        return true;
    }

private:
    opc_opr_thread arr[32]; 

};