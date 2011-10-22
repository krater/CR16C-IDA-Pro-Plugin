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


//----------------------------------------------------------------------
void idaapi cr16c_out(void) 
{
	char str[MAXSTR];  //MAXSTR is an IDA define from pro.h
	init_output_buffer(str, sizeof(str));

	OutMnem(12);       //first we output the mnemonic

	switch(cmd.auxpref)
	{
		case ooType0:					//no operands
			break;

		case ooType1:					//4,0x444(r0)	->1,20
			out_one_operand(1);
			out_symbol(',');
			out_one_operand(2);
			out_one_operand(0);
			break;

		case ooType2:					//4				->0
			out_one_operand(0);
			break;

		case ooType3:					//6(r5), r1		->20,1
			out_one_operand(2);
			out_one_operand(0);
			out_symbol(',');
			out_one_operand(1);
			break;

		case ooType4:					//$4,0x444		->1,0
			out_one_operand(1);
			out_symbol(',');
			out_one_operand(0);
			break;

		case ooType5:					//0x66666, r5	->0,1
			out_one_operand(0);
			out_symbol(',');
			out_one_operand(1);
			break;

		case ooType6:					//$7, [r12]0x26666	->1,[2]0
			out_one_operand(1);
			out_symbol(',');
			out_symbol('[');
			out_one_operand(2);
			out_symbol(']');
			out_one_operand(0);
			break;

		case ooType7:					//$7, [r12]0x26666(r3,r2)
			out_one_operand(1);
			out_symbol(',');
			out_symbol('[');
			out_one_operand(3);
			out_symbol(']');
			out_one_operand(2);
			out_one_operand(0);
			break;

		case ooType8:					//[r12]0x26666(r3,r2), r0
			out_symbol('[');
			out_one_operand(3);
			out_symbol(']');
			out_one_operand(2);
			out_one_operand(0);
			out_symbol(',');
			out_one_operand(1);
			break;

		case ooType9:					//[r12]0x26666,R3	->[2]0,1
			out_symbol('[');
			out_one_operand(2);
			out_symbol(']');
			out_one_operand(0);
			out_symbol(',');
			out_one_operand(1);
			break;

		case ooType10:					//x,y,z			->0,1,2
			out_one_operand(0);
			out_symbol(',');
			out_one_operand(1);
			out_symbol(',');
			out_one_operand(2);
			break;

		case ooType11:					//4				->2
			out_one_operand(2);
			break;

		case ooType12:					//y,x{,z}		->1,0{,2}
			out_one_operand(1);
			out_symbol(',');
			out_one_operand(0);
			if(cmd.Op3.type != o_void) 
			{
				out_symbol(',');
				out_one_operand(2);
			}
			break;


		default:
			if(cmd.Op1.type != o_void) 
			{
				out_one_operand(0);
			}

			out_snprintf(" , ");

			if(cmd.Op2.type != o_void) 
			{  //then there is an argument to print
				out_one_operand(1);
			}

			out_snprintf(" , ");

			if(cmd.Op3.type != o_void) 
			{  //then there is an argument to print
				out_one_operand(2);
			}
	}




	term_output_buffer();
	gl_comm = 1;      //we want comments!
	MakeLine(str);    //output the line with default indentation
}

//--------------------------------------------------------------------------
// function to produce start of disassembled text
//set as member of LPH struct
void idaapi header(void) 
{
	printf_line(0,"");
	printf_line(0,"");
	printf_line(0,"# CR16C Processor plugin by Andreas Schuler <andreas@schulerdev.de>");
	printf_line(0,"# ");
	printf_line(0,"# Based on Simple Python Byte Code Module (Chris Eagle <cseagle@gmail.com>)");
	printf_line(0,"# Released under GPL v2");
	printf_line(0,"# ");
	printf_line(0,"# More infos at http://www.codenaschen.de");
}

void idaapi footer() 
{
}

//----------------------------------------------------------------------
// function to produce start of segment
void idaapi segstart(ea_t ea) 
{  
}

//--------------------------------------------------------------------------
// function to produce end of segment
void idaapi segend(ea_t ea) 
{
}

//--------------------------------------------------------------------------
void idaapi cr16c_data(ea_t ea) 
{
   char obuf[256];
   init_output_buffer(obuf, sizeof(obuf));
   int col = 0;
   uint32 flags = get_flags_novalue(ea);
   if (isWord(flags)) {
      out_snprintf("%s %xh", ash.a_word ? ash.a_word : "", get_word(ea));
   }
   else if (isDwrd(flags)) {
      out_snprintf("%s %xh", ash.a_dword ? ash.a_dword : "", get_long(ea));
   }
   else { //if (isByte(flags)) {
      int val = get_byte(ea);
      char ch = ' ';
      if (val >= 0x20 && val <= 0x7E) {
         ch = val;
      }
      out_snprintf("%s %02xh   ; %c", ash.a_byte ? ash.a_byte : "", val, ch);
   }
   term_output_buffer();
   gl_comm = 1;
   MakeLine(obuf);
   return;
}

//--------------------------------------------------------------------------

bool idaapi cr16c_outop(op_t& x) 
{

	switch(x.type)
	{
		case o_reg:
			out_register(ph.regNames[x.reg]);
			break;
		case o_displ:
			OutValue(x,OOF_SIGNED|OOFW_32);
			break;
		case o_phrase:

			out_symbol('(');
			switch(x.specflag1)
			{
				default:
				case PAR_ind_reg:
					out_register(ph.regNames[x.reg]);
					break;
				case PAR_ind_rp:
					out_register(ph.regNames[x.reg+16]);
					break;
/*				case PAR_ind_prp:
					out_register(ph.regNames[x.reg+16]);
					break;*/
				case PAR_ind_rrp:
					out_register(ph.regNames[x.reg+32]);
					break;
			}

			out_symbol(')');
			break;
		case o_mem:
			OutValue(x,OOF_SIGNED|OOFW_32);
			break;
		case o_imm:
			out_symbol('$');
			OutValue(x,OOF_SIGNED|OOFW_32);
			break;
		case o_idpspec0:
			 out_symbol('[');

			if(x.specval&0x4)
				OutChar('d');

			if((x.specval&0x4)&&((x.specval&0x2)||(x.specval&0x1)))
				out_symbol(',');

			if(x.specval&0x2)
				OutChar('i');

			if((x.specval&0x2)&&(x.specval&0x1))
				out_symbol(',');

			if(x.specval&0x1)
				OutChar('u');

			out_symbol(']');
			break;

		default:;
	}
	//out_name_expr(x, x.addr, x.addr);

/*   if (cmd.itype == COMPARE_OP) 
   {
      //For comparisons, the argument indicates the type of comparison to be
      //performed.  Print a symbolic representation of the comparison rather
      //than a number.
      if (x.value < qnumber(compare_ops)) 
	  {
         OutLine(compare_ops[x.value]);
      }
      else 
	  {
         OutLine("BAD OPERAND");
      }
   }
   else if (cmd.auxpref & HAS_JREL) 
   {
      //we don't test for x.type == o_near here because we need to distinguish
      //between relative jumps and absolute jumps.  In our case, HAS_JREL 
      //implies o_near
      out_name_expr(x, x.addr, x.addr);
   }
   else 
   {  //otherwise just print the operand value
      OutValue(x);
   }*/
   return true;
}

