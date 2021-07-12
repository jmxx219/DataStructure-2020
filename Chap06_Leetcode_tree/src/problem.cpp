#include <iostream>
#include <deque>
#include <vector>
#include <set>
#include <unordered_map>
#include <unordered_set>

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


// 112. Path Sum
bool hasPathSum(TreeNode* root, int sum) {

}

// 235. Lowest Common Ancestor of a Binary Search Tree
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
	if(root->val>p->val && root->val>q->val) return lowestCommonAncestor(root->left, p, q);
	if(root->val<p->val && root->val<q->val) return lowestCommonAncestor(root->right, p, q);
	return root;
}

//108. Convert Sorted Array to Binary Search Tree
TreeNode* balanceTree(int low, int high, std::vector<int>& nums){
	if(low>high) return nullptr;
	if(low==high) return new TreeNode(nums[low]);

	int mid = low + (high-low)/2;
	TreeNode* root = new TreeNode(nums[mid]);
	root->left = balanceTree(low,mid-1, nums);
	root->right = balanceTree(mid+1,high, nums);

	return root;
}
TreeNode* sortedArrayToBST(std::vector<int>& nums) {
	return balanceTree(0, nums.size()-1, nums);
}

// 572. Subtree of Another Tree
bool isSameTree(TreeNode* s, TreeNode* t) {
	if(s==nullptr&&t==nullptr) return true;
	else if(s==nullptr||t==nullptr) return false;
	if(s->val != t->val) return false;
	return isSameTree(s->left, t->left) && isSameTree(s->right,t->right);
}
bool isSubtree(TreeNode* s, TreeNode* t) {
	if(s==nullptr&&t==nullptr) return true;
	else if(s==nullptr||t==nullptr) return false;
	if(isSameTree(s, t)) return true;
	else return isSubtree(s->left, t) || isSubtree(s->right, t);
}

//938. Range Sum of BST
int rangeSumBST(TreeNode* root, int low, int high) {
	int sum{0};
	if(root==nullptr) return 0;
	if(root->left!=nullptr) sum+= rangeSumBST(root->left, low, high);
	if(root->val>=low&&root->val<=high) sum+= root->val;
	if(root->right!=nullptr) sum+= rangeSumBST(root->right, low, high);
	return sum;
}

void rangeSumBST(TreeNode* root, int low, int high, std::vector<int>& arr) {
   if(root == nullptr) return;
   rangeSumBST(root->left, low, high, arr);
   if (root->val >= low && root->val <= high) arr.push_back(root->val);
   rangeSumBST(root->right, low, high, arr);
}
int rangeSumBST(TreeNode* root, int low, int high) {
   std::vector<int> arr;
   int sum = 0;
   rangeSumBST(root, low, high, arr);
   for (int i = 0; i < arr.size(); i++)sum += arr[i];
   return sum;
}

//404. Sum of Left Leaves
int sumOfLeftLeaves(TreeNode* root) {
	if(root==nullptr) return 0;
	int sum{0};
	if(root->left && !root->left->left && !root->left->right) sum+= root->left->val;
	sum+=sumOfLeftLeaves(root->left);
	sum+=sumOfLeftLeaves(root->right);
	return sum;
}

void sumOfLeftLeaves(TreeNode* root, std::vector<int> &sums) {
	if(root==nullptr) return ;
	if(root->left && !root->left->left && !root->left->right) sums.push_back(root->left->val);
	sumOfLeftLeaves(root->left);
	sumOfLeftLeaves(root->right);
}
int sumOfLeftLeaves(TreeNode* root) {
	if(root==nullptr) return 0;
	int sum{0};
	std::vector<int> sums;
	sumOfLeftLeaves(root, sums);
	for(int i=0; i<sums.size();i++) sum+= sums[i];
	return sum;
}

//501. Find Mode in Binary Search Tree
void inorder(TreeNode* root, std::unordered_map<int, int> &freq){
	if(root->left !=nullptr) inorder(root->left,freq);
	freq[root->val]++;
	if(root->right !=nullptr) inorder(root->right,freq);
}
std::vector<int> findMode(TreeNode* root) {
	std::vector<int> vec;
	if(root==nullptr) return vec;
	std::unordered_map<int,int> map;
	inorder(root, map);
	int max=INT_MIN;
	for(auto i: map) if(i.second>max) max=i.second;
	for(auto i: map) if(i.second==max) vec.push_back(i.first);
	return vec;
}

// 110. Balanced Binary Tree
int height(TreeNode* curr){
	if(curr==nullptr) return 0;
	else return std::max(height(curr->left), height(curr->right))+1;
}
bool isBalanced(TreeNode* root) {
	if(root==nullptr) return true;
	int left = height(root->left)-1;
	int right = height(root->right)-1;
	if(std::abs(left-right)>1) return false;
	return isBalanced(root->left) && isBalanced(root->right);
}

//111. Minimum Depth of Binary Tree
int minDepth(TreeNode* root) {
	if (root == nullptr) return 0;
	else if (root->left == nullptr) return minDepth(root->right) + 1;
	else if (root->right == nullptr) return minDepth(root->left) + 1;
	return std::min(minDepth(root->left), minDepth(root->right)) + 1;
}

int minDepth(TreeNode* root) {
	if(root==nullptr) return 0;
	int left=minDepth(root->left)+1;
	int right=minDepth(root->right)+1;
	if(left==1) return right;
	else if(right==1) return left;
	return std::min(left,right);
}

//104. Maximum Depth of Binary Tree
int maxDepth(TreeNode* root) {
	if(root==nullptr) return 0;
	else return std::max(maxDepth(root->left),maxDepth(root->right))+1;
}

//617. Merge Two Binary Trees
TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2) {
	if(t1==nullptr) return t2;
	if(t2==nullptr) return t1;
	t1->val += t2->val;
	t1->left = mergeTrees(t1->left, t2->left);
	t1->right = mergeTrees(t1->right, t2->right);
	return t1;
}

//144. Binary Tree Preorder Traversal
void preorderTraversal(TreeNode* root, std::vector<int> &node) {
	if(root==nullptr)return;
	node.push_back(root->val);
	if(root->left) preorderTraversal(root->left, node);
	if(root->right) preorderTraversal(root->right, node);
}
std::vector<int> preorderTraversal(TreeNode* root) {
	std::vector<int> node;
	preorderTraversal(root, node);
	return node;
}

//872. Leaf-Similar Trees
void bfs(TreeNode* root, std::vector<int> &st){
	if(root==nullptr) return;
	if(root->left==nullptr&&root->right==nullptr)
		st.push_back(root->val);
	else{
		bfs(root->left, st);
		bfs(root->right, st);
	}
}
bool leafSimilar(TreeNode* root1, TreeNode* root2) {
	std::vector<int> st1;
	std::vector<int> st2;
	bfs(root1, st1);
	bfs(root2, st2);
	return st1==st2;
}

//226. Invert Binary Tree
TreeNode* invertTree(TreeNode* root) {
	if(root == nullptr) return root;

	TreeNode*tmp = root->left;
	root->left = root->right;
	root->right = tmp;

	invertTree(root->left);
	invertTree(root->right);
	return root;
}

//100. SameTree
bool isSameTree(TreeNode* p, TreeNode* q) {
	if(p==nullptr&&q==nullptr) return true;
	else if(p==nullptr||q==nullptr) return false;
	if(p->val != q->val) return false;
	return isSameTree(p->left, q->left) && isSameTree(p->right,q->right);
}

// 101. Symmetric Tree - Recursive
bool symmetric1(TreeNode* rootLeft, TreeNode* rootRight){
	if(rootLeft == nullptr && rootRight == nullptr) return true;
	else if(rootLeft == nullptr || rootRight == nullptr) return false;
	if(rootLeft->val != rootRight->val) return false;
	return symmetric1(rootLeft->left, rootRight->right) && symmetric1(rootLeft->right, rootRight->left);
}

bool isSymmetric1(TreeNode* root) {
	if(root == nullptr) return true;
	return symmetric1(root->left, root->right);
}

// 101. Symmetric Tree - Iterative
bool isSymmetric2(TreeNode* root) {
	if(root == nullptr||(root->left==nullptr&&root->right==nullptr)) return true;
	std::deque<TreeNode*> deque;
	deque.push_back(root->left);
	deque.push_back(root->right);

	while(!deque.empty()){
		TreeNode* left = deque.front();
		deque.pop_front();
		TreeNode* right = deque.back();
		deque.pop_back();

		if(left == nullptr && right == nullptr) continue;
		if(left == nullptr ||  right == nullptr) return false;
		if(left->val != right->val) return false;

		deque.push_front(left->left);
		deque.push_back(right->right);
		deque.push_front(left->right);
		deque.push_back(right->left);
	}
	return true;
}

// 202. Happy Number -> ÇØ½Ì
bool isHappy(int n) {
	//std::unordered_set<int> set(131);
	std::set<int> set;
	while(n!=1){
		int sum = 0;
		while(n>0){
			sum += (n%10)*(n%10);
			n /= 10;
		}
		if(sum==1) return true;
		else if(set.find(sum)!= set.end()) return false;
		else{
			set.insert(sum);
			n = sum;
		}
	}
	return true;
}
bool isIsomorphic(std::string s, std::string t) {
	std::unordered_map<char, int> s_map;
	std::unordered_map<char, int> t_map;
	for(int i = 0; i < s.size(); i++){
		if(!s_map.count(s[i])) s_map[s[i]] = i;
		if(!t_map.count(t[i])) t_map[t[i]] = i;
		if(s_map[s[i]] != t_map[t[i]]) return false;
	}
	return true;
}

int main(){
	TreeNode* root1 = new TreeNode(1, new TreeNode(2, new TreeNode(3),
			new TreeNode(4)), new TreeNode(2, new TreeNode(4), new TreeNode(3)));
	TreeNode* root2 = new TreeNode(1, new TreeNode(2, new TreeNode(3),
				new TreeNode(4)), new TreeNode(2, new TreeNode(4), new TreeNode(3)));
	std::cout << isSameTree(root1, root2) << std::endl;
	return 0;
}
