/*
   IDA Pro Processor Module for CR16C Instruction Set
   
   Copyright (C) 2011 
   Andreas Schuler <andreas@schulerdev.de>

   Based on Simple Python Byte Code Module (Chris Eagle <cseagle@gmail.com>)
   
   This program is free software; you can redistribute it and/or modify it
   under the terms of the GNU General Public License version 2 as published 
   by the Free Software Foundation.
   
   This program is distributed in the hope that it will be useful, but WITHOUT
   ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or 
   FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for 
   more details.
   
   You should have received a copy of the GNU General Public License along with 
   this program; if not, write to the Free Software Foundation, Inc., 59 Temple 
   Place, Suite 330, Boston, MA 02111-1307 USA
*/

#ifndef __INST_H
#define __INST_H

#include <ida.hpp>
#include <idp.hpp>

extern instruc_t Instructions[];

//
enum inst_names 
{
CR16C_null = 0,
CR16C_addb,
CR16C_addw,
CR16C_addd,
CR16C_addub,
CR16C_adduw,
CR16C_addcb,
CR16C_addcw,
CR16C_andb,
CR16C_andw,
CR16C_andd,
CR16C_ashub,
CR16C_ashuw,
CR16C_ashud,
CR16C_bal,
CR16C_beq,
CR16C_bne,
CR16C_bcs,
CR16C_bcc,
CR16C_bhi,
CR16C_bls,
CR16C_bgt,
CR16C_ble,
CR16C_bfs,
CR16C_bfc,
CR16C_blo,
CR16C_bhs,
CR16C_blt,
CR16C_bge,
CR16C_beq0b,
CR16C_beq0w,
CR16C_bne0b,
CR16C_bne0w,
CR16C_br,
CR16C_cbitb,
CR16C_cbitw,
CR16C_cinv,
CR16C_cmpb,
CR16C_cmpw,
CR16C_cmpd,
CR16C_di,
CR16C_ei,
CR16C_eiwait,
CR16C_excp,
CR16C_jeq,
CR16C_jne,
CR16C_jcs,
CR16C_jcc,
CR16C_jhi,
CR16C_jls,
CR16C_jgt,
CR16C_jle,
CR16C_jfs,
CR16C_jfc,
CR16C_jlo,
CR16C_jhs,
CR16C_jlt,
CR16C_jge,
CR16C_jal,
CR16C_jump,
CR16C_jusr,
CR16C_loadb,
CR16C_loadw,
CR16C_loadd,
CR16C_loadm,
CR16C_loadmp,
CR16C_lpr,
CR16C_lprd,
CR16C_lshb,
CR16C_lshw,
CR16C_lshd,
CR16C_macsw,
CR16C_macuw,
CR16C_macqw,
CR16C_movb,
CR16C_movw,
CR16C_movd,
CR16C_movxb,
CR16C_movxw,
CR16C_movzb,
CR16C_movzw,
CR16C_mulb,
CR16C_mulw,
CR16C_mulsb,
CR16C_mulsw,
CR16C_muluw,
CR16C_nop,
CR16C_orb,
CR16C_orw,
CR16C_ord,
CR16C_pop,
CR16C_popret,
CR16C_push,
CR16C_retx,
CR16C_sbitb,
CR16C_sbitw,
CR16C_seq,
CR16C_sne,
CR16C_scs,
CR16C_scc,
CR16C_shi,
CR16C_sls,
CR16C_sgt,
CR16C_sle,
CR16C_sfs,
CR16C_sfc,
CR16C_slo,
CR16C_shs,
CR16C_slt,
CR16C_sge,
CR16C_spr,
CR16C_sprd,
CR16C_storb,
CR16C_storw,
CR16C_stord,
CR16C_storm,
CR16C_stormp,
CR16C_subb,
CR16C_subw,
CR16C_subd,
CR16C_subcb,
CR16C_subcw,
CR16C_tbit,
CR16C_tbitb,
CR16C_tbitw,
CR16C_wait,
CR16C_xorb,
CR16C_xorw,
CR16C_xord,
CR16C_uknnop,
CR16C_ukntrap,
CR16C_lastinstruction
};

enum par_types
{
PAR_none,
PAR_reg,
PAR_rp,
PAR_rp2,
PAR_rrp,
PAR_rs,
PAR_disp,
PAR_disp2,
PAR_disp2o,
PAR_disp2p,
PAR_dispn,
PAR_ind_rp,
PAR_ind_reg,
PAR_ind_prp,
PAR_ind_rrp,
PAR_abs,
PAR_imm,
PAR_immn,
PAR_pr,
PAR_prd,
PAR_vect
};


#endif

