#define _CRT_SECURE_NO_WARNINGS 1
#include "hash.hpp"
#include "hashBuckt.hpp"
#include "common.hpp"
#include "unOrderedMap.hpp"
#include "unOrderedSet.hpp"
void TestHashTable(){

	HashTable<int> hash;

	cout << hash.size() << endl;
	hash.Insert(87);
	cout << hash.size() << endl;
	hash.Erase(44);
	cout << hash.size() << endl;
}
void TestStringTable(){
	vector<string> arr{ "abc", "abc", "def", "cba" };
	HashTable<string, DFStr> hash;
}

void TestHashBucket(){
	HashBucket<int> hash;
	hash.InsertUnique(2);
	hash.InsertUnique(1);
	hash.InsertUnique(4);
	hash.InsertUnique(13);
	hash.InsertRepeate(13);
	hash.InsertRepeate(13);
	hash.InsertRepeate(13);
	hash.InsertRepeate(13);
	hash.InsertRepeate(13);
	hash.InsertRepeate(13);
	hash.InsertRepeate(13);
	hash.HashBucketPrint();

	hash.InsertRepeate(8);
	hash.HashBucketPrint();

	hash.HashBucketPrint();
	hash.InsertUnique(4);
	hash.HashBucketPrint();
	hash.InsertRepeate(13);
	hash.HashBucketPrint();
	hash.EraseAll(13);
	hash.HashBucketPrint();
	auto p=hash.find(4);
	int cur = p._pNode->_data;
	cout << cur << endl;

	HashBucket<int> hash2;
	hash2.swap(hash);
	hash.HashBucketPrint();
}



int main(){
	//TestHashTable();
	//TestStringTable();
	//TestHashBucket();
	//TestMyUnordered_map();
	TestMyUnordered_set();
	system("pause");
	return 0;
}