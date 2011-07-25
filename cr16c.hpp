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

#ifndef __CR16C_HPP
#define __CR16C_HPP

#define PLFM_CR16C 0x42236

#include <pro.h>
#include <kernwin.hpp>
#include "../idaidp.hpp"
#include <fpro.h>
#include "ins.hpp"

#pragma pack(1)
#define null 0


#define GET_P1_3(x)			(((x)&0x0007))
#define GET_P2_3(x)			(((x)&0x0070)>>4)


#define GET_P1_4(x)			(((x)&0x000f))
#define GET_P2_4(x)			(((x)&0x00f0)>>4)
#define GET_P3_4(x)			(((x)&0x0f00)>>8)
#define GET_P4_4(x)			(((x)&0xf000)>>12)

#define GET_P1_20(x,y)		((((int)GET_P1_4(x))<<16)+(y))
#define GET_P3_20(x,y)		((((int)GET_P3_4(x))<<16)+(y))

#define GET_P1_24_1(x,y)	((((int)GET_P1_4(x))<<20)+(GET_P3_20(x,y)))						//like in fmt #3
#define GET_P1_24_2(x,y)	((((int)GET_P1_24_1(x,y))&0xfffffe)+(((int)((y)&0x01))<<24))	//like in fmt #3a
#define GET_P1_24_3(x,y)	(((((int)(x))&0xff)<<16)+((y)&0xfffe)+(((int)(y))<<24))			//like in fmt #5

#define GET_P2_32(x,y)		(((x)<<16)|(y))

#define GET_P3_14(x,y)		((GET_P3_B136(y)<<8)|(GET_P3_B76(y)<<6)|(GET_P3_B54(x)<<4)|GET_P1_4(y))

#define GET_P3_B54(x)		(((x)&0x0030)>>4)
#define GET_P3_B76(x)		(((x)&0xc000)>>14)
#define GET_P3_B136(x)		(((x)&0x3f00)>>8)


struct t_cmdinfo
{
	enum inst_names type;
	enum par_types p[3];
	enum op_order op_order;
	int fmt;
	char len;	
};

typedef t_cmdinfo t_subop20_tbl;
typedef t_cmdinfo t_op12_tbl;
typedef t_cmdinfo t_op10_tbl;
typedef t_cmdinfo t_op9_tbl;

struct t_op16_tbl
{
	t_subop20_tbl *subop;
	enum inst_names type;
	enum par_types p[3];
	enum op_order op_order;
	int fmt;
	char len;
};


struct t_pars
{
	unsigned int par[3];
};

enum op_order
{
	ooType,
	ooType0,	//no operand
	ooType1,	//$4, 0x444(r0)
	ooType2,	//r0, 0(r1)
	ooType3,	//0x6(r5), r1
	ooType4,	//$4, 0x444
	ooType5,	//0x66666, r5
	ooType6,	//r7, 0x66666
	ooType7,
	ooType8,
	ooType9,
	ooType10,
	ooType11,
	ooType12
};



//------------------------------------------------------------------------
// Helper functions

void analyze_opcode16(ushort w1);
void analyze_opcode13(ushort w1);
void analyze_opcode12(ushort w1);
void analyze_opcode10(ushort w1);
void analyze_opcode9(ushort w1);
void analyze_opcode7(ushort w1);
void analyze_opcode8(ushort w1);
void analyze_opcode4(ushort w1);

void get_parametervalues(int fmt,ushort w1,ushort w2,struct t_pars &pars);
void set_operand(int opnum,enum par_types ptype,int value);
void fill_cmd(t_cmdinfo &tmpcmd,ushort w1,ushort w2);

//------------------------------------------------------------------------
enum cr16c_registers
{ 
	//General Purpose Registers
	rR0,rR1,rR2,rR3,rR4,rR5,rR6,rR7,rR8,
	rR9,rR10,rR11,rR12_L,rR13_L,rRA_L,rSP_L,

	//Register Pairs
	rRP0,rRP1,rRP2,rRP3,rRP4,rRP5,rRP6,rRP7,
	rRP8,rRP9,rRP10,rRP11,rRP12,rRP13,rRPRA,rRPSP,

	//Processor registers for LPRD/SPRD
	rDDBS,rDDSR,rDDCS,rDI3,rDCAR0,rDI5,rDCAR1,rDI7,
	rDCFG,rDPSR,rDINTBASE,rDI11,rDISP,rDI13,rDUSP,rDI15,

	//Processor registers for LPR/SPR
	rDBS,rDSR,rDCRL,rDCRH,rCAR0L,rCAR0H,rCAR1L,rCAR1H,
	rCFG,rPSR,rINTBASEL,rINTBAEH,rISPL,rISPH,rUSPL,rUSPH,

	//Exception Vector
	rEI0,rEI1,rEI2,rEI3,rEI4,rSVC,rDVZ,rFLG,
	rBPT,rTRC,rUND,rEI10,rIAD,rEI12,rCBD,rISE,

	rVds,rVcs	
};

//------------------------------------------------------------------------
void  idaapi header(void);
void  idaapi footer(void);

void  idaapi segstart(ea_t ea);
void  idaapi segend(ea_t ea);

int   idaapi cr16c_ana(void);
int   idaapi cr16c_emu(void);
void  idaapi cr16c_out(void);
bool  idaapi cr16c_outop(op_t &op);

void  idaapi cr16c_data(ea_t ea);

void  loader(linput_t *li, bool manualload);
ea_t  idaapi get_ref_addr(ea_t ea, const char *str, int pos);

int   cmp_opnd(op_t &op1, op_t &op2);


#pragma pack()
#endif


