# STL

## STL中unordered_map(hash_map)和map的区别

- map中的元素是按照二叉搜索树存储，进行中序遍历会得到有序遍历。需要定义operator<
- unordered_map不会根据key的大小进行排序，存储时是根据key的hash值判断元素是否相同，即unordered_map内部元素是无序的。需要定义hash_value函数并且重载operator==

hash_map底层使用的是hash_table，而hash_table使用的开链法进行冲突避免，所有hash_map采用开链法进行冲突解决。

当向容器添加元素的时候，会判断当前容器的元素个数，如果大于等于阈值—即当前数组的长度乘以加载因子的值的时候，就要自动扩容啦。 