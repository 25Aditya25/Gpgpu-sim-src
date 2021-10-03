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



bool isRepWorthy(int op){
    switch(op){
        case ABS_OP:return true;
        case ADD_OP:return true;
        case ADDP_OP:return true;
        case ADDC_OP:return false;
        case AND_OP:return true;
        case ANDN_OP:return true;
        case ATOM_OP:return false;
        case BAR_OP:return false;
        case BFE_OP:return false;
        case BFI_OP:return false;
        case BFIND_OP:return false;
        case BRA_OP:return false;
        case BRX_OP:return false;
        case BREV_OP:return false;
        case BRKPT_OP:return false;
        case CALL_OP:return false;
        case CALLP_OP:return false;
        case CLZ_OP:return false;
        case CNOT_OP:return false;
        case COS_OP:return false;//------------------
        case CVT_OP:return true;
        case CVTA_OP:return false;
        case DIV_OP:return true;
        case EX2_OP:return false;//--------
        case EXIT_OP:return false;
        case FMA_OP:return true;
        case ISSPACEP_OP:return false;
        case LD_OP:return false;
        case LDU_OP:return false;
        case LG2_OP:return false;//-------
        case MAD24_OP:return true;
        case MAD_OP:return true;
        case MADP_OP:return true;
        case MAX_OP:return true;
        case MEMBAR_OP:return false;
        case MIN_OP:return true;
        case MOV_OP:return false;
        case MUL24_OP:return true;
        case MUL_OP:return true;
        case NEG_OP:return true;
        case NANDN_OP:return true;
        case NORN_OP:return true;
        case NOT_OP:return true;
        case OR_OP:return true;
        case ORN_OP:return true;
        case PMEVENT_OP:return false;
        case POPC_OP:return true;
        case PREFETCH_OP:return false;
        case PREFETCHU_OP:return false;
        case PRMT_OP:return false;
        case RCP_OP:return false; //---------------
        case RED_OP:return false;
        case REM_OP:return true;
        case RET_OP:return false;
        case RETP_OP:return false;
        case RSQRT_OP:return false;//--------------
        case SAD_OP:return true;
        case SELP_OP:return true;
        case SETP_OP:return false;
        case SET_OP:return true;
        case SHL_OP:return true;
        case SHR_OP:return true;
        case SIN_OP:return false;//----------------
        case SLCT_OP:return true;
        case SQRT_OP:return false;//--------------
        case SSY_OP:return false;
        case ST_OP:return false;
        case SUB_OP:return true;
        case SUBC_OP:return false;
        case SULD_OP:return false;
        case SURED_OP:return false;
        case SUST_OP:return false;
        case SUQ_OP:return false;
        case TEX_OP:return false;
        case TRAP_OP:return false;
        case VABSDIFF_OP:return false;
        case VADD_OP:return false;
        case VMAD_OP:return false;
        case VMAX_OP:return false;
        case VMIN_OP:return false;
        case VSET_OP:return false;
        case VSHL_OP:return false;
        case VSHR_OP:return false;
        case VSUB_OP:return false;
        case VOTE_OP:return false;
        case XOR_OP:return true;
        case NOP_OP:return false;
        case BREAK_OP:return false;
        case BREAKADDR_OP:return false;    
        default: return false;
    }    
}  

bool isALUiType(unsigned i_type,int op){
    if(i_type>305 && i_type<310) return false;
    else if(i_type>297 && i_type<306){          //also put else if here
        switch(op){
            case ABS_OP:return true;
            case ADD_OP:return true;
            case ADDP_OP:return true;
            case ADDC_OP:return true;
            case AND_OP:return true;
            case ANDN_OP:return true;
            case ATOM_OP:return false;
            case BAR_OP:return false;
            case BFE_OP:return false;
            case BFI_OP:return false;
            case BFIND_OP:return false;
            case BRA_OP:return true;
            case BRX_OP:return true;
            case BREV_OP:return false;
            case BRKPT_OP:return false;
            case CALL_OP:return true;
            case CALLP_OP:return true;
            case CLZ_OP:return false;
            case CNOT_OP:return false;
            case COS_OP:return false;
            case CVT_OP:return true;
            case CVTA_OP:return true;
            case DIV_OP:return true;
            case EX2_OP:return false;
            case EXIT_OP:return true;
            case FMA_OP:return true;
            case ISSPACEP_OP:return false;
            case LD_OP:return false;
            case LDU_OP:return false;
            case LG2_OP:return false;
            case MAD24_OP:return true;
            case MAD_OP:return true;
            case MADP_OP:return true;
            case MAX_OP:return true;
            case MEMBAR_OP:return false;
            case MIN_OP:return true;
            case MOV_OP:return true;
            case MUL24_OP:return true;
            case MUL_OP:return true;
            case NEG_OP:return true;
            case NANDN_OP:return true;
            case NORN_OP:return true;
            case NOT_OP:return true;
            case OR_OP:return true;
            case ORN_OP:return true;
            case PMEVENT_OP:return false;
            case POPC_OP:return true;
            case PREFETCH_OP:return false;
            case PREFETCHU_OP:return false;
            case PRMT_OP:return false;
            case RCP_OP:return false;
            case RED_OP:return false;
            case REM_OP:return true;
            case RET_OP:return true;
            case RETP_OP:return true;
            case RSQRT_OP:return false;
            case SAD_OP:return true;
            case SELP_OP:return true;
            case SETP_OP:return true;
            case SET_OP:return true;
            case SHL_OP:return true;
            case SHR_OP:return true;
            case SIN_OP:return false;
            case SLCT_OP:return true;
            case SQRT_OP:return false;
            case SSY_OP:return true;
            case ST_OP:return false;
            case SUB_OP:return true;
            case SUBC_OP:return false;
            case SULD_OP:return false;
            case SURED_OP:return false;
            case SUST_OP:return false;
            case SUQ_OP:return false;
            case TEX_OP:return false;
            case TRAP_OP:return false;
            case VABSDIFF_OP:return false;
            case VADD_OP:return false;
            case VMAD_OP:return false;
            case VMAX_OP:return false;
            case VMIN_OP:return false;
            case VSET_OP:return false;
            case VSHL_OP:return false;
            case VSHR_OP:return false;
            case VSUB_OP:return false;
            case VOTE_OP:return false;
            case XOR_OP:return true;
            case NOP_OP:return true;
            case BREAK_OP:return false;
            case BREAKADDR_OP:return false;    
            default: return false;
        }
    }
    else return false;
}

bool isALUfType(unsigned i_type,int op){
    if(i_type>297 && i_type<306) return false;
    else if(i_type>305 && i_type<310){
        switch(op){
            case ABS_OP:return true;
            case ADD_OP:return true;
            case ADDP_OP:return true;
            case ADDC_OP:return true;
            case AND_OP:return true;
            case ANDN_OP:return true;
            case ATOM_OP:return false;
            case BAR_OP:return false;
            case BFE_OP:return false;
            case BFI_OP:return false;
            case BFIND_OP:return false;
            case BRA_OP:return true;
            case BRX_OP:return true;
            case BREV_OP:return false;
            case BRKPT_OP:return false;
            case CALL_OP:return true;
            case CALLP_OP:return true;
            case CLZ_OP:return false;
            case CNOT_OP:return false;
            case COS_OP:return false;
            case CVT_OP:return true;
            case CVTA_OP:return true;
            case DIV_OP:return true;
            case EX2_OP:return false;
            case EXIT_OP:return true;
            case FMA_OP:return true;
            case ISSPACEP_OP:return false;
            case LD_OP:return false;
            case LDU_OP:return false;
            case LG2_OP:return false;
            case MAD24_OP:return true;
            case MAD_OP:return true;
            case MADP_OP:return true;
            case MAX_OP:return true;
            case MEMBAR_OP:return false;
            case MIN_OP:return true;
            case MOV_OP:return true;
            case MUL24_OP:return true;
            case MUL_OP:return true;
            case NEG_OP:return true;
            case NANDN_OP:return true;
            case NORN_OP:return true;
            case NOT_OP:return true;
            case OR_OP:return true;
            case ORN_OP:return true;
            case PMEVENT_OP:return false;
            case POPC_OP:return true;
            case PREFETCH_OP:return false;
            case PREFETCHU_OP:return false;
            case PRMT_OP:return false;
            case RCP_OP:return false;
            case RED_OP:return false;
            case REM_OP:return true;
            case RET_OP:return true;
            case RETP_OP:return true;
            case RSQRT_OP:return false;
            case SAD_OP:return true;
            case SELP_OP:return true;
            case SETP_OP:return true;
            case SET_OP:return true;
            case SHL_OP:return true;
            case SHR_OP:return true;
            case SIN_OP:return false;
            case SLCT_OP:return true;
            case SQRT_OP:return false;
            case SSY_OP:return true;
            case ST_OP:return false;
            case SUB_OP:return true;
            case SUBC_OP:return false;
            case SULD_OP:return false;
            case SURED_OP:return false;
            case SUST_OP:return false;
            case SUQ_OP:return false;
            case TEX_OP:return false;
            case TRAP_OP:return false;
            case VABSDIFF_OP:return false;
            case VADD_OP:return false;
            case VMAD_OP:return false;
            case VMAX_OP:return false;
            case VMIN_OP:return false;
            case VSET_OP:return false;
            case VSHL_OP:return false;
            case VSHR_OP:return false;
            case VSUB_OP:return false;
            case VOTE_OP:return false;
            case XOR_OP:return true;
            case NOP_OP:return true;
            case BREAK_OP:return false;
            case BREAKADDR_OP:return false;    
            default: return false;
        }
    }
    else return false;
}     




bool isSFUType(unsigned i_type,int op){
    switch(op){
        case ABS_OP:return false;
        case ADD_OP:return false;
        case ADDP_OP:return false;
        case ADDC_OP:return false;
        case AND_OP:return false;
        case ANDN_OP:return false;
        case ATOM_OP:return false;
        case BAR_OP:return false;
        case BFE_OP:return false;
        case BFI_OP:return false;
        case BFIND_OP:return false;
        case BRA_OP:return false;
        case BRX_OP:return false;
        case BREV_OP:return false;
        case BRKPT_OP:return false;
        case CALL_OP:return false;
        case CALLP_OP:return false;
        case CLZ_OP:return false;
        case CNOT_OP:return false;
        case COS_OP:return true;
        case CVT_OP:return false;
        case CVTA_OP:return false;
        case DIV_OP:return false;
        case EX2_OP:return true;
        case EXIT_OP:return false;
        case FMA_OP:return false;
        case ISSPACEP_OP:return false;
        case LD_OP:return false;
        case LDU_OP:return false;
        case LG2_OP:return true;
        case MAD24_OP:return false;
        case MAD_OP:return false;
        case MADP_OP:return false;
        case MAX_OP:return false;
        case MEMBAR_OP:return false;
        case MIN_OP:return false;
        case MOV_OP:return false;
        case MUL24_OP:return false;
        case MUL_OP:return false;
        case NEG_OP:return false;
        case NANDN_OP:return false;
        case NORN_OP:return false;
        case NOT_OP:return false;
        case OR_OP:return false;
        case ORN_OP:return false;
        case PMEVENT_OP:return false;
        case POPC_OP:return false;
        case PREFETCH_OP:return false;
        case PREFETCHU_OP:return false;
        case PRMT_OP:return false;
        case RCP_OP:return true;
        case RED_OP:return false;
        case REM_OP:return false;
        case RET_OP:return false;
        case RETP_OP:return false;
        case RSQRT_OP:return true;
        case SAD_OP:return false;
        case SELP_OP:return false;
        case SETP_OP:return false;
        case SET_OP:return false;
        case SHL_OP:return false;
        case SHR_OP:return false;
        case SIN_OP:return true;
        case SLCT_OP:return false;
        case SQRT_OP:return true;
        case SSY_OP:return false;
        case ST_OP:return false;
        case SUB_OP:return false;
        case SUBC_OP:return false;
        case SULD_OP:return false;
        case SURED_OP:return false;
        case SUST_OP:return false;
        case SUQ_OP:return false;
        case TEX_OP:return false;
        case TRAP_OP:return false;
        case VABSDIFF_OP:return false;
        case VADD_OP:return false;
        case VMAD_OP:return false;
        case VMAX_OP:return false;
        case VMIN_OP:return false;
        case VSET_OP:return false;
        case VSHL_OP:return false;
        case VSHR_OP:return false;
        case VSUB_OP:return false;
        case VOTE_OP:return false;
        case XOR_OP:return false;
        case NOP_OP:return false;
        case BREAK_OP:return false;
        case BREAKADDR_OP:return false;    
        default: return false;
    }
}

bool isLastInst(int op){return (op==EXIT_OP);}