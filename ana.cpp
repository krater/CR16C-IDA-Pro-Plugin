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

#include "cr16c.hpp"


t_subop20_tbl subop20_10000_tbl[16]=
{
	{CR16C_br,		{PAR_disp2,		PAR_imm,	PAR_none},	ooType,		24,	2},
	{CR16C_uknnop,	{PAR_none,		PAR_none,	PAR_none},	ooType0,	3,	3},
	{CR16C_bal,		{PAR_disp2,		PAR_rp,		PAR_none},	ooType,		24,	3},
	{CR16C_uknnop,	{PAR_none,		PAR_none,	PAR_none},	ooType0,	3,	3},
	{CR16C_cbitb,	{PAR_ind_reg,	PAR_imm,	PAR_disp},	ooType1,	2,	3},	
	{CR16C_cbitb,	{PAR_ind_rp,	PAR_imm,	PAR_disp},	ooType1,	2,	3},	
	{CR16C_cbitb,	{PAR_ind_rrp,	PAR_imm,	PAR_disp},	ooType7,	2,	3},	
	{CR16C_cbitb,	{PAR_abs,		PAR_imm,	PAR_none},	ooType4,	3,	3},	
	{CR16C_sbitb,	{PAR_ind_reg,	PAR_imm,	PAR_disp},	ooType1,	2,	3},	
	{CR16C_sbitb,	{PAR_ind_rp,	PAR_imm,	PAR_disp},	ooType1,	2,	3},
	{CR16C_sbitb,	{PAR_ind_rrp,	PAR_imm,	PAR_disp},	ooType7,	2,	3},	
	{CR16C_sbitb,	{PAR_abs,		PAR_imm,	PAR_none},	ooType4,	3,	3},	
	{CR16C_tbitb,	{PAR_ind_reg,	PAR_imm,	PAR_disp},	ooType1,	2,	3},	
	{CR16C_tbitb,	{PAR_ind_rp,	PAR_imm,	PAR_disp},	ooType1,	2,	3},	
	{CR16C_tbitb,	{PAR_ind_rrp,	PAR_imm,	PAR_disp},	ooType7,	2,	3},	
	{CR16C_tbitb,	{PAR_abs,		PAR_imm,	PAR_none},	ooType4,	3,	3}
};

t_subop20_tbl subop20_10001_tbl[16]=
{
	{CR16C_uknnop,	{PAR_none,		PAR_none,	PAR_none},	ooType0,	3,	3},
	{CR16C_uknnop,	{PAR_none,		PAR_none,	PAR_none},	ooType0,	3,	3},
	{CR16C_uknnop,	{PAR_none,		PAR_none,	PAR_none},	ooType0,	3,	3},
	{CR16C_uknnop,	{PAR_none,		PAR_none,	PAR_none},	ooType0,	3,	3},
	{CR16C_cbitw,	{PAR_ind_reg,	PAR_imm,	PAR_disp},	ooType1,	2,	3},	
	{CR16C_cbitw,	{PAR_ind_rp,	PAR_imm,	PAR_disp},	ooType1,	2,	3},
	{CR16C_cbitw,	{PAR_ind_rrp,	PAR_imm,	PAR_disp},	ooType7,	2,	3},
	{CR16C_cbitw,	{PAR_abs,		PAR_imm,	PAR_none},	ooType4,	3,	3},
	{CR16C_sbitw,	{PAR_ind_reg,	PAR_imm,	PAR_disp},	ooType1,	2,	3},	
	{CR16C_sbitw,	{PAR_ind_rp,	PAR_imm,	PAR_disp},	ooType1,	2,	3},
	{CR16C_sbitw,	{PAR_ind_rrp,	PAR_imm,	PAR_disp},	ooType7,	2,	3},
	{CR16C_sbitw,	{PAR_abs,		PAR_imm,	PAR_none},	ooType4,	3,	3},
	{CR16C_tbitw,	{PAR_ind_reg,	PAR_imm,	PAR_disp},	ooType1,	2,	3},	
	{CR16C_tbitw,	{PAR_ind_rp,	PAR_imm,	PAR_disp},	ooType1,	2,	3},
	{CR16C_tbitw,	{PAR_ind_rrp,	PAR_imm,	PAR_disp},	ooType7,	2,	3},
	{CR16C_tbitw,	{PAR_abs,		PAR_imm,	PAR_none},	ooType4,	3,	3}
};


t_subop20_tbl subop20_10010_tbl[16]=
{
	{CR16C_storb,	{PAR_ind_reg,	PAR_imm,	PAR_disp},	ooType1,	2,	3},
	{CR16C_storb,	{PAR_ind_rp,	PAR_imm,	PAR_disp},	ooType1,	2,	3},
	{CR16C_storb,	{PAR_ind_rrp,	PAR_imm,	PAR_disp},	ooType7,	2,	3},
	{CR16C_storb,	{PAR_abs,		PAR_imm,	PAR_none},	ooType4,	3,	3},
	{CR16C_loadb,	{PAR_ind_reg,	PAR_reg,	PAR_disp},	ooType3,	2,	3},
	{CR16C_loadb,	{PAR_ind_rp,	PAR_reg,	PAR_disp},	ooType3,	2,	3},
	{CR16C_loadb,	{PAR_ind_rrp,	PAR_reg,	PAR_disp},	ooType8,	2,	3},
	{CR16C_loadb,	{PAR_abs,		PAR_reg,	PAR_none},	ooType5,	3,	3},
	{CR16C_loadd,	{PAR_ind_reg,	PAR_ind_rp,	PAR_disp},	ooType3,	2,	3},
	{CR16C_loadd,	{PAR_ind_rp,	PAR_ind_rp,	PAR_disp},	ooType3,	2,	3},
	{CR16C_loadd,	{PAR_ind_rrp,	PAR_ind_rp,	PAR_disp},	ooType8,	2,	3},
	{CR16C_loadd,	{PAR_abs,		PAR_ind_rp,	PAR_none},	ooType5,	3,	3},
	{CR16C_loadw,	{PAR_ind_reg,	PAR_reg,	PAR_disp},	ooType3,	2,	3},
	{CR16C_loadw,	{PAR_ind_rp,	PAR_reg,	PAR_disp},	ooType3,	2,	3},
	{CR16C_loadw,	{PAR_ind_rrp,	PAR_reg,	PAR_disp},	ooType8,	2,	3},
	{CR16C_loadw,	{PAR_abs,		PAR_reg,	PAR_none},	ooType5,	3,	3}
};


t_subop20_tbl subop20_10011_tbl[16]=
{
	{CR16C_storw,	{PAR_ind_reg,	PAR_imm,	PAR_disp},	ooType1,	2,	3},
	{CR16C_storw,	{PAR_ind_rp,	PAR_imm,	PAR_disp},	ooType1,	2,	3},
	{CR16C_storw,	{PAR_ind_rrp,	PAR_imm,	PAR_disp},	ooType7,	2,	3},
	{CR16C_storw,	{PAR_abs,		PAR_imm,	PAR_none},	ooType4,	3,	3},
	{CR16C_storb,	{PAR_ind_reg,	PAR_reg,	PAR_disp},	ooType2,	2,	3},
	{CR16C_storb,	{PAR_ind_rp,	PAR_reg,	PAR_disp},	ooType2,	2,	3},
	{CR16C_storb,	{PAR_ind_rrp,	PAR_reg,	PAR_disp},	ooType9,	2,	3},
	{CR16C_storb,	{PAR_abs,		PAR_reg,	PAR_none},	ooType6,	3,	3},
	{CR16C_stord,	{PAR_ind_reg,	PAR_ind_rp,	PAR_disp},	ooType2,	2,	3},
	{CR16C_stord,	{PAR_ind_rp,	PAR_ind_rp,	PAR_disp},	ooType2,	2,	3},
	{CR16C_stord,	{PAR_ind_rrp,	PAR_ind_rp,	PAR_disp},	ooType9,	2,	3},
	{CR16C_stord,	{PAR_abs,		PAR_ind_rp,	PAR_none},	ooType6,	3,	3},
	{CR16C_storw,	{PAR_ind_reg,	PAR_reg,	PAR_disp},	ooType2,	2,	3},
	{CR16C_storw,	{PAR_ind_rp,	PAR_reg,	PAR_disp},	ooType2,	2,	3},
	{CR16C_storw,	{PAR_ind_rrp,	PAR_reg,	PAR_disp},	ooType9,	2,	3},
	{CR16C_storw,	{PAR_abs,		PAR_reg,	PAR_none},	ooType6,	3,	3}
};

t_subop20_tbl subop20_10100_tbl[16]=
{
	{CR16C_lpr,		{PAR_reg,		PAR_pr,		PAR_none},	ooType5,	1,	2},
	{CR16C_lprd,	{PAR_ind_rp,	PAR_prd,	PAR_none},	ooType5,	1,	2},
	{CR16C_spr,		{PAR_reg,		PAR_pr,		PAR_none},	ooType6,	1,	2},
	{CR16C_sprd,	{PAR_ind_rp,	PAR_prd,	PAR_none},	ooType6,	1,	2},
	{CR16C_uknnop,	{PAR_none,		PAR_none,	PAR_none},	ooType0,	1,	2},
	{CR16C_uknnop,	{PAR_none,		PAR_none,	PAR_none},	ooType0,	1,	2},
	{CR16C_uknnop,	{PAR_none,		PAR_none,	PAR_none},	ooType0,	1,	2},
	{CR16C_uknnop,	{PAR_none,		PAR_none,	PAR_none},	ooType0,	1,	2},
	{CR16C_jal,		{PAR_ind_rp,	PAR_ind_rp,	PAR_none},	ooType5,	1,	2},
	{CR16C_ord,		{PAR_ind_rp,	PAR_ind_rp,	PAR_none},	ooType6,	1,	2},
	{CR16C_xord,	{PAR_ind_rp,	PAR_ind_rp,	PAR_none},	ooType6,	1,	2},
	{CR16C_andd,	{PAR_ind_rp,	PAR_ind_rp,	PAR_none},	ooType6,	1,	2},
	{CR16C_subd,	{PAR_ind_rp,	PAR_ind_rp,	PAR_none},	ooType6,	1,	2},
	{CR16C_macqw,	{PAR_reg,		PAR_reg,	PAR_ind_rp},ooType10,	1,	2},
	{CR16C_macuw,	{PAR_reg,		PAR_reg,	PAR_ind_rp},ooType10,	1,	2},
	{CR16C_macsw,	{PAR_reg,		PAR_reg,	PAR_ind_rp},ooType10,	1,	2}
};


t_subop20_tbl subop20_11000_tbl[16]=
{
	{CR16C_ukntrap,	{PAR_none,		PAR_none,	PAR_none},	ooType0,	0,	3},
	{CR16C_ukntrap,	{PAR_none,		PAR_none,	PAR_none},	ooType0,	0,	3},
	{CR16C_ukntrap,	{PAR_none,		PAR_none,	PAR_none},	ooType0,	0,	3},
	{CR16C_ukntrap,	{PAR_none,		PAR_none,	PAR_none},	ooType0,	0,	3},
	{CR16C_loadb,	{PAR_ind_reg,	PAR_reg,	PAR_dispn},	ooType3,	2,	3},
	{CR16C_loadb,	{PAR_ind_rp,	PAR_reg,	PAR_dispn},	ooType3,	2,	3},
	{CR16C_ukntrap,	{PAR_none,		PAR_none,	PAR_none},	ooType0,	0,	3},
	{CR16C_ukntrap,	{PAR_none,		PAR_none,	PAR_none},	ooType0,	0,	3},
	{CR16C_loadd,	{PAR_ind_reg,	PAR_ind_rp,	PAR_dispn},	ooType3,	2,	3},
	{CR16C_loadd,	{PAR_ind_rp,	PAR_ind_rp,	PAR_dispn},	ooType3,	2,	3},
	{CR16C_ukntrap,	{PAR_none,		PAR_none,	PAR_none},	ooType0,	0,	3},
	{CR16C_ukntrap,	{PAR_none,		PAR_none,	PAR_none},	ooType0,	0,	3},
	{CR16C_loadw,	{PAR_ind_reg,	PAR_reg,	PAR_dispn},	ooType3,	2,	3},
	{CR16C_loadw,	{PAR_ind_rp,	PAR_reg,	PAR_dispn},	ooType3,	2,	3},
	{CR16C_ukntrap,	{PAR_none,		PAR_none,	PAR_none},	ooType0,	0,	3},
	{CR16C_ukntrap,	{PAR_none,		PAR_none,	PAR_none},	ooType0,	0,	3}
};


t_subop20_tbl subop20_11001_tbl[16]=
{
	{CR16C_ukntrap,	{PAR_none,		PAR_none,	PAR_none},	ooType0,	0,	3},
	{CR16C_ukntrap,	{PAR_none,		PAR_none,	PAR_none},	ooType0,	0,	3},
	{CR16C_ukntrap,	{PAR_none,		PAR_none,	PAR_none},	ooType0,	0,	3},
	{CR16C_ukntrap,	{PAR_none,		PAR_none,	PAR_none},	ooType0,	0,	3},
	{CR16C_storb,	{PAR_ind_reg,	PAR_reg,	PAR_dispn},	ooType2,	2,	3},
	{CR16C_storb,	{PAR_ind_rp,	PAR_reg,	PAR_dispn},	ooType2,	2,	3},
	{CR16C_ukntrap,	{PAR_none,		PAR_none,	PAR_none},	ooType0,	0,	3},
	{CR16C_ukntrap,	{PAR_none,		PAR_none,	PAR_none},	ooType0,	0,	3},
	{CR16C_stord,	{PAR_ind_reg,	PAR_ind_rp,	PAR_dispn},	ooType2,	2,	3},
	{CR16C_stord,	{PAR_ind_rp,	PAR_ind_rp,	PAR_dispn},	ooType2,	2,	3},
	{CR16C_ukntrap,	{PAR_none,		PAR_none,	PAR_none},	ooType0,	0,	3},
	{CR16C_ukntrap,	{PAR_none,		PAR_none,	PAR_none},	ooType0,	0,	3},
	{CR16C_storw,	{PAR_ind_reg,	PAR_reg,	PAR_dispn},	ooType2,	2,	3},
	{CR16C_storw,	{PAR_ind_rp,	PAR_reg,	PAR_dispn},	ooType2,	2,	3},
	{CR16C_ukntrap,	{PAR_none,		PAR_none,	PAR_none},	ooType0,	0,	3},
	{CR16C_ukntrap,	{PAR_none,		PAR_none,	PAR_none},	ooType0,	0,	3}
};

struct t_op16_tbl op16_tbl[]=
{	
	{null,				CR16C_ukntrap,			{PAR_none,	PAR_none,	PAR_none},	ooType0,	0,	1},		//00000
	{null,				CR16C_ukntrap,			{PAR_none,	PAR_none,	PAR_none},	ooType0,	0,	1},		//00001
	{null,				CR16C_ukntrap,			{PAR_none,	PAR_none,	PAR_none},	ooType0,	0,	1},		//00010
	{null,				CR16C_retx,				{PAR_none,	PAR_none,	PAR_none},	ooType0,	4,	1},		//00011
	{null,				CR16C_di,				{PAR_none,	PAR_none,	PAR_none},	ooType0,	4,	1},		//00100
	{null,				CR16C_ei,				{PAR_none,	PAR_none,	PAR_none},	ooType0,	4,	1},		//00101
	{null,				CR16C_wait,				{PAR_none,	PAR_none,	PAR_none},	ooType0,	4,	1},		//00110
	{null,				CR16C_eiwait,			{PAR_none,	PAR_none,	PAR_none},	ooType0,	4,	1},		//00111
	{null,				CR16C_ukntrap,			{PAR_none,	PAR_none,	PAR_none},	ooType0,	0,	1},		//01000
	{null,				CR16C_ukntrap,			{PAR_none,	PAR_none,	PAR_none},	ooType0,	0,	1},		//01001
	{null,				CR16C_cinv,				{PAR_none,	PAR_none,	PAR_none},	ooType12,	4,	1},		//01010
	{null,				CR16C_cinv,				{PAR_none,	PAR_none,	PAR_none},	ooType12,	4,	1},		//01011
	{null,				CR16C_cinv,				{PAR_none,	PAR_none,	PAR_none},	ooType12,	4,	1},		//01100
	{null,				CR16C_cinv,				{PAR_none,	PAR_none,	PAR_none},	ooType12,	4,	1},		//01101
	{null,				CR16C_cinv,				{PAR_none,	PAR_none,	PAR_none},	ooType12,	4,	1},		//01110
	{null,				CR16C_cinv,				{PAR_none,	PAR_none,	PAR_none},	ooType12,	4,	1},		//01111
	{subop20_10000_tbl,	CR16C_null,				{PAR_none,	PAR_none,	PAR_none},	ooType0,	0,	0},		//10000
	{subop20_10001_tbl,	CR16C_null,				{PAR_none,	PAR_none,	PAR_none},	ooType0,	0,	0},		//10001
	{subop20_10010_tbl,	CR16C_null,				{PAR_none,	PAR_none,	PAR_none},	ooType0,	0,	0},		//10010
	{subop20_10011_tbl,	CR16C_null,				{PAR_none,	PAR_none,	PAR_none},	ooType0,	0,	0},		//10011
	{subop20_10100_tbl,	CR16C_null,				{PAR_none,	PAR_none,	PAR_none},	ooType0,	0,	0},		//10100
	{null,				CR16C_ukntrap,			{PAR_none,	PAR_none,	PAR_none},	ooType0,	0,	2},		//10101
	{null,				CR16C_ukntrap/*movmcr*/,{PAR_none,	PAR_none,	PAR_none},	ooType0,	1,	2},		//10110
	{null,				CR16C_ukntrap/*movmrc*/,{PAR_none,	PAR_none,	PAR_none},	ooType0,	1,	2},		//10111
	{subop20_11000_tbl,	CR16C_null,				{PAR_none,	PAR_none,	PAR_none},	ooType0,	0,	0},		//11000
	{subop20_11001_tbl,	CR16C_null,				{PAR_none,	PAR_none,	PAR_none},	ooType0,	0,	0},		//11001
	{null,				CR16C_ukntrap,			{PAR_none,	PAR_none,	PAR_none},	ooType0,	0,	3},		//11010
	{null,				CR16C_ukntrap,			{PAR_none,	PAR_none,	PAR_none},	ooType0,	0,	3},		//11011
	{null,				CR16C_ukntrap,			{PAR_none,	PAR_none,	PAR_none},	ooType0,	0,	3},		//11100
	{null,				CR16C_ukntrap,			{PAR_none,	PAR_none,	PAR_none},	ooType0,	0,	3},		//11101
	{null,				CR16C_ukntrap,			{PAR_none,	PAR_none,	PAR_none},	ooType0,	0,	3},		//11110
	{null,				CR16C_ukntrap,			{PAR_none,	PAR_none,	PAR_none},	ooType0,	0,	3}		//11111
};


//----------------------------------------------------------------------
int idaapi cr16c_ana(void) 
{
	ushort w1=ua_next_word();

	if((w1&0xffe0)==0x0000)			//00000000000xxxxx
		analyze_opcode16(w1);
	else if((w1&0xffe0)==0x00a0)	//00000000101xxxxx
		analyze_opcode13(w1);
	else if((w1&0xff00)==0x0000)	//00000000xxxxxxxx
		analyze_opcode12(w1);
/*	else if(((w1&0xff80)==0x6a80)||	//0110101010xxxxxx
			((w1&0xff80)==0x7280)||	//0111001010xxxxxx
			((w1&0xff80)==0x7a80)||	//0111101010xxxxxx
			((w1&0xff00)==0x8600)||	//10000110xxxxxxxx
			((w1&0xff00)==0xc600))	//11000110xxxxxxxx
		analyze_opcode10(w1);
/*	else if(((w1&0xff80)==0x6a00)||	//011010100xxxxxxx
			((w1&0xff80)==0x7200)||	//011100100xxxxxxx
			((w1&0xff80)==0x7a00)||	//011110100xxxxxxx
			((w1&0xff80)==0xff80)||	//111111111xxxxxxx
			((w1&0xff00)==0x0900)||	//00001001xxxxxxxx
			((w1&0xff00)==0x4000)||	//01000000xxxxxxxx
			((w1&0xff00)==0x6b00)||	//01101011xxxxxxxx
			((w1&0xff00)==0x7300)||	//01110011xxxxxxxx
			((w1&0xff00)==0x7b00))	//01111011xxxxxxxx
		analyze_opcode9(w1);
	else if(((w1&0xfe00)==0x6c00)||	//0110110xxxxxxxxx
			((w1&0xfe00)==0x7400)||	//0111010xxxxxxxxx
			((w1&0xfe00)==0x7c00)||	//0111110xxxxxxxxx
			((w1&0xfe00)==0x4a00)||	//0100101xxxxxxxxx
			((w1&0xfe00)==0x4c00)||	//0100110xxxxxxxxx
			((w1&0xfe00)==0x4e00)||	//0100111xxxxxxxxx
			((w1&0xfe00)==0x8400)||	//1000010xxxxxxxxx
			((w1&0xfe00)==0x8a00)||	//1000101xxxxxxxxx
			((w1&0xfe00)==0x8c00)||	//1000110xxxxxxxxx
			((w1&0xfe00)==0x8e00)||	//1000111xxxxxxxxx
			((w1&0xfe00)==0xc400)||	//1100010xxxxxxxxx
			((w1&0xfe00)==0xca00)||	//1100101xxxxxxxxx
			((w1&0xfe00)==0xcc00)||	//1100110xxxxxxxxx
			((w1&0xfe00)==0xce00))	//1100111xxxxxxxxx
		analyze_opcode7(w1);
	else if(((w1&0xf000)==0x0000)||	//00000000xxxxxxxx
			((w1&0xe000)==0x2000)||	//00100000xxxxxxxx
			((w1&0xe000)==0x4000)||	//01000000xxxxxxxx
			((w1&0xe000)==0x6000)||	//01100000xxxxxxxx
			((w1&0xf000)==0x8000)||	//10000000xxxxxxxx
			((w1&0xf800)==0xc000)||	//11000000xxxxxxxx
			((w1&0xfe00)==0xc800))	//1100100xxxxxxxxx
		//for optimization must this be here and not before analyze_opcode7()
		analyze_opcode8(w1);
	else if(((w1&0xf000)==0x1000)||	//0001xxxxxxxxxxxx
			((w1&0xf000)==0x9000)||	//1001xxxxxxxxxxxx
			((w1&0xf000)==0xa000)||	//1010xxxxxxxxxxxx
			((w1&0xf000)==0xb000)||	//1011xxxxxxxxxxxx
			((w1&0xf000)==0xd000)||	//1101xxxxxxxxxxxx
			((w1&0xf000)==0xe000)||	//1110xxxxxxxxxxxx
			((w1&0xf000)==0xf000))	//1111xxxxxxxxxxxx
		analyze_opcode4(w1);*/
	else
		return 0;

	return cmd.size;

}


t_op12_tbl op12_tbl[16]=
{
	{CR16C_null,	{PAR_none,		PAR_none,	PAR_none},	ooType0,	0,	1},
	{CR16C_null,	{PAR_none,		PAR_none,	PAR_none},	ooType0,	0,	1},
	{CR16C_addd,	{PAR_ind_rp,	PAR_imm,	PAR_none},	ooType4,	23,	3},
	{CR16C_subd,	{PAR_ind_rp,	PAR_imm,	PAR_none},	ooType4,	23,	3},
	{CR16C_andd,	{PAR_ind_rp,	PAR_imm,	PAR_none},	ooType4,	23,	3},
	{CR16C_ord,		{PAR_ind_rp,	PAR_imm,	PAR_none},	ooType4,	23,	3},
	{CR16C_xord,	{PAR_ind_rp,	PAR_imm,	PAR_none},	ooType4,	23,	3},
	{CR16C_movd,	{PAR_ind_rp,	PAR_imm,	PAR_none},	ooType4,	23,	3},
	{CR16C_null,	{PAR_none,		PAR_none,	PAR_none},	ooType0,	0,	1},	//trap fc
	{CR16C_cmpd,	{PAR_ind_rp,	PAR_imm,	PAR_none},	ooType4,	23,	3},
	{CR16C_null,	{PAR_none,		PAR_none,	PAR_none},	ooType0,	0,	1},
	{CR16C_null,	{PAR_none,		PAR_none,	PAR_none},	ooType0,	0,	1},
	{CR16C_excp,	{PAR_vect,		PAR_none,	PAR_none},	ooType12,	11,	1},
	{CR16C_jal,		{PAR_ind_rp,	PAR_ind_rp,	PAR_none},	ooType2,	11,	1},
	{CR16C_null,	{PAR_none,		PAR_none,	PAR_none},	ooType0,	0,	1},
	{CR16C_null,	{PAR_none,		PAR_none,	PAR_none},	ooType0,	0,	1}
};


void analyze_opcode12(ushort w1)
{
	ushort opcode=(w1&0x00f0)>>4;

	if(op12_tbl[opcode].type==CR16C_null)
	{
		cmd.itype=CR16C_ukntrap;
	}
	else
	{
		ushort w2=ua_next_word();

		cmd.itype=op12_tbl[opcode].type;
		cmd.auxpref=op12_tbl[opcode].op_order;

		struct t_pars pars;
		get_parametervalues(op12_tbl[opcode].fmt,w1,w2,pars);

		if(cmd.itype==CR16C_jal)
			pars.par[1]=rRA_L;	//(RA)

		for(int i=0;i<3;i++)
			set_operand(i,op12_tbl[opcode].p[i],pars.par[i]);
	}
}


void analyze_opcode13(ushort w1)
{
	switch((w1&0x18)>>3)
	{
		case 0:
			cmd.itype=CR16C_loadm;
			break;
		case 1:
			cmd.itype=CR16C_loadmp;
			break;
		case 2:
			cmd.itype=CR16C_storm;
			break;
		case 3:
			cmd.itype=CR16C_stormp;
			break;
	}

	cmd.auxpref=ooType11;

	cmd.Operands[0].type=o_imm;
	cmd.Operands[0].value=GET_P1_3(w1)+1;
	cmd.Operands[0].dtyp=dt_dword;
}


void analyze_opcode16(ushort w1)
{
	t_cmdinfo tmpcmd;

	ushort opcode=w1&0x001f;

	if(op16_tbl[opcode].fmt==4)
	{
		cmd.itype=op16_tbl[opcode].type;
		cmd.auxpref=op16_tbl[opcode].op_order;

		if(cmd.itype==CR16C_cinv)
		{
			cmd.Operands[0].type=o_idpspec0;
			cmd.Operands[0].specval=w1&0x0007;
		}

		return;
	}

	ushort w2=ua_next_word();

	if(op16_tbl[opcode].type==CR16C_null)
	{
		tmpcmd=op16_tbl[opcode].subop[GET_P4_4(w2)];
		cmd.itype=tmpcmd.type;
	}
	else
	{
		cmd.itype=op16_tbl[opcode].type;

		tmpcmd.type=op16_tbl[opcode].type;
		tmpcmd.fmt=op16_tbl[opcode].fmt;
		tmpcmd.p[0]=op16_tbl[opcode].p[0];
		tmpcmd.p[1]=op16_tbl[opcode].p[1];
		tmpcmd.p[2]=op16_tbl[opcode].p[2];
		tmpcmd.op_order=op16_tbl[opcode].op_order;
	}

	cmd.auxpref=tmpcmd.op_order;

	struct t_pars pars;
	get_parametervalues(tmpcmd.fmt,w1,w2,pars);

	for(int i=0;i<3;i++)
		set_operand(i,tmpcmd.p[i],pars.par[i]);

}


void get_parametervalues(int fmt,ushort w1,ushort w2,struct t_pars &pars)
{
	switch(fmt)
	{
		case 1:
			pars.par[0]=GET_P1_4(w2);
			pars.par[1]=GET_P2_4(w2);
			pars.par[2]=GET_P3_4(w2);
			break;
		case 2:
			pars.par[0]=GET_P1_4(w2);
			pars.par[1]=GET_P2_4(w2);
			pars.par[2]=GET_P3_20(w2,ua_next_word());
			break;
		case 3:
			pars.par[0]=GET_P1_24_1(w2,ua_next_word());
			pars.par[1]=GET_P2_4(w2);
			pars.par[2]=0;
			break;
		case 24: //3a
			pars.par[0]=GET_P1_24_1(w2,ua_next_word());
			pars.par[1]=GET_P2_4(w2);
			pars.par[2]=0;
			break;
		case 5:
			break;
		case 6:
			break;
		case 7:
			break;
		case 11:
			pars.par[0]=GET_P1_4(w1);
			pars.par[1]=0;
			pars.par[2]=0;
			break;
		case 23:
			pars.par[0]=GET_P1_4(w1);
			pars.par[1]=GET_P2_32(w2,ua_next_word());
			pars.par[2]=0;
			break;


		case 0:
		case 4:
		default:
			return;
	}
}

void set_operand(int opnum,enum par_types ptype,int value)
{
	if(opnum>4)
		return;

	switch(ptype)
	{
/*		case PAR_rrp:
			cmd.Operands[opnum].type=o_reg;
			cmd.Operands[opnum].reg=value;

			cmd.Operands[opnum].type=o_reg;
			cmd.Operands[opnum].reg=value;
			break;*/

		case PAR_reg:
			cmd.Operands[opnum].type=o_reg;
			cmd.Operands[opnum].reg=value;
			break;

		case PAR_rp:
			cmd.Operands[opnum].type=o_reg;
			cmd.Operands[opnum].reg=value+rRP0;
			break;

		case PAR_prd:
			cmd.Operands[opnum].type=o_reg;
			cmd.Operands[opnum].reg=value+rDDBS;
			break;

		case PAR_pr:
			cmd.Operands[opnum].type=o_reg;
			cmd.Operands[opnum].reg=value+rDBS;
			break;

		case PAR_vect:
			cmd.Operands[opnum].type=o_reg;
			cmd.Operands[opnum].reg=value+rEI0;
			break;

		case PAR_rp2:
//		case PAR_prp:	//if CFG.SR set: prp is reg else prp is rrp
		case PAR_rs:
			cmd.Operands[opnum].type=o_reg;
			cmd.Operands[opnum].reg=value;
			break;
		case PAR_disp:
			cmd.Operands[opnum].type=o_displ;
			cmd.Operands[opnum].value=value;
			break;
		case PAR_disp2:
			cmd.Operands[opnum].type=o_displ;
			cmd.Operands[opnum].value=value*2;
			break;
		case PAR_dispn:
			cmd.Operands[opnum].type=o_displ;
			cmd.Operands[opnum].value=-value;
			break;
		case PAR_ind_rp:
		case PAR_ind_reg:
		case PAR_ind_prp:	//if CFG.SR set: prp is reg else prp is rrp
			cmd.Operands[opnum].type=o_phrase;
			cmd.Operands[opnum].reg=value;
			cmd.Operands[opnum].specflag1=ptype;
			break;
		case PAR_ind_rrp:
			cmd.Operands[opnum].type=o_phrase;
			cmd.Operands[opnum].reg=(value&0x07)<<1;
			cmd.Operands[opnum].specflag1=PAR_ind_rp;

			cmd.Operands[3].type=o_reg;
			cmd.Operands[3].reg=((value&0x08)>>3)+rRP12;
			break;

		case PAR_abs:
			cmd.Operands[opnum].type=o_mem;
			cmd.Operands[opnum].value=value;
			break;
		case PAR_imm:
			cmd.Operands[opnum].type=o_imm;
			cmd.Operands[opnum].value=value;
			cmd.Operands[opnum].dtyp=dt_dword;
			break;
		case PAR_none:
			break;
		default:
			warning("analyze:unknown ptype");
			break;
	}


}


