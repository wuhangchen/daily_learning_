
using namespace self {
	class solution{
		publice:
			struct ListNode{
				int value;
				struct ListNode *next;
			};
			//增加一个元素在尾端。
			void addto_tail(struct ListNode**phead,int val){
				struct ListNode* pNew = ListNode();
				pNew->value = val;
				pNew->next = nullptr;

				if(*phead==nullptr)
					*phead=pNew;
				else{
					ListNode *p1 = *phead;
					while(p1->next != nullptr){
						p1=p1->next;
					}
					p1->next = pNew;
				}
				return ;
			}

                       //从尾端到头打印链表
		       void print_list_reversingly_iter(struct ListNode *phead){
		       		std::stack<ListNode*> nodes;
				ListNode *pNode = phead;
				while(pNode != nullptr){
					nodes.push(pNode);
					pNode=pNode->next;
				}
				while(!nodes.empty()){
					pNode = nodes.top();
					printf("%d\n",pNode->value);
					nodes.pop();
				}
				return ;
		       }

		       //利用递归版本。
		       void print_list_reversingly_iter_version_1(struct ListNode *phead){
		       		if(phead!=nullptr){
					if(phead->next != nullptr){
						print_list_reversingly_iter_version_1(phead->next);
					}
					printf("%d\n",phead->value);
				}
		       }
	};
	
}
