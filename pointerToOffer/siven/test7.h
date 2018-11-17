//重建二叉树
struct BinaryTreeNode{
	int value;
	struct BinaryTreeNode* left;
	struct BinaryTreeNode* right;
};

struct BinaryTreeNode* construct(int *preorder,int *inorder,int length){
	if(preorder == nullptr || inorder == nullptr || length<=0)
		return nullptr;
	return construct_core(preorder,preorder+length-1,
				inorder,inorder+length-1);
}

//接受4个指针的construct_core函数.
struct BinaryTreeNode* construct_core(int *start_preorder,int *end_preorder
					int *start_inorder,int *end_inorder){
	int root_value = start_inorder[0];

	struct BinaryTreeNode *root = new struct BinaryTreeNode();
	root->value = root_value;
	root->left = nullptr;
	root->right = nullptr;

	if(start_preorder == end_preorder){
		if(start_inorder == end_inorder){
			return root;
		}else{
			throw std::exception("invalid input");
		}
	}

	//在中序遍历中找到根结点的值。
	int *root_inorder = start_inorder;
	while(root_inorder <= end_inorder && *root_inorder != root_value){
		++root_inorder;
	}

	if(root_inorder == end_inorder && *root_inorder != root_value)
		throw std::exception("invailed input");

	int left_length = root_inorder-start_inorder;
	int *left_preorder_end = start_preorder + left_length;
	//构建左子树
	if(left_length>0){
		root->left = construct_core(start_preorder+1,left_preorder_end,
						start_inorder,root_inorder-1
					);
	}
	//构建右子树
	if(left_length<end_preorder-start_preorder ){
		root->right = construct_core(left_preorder_end+1,end_preorder,
						root_inorder+1,end_inorder
				);
	}

	return root;
}
