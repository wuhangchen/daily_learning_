/*
 *二叉树的下一个结点。
 *思路：
 1. 如果一个节点有右子树，那么它的下一个节点就是它的右子树中的最左节点。
 2. 一个节点没有右子树的情形，如果节点是它父亲节点的左子节点，那么它的下一个节点是它的父亲节点
 3. 如果一个节点既没有右子树，并且它还是它的父亲的右子节点，那么我们需要沿着父节点的指针一直向上
    找到第一个是它父节点的左子节点的节点。如果这样的节点存在，那么节点b的父节点就是我门要找的下一个节点。
 */

struct BinaryTreeNode{
	int value;
	struct BinaryTreeNode* parent;
	struct BinaryTreeNode* left;
	struct BinaryTreeNode* right;
};
struct BinaryTreeNode* get_next(struct BinaryTreeNode* pnode){
	if(pnode==nullptr){
		return nullptr;
	}
	struct BinaryTreeNode *pnext = nullptr;
	if(pnode->right!=nullptr){
		struct BinaryTreeNode *pright = pnode->right;
		while(pright->left!=nullptr)
			pright=pright->left;

		pnext = pright;
	}else if(pnode->parent != nullptr){
		struct BinaryTreeNode* pcurrent = pnode;
		struct BinaryTreeNode* pparent = pnode->parent;
		while(pparent!=nullptr && pparent->right){
			pcurrent = pparent;
			pparent = pparent->parent;
		}
		pnext = pparent;
	}
	return pnext;
	
}
