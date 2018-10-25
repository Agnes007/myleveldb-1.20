#include <assert.h>
#include <string.h>
#include <iostream>
#include <leveldb/db.h>
#include <rados/librados.hpp>
#include "db/cepher.h"


using namespace std;

int main(){
	leveldb::DB* db;
	leveldb::Options options;
	options.create_if_missing = true;
	leveldb::Status status = leveldb::DB::Open(options,"tmp/testdb", &db);
	assert(status.ok());
	std::cout<<"***************************"<<std::endl;
	cout<<"open db ok."<<endl;

	std::string key1="hyf";
	std::string value1="hyf@gmail.com";
	cout<<key1<<endl;
	cout<<value1<<endl;
	std::string key2="ag";
	std::string value2="ag@gmail.com";

	string value;
	leveldb::Status s;
	s=db->Put(leveldb::WriteOptions(),key1,value1);
	s=db->Put(leveldb::WriteOptions(),key2,value2);

	s=db->Get(leveldb::ReadOptions(),key1,&value);
	cout<<value<<endl;

	s=db->Get(leveldb::ReadOptions(),key2,&value);
	cout<<value<<endl;
	delete db;
	return 0;
}
