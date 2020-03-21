#define _CRT_SECURE_NO_WARNINGS 1

//description：40亿个整形数据，快速查找摸个数据是否在集合中
//想到方法：1.直接遍历       慢+io次数多
//		2.排序+二分查找   慢 复杂度高
//		3.借助哈希       速度快 但数据不一定能全部放到哈希表中
//		4.使用位图       使用1个比特位来表示数据是否存在  ----最佳方式
//             其实使用的还是哈希的思想：直接定值法
//        方式：将40亿个整型数据映射到位图中，比如10  除8=1 模8=2 那么第一个字节的第二个比特位如果是1 那么就表示10存在，0表示不存在
//      问题：如果将40亿的整形数据加载到内存中需要多大空间      14g  然而一个内存只有4g的大小 
//           如果将40亿的整形数据使用位图映射，需要多大空间    
//                int类型能表示的总个数 2^32 那么所需的比特位也是2^32  2^32/8/1024/1024 m
//           位图使用，先计算该数在哪个字节--除8 在计算在该字节的那个比特位--模8
//     查找，将该数除8--字节 模8-位数 看该位是0还是1



#include "BitSetTest.hpp"
#include "BitSetAccomplish.h"
int main(){
	//TestBitSet();
	Test();
	system("pause");
	return 0;
}


//位图的其他题目
//1.给定100亿个数据，设计算法找到只出现一次的整数
//   用两个比特位表示某个数的个数：00表示数据不存在  01表示数据只出现1次 10表示数据出现多次  11--不用
//   需要多大空间存储？int可以表达的数2^32/4B
//   确定位置index=除4 pos=模4*2  00置01 01置10 
//   检测，若是01，表示该数据出现了1次  再确定原来的数为index*4+pos/2
//2.给定100亿个数据，设计算法找到不超过2个的整数
//       同1 用两个比特位表示某个数的个数：00表示数据不存在  01表示数据只出现1次 10表示数据出现两次  11--多次
//       那么找不超过n个的整数呢？  用足够多个比特位去表达状态即可，过程一样

//3.两个文件中，分别有100亿个数，只有1g内存，如何找两个文件的交集（并集）？
//     a.将两个文件中的数据分别映射到两个位图中 需要512m*2空间
//     b.将两个位图对应的字节&（|）
//     c.检测&（|）完后的结果，为1的比特位对应的数据就是两个文件的交集（并集）


//总结：哪里可以用上位图的？ 
//   查找：集合映射+判断 
//   排序（无重复数字）：映射+从小到大的重新回收
//   找两个集合的交集：将两个集合映射+每个字节相与
//   找两个集合的并集：将两个集合映射+每个字节相或
//   操作系统中磁盘标记：块空位0，块不空为1