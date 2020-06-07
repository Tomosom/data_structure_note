1.main文件版本说明


遗留尚未完善的部分：
1.
2.用share_pointer替换link_list中的原生指针
3.用内核链表实现的双向循环链表实现约瑟夫环的问题
4.No.33 双向循环链表课后思考习题

	struct Node : public Object {
		list_head head;
		T value;
	};

	Node node;
	list_head *ld = &node.head;

	Node *pn1 = reinterpret_cast<Node*>(ld);
	Node *pn2 = list_entry(ld, Node, head);

	上面的pn1和pn2是否相等，为什么?


