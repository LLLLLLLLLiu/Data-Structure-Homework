// abstract class bsTree
// abstract data type specification for binary search trees
// all methods are pure virtual functions
// K is key type and E is value type
#ifndef bsTree_
#define bsTree_

using namespace std;
template<class K, class E>
class bsTree{
public:
	virtual ~bsTree() {}
	virtual bool empty() const = 0;
	// return true iff dictionary is empty
	virtual int size() const = 0;
	// return number of pairs in dictionary
	virtual BinNodePosi(K, E) search(const K&) const = 0;
	// return pointer to matching pair
	virtual void remove(const K&) = 0;
	// remove matching pair
	virtual void insert(const pair<const K, E>&) = 0;
	// insert a (key, value) pair into the dictionary
	virtual void ascend() = 0;
	// output in ascending order of key
};
#endif
