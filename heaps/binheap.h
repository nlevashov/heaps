#include <list>

template <typename K, typename V>
class binheap {
	struct _node {
		K _key;
		V _value;
		std::list<_node *> _childs;
	};

	std::list<_node *> _roots;

public:
	binheap () {}
	binheap (const binheap & h);
	binheap & operator = (const binheap & h);

	std::pair<K, V> top () const;
	std::pair<K, V> pop ();
	void push (K key, V value);
	binheap & join (const binheap & h);
	binheap & operator += (const binheap & h);
	size_t size () const;

private:
	std::list<_node *> recursive_list_copy (const std::list<_node *> & old_list) const;
	typename std::list<_node *>::const_iterator find_min () const;
	typename std::list<_node *>::iterator find_min ();
	void balance ();
	void join_tree (
		typename std::list<_node *>::iterator tree1,
		typename std::list<_node *>::iterator tree2);
};


template <typename K, typename V>
binheap<K, V>::binheap (const binheap<K, V> & h)
{
	_roots = recursive_list_copy(h._roots);
}

template <typename K, typename V>
binheap<K, V> & binheap<K, V>::operator = (const binheap<K, V> & h)
{
	_roots = recursive_list_copy(h._roots);
}

template <typename K, typename V>
std::pair<K, V> binheap<K, V>::top () const
{
	if (_roots.size() == 0) {
		throw "Empty heap\n";
	} else {
		auto min = find_min();
		return std::pair<K, V> ((*min)->_key, (*min)->_value);
	}
}

template <typename K, typename V>
std::pair<K, V> binheap<K, V>::pop ()
{
	if (_roots.size() == 0) {
		throw "Empty heap\n";
	} else {
		auto min = find_min();
		std::pair<K, V> result((*min)->_key, (*min)->_value);

		binheap temp;
		temp._roots = (*min)->_childs;
		_roots.erase(min);
		join(temp);

		return result;
	}
}

template <typename K, typename V>
void binheap<K, V>::push (K key, V value)
{
	_node * n = new _node;
	n->_key = key;
	n->_value = value;

	_roots.push_front(n);
	balance();
}

template <typename K, typename V>
binheap<K, V> & binheap<K, V>::join (const binheap<K, V> & h)
{
	auto pos = _roots.begin();
	for (auto p : h._roots) {
		while ((pos != _roots.end()) && ((*pos)->_childs.size() <= p->_childs.size())) pos++;
		_roots.insert(pos, p);
	}
	balance();
	return *this;
}

template <typename K, typename V>
binheap<K, V> & binheap<K, V>::operator += (const binheap<K, V> & h)
{
	return join(h);
}

template <typename K, typename V>
size_t binheap<K, V>::size () const
{
	size_t sum = 0;
	for (auto p : _roots) sum += 1 << p->_childs.size();
	return sum;
}

//--private-functions-------------

template <typename K, typename V>
std::list<typename binheap<K, V>::_node *> binheap<K, V>::recursive_list_copy (const std::list<typename binheap<K, V>::_node *> & old_list) const
{
	std::list<_node *> new_list;
	for (auto p : old_list) {
		_node * n = new _node;
		n->_key = p->_key;
		n->_value = p->_value;
		n->_childs = recursive_list_copy(p->_childs);
		new_list.push_back(n);
	}
	return new_list;
}


template <typename K, typename V>
typename std::list<typename binheap<K, V>::_node *>::const_iterator binheap<K, V>::find_min () const
{
	typename std::list<_node *>::const_iterator min = _roots.begin();
	for (auto p = _roots.begin(); p != _roots.end(); ++p) {
		if ((*p)->_key < (*min)->_key) min = p;
	}
	return min;
}

template <typename K, typename V>
typename std::list<typename binheap<K, V>::_node *>::iterator binheap<K, V>::find_min ()
{
	typename std::list<_node *>::iterator min = _roots.begin();
	typename std::list<_node *>::iterator p = _roots.begin();
	for (size_t i = 0; i < _roots.size(); ++i) {
		if ((*p)->_key < (*min)->_key) min = p;
		++p;
	}
	return min;
}

template <typename K, typename V>
void binheap<K, V>::balance ()
{
	if (_roots.size() < 3) {
		if (_roots.size() == 2) {
			auto p2 = _roots.begin();
			auto p1 = p2++;
			if ((*p1)->_childs.size() == (*p2)->_childs.size()) join_tree(p1, p2);
		}
	} else {
		auto end = _roots.begin();
		++++end;
		while (end != _roots.end()) {
			auto p1 = end,
				 p3 = p1--,
				 p2 = p1--;
			++end;
			if ((*p2)->_childs.size() == (*p1)->_childs.size()) {
				if ((*p3)->_childs.size() == (*p1)->_childs.size()) join_tree(p2, p3);
				else join_tree(p1, p2);
			}
		}
		auto p2 = --end,
			 p1 = --end;
		if ((*p1)->_childs.size() == (*p2)->_childs.size()) join_tree(p1, p2);
	}
}

template <typename K, typename V>
void binheap<K, V>::join_tree (
	typename std::list<typename binheap<K, V>::_node *>::iterator tree1,
	typename std::list<typename binheap<K, V>::_node *>::iterator tree2)
{
	if ((*tree1)->_key < (*tree2)->_key) {
		(*tree1)->_childs.push_back(*tree2);
		_roots.erase(tree2);
	} else {
		(*tree2)->_childs.push_back(*tree1);
		_roots.erase(tree1);
	}
}
