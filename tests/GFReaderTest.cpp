/*************************************************************************
** GFReaderTest.cpp                                                     **
**                                                                      **
** This file is part of dvisvgm -- the DVI to SVG converter             **
** Copyright (C) 2005-2012 Martin Gieseking <martin.gieseking@uos.de>   **
**                                                                      **
** This program is free software; you can redistribute it and/or        **
** modify it under the terms of the GNU General Public License as       **
** published by the Free Software Foundation; either version 3 of       **
** the License, or (at your option) any later version.                  **
**                                                                      **
** This program is distributed in the hope that it will be useful, but  **
** WITHOUT ANY WARRANTY; without even the implied warranty of           **
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the         **
** GNU General Public License for more details.                         **
**                                                                      **
** You should have received a copy of the GNU General Public License    **
** along with this program; if not, see <http://www.gnu.org/licenses/>. **
*************************************************************************/

#include <gtest/gtest.h>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include "GFReader.h"
#include "macros.h"

#ifndef SRCDIR
#define SRCDIR "."
#endif

using namespace std;


struct PixelActions : public Bitmap::ForAllData
{
	void pixel (int x, int y, bool set, const Bitmap &bm) {
		if (charmap.size() == 0) {
			charmap.resize(bm.height());
			for (int i=0; i < bm.height(); i++)
				charmap[i] = string(bm.width(), ' ');
		}
		ASSERT_GE(x, 0);
		ASSERT_LT(x, bm.width());
		ASSERT_GE(y, 0);
		ASSERT_LT(y, bm.height());
		charmap[y][x] = (set ? '*' : '-');
	}

	vector<string> charmap;
};


const char *letter_a[] = {
	"-----------********--------------------",
	"--------**************-----------------",
	"------*****-------******---------------",
	"-----***------------*****--------------",
	"----*****------------******------------",
	"---*******------------******-----------",
	"---********-----------******-----------",
	"---********------------******----------",
	"---********------------******----------",
	"---********-------------******---------",
	"----******--------------******---------",
	"-----****---------------******---------",
	"------------------------******---------",
	"------------------------******---------",
	"------------------------******---------",
	"------------------------******---------",
	"-----------------*************---------",
	"-------------*****************---------",
	"----------*********-----******---------",
	"--------*******---------******---------",
	"------*******-----------******---------",
	"----********------------******---------",
	"---*******--------------******---------",
	"--********--------------******---------",
	"-********---------------******---------",
	"-*******----------------******---------",
	"-*******----------------******------**-",
	"*******-----------------******------**-",
	"*******-----------------******------**-",
	"*******-----------------******------**-",
	"*******----------------*******------**-",
	"*******----------------*******------**-",
	"********--------------********------**-",
	"-*******-------------***-*****------**-",
	"-********------------**---*****----**--",
	"--********---------****---*****----**--",
	"----*******------****------*********---",
	"------**************--------*******----",
	"---------********------------*****-----",
};


const char *letter_g[] = {
	"------------------------------******---",
	"------------********--------*********--",
	"----------************----****----****-",
	"--------*****------*****-***-----*****-",
	"-------*****--------*******------*****-",
	"------*****----------*****-------*****-",
	"-----*****------------*****--------*---",
	"----******------------******-----------",
	"----******------------******-----------",
	"---******--------------******----------",
	"---******--------------******----------",
	"---******--------------******----------",
	"---******--------------******----------",
	"---******--------------******----------",
	"---******--------------******----------",
	"---******--------------******----------",
	"---******--------------******----------",
	"----******------------******-----------",
	"----******------------******-----------",
	"-----*****------------*****------------",
	"------*****----------*****-------------",
	"------******--------*****--------------",
	"------*******------*****---------------",
	"-----***--************-----------------",
	"-----**-----********-------------------",
	"----***--------------------------------",
	"----***--------------------------------",
	"----***--------------------------------",
	"----***--------------------------------",
	"----****-------------------------------",
	"----****-------------------------------",
	"----******-----------------------------",
	"-----*********************-------------",
	"-----************************----------",
	"------*************************--------",
	"-------**************************------",
	"------****************************-----",
	"----*****----------------**********----",
	"---*****--------------------********---",
	"--*****-----------------------******---",
	"-*****-------------------------*****---",
	"-*****-------------------------******--",
	"*****---------------------------*****--",
	"*****---------------------------*****--",
	"*****---------------------------*****--",
	"*****---------------------------*****--",
	"*****---------------------------*****--",
	"******-------------------------******--",
	"-*****-------------------------*****---",
	"--*****-----------------------*****----",
	"--******---------------------******----",
	"----*****-------------------*****------",
	"-----******---------------******-------",
	"-------*******---------*******---------",
	"---------*******************-----------",
	"-------------***********---------------",
};


const char *letter_M[] = {
	"****************-------------------------------------****************-",
	"*****************-----------------------------------*****************-",
	"*****************-----------------------------------*****************-",
	"-------**********-----------------------------------**********--------",
	"--------**-*******---------------------------------**-*******---------",
	"--------**-*******---------------------------------**-*******---------",
	"--------**--*******-------------------------------**--*******---------",
	"--------**--*******-------------------------------**--*******---------",
	"--------**--*******-------------------------------**--*******---------",
	"--------**---*******-----------------------------**---*******---------",
	"--------**---*******-----------------------------**---*******---------",
	"--------**---*******-----------------------------**---*******---------",
	"--------**----*******---------------------------**----*******---------",
	"--------**----*******---------------------------**----*******---------",
	"--------**-----*******-------------------------**-----*******---------",
	"--------**-----*******-------------------------**-----*******---------",
	"--------**-----*******-------------------------**-----*******---------",
	"--------**------*******-----------------------**------*******---------",
	"--------**------*******-----------------------**------*******---------",
	"--------**-------*******---------------------**-------*******---------",
	"--------**-------*******---------------------**-------*******---------",
	"--------**-------*******---------------------**-------*******---------",
	"--------**--------*******-------------------**--------*******---------",
	"--------**--------*******-------------------**--------*******---------",
	"--------**--------*******-------------------**--------*******---------",
	"--------**---------*******-----------------**---------*******---------",
	"--------**---------*******-----------------**---------*******---------",
	"--------**----------*******---------------**----------*******---------",
	"--------**----------*******---------------**----------*******---------",
	"--------**----------*******---------------**----------*******---------",
	"--------**-----------*******-------------**-----------*******---------",
	"--------**-----------*******-------------**-----------*******---------",
	"--------**------------*******-----------**------------*******---------",
	"--------**------------*******-----------**------------*******---------",
	"--------**------------*******-----------**------------*******---------",
	"--------**-------------*******---------**-------------*******---------",
	"--------**-------------*******---------**-------------*******---------",
	"--------**-------------*******---------**-------------*******---------",
	"--------**--------------*******-------**--------------*******---------",
	"--------**--------------*******-------**--------------*******---------",
	"--------**---------------*******-----**---------------*******---------",
	"--------**---------------*******-----**---------------*******---------",
	"--------**---------------*******-----**---------------*******---------",
	"--------**----------------*******---**----------------*******---------",
	"--------**----------------*******---**----------------*******---------",
	"--------**-----------------*******-**-----------------*******---------",
	"--------**-----------------*******-**-----------------*******---------",
	"--------**-----------------*******-**-----------------*******---------",
	"--------**------------------********------------------*******---------",
	"--------**------------------********------------------*******---------",
	"--------**------------------********------------------*******---------",
	"-------****------------------******-------------------*******---------",
	"------******-----------------******-------------------*******---------",
	"----**********----------------****-------------------*********--------",
	"******************------------****------------***********************-",
	"******************------------****------------***********************-",
	"******************-------------**-------------***********************-",
};


static void check_letter (const char **lettermap, const vector<string> &charmap) {
	for (size_t i=0; i < charmap.size(); i++)
		ASSERT_EQ(lettermap[i], charmap[charmap.size()-i-1]);
}


TEST(GFReaderTest, executeChar) {
	string gf = string(SRCDIR)+"/cmr10.600gf";
	ifstream ifs(gf.c_str(), ios::binary);
	ASSERT_TRUE(ifs);
	GFReader gfReader(ifs);
	PixelActions actions;

	gfReader.executeChar('a');
	ASSERT_EQ(gfReader.getBitmap().width(), 39);
	ASSERT_EQ(gfReader.getBitmap().height(), 39);
	gfReader.getBitmap().forAllPixels(actions);
	check_letter(letter_a, actions.charmap);

	actions.charmap.clear();
	gfReader.executeChar('g');
	ASSERT_EQ(gfReader.getBitmap().width(), 39);
	ASSERT_EQ(gfReader.getBitmap().height(), 56);
	gfReader.getBitmap().forAllPixels(actions);
	check_letter(letter_g, actions.charmap);

	actions.charmap.clear();
	gfReader.executeChar('M');
	ASSERT_EQ(gfReader.getBitmap().width(), 70);
	ASSERT_EQ(gfReader.getBitmap().height(), 57);
	gfReader.getBitmap().forAllPixels(actions);
	check_letter(letter_M, actions.charmap);
}

