#pragma once
//binnode 状态与性质判断
#define IsRoot(x)		(!((x).parent))
#define IsLChild(x)		(!IsRoot(x)&&(&(x)==(x).parent->lc))
#define IsRChild(x)		(!IsRoot(x)&&(&(x)==(x).parent->rc))
#define HasParent(x)	(!IsRoot(x))
#define HasLChild(x)	((x).lc)
#define HasRChild(x)	((x).rc)
#define HasCHild(x)		(HasLChild(x)||HasRChild(x))//至少拥有一个孩子
#define HasBothChild(x) (HasLChild(x)&&HasRChild(x))//同时拥有两个孩子
#define IsLeaf(x)(!HasCHild(x))


//与binnose具有特定关系的节点及指针

#define sibling(p)/*兄弟*/\
(IsLChild(*(p))?(p)->parent->rc:(p)->parent->lc)

#define uncle(x)/*叔叔*/\
(IsLChild(*((x)->parent))?(x)->parent->rc:(x)->parent->parent-lc)

#define FromParentTo(x) /*来自父亲的引用*/ \
   ( IsRoot(x) ? _root : ( IsLChild(x) ? (x).parent->lc : (x).parent->rc ) )
