#include <iostream>
using namespace std;

/*
 * 1. new和malloc区别
 *    a. malloc返回void *，new返回对于类型的指针
 *    b. 对于类类型,new会调用构造
 *    c. new时可以进行元素初始化
 *    d. 可以定位new
 */

/*
 * 2. new t和 delete[] 可以混用吗？
 *    基础类型可以混用
 *    类类型不能混用，因为类类型要进行析构，
 *    编译器为了知道析构的对象数量，在构造 new vector<int>[5] 时，
 *    首先分配4字节存放数组元素数量5，再分配5个vector<int>的内存
 *    再对每个元素进行定位new，调用其构造函数。
 *    返回给用户的地址不是分配的首地址（存放数组元素数量的内存的地址）
 *    而是数组首元素的地址。
 *
 *    当delete[] xx时，编译器会对xx地址想后偏移4字节得到数组元素的长度，
 *    并根据长度对xx开始的元素数组依次调用析构函数，
 *    再释放整个内存
 */

/*
 * 3. 重载new
 */

class Queue {
	public:
		Queue() {
			_head = nullptr;
			_tail = nullptr;
		}

		~Queue() {
			QueueItem *item, *tmp;

			for (item = _head,tmp = _head == nullptr ? nullptr : _head->next; 
					item != _tail; item = tmp, tmp = item->next) {
				delete item;	
			}
		}

		Queue &push(const int data) {
			QueueItem *item;

			item = new QueueItem;
			item->prev = nullptr;
			item->next = _head;
			if (_head)
				_head->prev = item;
			_head = item;

			if (_tail == nullptr)
				_tail = item;

			return *this;
		}

		int pop() {
			QueueItem *item;
			int data;

			if (_tail == nullptr)
				throw "QueueIsEmpty";

			item = _tail;	
			_tail = _tail->prev;
			if (_tail)
				_tail->next = nullptr;
			data = item->data;
			delete item;

			return data;
		}


		struct QueueItem {
			QueueItem *next;
			QueueItem *prev;
			int data;

			void *operator new(size_t size) {
				if (QueueItemList == nullptr) {
					int i;
					QueueItemList = new QueueItem[QueueItemBatch];
					for (i = 0; i < QueueItemBatch - 1; i++)
						QueueItemList[i].next = &QueueItemList[i + 1];
					QueueItemList[i].next = nullptr;
				}
				QueueItem *ret = QueueItemList;		
				QueueItemList = QueueItemList->next;
				return ret;
			}

			static void operator delete(void *p) {
				QueueItem *item = (QueueItem *)p;
				
				item->next = QueueItemList;
				QueueItemList = item;
			}

			// 1. 注意static基础类型可以在class{} 中初始化
			//    类类型不可以，因为类类型会调用构造函数，
			//    编译阶段无法执行构造
			static const int QueueItemBatch = 100;
			static QueueItem *QueueItemList;
		};

	private:

		QueueItem *_head;
		QueueItem *_tail;
};


Queue::QueueItem *Queue::QueueItem::QueueItemList = nullptr;


int main()
{
	Queue q;	

	for (int i = 0; i < 10; i++) {
		q.push(i);
		cout << q.pop() << " ";
	}
	cout << endl;

	return 0;
}
