/*
Every thing in this header file is added by Aditya
*/
#ifndef profile_H_INCLUDED
#define profile_H_INCLUDED

//#include "cuda-sim/ptx_sim.h" //absolutely needed
#include <deque>
//using namespace std;
/*Added by Aditya*/
#include "cuda-sim/ptx_reg.h"
/*End of Added by Aditya*/



#define maxoowqSize 512

class opc_opr_thread{
public:
    opc_opr_thread(){
        opcode=0;
    }

    
    void addValues(ptx_reg_t s1,ptx_reg_t s2,ptx_reg_t s3,int op);
    /*{
        src1=s1;
        src2=s2;
        src3=s3;
        //dest=d;
        opcode=op;
    }*/

    bool isooEqual(opc_opr_thread o);
    /*{
        return ((opcode==o.opcode) && src1.isEqual(o.src1) && src2.isEqual(o.src2) && src3.isEqual(o.src3));
    }*/

 private:    
    ptx_reg_t src1,src2,src3;//,dest;
    int opcode;   
};

class opc_opr_warp{

public:
    void add_opc_opr(ptx_reg_t s1, ptx_reg_t s2, ptx_reg_t s3, ptx_reg_t d, int op, int tid);
    /*{
        arr[tid].addValues(s1,s2,s3,op);
    }*/

    opc_opr_thread* get_opc_opr_warp(){ //need to think again
        return arr;
    } 

    bool isoowEqual(opc_opr_warp o);
    /*{
        for(int i=0;i<32;i++){
            if(!(arr[i].isooEqual(o.arr[i]))) return false;
        }
        return true;
    }*/

    opc_opr_thread arr[32]; 

};

class opc_opr_warp_queue{
private:
    std::deque<opc_opr_warp> oowq;
    int i,found;

public:
    bool inqueue(opc_opr_warp o);
    /*{
        if(oowq.size()==0) return false;
        else{
            found=0;
            for(i=0;i<oowq.size();i++){
                if(o.isoowEqual(oowq[i]))found=1;
            }
            if(found) return true;
            else return false;
        }
    }*/

    void insert(opc_opr_warp o);
    /*{
        if(oowq.size()<maxoowqSize){
            oowq.push_back(o);
        }
        else{
            oowq.pop_front();
            oowq.push_back(o);
        }
    }*/


};


#endif