/*
Every thing in this header file is added by Aditya
*/
#include "profile.h"

void opc_opr_thread::addValues(ptx_reg_t s1,ptx_reg_t s2,ptx_reg_t s3,int op){
        src1=s1;
        src2=s2;
        src3=s3;
        //dest=d;
        opcode=op;
    }


bool opc_opr_thread::isooEqual(opc_opr_thread o){
	return ((opcode==o.opcode) && src1.isEqual(o.src1) && src2.isEqual(o.src2) && src3.isEqual(o.src3) /*&& dest.isEqual(o.dest)*/);
}

void opc_opr_warp::add_opc_opr(ptx_reg_t s1, ptx_reg_t s2, ptx_reg_t s3, ptx_reg_t d, int op, int tid){
        arr[tid].addValues(s1,s2,s3,op);
    }

bool opc_opr_warp::isoowEqual(opc_opr_warp o){
        for(int i=0;i<32;i++){
            if(!(arr[i].isooEqual(o.arr[i]))) return false;
        }
        return true;
    }    


bool opc_opr_warp_queue::inqueue(opc_opr_warp o){
    if(oowq.size()==0) return false;
    else{
        found=0;
        for(i=0;i<oowq.size();i++){
            if(o.isoowEqual(oowq[i]))found=1;
        }
        if(found) return true;
        else return false;
    }
}

void opc_opr_warp_queue::insert(opc_opr_warp o){
        if(oowq.size()<maxoowqSize){
            oowq.push_back(o);
        }
        else{
            oowq.pop_front();
            oowq.push_back(o);
        }
    }