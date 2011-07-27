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
	{CR16C_storb,	{PAR_ind_reg,	PAR_reg,	PAR_disp},	ooType1,	2,	3},
	{CR16C_storb,	{PAR_ind_rp,	PAR_reg,	PAR_disp},	ooType1,	2,	3},
	{CR16C_storb,	{PAR_ind_rrp,	PAR_reg,	PAR_disp},	ooType7,	2,	3},
	{CR16C_storb,	{PAR_abs,		PAR_reg,	PAR_none},	ooType4,	3,	3},
	{CR16C_stord,	{PAR_ind_reg,	PAR_ind_rp,	PAR_disp},	ooType1,	2,	3},
	{CR16C_stord,	{PAR_ind_rp,	PAR_ind_rp,	PAR_disp},	ooType1,	2,	3},
	{CR16C_stord,	{PAR_ind_rrp,	PAR_ind_rp,	PAR_disp},	ooType7,	2,	3},
	{CR16C_stord,	{PAR_abs,		PAR_ind_rp,	PAR_none},	ooType4,	3,	3},
	{CR16C_storw,	{PAR_ind_reg,	PAR_reg,	PAR_disp},	ooType1,	2,	3},
	{CR16C_storw,	{PAR_ind_rp,	PAR_reg,	PAR_disp},	ooType1,	2,	3},
	{CR16C_storw,	{PAR_ind_rrp,	PAR_reg,	PAR_disp},	ooType7,	2,	3},
	{CR16C_storw,	{PAR_abs,		PAR_reg,	PAR_none},	ooType4,	3,	3}
};

t_subop20_tbl subop20_10100_tbl[16]=
{
	{CR16C_lpr,		{PAR_reg,		PAR_pr,		PAR_none},	ooType5,	1,	2},
	{CR16C_lprd,	{PAR_ind_rp,	PAR_prd,	PAR_none},	ooType5,	1,	2},
	{CR16C_spr,		{PAR_reg,		PAR_pr,		PAR_none},	ooType4,	1,	2},
	{CR16C_sprd,	{PAR_ind_rp,	PAR_prd,	PAR_none},	ooType4,	1,	2},
	{CR16C_uknnop,	{PAR_none,		PAR_none,	PAR_none},	ooType0,	1,	2},
	{CR16C_uknnop,	{PAR_none,		PAR_none,	PAR_none},	ooType0,	1,	2},
	{CR16C_uknnop,	{PAR_none,		PAR_none,	PAR_none},	ooType0,	1,	2},
	{CR16C_uknnop,	{PAR_none,		PAR_none,	PAR_none},	ooType0,	1,	2},
	{CR16C_jal,		{PAR_ind_rp,	PAR_ind_rp,	PAR_none},	ooType5,	1,	2},
	{CR16C_ord,		{PAR_ind_rp,	PAR_ind_rp,	PAR_none},	ooType4,	1,	2},
	{CR16C_xord,	{PAR_ind_rp,	PAR_ind_rp,	PAR_none},	ooType4,	1,	2},
	{CR16C_andd,	{PAR_ind_rp,	PAR_ind_rp,	PAR_none},	ooType4,	1,	2},
	{CR16C_subd,	{PAR_ind_rp,	PAR_ind_rp,	PAR_none},	ooType4,	1,	2},
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
	{CR16C_storb,	{PAR_ind_reg,	PAR_reg,	PAR_dispn},	ooType1,	2,	3},
	{CR16C_storb,	{PAR_ind_rp,	PAR_reg,	PAR_dispn},	ooType1,	2,	3},
	{CR16C_ukntrap,	{PAR_none,		PAR_none,	PAR_none},	ooType0,	0,	3},
	{CR16C_ukntrap,	{PAR_none,		PAR_none,	PAR_none},	ooType0,	0,	3},
	{CR16C_stord,	{PAR_ind_reg,	PAR_ind_rp,	PAR_dispn},	ooType1,	2,	3},
	{CR16C_stord,	{PAR_ind_rp,	PAR_ind_rp,	PAR_dispn},	ooType1,	2,	3},
	{CR16C_ukntrap,	{PAR_none,		PAR_none,	PAR_none},	ooType0,	0,	3},
	{CR16C_ukntrap,	{PAR_none,		PAR_none,	PAR_none},	ooType0,	0,	3},
	{CR16C_storw,	{PAR_ind_reg,	PAR_reg,	PAR_dispn},	ooType1,	2,	3},
	{CR16C_storw,	{PAR_ind_rp,	PAR_reg,	PAR_dispn},	ooType1,	2,	3},
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
	{null,				CR16C_cinv,				{PAR_none,	PAR_none,	PAR_none},	ooType2,	4,	1},		//01010
	{null,				CR16C_cinv,				{PAR_none,	PAR_none,	PAR_none},	ooType2,	4,	1},		//01011
	{null,				CR16C_cinv,				{PAR_none,	PAR_none,	PAR_none},	ooType2,	4,	1},		//01100
	{null,				CR16C_cinv,				{PAR_none,	PAR_none,	PAR_none},	ooType2,	4,	1},		//01101
	{null,				CR16C_cinv,				{PAR_none,	PAR_none,	PAR_none},	ooType2,	4,	1},		//01110
	{null,				CR16C_cinv,				{PAR_none,	PAR_none,	PAR_none},	ooType2,	4,	1},		//01111
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

//----------------------------------------------------------------------------------

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
	{CR16C_excp,	{PAR_vect,		PAR_none,	PAR_none},	ooType2,	11,	1},
	{CR16C_jal,		{PAR_ind_rp,	PAR_ind_rp,	PAR_none},	ooType1,	11,	1},
	{CR16C_null,	{PAR_none,		PAR_none,	PAR_none},	ooType0,	0,	1},
	{CR16C_null,	{PAR_none,		PAR_none,	PAR_none},	ooType0,	0,	1}
};

//----------------------------------------------------------------------------------

t_op10_tbl op10_8600_tbl[4]=
{
	{CR16C_storb,	{PAR_ind_rrp,	PAR_imm,	PAR_disp},	ooType7,	17,	2},
	{CR16C_loadb,	{PAR_ind_rrp,	PAR_reg,	PAR_disp},	ooType8,	17,	2},
	{CR16C_loadd,	{PAR_ind_rrp,	PAR_ind_rp,	PAR_disp},	ooType8,	17,	2},
	{CR16C_loadw,	{PAR_ind_rrp,	PAR_reg,	PAR_disp},	ooType8,	17,	2}
};

t_op10_tbl op10_c600_tbl[4]=
{
	{CR16C_storw,	{PAR_ind_rrp,	PAR_imm,	PAR_disp},	ooType7,	17,	2},
	{CR16C_storb,	{PAR_ind_rrp,	PAR_reg,	PAR_disp},	ooType7,	17,	2},
	{CR16C_stord,	{PAR_ind_rrp,	PAR_ind_rp,	PAR_disp},	ooType7,	17,	2},
	{CR16C_storw,	{PAR_ind_rrp,	PAR_reg,	PAR_disp},	ooType7,	17,	2}
};

t_op10_tbl op10_6a80_tbl[2]=
{
	{CR16C_cbitb,	{PAR_ind_rrp,	PAR_imm,	PAR_disp},	ooType7,	17,	2},
	{CR16C_cbitw,	{PAR_ind_rrp,	PAR_imm,	PAR_disp},	ooType7,	17,	2}
};

t_op10_tbl op10_7280_tbl[2]=
{
	{CR16C_sbitb,	{PAR_ind_rrp,	PAR_imm,	PAR_disp},	ooType7,	17,	2},
	{CR16C_sbitw,	{PAR_ind_rrp,	PAR_imm,	PAR_disp},	ooType7,	17,	2}
};

t_op10_tbl op10_7a80_tbl[2]=
{
	{CR16C_tbitb,	{PAR_ind_rrp,	PAR_imm,	PAR_disp},	ooType7,	17,	2},
	{CR16C_tbitw,	{PAR_ind_rrp,	PAR_imm,	PAR_disp},	ooType7,	17,	2}
};

//----------------------------------------------------------------------------------

t_op9_tbl op9_0900_tbl[1]=
{
	{CR16C_lshb,	{PAR_reg,		PAR_immn,	PAR_none},	ooType4,	9,	1}
};

t_op9_tbl op9_4000_tbl[2]=
{
	{CR16C_ashub,	{PAR_reg,		PAR_imm,	PAR_none},	ooType4,	9,	1},
	{CR16C_ashub,	{PAR_reg,		PAR_immn,	PAR_none},	ooType4,	9,	1}
};

t_op9_tbl op9_6a00_tbl[4]=
{
	{CR16C_cbitb,	{PAR_ind_rp,	PAR_imm,	PAR_none},	ooType1,	9,	1},
	{CR16C_null,	{PAR_none,		PAR_none,	PAR_none},	ooType0,	0,	1},
	{CR16C_cbitb,	{PAR_ind_rp,	PAR_imm,	PAR_disp},	ooType1,	10,	2},
	{CR16C_cbitb,	{PAR_abs,		PAR_imm,	PAR_none},	ooType4,	7,	2}
};

t_op9_tbl op9_7200_tbl[4]=
{
	{CR16C_sbitb,	{PAR_ind_rp,	PAR_imm,	PAR_none},	ooType1,	9,	1},
	{CR16C_null,	{PAR_none,		PAR_none,	PAR_none},	ooType0,	0,	1},
	{CR16C_sbitb,	{PAR_ind_rp,	PAR_imm,	PAR_disp},	ooType1,	10,	2},
	{CR16C_sbitb,	{PAR_abs,		PAR_imm,	PAR_none},	ooType4,	7,	2}
};

t_op9_tbl op9_7a00_tbl[4]=
{
	{CR16C_tbitb,	{PAR_ind_rp,	PAR_imm,	PAR_none},	ooType1,	9,	1},
	{CR16C_null,	{PAR_none,		PAR_none,	PAR_none},	ooType0,	0,	1},
	{CR16C_tbitb,	{PAR_ind_rp,	PAR_imm,	PAR_disp},	ooType1,	10,	2},
	{CR16C_tbitb,	{PAR_abs,		PAR_imm,	PAR_none},	ooType4,	7,	2}
};

//----------------------------------------------------------------------------------

t_op7_tbl op7_4800_tbl[4]=
{
	{CR16C_null,	{PAR_none,		PAR_none,	PAR_none},	ooType0,	0,	1},
	{CR16C_lshd,	{PAR_ind_rp,	PAR_immn,	PAR_rs},	ooType4,	20,	1},
	{CR16C_ashud,	{PAR_ind_rp,	PAR_imm,	PAR_rs},	ooType4,	20,	1},
	{CR16C_ashud,	{PAR_ind_rp,	PAR_immn,	PAR_rs},	ooType4,	20,	1}
};

t_op7_tbl op7_8800_tbl[4]=
{
	{CR16C_null,	{PAR_none,		PAR_none,	PAR_none},	ooType0,	0,	1},
	{CR16C_loadb,	{PAR_abs,		PAR_reg,	PAR_rs},	ooType9,	13,	2},
	{CR16C_loadd,	{PAR_abs,		PAR_ind_rp,	PAR_rs},	ooType9,	13,	2},
	{CR16C_loadw,	{PAR_abs,		PAR_reg,	PAR_rs},	ooType9,	13,	2}
};

t_op7_tbl op7_c800_tbl[4]=
{
	{CR16C_null,	{PAR_none,		PAR_none,	PAR_none},	ooType0,	0,	1},
	{CR16C_storb,	{PAR_abs,		PAR_reg,	PAR_rs},	ooType6,	13,	2},
	{CR16C_stord,	{PAR_abs,		PAR_ind_rp,	PAR_rs},	ooType6,	13,	2},
	{CR16C_storw,	{PAR_abs,		PAR_reg,	PAR_rs},	ooType6,	13,	2}
};

t_op7_tbl op7_other_tbl[5]=
{
	{CR16C_cbitw,	{PAR_abs,		PAR_imm,	PAR_rs},	ooType6,	13,	2},		//6c00
	{CR16C_sbitw,	{PAR_abs,		PAR_imm,	PAR_rs},	ooType6,	13,	2},		//7400
	{CR16C_tbitw,	{PAR_abs,		PAR_imm,	PAR_rs},	ooType6,	13,	2},		//7c00
	{CR16C_storb,	{PAR_abs,		PAR_imm,	PAR_rs},	ooType6,	13,	2},		//8400
	{CR16C_storw,	{PAR_abs,		PAR_imm,	PAR_rs},	ooType6,	13,	2}		//c400
};

//----------------------------------------------------------------------------------

t_op4_tbl op4_0e00_tbl[8]=
{
	{CR16C_null,	{PAR_none,		PAR_none,	PAR_none},	ooType0,	0,	1},
	{CR16C_loadw,	{PAR_ind_rrp,	PAR_reg,	PAR_none},	ooType8,	18,	1},
	{CR16C_loadd,	{PAR_ind_rrp,	PAR_ind_rp,	PAR_none},	ooType8,	18,	1},
	{CR16C_loadb,	{PAR_ind_rrp,	PAR_reg,	PAR_none},	ooType8,	18,	1},
	{CR16C_null,	{PAR_none,		PAR_none,	PAR_none},	ooType0,	0,	1},
	{CR16C_storw,	{PAR_ind_rrp,	PAR_reg,	PAR_none},	ooType3,	18,	1},
	{CR16C_stord,	{PAR_ind_rrp,	PAR_ind_rp,	PAR_none},	ooType7,	18,	1},
	{CR16C_storb,	{PAR_ind_rrp,	PAR_reg,	PAR_none},	ooType7,	18,	1},
};

t_op4_tbl op4_0f00_tbl[8]=
{
	{CR16C_null,	{PAR_none,		PAR_none,	PAR_none},	ooType0,	0,	1},
	{CR16C_loadw,	{PAR_ind_rp,	PAR_reg,	PAR_disp},	ooType3,	19,	2},
	{CR16C_loadd,	{PAR_ind_rp,	PAR_ind_rp,	PAR_disp},	ooType3,	19,	2},
	{CR16C_loadb,	{PAR_ind_rp,	PAR_reg,	PAR_disp},	ooType3,	19,	2},
	{CR16C_null,	{PAR_none,		PAR_none,	PAR_none},	ooType0,	0,	1},
	{CR16C_storw,	{PAR_ind_rp,	PAR_reg,	PAR_disp},	ooType1,	19,	2},
	{CR16C_stord,	{PAR_ind_rp,	PAR_ind_rp,	PAR_disp},	ooType1,	19,	2},
	{CR16C_storb,	{PAR_ind_rp,	PAR_reg,	PAR_disp},	ooType1,	19,	2},
};

t_op4_tbl op4_other_tbl[8]=
{
	{CR16C_null,	{PAR_none,		PAR_none,	PAR_none},	ooType0,	0,	1},
	{CR16C_loadw,	{PAR_ind_rp,	PAR_reg,	PAR_disp2},	ooType3,	18,	1},
	{CR16C_loadd,	{PAR_ind_rp,	PAR_ind_rp,	PAR_disp2},	ooType3,	18,	1},
	{CR16C_loadb,	{PAR_ind_rp,	PAR_reg,	PAR_disp},	ooType3,	18,	1},
	{CR16C_null,	{PAR_none,		PAR_none,	PAR_none},	ooType0,	0,	1},
	{CR16C_storw,	{PAR_ind_rp,	PAR_reg,	PAR_disp2},	ooType1,	18,	1},
	{CR16C_stord,	{PAR_ind_rp,	PAR_ind_rp,	PAR_disp2},	ooType1,	18,	1},
	{CR16C_storb,	{PAR_ind_rp,	PAR_reg,	PAR_disp},	ooType1,	18,	1},
};

//----------------------------------------------------------------------------------

int idaapi cr16c_ana(void) 
{
	if(cmd.ea&0x01)			//only process even addresses
		return 0;

	ushort w1=ua_next_word();

	if((w1&0xffe0)==0x0000)			//00000000000xxxxx
		analyze_opcode16(w1);
	else if((w1&0xffe0)==0x00a0)	//00000000101xxxxx
		analyze_opcode13(w1);
	else if((w1&0xff00)==0x0000)	//00000000xxxxxxxx
		analyze_opcode12(w1);
	else if(((w1&0xff80)==0x6a80)||	//0110101010xxxxxx
			((w1&0xff80)==0x7280)||	//0111001010xxxxxx
			((w1&0xff80)==0x7a80)||	//0111101010xxxxxx
			((w1&0xff00)==0x8600)||	//10000110xxxxxxxx
			((w1&0xff00)==0xc600))	//11000110xxxxxxxx
		analyze_opcode10(w1);
	else if(((w1&0xff80)==0x6a00)||	//011010100xxxxxxx
			((w1&0xff80)==0x7200)||	//011100100xxxxxxx
			((w1&0xff80)==0x7a00)||	//011110100xxxxxxx
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
		//for optimization this must be here and not before analyze_opcode7()
		analyze_opcode8(w1);
	else if(((w1&0xf000)==0x1000)||	//0001xxxxxxxxxxxx
			((w1&0xf000)==0x9000)||	//1001xxxxxxxxxxxx
			((w1&0xf000)==0xa000)||	//1010xxxxxxxxxxxx
			((w1&0xf000)==0xb000)||	//1011xxxxxxxxxxxx
			((w1&0xf000)==0xd000)||	//1101xxxxxxxxxxxx
			((w1&0xf000)==0xe000)||	//1110xxxxxxxxxxxx
			((w1&0xf000)==0xf000))	//1111xxxxxxxxxxxx
		analyze_opcode4(w1);
	else
		return 0;

	return cmd.size;

}


t_op8_tbl op8_0000xxxx_tbl[16]=
{
	{CR16C_null,	{PAR_none,		PAR_none,	PAR_none},	ooType0,	0,	1},
	{CR16C_push,	{PAR_reg,		PAR_imm,	PAR_imm},	ooType,		14,	1},
	{CR16C_pop,		{PAR_reg,		PAR_imm,	PAR_imm},	ooType,		14,	1},
	{CR16C_popret,	{PAR_reg,		PAR_imm,	PAR_imm},	ooType,		14,	1},
	{CR16C_addd,	{PAR_imm,		PAR_ind_rp,	PAR_ind_rp},ooType,		12,	1},
	{CR16C_movd,	{PAR_imm,		PAR_reg,	PAR_ind_rp},ooType,		12,	1},
	{CR16C_tbit,	{PAR_reg,		PAR_ind_rp,	PAR_imm},	ooType,		15,	1},
	{CR16C_tbit,	{PAR_reg,		PAR_reg,	PAR_reg},	ooType,		15,	1},
	{CR16C_null/*scond*/,	{PAR_reg,		PAR_none,	PAR_imm},	ooType,		15,	1},
	{CR16C_null,	{PAR_none,		PAR_none,	PAR_none},	ooType0,	0,	1},
	{CR16C_null/*jcondb*/,	{PAR_rp2,		PAR_imm,	PAR_imm},	ooType,		15,	1},
	{CR16C_mulsb,	{PAR_reg,		PAR_ind_rp,	PAR_reg},	ooType,		15,	1},
	{CR16C_beq0b,	{PAR_reg,		PAR_reg,	PAR_disp2p},ooType,		15,	1},
	{CR16C_bne0b,	{PAR_reg,		PAR_none,	PAR_disp2p},ooType,		15,	1},
	{CR16C_beq0w,	{PAR_reg,		PAR_reg,	PAR_disp2p},ooType,		15,	1},
	{CR16C_bne0w,	{PAR_reg,		PAR_ind_rp,	PAR_disp2p},ooType,		15,	1}
};

t_op8_tbl op8_001xxxxx_tbl[32]=
{
	{CR16C_andb,	{PAR_reg,		PAR_imm,	PAR_none},	ooType0,	25,	2},
	{CR16C_andb,	{PAR_reg,		PAR_reg,	PAR_none},	ooType,		15,	1},
	{CR16C_andw,	{PAR_reg,		PAR_imm,	PAR_none},	ooType,		25,	2},
	{CR16C_andw,	{PAR_reg,		PAR_reg,	PAR_none},	ooType,		15,	1},
	{CR16C_orb,		{PAR_reg,		PAR_imm,	PAR_none},	ooType,		25,	2},
	{CR16C_orb,		{PAR_reg,		PAR_reg,	PAR_none},	ooType,		15,	1},
	{CR16C_orw,		{PAR_reg,		PAR_imm,	PAR_none},	ooType,		25,	2},
	{CR16C_orw,		{PAR_reg,		PAR_reg,	PAR_none},	ooType,		15,	1},
	{CR16C_xorb,	{PAR_reg,		PAR_imm,	PAR_none},	ooType,		25,	2},
	{CR16C_xorb,	{PAR_reg,		PAR_reg,	PAR_none},	ooType,		15,	1},
	{CR16C_xorw,	{PAR_reg,		PAR_imm,	PAR_none},	ooType,		25,	2},
	{CR16C_xorw,	{PAR_reg,		PAR_reg,	PAR_none},	ooType,		15,	1},
	{CR16C_addub,	{PAR_reg,		PAR_imm,	PAR_none},	ooType,		25,	2},
	{CR16C_addub,	{PAR_reg,		PAR_reg,	PAR_none},	ooType,		15,	1},
	{CR16C_adduw,	{PAR_reg,		PAR_imm,	PAR_none},	ooType,		25,	2},
	{CR16C_adduw,	{PAR_reg,		PAR_reg,	PAR_none},	ooType,		15,	1},
	{CR16C_andb,	{PAR_reg,		PAR_imm,	PAR_none},	ooType,		25,	2},
	{CR16C_andb,	{PAR_reg,		PAR_reg,	PAR_none},	ooType,		15,	1},
	{CR16C_andw,	{PAR_reg,		PAR_imm,	PAR_none},	ooType,		25,	2},
	{CR16C_andw,	{PAR_reg,		PAR_reg,	PAR_none},	ooType,		15,	1},
	{CR16C_addcb,	{PAR_reg,		PAR_imm,	PAR_none},	ooType,		25,	2},
	{CR16C_addcb,	{PAR_reg,		PAR_reg,	PAR_none},	ooType,		15,	1},
	{CR16C_addcw,	{PAR_reg,		PAR_imm,	PAR_none},	ooType,		25,	2},
	{CR16C_addcw,	{PAR_reg,		PAR_reg,	PAR_none},	ooType,		15,	1},
	{CR16C_subb,	{PAR_reg,		PAR_imm,	PAR_none},	ooType,		25,	2},
	{CR16C_subb,	{PAR_reg,		PAR_reg,	PAR_none},	ooType,		15,	1},
	{CR16C_subw,	{PAR_reg,		PAR_imm,	PAR_none},	ooType,		25,	2},
	{CR16C_subw,	{PAR_reg,		PAR_reg,	PAR_none},	ooType,		15,	1},
	{CR16C_subcb,	{PAR_reg,		PAR_imm,	PAR_none},	ooType,		25,	2},
	{CR16C_subcb,	{PAR_reg,		PAR_reg,	PAR_none},	ooType,		15,	1},
	{CR16C_subcw,	{PAR_reg,		PAR_imm,	PAR_none},	ooType,		25,	2},
	{CR16C_subcw,	{PAR_reg,		PAR_reg,	PAR_none},	ooType,		15,	1}
};

t_op8_tbl op8_01000xxx_tbl[8]=
{
	{CR16C_null,	{PAR_reg,		PAR_reg,	PAR_none},	ooType,		15,	1},
	{CR16C_ashub,	{PAR_reg,		PAR_imm,	PAR_none},	ooType,		15,	1},
	{CR16C_ashuw,	{PAR_reg,		PAR_imm,	PAR_none},	ooType,		15,	1},
	{CR16C_ashuw,	{PAR_reg,		PAR_reg,	PAR_none},	ooType,		15,	1},
	{CR16C_lshb,	{PAR_reg,		PAR_reg,	PAR_none},	ooType,		15,	1},
	{CR16C_ashuw,	{PAR_reg,		PAR_reg,	PAR_none},	ooType,		15,	1},
	{CR16C_lshw,	{PAR_reg,		PAR_reg,	PAR_none},	ooType,		15,	1},
	{CR16C_lshd,	{PAR_ind_rp,	PAR_reg,	PAR_none},	ooType,		15,	1}
};

t_op8_tbl op8_0100100x_tbl[2]=
{
	{CR16C_ashud,	{PAR_ind_rp,	PAR_reg,	PAR_none},	ooType,		15,	1},
	{CR16C_lshw,	{PAR_reg,		PAR_imm,	PAR_none},	ooType,		15,	1}
};

t_op8_tbl op8_0101xxxx_tbl[16]=
{
	{CR16C_cmpb,	{PAR_reg,		PAR_imm,	PAR_none},	ooType0,	25,	2},
	{CR16C_cmpb,	{PAR_reg,		PAR_reg,	PAR_none},	ooType,		15,	1},
	{CR16C_cmpw,	{PAR_reg,		PAR_imm,	PAR_none},	ooType,		25,	2},
	{CR16C_cmpw,	{PAR_reg,		PAR_reg,	PAR_none},	ooType,		15,	1},
	{CR16C_movd,	{PAR_ind_rp,	PAR_imm,	PAR_none},	ooType,		25,	2},
	{CR16C_movd,	{PAR_ind_rp,	PAR_ind_rp,	PAR_none},	ooType,		15,	1},
	{CR16C_cmpd,	{PAR_ind_rp,	PAR_imm,	PAR_none},	ooType,		25,	2},
	{CR16C_cmpd,	{PAR_ind_rp,	PAR_ind_rp,	PAR_none},	ooType,		15,	1},
	{CR16C_movb,	{PAR_reg,		PAR_imm,	PAR_none},	ooType,		25,	2},
	{CR16C_movb,	{PAR_reg,		PAR_reg,	PAR_none},	ooType0,	15,	1},
	{CR16C_movw,	{PAR_reg,		PAR_imm,	PAR_none},	ooType,		25,	2},
	{CR16C_movw,	{PAR_reg,		PAR_reg,	PAR_none},	ooType,		15,	1},
	{CR16C_movxb,	{PAR_reg,		PAR_reg,	PAR_none},	ooType,		15,	1},
	{CR16C_movzb,	{PAR_reg,		PAR_reg,	PAR_none},	ooType,		15,	1},
	{CR16C_movxw,	{PAR_ind_rp,	PAR_reg,	PAR_none},	ooType,		15,	1},
	{CR16C_movzw,	{PAR_ind_rp,	PAR_reg,	PAR_none},	ooType,		15,	1}
};

t_op8_tbl op8_011xxxxx_tbl[32]=
{
	{CR16C_addd,	{PAR_ind_rp,	PAR_imm,	PAR_none},	ooType0,	25,	2},
	{CR16C_addd,	{PAR_ind_rp,	PAR_ind_rp,	PAR_none},	ooType,		15,	1},
	{CR16C_mulsw,	{PAR_ind_rp,	PAR_reg,	PAR_none},	ooType,		15,	2},
	{CR16C_muluw,	{PAR_ind_rp,	PAR_reg,	PAR_none},	ooType,		15,	1},
	{CR16C_mulb,	{PAR_reg,		PAR_imm,	PAR_none},	ooType,		25,	2},
	{CR16C_mulb,	{PAR_reg,		PAR_reg,	PAR_none},	ooType,		15,	1},
	{CR16C_mulw,	{PAR_reg,		PAR_imm,	PAR_none},	ooType,		25,	2},
	{CR16C_mulw,	{PAR_reg,		PAR_reg,	PAR_none},	ooType,		15,	1},
	{CR16C_cbitb,	{PAR_abs,		PAR_imm,	PAR_rs},	ooType,		8,	2},
	{CR16C_cbitw,	{PAR_ind_rp,	PAR_imm,	PAR_disp},	ooType0,	16,	2},
	{CR16C_null,	{PAR_none,		PAR_none,	PAR_none},	ooType0,	0,	1},
	{CR16C_null,	{PAR_none,		PAR_none,	PAR_none},	ooType0,	0,	1},
	{CR16C_null,	{PAR_none,		PAR_none,	PAR_none},	ooType0,	0,	1},
	{CR16C_null,	{PAR_none,		PAR_none,	PAR_none},	ooType0,	0,	1},
	{CR16C_cbitw,	{PAR_ind_rp,	PAR_imm,	PAR_none},	ooType,		15,	2},
	{CR16C_cbitw,	{PAR_abs,		PAR_imm,	PAR_none},	ooType,		12,	2},
	{CR16C_sbitb,	{PAR_abs,		PAR_imm,	PAR_rs},	ooType,		8,	2},
	{CR16C_sbitw,	{PAR_ind_rp,	PAR_imm,	PAR_disp},	ooType,		16,	2},
	{CR16C_null,	{PAR_none,		PAR_none,	PAR_none},	ooType0,	0,	1},
	{CR16C_null,	{PAR_none,		PAR_none,	PAR_none},	ooType0,	0,	1},
	{CR16C_null,	{PAR_none,		PAR_none,	PAR_none},	ooType0,	0,	1},
	{CR16C_null,	{PAR_none,		PAR_none,	PAR_none},	ooType0,	0,	1},
	{CR16C_sbitw,	{PAR_ind_rp,	PAR_imm,	PAR_none},	ooType,		15,	2},
	{CR16C_sbitw,	{PAR_abs,		PAR_imm,	PAR_none},	ooType,		12,	2},
	{CR16C_tbitb,	{PAR_abs,		PAR_imm,	PAR_rs},	ooType,		8,	2},
	{CR16C_tbitw,	{PAR_ind_rp,	PAR_imm,	PAR_disp},	ooType,		16,	2},
	{CR16C_null,	{PAR_none,		PAR_none,	PAR_none},	ooType0,	0,	1},
	{CR16C_null,	{PAR_none,		PAR_none,	PAR_none},	ooType0,	0,	1},
	{CR16C_null,	{PAR_none,		PAR_none,	PAR_none},	ooType0,	0,	1},
	{CR16C_null,	{PAR_none,		PAR_none,	PAR_none},	ooType0,	0,	1},
	{CR16C_tbitw,	{PAR_ind_rp,	PAR_imm,	PAR_none},	ooType,		15,	1},
	{CR16C_tbitw,	{PAR_abs,		PAR_imm,	PAR_none},	ooType,		12,	2}
};


t_op8_tbl op8_100000xx_tbl[4]=
{
	{CR16C_null,	{PAR_none,		PAR_none,	PAR_none},	ooType0,	0,	1},
	{CR16C_storb,	{PAR_abs,		PAR_imm,	PAR_none},	ooType,		12,	2},
	{CR16C_storb,	{PAR_ind_rp,	PAR_imm,	PAR_none},	ooType,		15,	1},
	{CR16C_storb,	{PAR_ind_rp,	PAR_imm,	PAR_disp},	ooType,		16,	2}
};

t_op8_tbl op8_10000111_tbl[4]=
{
	{CR16C_loadd,	{PAR_abs,		PAR_ind_rp,	PAR_none},	ooType,		12,	2}
};

t_op8_tbl op8_1000100x_tbl[4]=
{
	{CR16C_loadb,	{PAR_abs,		PAR_reg,	PAR_none},	ooType,		12,	2},
	{CR16C_loadw,	{PAR_abs,		PAR_reg,	PAR_none},	ooType,		12,	2}
};

t_op8_tbl op8_110000xx_tbl[4]=
{
	{CR16C_bal,		{PAR_disp2,		PAR_none,	PAR_none},	ooType,		5,	2},
	{CR16C_storw,	{PAR_abs,		PAR_imm,	PAR_none},	ooType,		12,	2},
	{CR16C_storw,	{PAR_ind_rp,	PAR_imm,	PAR_none},	ooType,		15,	1},
	{CR16C_storw,	{PAR_ind_rp,	PAR_imm,	PAR_disp},	ooType,		16,	2}
};

t_op8_tbl op8_11000111_tbl[4]=
{
	{CR16C_stord,	{PAR_abs,		PAR_ind_rp,	PAR_none},	ooType,		12,	2}
};

t_op8_tbl op8_1100100x_tbl[4]=
{
	{CR16C_storb,	{PAR_abs,		PAR_reg,	PAR_none},	ooType,		12,	2},
	{CR16C_storw,	{PAR_abs,		PAR_reg,	PAR_none},	ooType,		12,	2}
};




void analyze_opcode8(ushort w1)
{
	t_cmdinfo tmpcmd;

	if((w1&0xf000)==0x0000)			tmpcmd=op8_0000xxxx_tbl[];
	else if((w1&0xe000)==0x2000)	tmpcmd=op8_001xxxxx_tbl[];
	else if((w1&0xf800)==0x4000)	tmpcmd=op8_01000xxx_tbl[];
	else if((w1&0xfe00)==0x4800)	tmpcmd=op8_0100100x_tbl[];
	else if((w1&0xf000)==0x5000)	tmpcmd=op8_0101xxxx_tbl[];
	else if((w1&0xe000)==0x6000)	tmpcmd=op8_011xxxxx_tbl[];
	else if((w1&0xfc00)==0x8000)	tmpcmd=op8_100000xx_tbl[];
	else if((w1&0xff00)==0x8700)	tmpcmd=op8_10000111_tbl[];
	else if((w1&0xfe00)==0x8800)	tmpcmd=op8_1000100x_tbl[];
	else if((w1&0xfc00)==0xc000)	tmpcmd=op8_110000xx_tbl[];
	else if((w1&0xff00)==0xc700)	tmpcmd=op8_11000111_tbl[];
	else if((w1&0xfe00)==0xc800)	tmpcmd=op8_1100100x_tbl[];
	else {cmd.size=0;return;}

	ushort w2;

	switch(tmpcmd.fmt)
	{
		case 5:
		case 12:
		case 16:
		case 25:
			w2=ua_next_word();
			break;
		default:
			break;
	}

	fill_cmd(tmpcmd,w1,w2);

}


t_cond_tbl cond_branch_tbl[16]=
{
CR16C_beq,CR16C_bne,CR16C_bcs,CR16C_bcc,CR16C_bhi,CR16C_bls,CR16C_bgt,CR16C_ble,
CR16C_bfs,CR16C_bfc,CR16C_blo,CR16C_bhs,CR16C_blt,CR16C_bge,CR16C_br,CR16C_null
};

void analyze_opcode4(ushort w1)
{
	t_cmdinfo tmpcmd;

	if(w1&0x8000)
	{
		ushort opcode=(w1&0x0f00);

		switch(opcode)
		{
			case 0x0e00:
				tmpcmd=op4_0e00_tbl[(w1&0x7000)>>12];
				break;
			case 0x0f00:
				tmpcmd=op4_0f00_tbl[(w1&0x7000)>>12];
				break;
			default:
				tmpcmd=op4_other_tbl[(w1&0x7000)>>12];
				break;
		}
	}
	else
	{
		//branch
		tmpcmd.type=cond_branch_tbl[GET_P2_4(w1)].type;

		if((w1&0xff0f)==0x1800)
		{
			tmpcmd.p[0]=PAR_none;
			tmpcmd.p[1]=PAR_none;
			tmpcmd.p[2]=PAR_disp2o;			//buggy
			tmpcmd.op_order=ooType11;
			tmpcmd.fmt=22;
		}
		else
		{
			tmpcmd.p[0]=PAR_disp2o;
			tmpcmd.p[1]=PAR_none;
			tmpcmd.p[2]=PAR_none;			//untested for negative offsets
			tmpcmd.op_order=ooType2;
			tmpcmd.fmt=21;
		}
	}

	ushort w2;

	if((tmpcmd.fmt==19)||(tmpcmd.fmt==22))
		w2=ua_next_word();

	fill_cmd(tmpcmd,w1,w2);

}



void analyze_opcode7(ushort w1)
{
	t_cmdinfo tmpcmd;

	ushort opcode=(w1&0xf800);

	switch(opcode)
	{
		case 0x4800:
			tmpcmd=op7_4800_tbl[(w1&0x0600)>>9];
			break;
		case 0x8800:
			tmpcmd=op7_8800_tbl[(w1&0x0600)>>9];
			break;
		case 0xc800:
			tmpcmd=op7_c800_tbl[(w1&0x0600)>>9];
			break;
		case 0x6800:
			tmpcmd=op7_other_tbl[0];
			break;
		case 0x7000:
			tmpcmd=op7_other_tbl[1];
			break;
		case 0x7800:
			tmpcmd=op7_other_tbl[2];
			break;
		case 0x8000:
			tmpcmd=op7_other_tbl[3];
			break;
		case 0xc000:
			tmpcmd=op7_other_tbl[4];
			break;


		default:
			warning("unknown opcode7");
			cmd.size=0;
			return;
	}

	ushort w2;

	if((tmpcmd.fmt==13))
		w2=ua_next_word();

	fill_cmd(tmpcmd,w1,w2);

}


void analyze_opcode9(ushort w1)
{
	t_cmdinfo tmpcmd;

	ushort opcode=(w1&0xfe00);

	switch(opcode)
	{
		case 0x7200:
			tmpcmd=op9_7200_tbl[(w1&0x0180)>>7];
			break;
		case 0x7a00:
			tmpcmd=op9_7a00_tbl[(w1&0x0180)>>7];
			break;
		case 0x6a00:
			tmpcmd=op9_6a00_tbl[(w1&0x0180)>>7];
			break;
		case 0x4000:
			tmpcmd=op9_4000_tbl[(w1&0x0080)>>7];
			break;
		case 0x0800:				//0800 is 0900 , cause opcode=(w1&0xfe00)
			tmpcmd=op9_0900_tbl[0];
			break;

		default:
			warning("unknown opcode9");
			cmd.size=0;
			return;
	}

	ushort w2;

	if((tmpcmd.fmt==10)||(tmpcmd.fmt==7))
		w2=ua_next_word();

	fill_cmd(tmpcmd,w1,w2);

}


void analyze_opcode10(ushort w1)
{
	t_cmdinfo tmpcmd;

	ushort opcode=(w1&0xe700);
	ushort opcode2;

	switch(opcode)
	{
		case 0x8600:
			tmpcmd=op10_8600_tbl[(w1&0x00c0)>>6];
			break;
		case 0xc600:
			tmpcmd=op10_c600_tbl[(w1&0x00c0)>>6];
			break;
		case 0x6200:
			opcode2=(w1&0xff80);

			switch(opcode2)
			{
				case 0x6a80:
					tmpcmd=op10_6a80_tbl[(w1&0x0040)>>6];
					break;
				case 0x7280:
					tmpcmd=op10_7280_tbl[(w1&0x0040)>>6];
					break;
				case 0x7a80:
					tmpcmd=op10_7a80_tbl[(w1&0x0040)>>6];
					break;
				default:
				warning("unknown opcode10_2");
				cmd.size=0;
				return;
			}

			break;

		default:
			warning("unknown opcode10");
			cmd.size=0;
			return;
	}

	fill_cmd(tmpcmd,w1,ua_next_word());

}


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

	cmd.auxpref=ooType2;

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
		//cmd.itype=tmpcmd.type;
	}
	else
	{
		//cmd.itype=op16_tbl[opcode].type;

		tmpcmd.type=op16_tbl[opcode].type;
		tmpcmd.fmt=op16_tbl[opcode].fmt;
		tmpcmd.p[0]=op16_tbl[opcode].p[0];
		tmpcmd.p[1]=op16_tbl[opcode].p[1];
		tmpcmd.p[2]=op16_tbl[opcode].p[2];
		tmpcmd.op_order=op16_tbl[opcode].op_order;
	}

	fill_cmd(tmpcmd,w1,w2);

}

void fill_cmd(t_cmdinfo &tmpcmd,ushort w1,ushort w2)
{
	cmd.itype=tmpcmd.type;
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
			pars.par[0]=GET_P1_20(w1,w2);
			pars.par[1]=GET_P2_3(w1);
			pars.par[2]=0;
			break;

		case 9:
			pars.par[0]=GET_P1_4(w1);
			pars.par[1]=GET_P2_3(w1);
			pars.par[2]=0;
			break;

		case 10:
			pars.par[0]=GET_P1_4(w1);
			pars.par[1]=GET_P2_3(w1);
			pars.par[2]=w2;
			break;

		case 11:
			pars.par[0]=GET_P1_4(w1);
			pars.par[1]=0;
			pars.par[2]=0;
			break;

		case 13:
			pars.par[0]=GET_P1_20(w1,w2);
			pars.par[1]=GET_P2_4(w1);
			pars.par[2]=GET_P3_1(w1);
			break;

		case 17:
			pars.par[0]=GET_P1_4(w1);
			pars.par[1]=GET_P2_4(w2);
			pars.par[2]=GET_P3_14(w1,w2);
			break;

		case 18:
			pars.par[0]=GET_P1_4(w1);
			pars.par[1]=GET_P2_4(w1);
			pars.par[2]=GET_P3_4(w1);
			break;

		case 19:
			pars.par[0]=GET_P1_4(w1);
			pars.par[1]=GET_P2_4(w1);
			pars.par[2]=w2;
			break;

		case 20:
			pars.par[0]=GET_P1_4(w1);
			pars.par[1]=GET_P2_5(w1);
			pars.par[2]=0;
			break;

		case 21:
			pars.par[0]=GET_P1_8(w1);
			pars.par[1]=GET_P2_4(w1);
			pars.par[2]=0;
			break;

		case 22:
			pars.par[0]=GET_P1_8(w1);
			pars.par[1]=GET_P2_4(w1);
			pars.par[2]=GET_P3_16(w2);
			break;

		case 23:
			pars.par[0]=GET_P1_4(w1);
			pars.par[1]=GET_P2_32(w2,ua_next_word());
			pars.par[2]=0;
			break;


		case 0:
		case 4:
		default:
			pars.par[0]=0;
			pars.par[1]=0;
			pars.par[2]=0;
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
			cmd.Operands[opnum].type=o_reg;
			cmd.Operands[opnum].reg=value;
			break;
		case PAR_rs:
			cmd.Operands[opnum].type=o_reg;
			cmd.Operands[opnum].reg=value+rRP12;
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
		case PAR_disp2o:
			cmd.Operands[opnum].type=o_displ;
			cmd.Operands[opnum].value=(value*2)+cmd.ea;
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
		case PAR_immn:
			cmd.Operands[opnum].type=o_imm;
			cmd.Operands[opnum].value=-(8-value);
			cmd.Operands[opnum].dtyp=dt_dword;
			break;
		case PAR_none:
			break;
		default:
			warning("analyze:unknown parameter type");
			break;
	}


}


