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
*   $Id: returnedcolumn.cpp 9413 2013-04-22 22:03:42Z zzhu $
*
*
***********************************************************************/

#include <iostream>
#include <string>

#include "bytestream.h"
#include "returnedcolumn.h"
#include "objectreader.h"

using namespace std;
using namespace messageqcpp;

namespace execplan
{
/**
 * Constructors/Destructors
 */
ReturnedColumn::ReturnedColumn(): fReturnAll (false),
                                  fSessionID(0),
                                  fSequence(-1),
                                  fCardinality(0),
                                  fDistinct(false),
                                  fJoinInfo(0),
                                  fAsc(true),
                                  fNullsFirst(true),
                                  fOrderPos((uint64_t)-1),
                                  fColSource(0),
                                  fColPosition(-1),
                                  fInputIndex(-1),
                                  fOutputIndex(-1),
                                  fExpressionId ((uint)-1)
{
}

ReturnedColumn::ReturnedColumn(const string& sql):
    fReturnAll (false),
    fSessionID(0),
    fSequence(-1),
    fCardinality(0),
    fDistinct(false),
    fJoinInfo(0),
    fAsc(true),
    fNullsFirst(true),
    fOrderPos((uint64_t)-1),
    fColSource(0),
    fColPosition(-1),
    fData(sql),
    fInputIndex(-1),
    fOutputIndex(-1),
    fExpressionId ((uint)-1)
{
}

ReturnedColumn::ReturnedColumn(const u_int32_t sessionID, const bool returnAll):
                                  fReturnAll(returnAll),
                                  fSessionID(sessionID),
                                  fSequence(-1),
                                  fCardinality(0),
                                  fDistinct(false),
                                  fJoinInfo(0),
                                  fAsc(true),
                                  fNullsFirst(true),
                                  fOrderPos((uint64_t)-1),
                                  fColSource(0),
                                  fColPosition(-1),
                                  fInputIndex(-1),
                                  fOutputIndex(-1),
                                  fExpressionId ((uint)-1)
{
}

ReturnedColumn::ReturnedColumn(const ReturnedColumn& rhs, const u_int32_t sessionID):
	TreeNode(rhs),
	fReturnAll(rhs.fReturnAll),
	fSessionID(sessionID),
	fSequence(rhs.fSequence),
	fCardinality(rhs.fCardinality),
	fDistinct(rhs.fDistinct),
	fJoinInfo(rhs.fJoinInfo),
	fAsc(rhs.fAsc),
	fNullsFirst(rhs.fNullsFirst),
	fOrderPos(rhs.fOrderPos),
	fColSource(rhs.fColSource),
	fColPosition(rhs.fColPosition),
	fData(rhs.fData),
	fInputIndex(rhs.fInputIndex),
	fOutputIndex(rhs.fOutputIndex),
	fExpressionId (rhs.fExpressionId)
{
}

ReturnedColumn::~ReturnedColumn()
{
}

/**
 * ostream function
 */
ostream& operator<<(ostream &output, const ReturnedColumn &retCol)
{
	output << retCol.toString() << endl;
	return output;
}

void ReturnedColumn::serialize(messageqcpp::ByteStream& b) const
{
	b << (ObjectReader::id_t) ObjectReader::RETURNEDCOLUMN;
	b << fData;
	b << (uint64_t) fCardinality;
	b << fAlias;
	b << (uint8_t)fDistinct;
	b << (uint64_t)fJoinInfo;
	b << (uint8_t)fAsc;
	b << (uint8_t)fNullsFirst;
	b << (uint64_t)fOrderPos;
	b << (uint64_t)fColSource;
	b << (uint64_t)fColPosition;
	b << (uint32_t)fInputIndex;
	b << (uint32_t)fOutputIndex;
	b << (uint32_t)fSequence;
	fResultType.serialize(b);
	fOperationType.serialize(b);
	b << (uint32_t)fExpressionId;
}

void ReturnedColumn::unserialize(messageqcpp::ByteStream& b)
{
	ObjectReader::checkType(b, ObjectReader::RETURNEDCOLUMN);
	b >> fData;
	b >> (uint64_t&)fCardinality;
	b >> fAlias;
	b >> (uint8_t&)fDistinct;
	b >> (uint64_t&)fJoinInfo;
	b >> (uint8_t&)fAsc;
	b >> (uint8_t&)fNullsFirst;
	b >> (uint64_t&)fOrderPos;
	b >> (uint64_t&)fColSource;
	b >> (uint64_t&)fColPosition;
	b >> (uint32_t&)fInputIndex;
	b >> (uint32_t&)fOutputIndex;
	b >> (uint32_t&)fSequence;
	fResultType.unserialize(b);
	fOperationType.unserialize(b);
	b >> (uint32_t&)fExpressionId;
}

bool ReturnedColumn::operator==(const ReturnedColumn& t) const
{
	if (fData != t.fData)
		return false;
	if (fCardinality != t.fCardinality)
		return false;
	//if (fAlias != t.fAlias)
	//	return false;
	if (fDistinct != t.fDistinct)
		return false;
	if (fJoinInfo != t.fJoinInfo)
		return false;
	if (fAsc != t.fAsc)
		return false;
	if (fNullsFirst != t.fNullsFirst)
		return false;
	//if (fOrderPos != t.fOrderPos)
	//	return false;
	if (fInputIndex != t.fInputIndex)
		return false;
	if (fOutputIndex != t.fOutputIndex)
		return false;
	//if (fSequence != t.fSequence)
	//	return false;
	if (fResultType != t.fResultType)
		return false;
	if (fOperationType != t.fOperationType)
		return false;
	//if (fExpressionId != t.fExpressionId)
	//	return false;
	return true;
}

bool ReturnedColumn::operator==(const TreeNode* t) const
{
	const ReturnedColumn *rc;
	
	rc = dynamic_cast<const ReturnedColumn*>(t);
	if (rc == NULL)
		return false;
	return *this == *rc;
}

bool ReturnedColumn::operator!=(const ReturnedColumn& t) const
{
	return !(*this == t);
}

bool ReturnedColumn::operator!=(const TreeNode* t) const
{
	return !(*this == t);
}

const string ReturnedColumn::data() const
{
	return fData;
}

const string ReturnedColumn::toString() const
{
	return string(">ReturnedColumn<");
}

} // namespace execplan
