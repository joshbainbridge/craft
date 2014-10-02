#ifndef OCTREENODE_H__
	#define OCTREENODE_H__
	
	class octreeNode;
	
	class octreeNode
	{
		int value;
		
		octreeNode* branch01;
		octreeNode* branch02;
		octreeNode* branch03;
		octreeNode* branch04;
		octreeNode* branch05;
		octreeNode* branch06;
		octreeNode* branch07;
		octreeNode* branch08;
		
		public:
			octreeNode ();
			~octreeNode ();
			void setValue(int);
			int getValue();
			void setBranch(int, octreeNode*);
			octreeNode* getBranch(int);
	};
	
#endif