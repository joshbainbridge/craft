#include <craft/octreeNode.hpp>

octreeNode::octreeNode ()
{
}

octreeNode::~octreeNode ()
{
	delete branch01;
	delete branch02;
	delete branch03;
	delete branch04;
	delete branch05;
	delete branch06;
	delete branch07;
	delete branch08;
}

void octreeNode::setValue (int value_input)
{
	value = value_input;
}

int octreeNode::getValue ()
{
	return value;
}

void octreeNode::setBranch (int index, octreeNode* input_branch)
{
	switch (index)
	{
		case 1:
			branch01 = input_branch;
			break;
		case 2:
			branch02 = input_branch;
			break;
		case 3:
			branch03 = input_branch;
			break;
		case 4:
			branch04 = input_branch;
			break;
		case 5:
			branch05 = input_branch;
			break;
		case 6:
			branch06 = input_branch;
			break;
		case 7:
			branch07 = input_branch;
			break;
		case 8:
			branch08 = input_branch;
			break;
		default:
			break;
	}
}

octreeNode* octreeNode::getBranch (int index)
{
	switch (index)
	{
		case 1:
			return branch01;
		case 2:
			return branch02;
		case 3:
			return branch03;
		case 4:
			return branch04;
		case 5:
			return branch05;
		case 6:
			return branch06;
		case 7:
			return branch07;
		case 8:
			return branch08;
		default:
			return 0;
	}
}