/*
 * cephconn.cpp
 *
 *  Created on: Jan 3, 2018
 *      Author: ceph01
 */

#include "cepher.h"
#include <iostream>

namespace leveldb {

void cepher::ceph_conn() {
	// TODO Auto-generated constructor stub
	ret = 0;
	/* Declare the cluster handle and required variables. */
	// librados::Rados cluster;
	char cluster_name[] = "ceph";
	char user_name[] = "client.admin";
	uint64_t flags;

	/* Initialize the cluster handle with the "ceph" cluster name and "client.admin" user */
	{
		ret = cluster.init2(user_name, cluster_name, flags);
		if (ret < 0) {
			std::cerr << "Couldn't initialize the cluster handle! error " << ret
					<< std::endl;
			ret = EXIT_FAILURE;
			//return 1;
		} /*else {
		 std::cout << "Created a cluster handle." << std::endl;
		 }*/
	}

	/* Read a Ceph configuration file to configure the cluster handle. */
	{
		ret = cluster.conf_read_file("/etc/ceph/ceph.conf");
		if (ret < 0) {
			std::cerr << "Couldn't read the Ceph configuration file! error "
					<< ret << std::endl;
			ret = EXIT_FAILURE;
			//return 1;
		} /*else {
		 std::cout << "Read the Ceph configuration file." << std::endl;
		 }*/
	}

	/* Connect to the cluster */
	{
		ret = cluster.connect();
		if (ret < 0) {
			std::cerr << "Couldn't connect to cluster! error " << ret
					<< std::endl;
			ret = EXIT_FAILURE;
			//return 1;
		} else {
			std::cout << "Connected to the cluster." << std::endl;
		}
	}

	//librados::IoCtx io_ctx;
	pool_name = "test0116";

	{
		ret = cluster.ioctx_create(pool_name, io_ctx);
		if (ret < 0) {
			std::cerr << "Couldn't set up ioctx! error " << ret << std::endl;
			exit(EXIT_FAILURE);
		}/* else {
		 std::cout << "Created an ioctx for the pool." << std::endl;
		 }*/
	}
}

/* Continued from previous C++ example, where cluster handle and
 * connection are established. First declare an I/O Context.
 */

void cepher::ceph_write(const char* key, const char* val) {
	/* Write an object synchronously.*/
	{
		librados::bufferlist bl;
		bl.append(val, 20);
		ret = io_ctx.write_full(key, bl);
		if (ret < 0) {
			std::cerr << "Couldn't write object! error " << ret << std::endl;
			exit(EXIT_FAILURE);
		} /*else {
			std::cout << "Ceph wrote new object " << key << std::endl;
		}*/
	}
}

/*
 * Add an xattr to the object.

 {
 librados::bufferlist lang_bl;
 lang_bl.append("en_US");
 ret = io_ctx.setxattr("hw", "lang", lang_bl);
 if (ret < 0) {
 std::cerr << "failed to set xattr version entry! error "
 << ret << std::endl;
 exit(EXIT_FAILURE);
 } else {
 std::cout << "Set the xattr 'lang' on our object!" << std::endl;
 }
 }*/

void cepher::ceph_read(const char* key) {
	/*
	 * Read the object back asynchronously.*/

	librados::bufferlist read_buf;
	int read_len = 4194304;

	//Create I/O Completion.
	librados::AioCompletion *read_completion =
			librados::Rados::aio_create_completion();

	//Send read request.
	ret = io_ctx.aio_read(key, read_completion, &read_buf, read_len, 0);
	if (ret < 0) {
		std::cerr << "Couldn't start read object! error " << ret << std::endl;
		exit(EXIT_FAILURE);
	}

	// Wait for the request to complete, and check that it succeeded.
	read_completion->wait_for_complete();
	ret = read_completion->get_return_value();
	if (ret < 0) {
		std::cerr << "Couldn't read object! error " << ret << std::endl;
		exit(EXIT_FAILURE);
	} /*else {
		std::cout << "Ceph read object " << key
				<< " asynchronously with contents.\n" << "key: " << key
				<< "  val: " << read_buf.c_str() << std::endl;
	}*/

}

/*
 * Read the xattr.

 {
 librados::bufferlist lang_res;
 ret = io_ctx.getxattr("hw", "lang", lang_res);
 if (ret < 0) {
 std::cerr << "failed to get xattr version entry! error "
 << ret << std::endl;
 exit(EXIT_FAILURE);
 } else {
 std::cout << "Got the xattr 'lang' from object hw!"
 << lang_res.c_str() << std::endl;
 }
 }*/

/*
 * Remove the xattr.

 {
 ret = io_ctx.rmxattr("hw", "lang");
 if (ret < 0) {
 std::cerr << "Failed to remove xattr! error "
 << ret << std::endl;
 exit(EXIT_FAILURE);
 } else {
 std::cout << "Removed the xattr 'lang' from our object!" << std::endl;
 }
 }*/
void cepher::ceph_remove(const char* key) {
	/*
	 * Remove the object.*/

	{
		ret = io_ctx.remove(key);
		if (ret < 0) {
			std::cerr << "Couldn't remove object! error " << ret << std::endl;
			exit(EXIT_FAILURE);
		} else {
			std::cout << "Removed object " << key << std::endl;
		}
	}
}
void cepher::ceph_close() {
	io_ctx.close();
	cluster.shutdown();
	std::cout << "Ceph shutdown" << std::endl;
	//return 0;
}

}  // namespace leveldb

