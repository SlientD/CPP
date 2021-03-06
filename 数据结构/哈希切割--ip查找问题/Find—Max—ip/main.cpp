#define _CRT_SECURE_NO_WARNINGS 1


//题一：哈希切割
//description：文件大小100G，存储的是ip地址，找出现最多的前K个IP地址
//统计ip地址出现次数
//Case1：不考虑文件大小
//       w1.直接遍历，取一个ip地址，遍历文件检测ip出现次数
//       w2.对文件中ip地址排序，遍历一遍可统计所有
//       w3.unodered_map统计

//Case2:考虑文件大小：上面的方法因为会多次读取磁盘会被pass,也存不下那么多数据
//      w1.外部排序：归并排序，磁盘IO也很多，操作复杂
//      w2.不将所有的ip地址以及次数放到一个unodered_map
//         假设先用一个unordered_map统计，如果空间不够，可将该UNordered_map中的统计结果保存到后面文件，在统计后续结果
//         缺陷：相同的ip地址在文件中出现的可能比较离散，不能够一次性统计出相同ip的总次数 

//一般解决方法：将大规模的问题转化为小问题---对文件进行分割
//如何分割：
//w1.平均分割：分成100份，每份1G,然后对每个小文件中的ip地址采用unordered_map来进行统计
//       ---思想和Case2 w2 一样，也面临着这同样的问题，即相同ip分散的比较离散
//w2.最好的分割方式：能够让相同的ip地址放到同一个文件中
//                ----即哈希分割:让ip和页数建立关系，这样相同ip离得就很近了
//   S1:由于ip地址很大，所以我们每页不保存ip地址，我们保存一个与ip对应的整形数据
//        如何将ip地址转化为一个整形数据呢？并且这个转换还得是可逆的（网络中有api可以实现）
//   S2:然后用转化后的整型数据%文件份数-->该ip地址所在的文件编号-->最终想文件中放ip地址对应的整形数据  （借助多线程来进行分配，每个线程从固定的位置开始读取ip进行哈希，比如一个线程哈希1G的文件）
//   S3:相同的ip地址已经在同一个文件中，针对每个文件采用unordered_map来进行统计，就可以得到文件中ip地址出现的总次数
//   S4:会得到该文件中出现次数最多的ip地址，按照类似的方式处理后序文件  
//   注：这个方法可能会存在大量ip地址计算出来的页数为同一页----解决方法：扩容（增加文件份数）重新散列


//统计好次数后，我们要做的就是开始找TOP K  利用多线程对每个文件统计
//方法：利用priority_queue来找出现次数前k个ip
//     面临的问题：1.创建大堆还是小堆？ -->最多小堆 --》最少大堆 
//               2.堆中保存多少个元素？-->k个  
//               3.堆中元素如何比较？  --->保存的是pair<ip,次数>，所以我们要在构造一个比较器
//如何直接用Linux系统命令实现？？


