#pragma once
#ifndef BTNODE_H
#define BTNODE_H
#include "Vector.h"
#define BTNodePosi(T) BTNode<T>* //b树节点位置

template<typename T> struct BTNode{//b树节点模板类
//成员（为简化描述起见统一开放
	BTNodePosi(T) parent;//父节点
	Vector<T> key;//关键码向量
	Vector<BTNodePosi(T)>child;//孩子向量(其长度总比key多一）
};
#endif
