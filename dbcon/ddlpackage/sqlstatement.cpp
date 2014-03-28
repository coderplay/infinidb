/* Copyright (C) 2013 Calpont Corp.

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License
   as published by the Free Software Foundation; version 2 of
   the License.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
   MA 02110-1301, USA. */

/***********************************************************************
*   $Id: sqlstatement.cpp 9210 2013-01-21 14:10:42Z rdempsey $
*
*
***********************************************************************/

#define DDLPKG_DLLEXPORT
#include "ddlpkg.h"
#undef DDLPKG_DLLEXPORT

namespace ddlpackage {
	using namespace std;
	
	static u_int32_t sessionID = 1;
	
	SqlStatement::SqlStatement()
	{
		fSessionID = sessionID;
	}
	
	SqlStatement::~SqlStatement()
	{
	}

	ostream& operator<<(ostream &os, const SqlStatement& stmt)
	{
		return stmt.put(os);
	}
}
