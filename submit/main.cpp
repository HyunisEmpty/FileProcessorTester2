/*
* File Processing Report 2024 - Balanced Tree skeleton code in C/C++
*
* 본 Skeleton code는 구현에 도움을 주기 위해 작성된 코드입니다.
* ❗️본 Skeleton code는 과제의 요구 조건을 완전히 충족시키지 않을 수 있습니다.❗️
* ❗️최종 점수 산정은 과제 PDF에 명시된 요구 사항을 기준으로 이루어집니다.❗️
*
*/

#include <iostream>
#include <stack> // 해당 라이브러리 사용 여부 질문 해둔 상태

template <class _Tp, std::size_t M = 4> class Node;
template <class _Tp, std::size_t M = 4> class BT;

/*
* 아래는 반드시 사용해야하는 Node 클래스입니다.
* 멤버 변수는 추가, 삭제 및 변경이 불가능합니다.
*/
template <class _Tp, std::size_t M>
class Node {
private: // Member types
	typedef _Tp					__key_type;
	typedef Node<__key_type>* __node_pointer;
	typedef std::size_t			size_type;

public: // Member variables
	__key_type		__keys_[M - 1];     // 키는 M-1개
	__node_pointer	__children_[M];     // 자식 포인터 M개
	size_type		__size_;

public: // Constructor
	Node() : __size_(0) {                // 기본 생성자
		for (size_type i = 0; i < M; i++) {
			__children_[i] = nullptr;
		}
	}                                   // 키 하나를 받는 생성자
	Node(const __key_type& key) : Node() {
		__push_front(key, nullptr);
	}

public: // Modifier
	void __push_front(const __key_type& __key, const __node_pointer& __np) {
		__children_[__size_ + 1] = __children_[__size_];
		for (size_type __i = __size_; 0 < __i; --__i) {
			__keys_[__i] = __keys_[__i - 1];
			__children_[__i] = __children_[__i - 1];
		}
		__keys_[0] = __key;
		__children_[0] = __np;
		++size();
	}
	void __push_back(const __key_type& __key, const __node_pointer& __np) {
		__keys_[size()] = __key;
		__children_[size() + 1] = __np;
		++size();
	}
	__key_type __pop_front() {
		const __key_type __ret = __keys_[0];

		for (size_type __i = 0; __i < __size_ - 1; ++__i) {
			__keys_[__i] = __keys_[__i + 1];
			this->__children_[__i] = this->__children_[__i + 1];
		}
		this->__children_[__size_ - 1] = this->__children_[__size_];
		--size();

		return __ret;
	}
	__key_type __pop_back() { return __keys_[--size()]; }

public: // Capacity
	size_type& size() { return __size_; }
	const size_type& size() const { return __size_; }

	/*
	* 아래는 inorder traversal을 대체할 수 있는 operator<< 입니다.
	* 반드시 아래의 함수를 사용해야할 필요는 없습니다.
	*/
	friend std::ostream& operator<<(std::ostream& os, const __node_pointer& __np) {
		if (__np == nullptr || __np->size() == 0) {
			return os;
		}

		os << '<';
		os << __np->__children_[0] << ' ';
		for (std::size_t __i = 0; __i < __np->size() - 1; __i++) {
			os << __np->__keys_[__i] << ' ';
			if (__np->__children_[__i + 1] != nullptr) {
				os << __np->__children_[__i + 1] << ' ';
			}
		}
		os << __np->__keys_[__np->size() - 1] << ' ';
		os << __np->__children_[__np->size()];
		os << '>';

		return os;
	}
};

/*
* 아래 함수들의 설계 방식은 Tree와 Node의 구동부를 구현하기 위해 추천드리는 설계 방식입니다.
* 반드시 아래의 설계 방식을 따라야 하는 것은 아닙니다.
*/

/*
* PDF에 명시되어있는 출력 형식에 유의하세요.
* ❗️잘못된 출력 형식은 0점 처리됩니다.❗️
*/
template <class _NodePtr>
void __inorder(_NodePtr __x) {
	if (__x == nullptr || __x->size() == 0) {
		return;
	}

	std::cout << '<';
	std::cout << __x->__children_[0] << ' ';
	for (std::size_t __i = 0; __i < __x->size() - 1; __i++) {
		std::cout << __x->__keys_[__i] << ' ';
		if (__x->__children_[__i + 1] != nullptr) {
			std::cout << __x->__children_[__i + 1] << ' ';
		}
	}
	std::cout << __x->__keys_[__x->size() - 1] << ' ';
	std::cout << __x->__children_[__x->size()];
	std::cout << '>';

}

// Dangling pointer를 방지하기 위해 __x를 참조 타입으로 받도록 설계하였습니다.
template <class _NodePtr>
void __clear(_NodePtr& __x) {
	if (__x == nullptr) {
		return;
	}

	for (std::size_t __i = 0; __i <= __x->size(); __i++) {
		__clear(__x->__children_[__i]);
	}
	delete __x;
	__x = nullptr;
}

// searchPath 구현, stack을 받아와 원본을 수정하기에 반환하지 않습니다.
template <class _Tp, std::size_t M>
bool __searchPath(Node<_Tp, M>* __root, const _Tp& __key, std::stack<Node<_Tp, M>*>& __stack) {
	Node<_Tp, M>* __x = __root;

	while (__x != nullptr) {

		std::size_t i = 0;
		while (i < __x->size() && __key > __x->__keys_[i]) {  // i는 분기중 자식 노드의 포인터가 저장된 child의 인덱스를 가리킨다. 
			i++;
		}

		__stack.push(__x);  // stack에 경로 추가

		if (i < __x->size() && __key == __x->__keys_[i]) {  // 중복 키 인지 확인한다. 
			return true;
		}

		__x = __x->__children_[i];
	}

	// 중복키가 발견되지 않은 경우 false 반환
	return false;
}

// insertKey 구현
template <class _Tp, std::size_t M>
void __insertKey(Node<_Tp, M>* __x, Node<_Tp, M>* __y, const _Tp& __newKey) {
	int __i = __x->size() - 1;	// 마지막 인덱스 부터 탐색

	while (__i >= 0 && __newKey < __x->__keys_[__i]) {	// 값을 찾을때까지, 키와 포인터를 한칸씩 미룬다. 최종적으로 i + 1에 삽입하면 된다.
		__x->__keys_[__i + 1] = __x->__keys_[__i];
		__x->__children_[__i + 2] = __x->__children_[__i + 1];
		__i--;
	}

	// newKey >= __x -> __keys[i] 일때 끝나므로 i + 1에 삽입하면 된다. 
	__x->__keys_[__i + 1] = __newKey;
	__x->__children_[__i + 2] = __y;
	__x->size()++;
}

// splitNode 구현
template <class _Tp, std::size_t M>
std::pair<_Tp, Node<_Tp, M>*> __splitNode(Node<_Tp, M>* __x, Node<_Tp, M>* __y, const _Tp& __newKey)
{
	// M 기반 temporary 배열 생성
	_Tp tempKeys[M];
	Node<_Tp, M>* tempChildren[M + 1];

	int n = __x->size();

	// 기존 데이터 복사
	for (int i = 0; i < n; i++) tempKeys[i] = __x->__keys_[i];
	for (int i = 0; i <= n; i++) tempChildren[i] = __x->__children_[i];

	// newKey 삽입
	int i = n - 1;
	while (i >= 0 && __newKey < tempKeys[i]) {
		tempKeys[i + 1] = tempKeys[i];
		tempChildren[i + 2] = tempChildren[i + 1];
		i--;
	}
	tempKeys[i + 1] = __newKey;
	tempChildren[i + 2] = __y;
	n++;

	// 중앙값 계산
	int mid = n / 2;
	_Tp centerKey = tempKeys[mid];

	// 왼쪽 노드 생성
	__x->size() = 0;
	for (int j = 0; j < mid; j++) {
		__x->__keys_[j] = tempKeys[j];
		__x->__children_[j] = tempChildren[j];
		__x->size()++;
	}
	__x->__children_[mid] = tempChildren[mid];

	// 오른쪽 노드 생성
	Node<_Tp, M>* right = new Node<_Tp, M>();
	int idx = 0;
	for (int j = mid + 1; j < n; j++) {
		right->__keys_[idx] = tempKeys[j];
		right->__children_[idx] = tempChildren[j];
		right->size()++;
		idx++;
	}
	right->__children_[idx] = tempChildren[n];

	return { centerKey, right };
}

// insertBT 구현
template <class _Tp, std::size_t M>
std::pair<Node<_Tp, M>*, bool> __insertBT(Node<_Tp, M>*& __root, const _Tp& __key) {

	// 트리가 비어있는 경우 (새 루트 생성)
	if (__root == nullptr) {
		__root = new Node<_Tp, M>(__key);
		return std::make_pair(__root, true);
	}

	std::stack<Node<_Tp, M>*> __stack;		// 경로 저장용 스택
	bool found = __searchPath<_Tp, M>(__root, __key, __stack);	// 삽입할 키의 중복 여부를 반환 키가 있으면 True, 없으면 False 

	if (found) {	// 중복키가 있는 경우 중복키와 false 반환
		return std::make_pair(__stack.top(), false);
	}

	bool __finished = false;
	Node<_Tp, M>* __x = __stack.top();
	__stack.pop(); // 키 삽입할 노드
	Node<_Tp, M>* __y = nullptr;

	_Tp newKey = __key;

	do {
		if (__x->size() < M - 1) {	// Overflow가 발생하지 않은 경우 
			__insertKey<_Tp, M>(__x, __y, newKey);		// 노드 삽입
			__finished = true;				// 반복문 종료
		}
		else {	// Overflow발생
			std::pair<_Tp, Node<_Tp, M>*> __splitRes =
				__splitNode<_Tp, M>(__x, __y, newKey);

			newKey = __splitRes.first; 		// 위로 올릴 중간값, 중간 키가 부모 노드에 삽입할 키가 된다. 
			__y = __splitRes.second;			// 분할된 오른쪽 노드

			if (!__stack.empty()) {	// 부모노드 x에 midKey를 삽입한다.
				__x = __stack.top();
				__stack.pop();
			}
			else {					// 부모노드가 루트 노드여서 level이 증가하는 경우
				Node<_Tp, M>* __newRoot = new Node<_Tp, M>();
				__newRoot->__keys_[0] = newKey;
				__newRoot->__children_[0] = __x;
				__newRoot->__children_[1] = __y;
				__newRoot->size() = 1;

				__root = __newRoot;
				__finished = true;
				return std::make_pair(__newRoot, true);
			}
		}
	} while (!__finished);

	return std::make_pair(__root, true);
}

// deleteKey 구현
template <class _Tp, std::size_t M> 
void __deleteKey(Node<_Tp, M>* __x, const _Tp& __oldKey) {

	int i = 0;
	while (__oldKey > __x->__keys_[i]) {	// 삭제할 노드의 위치를 찾고
		i++;
	}

	while (i < __x->size()) {				// 삭제할 노드의 오른쪽에 있는 노드들을 한 칸씩 왼쪽으로 옮긴다.
		__x->__keys_[i] = __x->__keys_[i + 1];
		__x->__children_[i + 1] = __x->__children_[i + 2];
		i++;
	}
	__x->__children_[__x->size()] = nullptr;
	__x->size()--;	// 키의 개수 1감소
}

// bsetSibling 구현 
template <class _Tp, std::size_t M>
int __bestSibling(Node<_Tp, M>* __x, Node<_Tp, M>* __y) {
	int i = 0;

	while (__y->__children_[i] != __x) {
		i++;
	}

	// 내가 첫째면 둘째 선택
	if (i == 0) {
		return i + 1;
	}
	// 내가 막내면 맞형 선택
	else if (i == __y->size()) {
		return i - 1;
	}
	// 동생, 형 둘다 있으면 키 많은 형제 인덱스 반환
	else if (__y->__children_[i - 1]->size() >= __y->__children_[i + 1]->size()) {
		return i - 1;
	} 
	return i + 1;
}

// redistributeKeys 구현
template <class _Tp, std::size_t M> 
void __redistributeKeys(Node<_Tp, M>* __x, Node<_Tp, M>* __y, int __bestSib) {
	 int i = 0;
	 while (__y->__children_[i] != __x) {
		 i++;
	 }

	 Node<_Tp, M>* bestNode = __y->__children_[__bestSib];

	 if (__bestSib < i) {	// 왼쪽 형제에서 키를 빌려오는 경우 

		 _Tp lastKey = bestNode->__keys_[bestNode->size() - 1];		// 형제 마지막 키
		 __insertKey<_Tp, M>(__x, nullptr, __y->__keys_[i - 1]);	// 부모키를 내 앞으로

		 // 자식 포인터 정리
		 __x->__children_[1] = __x->__children_[0];						
		 __x->__children_[0] = bestNode->__children_[bestNode->size()];	
		 bestNode->__children_[bestNode->size()] = nullptr;

		 __deleteKey<_Tp, M>(bestNode, lastKey);	// 형제에게서 부모로 올라갈 키를 제거한다. 
		 __y->__keys_[i - 1] = lastKey;				// 부모의 키를 형제에게서 받은 키로 변경한다.
	 }
	 else{					// 오른쪽 형제에서 키를 빌려오는 경우 
		 _Tp firstKey = bestNode->__keys_[0];					// 형제의 첫번째 키
		 __insertKey<_Tp, M>(__x, nullptr, __y->__keys_[i]);	// 부모키를 내 뒤로

		 // 자식 포인터 정리
		 __x->__children_[__x->size()] = bestNode->__children_[0];
		 bestNode->__children_[0] = bestNode->__children_[1];
		
		 __deleteKey<_Tp, M>(bestNode, firstKey);	// 형제에게서 부모로 올라갈 키를 제거한다. 
		 __y->__keys_[i] = firstKey;				// 부모의 키를 형제에게서 받은 키로 변경한다.
	 }

 }

// mergeNode 구현
template <class _Tp, std::size_t M>
Node<_Tp, M>* __mergeNode(Node<_Tp, M>* __x, Node<_Tp, M>* __y, int __bestSib)
{
	int i = 0;

	while (i <= __y->size() && __y->__children_[i] != __x) i++;

	Node<_Tp, M>* bestNode = __y->__children_[__bestSib];

	// 오른쪽 형제가 왼쪽으로 오도록 swap
	if (__bestSib > i) {

		// 인덱스 교환
		int tmp = i;
		i = __baseSib;
		__bestSib = tmp;

		// 노드 포인터 교환
		Node<_Tp, M>* tmpNode = __x;
		__x = bestNode;
		bestNode = tmpNode;
	}

	// 부모 키 내려오기
	bestNode->__keys_[bestNode->size()] = __y->__keys_[i - 1];
	bestNode->size()++;

	// x 노드의 내용 bestNode에 붙여 넣는다. 
	for (int j = 0; j < __x->size(); j++) {
		bestNode->__keys_[bestNode->size()] = __x->__keys_[j];
		bestNode->__children_[bestNode->size()] = __x->__children_[j];
		bestNode->size()++;
	}
	bestNode->__children_[bestNode->size()] = __x->__children_[__x->size()];

	__deleteKey<_Tp, M>(__y, __y->__keys_[i - 1]);

	delete __x;

	return bestNode;
}

template <class _Tp, std::size_t M>
const Node<_Tp, M>* __eraseBT(Node<_Tp, M>*& __root, const _Tp& __key){

	std::stack<Node<_Tp, M>*> __stack;		// 경로 저장용 스택
	bool found = __searchPath<_Tp, M>(__root, __key, __stack);	// 삽입할 키의 중복 여부를 반환 키가 있으면 True, 없으면 False -> 삭제 에서는 false면 안된다.

	if (found == false || __stack.empty()){	// 삭제할 키가 없다면 즉시 종료
		return nullptr;
	}

	Node<_Tp, M>* __x =	__stack.top(); __stack.pop();	// 삭제할 키가 있는 노드
	Node<_Tp, M>* __y = nullptr;						

	int i = 0;
	while (__x->__keys_[i] != __key) {
		i++;
	}

	// oldKey가 단말 노드가 아니면
	if (__x->__children_[i + 1] != nullptr) {

		Node<_Tp, M>* internalNode = __x;
		__stack.push(__x);	// 경로 복구

		// 오른쪽 자식의 가장 왼쪽 자식 까지 내려갑니다. 
		Node<_Tp, M>* cur = __x->__children_[i + 1];
		__stack.push(cur);
		while (cur->__children_[0] != nullptr) {	// 해당 반복분이 끝나면 stack의 top에 교체할 키를 찾는다. 
			cur = cur->__children_[0];
			__stack.push(cur);
		}

		__x = __stack.top();
		__stack.pop();
		
		// 교체할 노드와 값 교환
		_Tp temp = internalNode->__keys_[i];
		internalNode->__keys_[i] = __x->__keys_[0];
		__x->__keys_[0] = temp;
	}

	bool finished = false;
	__deleteKey<_Tp, M>(__x, __key);	// 교환한 키를 단말 노드에서 삭제

	if (!__stack.empty()) {	// __X(키를 삭제한 노드)의 부모노드 __y설정
		__y = __stack.top(), __stack.pop();
	} 

	do {
		if (__x == __root || __x->size() >= (M - 1) / 2) {	// Root이거나, Underflow가 아닌 경우
			finished = true;
		}
		else {	// UnderFlow 발생
			int best = __bestSibling<_Tp, M>(__x, __y);

			if (__y->__children_[best]->size() > (M - 1) / 2) {	// 형제가 잘사는 경우 
				__redistributeKeys<_Tp, M>(__x, __y, best);
				finished = true;
			}													// 형제도 못사는 경우
			else {
				// 병합 -> 부모 UnderFlow 검사를 위해 __x = __y를 만든다. 
				__x = __mergeNode<_Tp, M>(__x, __y, best);
				__x = __y;

				if (!__stack.empty()) {
					__y = __stack.top(); __stack.pop();
				}
				else {
					finished = true;
				}
			}
		}
	} while (finished == false);

	if (__y != nullptr && __y->size() == 0) {
		__root = __y->__children_[0];
		delete __y;
	}

	return __root;

}


// 아래는 반드시 사용해야하는 BT 클래스입니다.
template <class _Tp, std::size_t M>
class BT {
public: // Member types
	typedef _Tp						key_type;
	typedef std::size_t				size_type;
	typedef Node<key_type>* pointer;
	typedef const Node<key_type>* const_pointer;

private: // Member variables
	pointer	__root_;

public: // Constructor
	BT() : __root_(nullptr) {}

public: // Lookup
	void inorder() const {
		// use __inorder or write your own code here
		__inorder(__root_);
		std::cout << std::endl;
	}

public: // Modifier
	std::pair<const_pointer, bool> insert(const key_type& key) {
		// use __insertBT or write your own code here
		return __insertBT<_Tp, M>(__root_, key);
	}

	const_pointer erase(const key_type& key) {
		// use __eraseBT or write your own code here
		return __eraseBT<_Tp, M>(__root_, key);
	}

	void clear() {
		// use __clear or write your own code here
		__clear(__root_);
	}

	/*
	* 아래는 inorder traversal을 대체할 수 있는 operator<< 입니다.
	* 반드시 아래의 함수를 사용해야할 필요는 없습니다.
	*/
	friend std::ostream& operator<<(std::ostream& os, const BT& tree) {
		os << tree.__root_;
		return os;
	}
};

/*
* 아래는 추천드리는 main 함수의 예시입니다.
* 반드시 아래의 main 함수를 사용해야할 필요는 없습니다.
* ❗️새로 구현하실 경우, 출력 형식에 주의하세요.❗️
*/
int main(int argc, char** argv) {
	BT<int>	tree;
	char	command;
	int		key;

	while (std::cin >> command >> key) {
		switch ((int)command) {
		case (int)'i':
			if (tree.insert(key).second == false) {
				std::cerr << "i " << key << ": The key already exists" << std::endl;
				continue;
			}
			break;
		case (int)'d':
			if (tree.erase(key) == nullptr) {
				std::cerr << "d " << key << ": The key does not exist" << std::endl;
				continue;
			}
			break;
		default:
			std::cerr << "Invalid command: " << command << std::endl;
			return (1);
			break;
		}
		std::cout << tree << std::endl;
	}

	// 프로그램 종료 전, 메모리 누수가 발생하지 않도록 할당받은 메모리를 반드시 해제해야 합니다.
	tree.clear();

	return (0);
}
