/*-------------------------------------------------------------------------
 *
 * o_indices.h
 * 		Declarations for orioledb indices system tree.
 *
 * Copyright (c) 2021-2022, Oriole DB Inc.
 *
 * IDENTIFICATION
 *	  contrib/orioledb/include/catalog/o_indices.h
 *
 *-------------------------------------------------------------------------
 */
#ifndef __O_INDICES_H__
#define __O_INDICES_H__

#include "orioledb.h"

#include "catalog/o_tables.h"
#include "tuple/format.h"

typedef struct
{
	ORelOids	indexOids;
	OIndexType	indexType;
	ORelOids	tableOids;
	OXid		createOxid;
	NameData	name;
	bool		primaryIsCtid;
	OCompress	compress;
	uint16		nLeafFields;
	uint16		nNonLeafFields;
	uint16		nUniqueFields;
	uint16		nKeyFields;
	uint16		nPrimaryFields;
	AttrNumber	primaryFieldsAttnums[INDEX_MAX_KEYS];
	OTableField *leafFields;
	OTableIndexField *nonLeafFields;
	List	   *predicate;		/* list of Expr */
	char	   *predicate_str;
	List	   *expressions;	/* list of Expr */
	MemoryContext index_mctx;
} OIndex;

/* callback for o_indices_foreach_oids() */
typedef void (*OIndexOidsCallback) (OIndexType type, ORelOids treeOids, ORelOids tableOids, void *arg);

extern OIndex *make_o_index(OTable *table, OIndexNumber ixNum);
extern void o_index_fill_descr(OIndexDescr *descr, OIndex *oIndex);
extern void free_o_index(OIndex *o_index);
extern bool o_indices_add(OTable *table, OIndexNumber ixNum, OXid oxid,
						  CommitSeqNo csn);
extern bool o_indices_del(OTable *table, OIndexNumber ixNum, OXid oxid,
						  CommitSeqNo csn);
extern OIndex *o_indices_get(ORelOids oids, OIndexType type);
extern bool o_indices_update(OTable *table, OIndexNumber ixNum,
							 OXid oxid, CommitSeqNo csn);
extern bool o_indices_find_table_oids(ORelOids indexOids, OIndexType type,
									  CommitSeqNo csn, ORelOids *tableOids);
extern void o_indices_foreach_oids(OIndexOidsCallback callback, void *arg);

#endif
