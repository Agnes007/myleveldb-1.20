/*
 * cephconn.h
 *
 *  Created on: Jan 3, 2018
 *      Author: ceph01
 */

//#ifndef STORAGE_LEVELDB_DB_DB_IMPL_H_
//#define STORAGE_LEVELDB_DB_DB_IMPL_H_

#include <iostream>
#include <string>
#include <rados/librados.hpp>

#include "leveldb/db.h"
#include "leveldb/env.h"

namespace leveldb {

class cepher {
public:
	
	void ceph_conn();
	void ceph_write(const char* key, const char* val);
	void ceph_read(const char* key);
	void ceph_remove(const char* key);
	void ceph_close();
private:
	int ret;
	librados::Rados cluster;
	librados::IoCtx io_ctx;
	const char *pool_name;
};
	
}

//#endif /* STORAGE_LEVELDB_DB_DB_IMPL_H_*/
