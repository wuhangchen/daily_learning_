/*
 *利用2个栈实现队列
 *
 */

template<typename T>
class self_queue{
	public:
		self_queue();
		~self_queue();
		void append_tail(const T &node);
		T delete_head();
	private:
		std::stack<T> stack1;
		std::stack<T> stack2;
};

template<typename T>
void self_queue::append_tail(const T &node){
	stack1.pusn(node);
}

template<typename T>
T self_queue::delete_head(){
	if(stack2.size()<=0){
		while(stack1.size()>0){
			T &data = stack1.top();
			stack1.pop();
			stack2.push(data);
		}
	}
	if(stack2.size()==0)
		throw new exception("queue is empty");
	T head = stack2.top();
	stack2.pop();

	return head;
}
