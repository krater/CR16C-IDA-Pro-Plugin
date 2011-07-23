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
#include <diskio.hpp>
#include <ieee.h>

// A well behaving processor module should call invoke_callbacks()
// in his notify() function. If invoke_callbacks function returns 0, 
// then the processor module should process the notification itself
// Otherwise the code should be returned to the caller:

//--------------------------------------------------------------------------
static int idaapi notify(processor_t::idp_notify msgid, ...)
{
	va_list va;
	va_start(va, msgid);   //setup args list
	int result = invoke_callbacks(HT_IDP, msgid, va);
	if (result == 0) 
	{
		result = 1;             //default success
		switch(msgid) 
		{
			case processor_t::init:
			inf.mf = 0;       //ensure little endian!
			break;         
			case processor_t::make_data: 
			{
				ea_t ea = va_arg(va, ea_t);
				flags_t flags = va_arg(va, flags_t);
				tid_t tid = va_arg(va, tid_t);
				asize_t len = va_arg(va, asize_t);

				if (len > 4)  //our d_out can only handle byte, word, dword
				{
					result = 0; //disallow big data
				}
				break;
			}
		}
	}
	va_end(va);
	return result;
}

//----------------------------------------------------------------------
// Set IDP options. Either from the configuration file either allow the user
// to specify them in a dialog box.
static const char* idaapi set_idp_options(const char *keyword, int value_type,const void *value)
{
	return(IDPOPT_OK);
}

//----------------------------------------------------------------------
static void idaapi func_header(func_t *f) 
{
	char buf[256];
	char name[64];

	printf_line(0, "# ||||||||||||||| S U B R O U T I N E |||||||||||||||");
	printf_line(0, "");

	get_func_name(f->startEA, name, sizeof(name));
	init_output_buffer(buf, sizeof(buf));
	out_snprintf("def %s(", name);
	out_snprintf("...):");
	term_output_buffer();
	printf_line(0, "%s", buf);
	printf_line(0, "");

}

static void idaapi func_footer(func_t *)
{
	printf_line(0, "# end function");
}

static bool idaapi python_specseg(ea_t ea, uchar)    
{ 
	cr16c_data(ea); 
	return false; 
}

//----------------------------------------------------------------------
ushort badinsts[] = {6, 7, 8, 14, 16, 17, 34, 35, 36, 37, 38, 39,
                     44, 45, 46, 47, 48, 49, 54, 69, 81, 94, 109,
                     114, 155, 117, 118, 123, 127, 128, 129, 138, 139, 0};

//----------------------------------------------------------------------
static asm_t cr16c_asm =
{
  AS_COLON|AS_UDATA|ASH_HEXF3|ASD_DECF0|AS_2CHRE|AS_ASCIIC|AS_1TEXT,
  0,
  "Generic CR16C assembler",
  0,        // no help screen
  NULL,     // header
  badinsts, // bad instructions
  NULL,     // origin
  NULL,     // end of file

  "#",     // comment string
  '"',      // string delimiter
  '\'',     // char delimiter
  "\"'\\",  // special symbols in char and string constants

  "",         // ascii string directive
  "db",         // byte directive
  "dw",       // word directive
  "dd",       // double words
  NULL,       // qwords
  NULL,       // oword  (16 bytes)
  NULL,       // float
  NULL,       // double
  NULL,       // no tbytes
  NULL,       // no packreal
  NULL,     // arrays:
            // #h - header(.byte,.word)
            // #d - size of array
            // #v - value of array elements
  NULL,         //".reserv  %s",  // uninited data (reserve space)
  " = ",        // equ
  NULL,         // seg prefix
  NULL,         // preline for checkarg
  NULL,         // checkarg_atomprefix
  NULL,         // checkarg operations
  NULL,         // XlatAsciiOutput
  NULL,         // a_curip
  func_header,  // func header
  func_footer,  // func footer
  "",     // public (disable ouput)
  NULL,		// weak
  NULL,		// extrn
  NULL,		// comm
  NULL,		// get_type_name
  NULL,		// align
  '(', ')',	// lbrace, rbrace
  "%",     // mod
  "&",     // and
  "|",     // or
  "^",     // xor
  "!",     // not
  "<<",    // shl
  ">>",    // shr
  NULL,    // sizeof
  0, NULL, NULL, NULL, NULL, NULL,
  NULL, NULL, NULL, NULL
};


//-----------------------------------------------------------------------
static asm_t *asms[]={&cr16c_asm,NULL};
static char *names[]={"CR16C",NULL};

//--------------------------------------------------------------------------
static uchar result_0[] = { 1/*RETURN_VALUE*/ };

static bytes_t results[] = 
{
 { sizeof(result_0), result_0 },
 { 0, NULL }
};


static char* RegNames[]=
{
	//General Purpose Registers (reg)
	"r0","r1","r2","r3","r4","r5","r6","r7","r8",
	"r9","r10","r11","r12_l","r13_l","ra_l","sp_l",

	//Register Pairs (rp)
	"r1,r0","r2,r1","r3,r2","r4,r3","r5,r4","r6,r5","r7,r6","r8,r7",
	"r9,r8","r10,r9","r11,r10","r12_l,r11","r12","r13","ra","sp",

	//Processor registers for LPRD/SPRD
	"dbs","dsr","dcr","<invalid3>","car0","<invalid5>","car1","<invalid7>",
	"cfg","psr","intbase","<invalid11>","isp","<invalid13>","usp","<invalid15>",

	//Processor registers for LPR/SPR
	"dbs","dsr","dcrl","dcrh","car0l","car0h","car1l","car1h",
	"cfg","psr","intbasel","intbaseh","ispl","isph","uspl","usph",

	//Exception Vector
	"<invalid0>","<invalid1>","<invalid2>","<invalid3>","<invalid4>","svc","dvz","flg",
	"bpt","trc","und","<invalid11>","iad","<invalid13>","cbg","ise",

	"ds","cs"	
};

//----------------------------------------
ea_t idaapi get_ref_addr(ea_t ea, const char *name, int pos) 
{
   return BADADDR-1;
}

//-----------------------------------------------------------------------
//      Processor Definition
//-----------------------------------------------------------------------
processor_t LPH =
{
   IDP_INTERFACE_VERSION,     //kernel version
   PLFM_CR16C,               //id
   PR_USE32|PRN_HEX|PR_CNDINSNS,
   8,                  // 8 bits in a byte for code segments
   8,                  // 8 bits in a byte for other segments

   names,
   names,

   asms,		//assemblers

   notify,

   header,      // function to produce start of disassembled text
   footer,      // function to produce end of disassembled text

   segstart,    // function to produce start of segment
   segend,      // function to produce end of segment

   NULL,        // function to produce assume directives

// Analyze one instruction and fill 'cmd' structure.
// cmd.ea contains address of instruction to analyze.
// Return length of the instruction in bytes, 0 if instruction can't be decoded.
// This function shouldn't change the database, flags or anything else.
// All these actions should be performed only by u_emu() function.
   cr16c_ana,

//
// Emulate instruction, create cross-references, plan to analyze
// subsequent instructions, modify flags etc. Upon entrance to this function
// all information about the instruction is in 'cmd' structure.
// Return length of the instruction in bytes.
   cr16c_emu,

// Generate text representation of an instruction in 'cmd' structure.
// This function shouldn't change the database, flags or anything else.
// All these actions should be performed only by u_emu() function.
   cr16c_out,

// Generate text representation of an instructon operand.
// This function shouldn't change the database, flags or anything else.
// All these actions should be performed only by u_emu() function.
// The output text is placed in the output buffer initialized with init_output_buffer()
// This function uses out_...() functions from ua.hpp to generate the operand text
// Returns: 1-ok, 0-operand is hidden.
   cr16c_outop,

// Generate text represenation of data items
// This function MAY change the database and create cross-references, etc.
   cr16c_data,    //sdk offers intel_data

   NULL,          //  cmp_opnd,  // 0 if not cmp 1 if eq
   NULL, //(&op)  int : 1 -yes 0-no

   qnumber(RegNames),  // Number of registers
   RegNames,           // Regsiter names
   NULL,               // get abstract register

   0,                  // Number of register files
   NULL,               // Register file names
   NULL,               // Register descriptions
   NULL,               // Pointer to CPU registers

   rVcs,rVds,
   0,                  // size of a segment register
   rVcs,rVds,

   NULL,               // No known code start sequences
   results,

   CR16C_null, 
   CR16C_lastinstruction,
   Instructions,

   NULL,               // isFarJump or Call
   NULL,               //  Offset Generation Function. Usually NULL.
   0,                  // size of tbyte
   ieee_realcvt,
   {0,7,15,0},         // real width
   NULL,               // is this instruction switch
   NULL,               // generate map-file
   get_ref_addr,       // extract address from a string
   NULL,               // is_sp_based
   NULL,               // create_func_frame
   NULL,               // get_func_retsize
   NULL,               // gen_stkvar_def
   NULL, //python_specseg,       // out special segments
   1,//RETURN_VALUE,              // icode_return
   NULL, //set_idp_options,    // Set IDP options
   NULL,               // Is alignment instruction?
   NULL,               // Micro virtual machine description
   0,                  // high_fixup_bits
};

//-----------------------------------------------------------------------
