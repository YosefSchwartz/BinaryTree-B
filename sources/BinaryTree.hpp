#pragma once
#include <stack>
#include <exception>
#include <iostream>

using namespace std;

namespace ariel{
    /*
    Enum Order - to identify the order of iterator.
        pre-order (Parent, Left, Right)
        in-order (Left, Parent, Right)
        post-order (Left, Right, Parent)
    */
    enum Order{
        preorder,
        inorder,
        postorder
    };

    template <class T>
    /*
    Class BinaryTree - This class represent generic binary tree.
        contain pointer to the root, and some iterators to get data on all the tree.
    */
    class BinaryTree{
        /*
        Class Node - represent one node in binary tree,
             contain 3 pointers to his children, right and left, and to his father.
             In additinal, he hold his T value.
        */
        class Node{
            public:
                T value;
                Node* rightSon;
                Node* leftSon;
                /*
                Constructor - Set the value to the given value.
                */
                Node(T val):value(val),rightSon(nullptr),leftSon(nullptr){}
        };
        /*
            Pointer to the root of Tree.
        */    
        Node* root;


        public:
        class iterator{
            private:
                std::stack<Node*> P;
                std::stack<Node*> L;
                std::stack<Node*> R;

                Node* curr;
                Order order;

            public: 
                iterator(Order ord = Order::inorder, Node* ptr = nullptr):order(ord),curr(ptr){
                    order = ord;
                    if(ptr != nullptr){
                        Node* tmp = ptr;
                        switch (order){
                        case Order::preorder:
                            break;
                        case Order::inorder:
                            L.push(tmp);
                            while (L.size()>0){
                                tmp = L.top();
                                L.pop();
                                if(tmp->rightSon != nullptr){
                                        R.push(tmp->rightSon);
                                }
                                P.push(tmp);
                                if(tmp->leftSon != nullptr){
                                    L.push(tmp->leftSon);
                                }
                            }
                            curr = P.top();
                            P.pop();
                            break;
                        
                        case Order::postorder :
                            while(tmp->leftSon != nullptr || tmp->rightSon != nullptr){
                                P.push(tmp);
                                if(tmp->rightSon != nullptr){
                                    R.push(tmp->rightSon);
                                }
                                if(tmp->leftSon != nullptr){
                                    L.push(tmp->leftSon);
                                }
                                if(L.size()>0){
                                    tmp = L.top();
                                    L.pop();
                                }else{
                                    tmp=R.top();
                                    R.pop();
                                }
                            }
                            curr = tmp;    
                        }
                    }
                }

                T& operator* () const{
                    return curr->value;
                }
                T* operator->() const{
                    return &(curr->value);
                }

                iterator& operator++(){
                    switch (order){
                        case Order::preorder :{
                            if(curr->leftSon != nullptr){
                                if(curr->rightSon != nullptr){
                                    R.push(curr->rightSon);
                                }
                                curr = curr->leftSon;
                            } else if(curr->rightSon != nullptr){
                                curr = curr->rightSon;
                            } else if (R.size()>0){
                                curr = R.top();
                                R.pop();
                            } else{
                                curr =  nullptr;
                            }
                            return *this;
                            break;
                        }
                
                        case Order::inorder :{
                            if(R.size()>0){ 
                                Node* tmp = R.top();
                                if(curr->rightSon == tmp){
                                    R.pop();
                                    while(tmp != nullptr){
                                        if(tmp->rightSon != nullptr){R.push(tmp->rightSon);}
                                        P.push(tmp);
                                        tmp = tmp->leftSon;
                                    }
                                    curr = P.top();
                                    P.pop(); 
                                }else{
                                curr = P.top();
                                P.pop();
                                }
                            } else {
                                if(P.size()>0){
                                    curr = P.top();
                                    P.pop();
                                }else{
                                curr = nullptr;
                                }
                            }    
                            break;
                        }
                        case Order::postorder :{
                            if(P.size()>0){
                                if (R.size()>0){
                                    Node* tmpP = P.top();
                                    Node* tmpR = R.top();
                                    if(tmpP->rightSon == tmpR){
                                        R.pop();
                                        while(tmpR->leftSon != nullptr || tmpR->rightSon != nullptr){
                                            if(tmpR->leftSon != nullptr){
                                                L.push(tmpR->leftSon);
                                            }
                                            P.push(tmpR);
                                            if(tmpR->rightSon != nullptr){
                                                R.push(tmpR->rightSon);
                                            }
                                            if(L.size()>0){
                                                tmpR = L.top();
                                                L.pop();
                                            }else{
                                                tmpR=R.top();
                                                R.pop();
                                            }
                                        }
                                        curr = tmpR;
                                    }else{
                                        P.pop();
                                        curr = tmpP;
                                    }
                                }else{
                                    curr=P.top();
                                    P.pop();
                                }
                            } else {
                                curr = nullptr;
                            }
                            break;
                        }
                    }
                    return *this;
                }

                iterator operator++(int){
                     iterator tmp = *this;
                     *this->operator++();
                     return tmp;
                } 
                Node* getCurr(){
                    return curr;
                }
            
                bool operator==(const iterator& rhs) const{
                    return rhs.curr==curr;
                }
                bool operator!=(const iterator& rhs) const{
                    return rhs.curr != curr;
                }
        };

                
                class const_iterator{
            private:
                std::stack<Node*> P;
                std::stack<Node*> L;
                std::stack<Node*> R;

                Node* curr;
                Order order;

            public: 
                const_iterator(Order ord = Order::inorder, Node* ptr = nullptr):order(ord),curr(ptr){
                    order = ord;
                    if(ptr != nullptr){
                        Node* tmp = ptr;
                        switch (order){
                        case Order::preorder:
                            break;
                        case Order::inorder:
                            L.push(tmp);
                            while (L.size()>0){
                                tmp = L.top();
                                L.pop();
                                if(tmp->rightSon != nullptr){
                                        R.push(tmp->rightSon);
                                }
                                P.push(tmp);
                                if(tmp->leftSon != nullptr){
                                    L.push(tmp->leftSon);
                                }
                            }
                            curr = P.top();
                            P.pop();
                            break;
                        
                        case Order::postorder :
                            while(tmp->leftSon != nullptr || tmp->rightSon != nullptr){
                                P.push(tmp);
                                if(tmp->rightSon != nullptr){
                                    R.push(tmp->rightSon);
                                }
                                if(tmp->leftSon != nullptr){
                                    L.push(tmp->leftSon);
                                }
                                if(L.size()>0){
                                    tmp = L.top();
                                    L.pop();
                                }else{
                                    tmp=R.top();
                                    R.pop();
                                }
                            }
                            curr = tmp;    
                        }
                    }
                }

                T& operator* () const{
                    return curr->value;
                }
                T* operator->() const{
                    return &(curr->value);
                }

                const_iterator& operator++(){
                    switch (order){
                        case Order::preorder :{
                            if(curr->leftSon != nullptr){
                                if(curr->rightSon != nullptr){
                                    R.push(curr->rightSon);
                                }
                                curr = curr->leftSon;
                            } else if(curr->rightSon != nullptr){
                                curr = curr->rightSon;
                            } else if (R.size()>0){
                                curr = R.top();
                                R.pop();
                            } else{
                                curr =  nullptr;
                            }
                            return *this;
                            break;
                        }
                
                        case Order::inorder :{
                            if(R.size()>0){ 
                                Node* tmp = R.top();
                                if(curr->rightSon == tmp){
                                    R.pop();
                                    while(tmp != nullptr){
                                        if(tmp->rightSon != nullptr){R.push(tmp->rightSon);}
                                        P.push(tmp);
                                        tmp = tmp->leftSon;
                                    }
                                    curr = P.top();
                                    P.pop(); 
                                }else{
                                curr = P.top();
                                P.pop();
                                }
                            } else {
                                if(P.size()>0){
                                    curr = P.top();
                                    P.pop();
                                }else{
                                curr = nullptr;
                                }
                            }    
                            break;
                        }
                        case Order::postorder :{
                            if(P.size()>0){
                                if (R.size()>0){
                                    Node* tmpP = P.top();
                                    Node* tmpR = R.top();
                                    if(tmpP->rightSon == tmpR){
                                        R.pop();
                                        while(tmpR->leftSon != nullptr || tmpR->rightSon != nullptr){
                                            if(tmpR->leftSon != nullptr){
                                                L.push(tmpR->leftSon);
                                            }
                                            P.push(tmpR);
                                            if(tmpR->rightSon != nullptr){
                                                R.push(tmpR->rightSon);
                                            }
                                            if(L.size()>0){
                                                tmpR = L.top();
                                                L.pop();
                                            }else{
                                                tmpR=R.top();
                                                R.pop();
                                            }
                                        }
                                        curr = tmpR;
                                    }else{
                                        P.pop();
                                        curr = tmpP;
                                    }
                                }else{
                                    curr=P.top();
                                    P.pop();
                                }
                            } else {
                                curr = nullptr;
                            }
                            break;
                        }
                    }
                    return *this;
                }

                const_iterator operator++(int){
                     const_iterator tmp = *this;
                     *this->operator++();
                     return tmp;
                } 
                Node* getCurr(){
                    return curr;
                }
            
                bool operator==(const const_iterator& rhs) const{
                    return rhs.curr==curr;
                }
                bool operator!=(const const_iterator& rhs) const{
                    return rhs.curr != curr;
                }
        };

        
            /*
            Constructor-
                Init the root to nullptr.
            */
            BinaryTree():root(nullptr){};

            /*
            Destructor-
                Remove all nodes from the root.
            */
            ~BinaryTree(){
                if(root != nullptr){
                    delete root;
                }
            } 

            /*
            Copy constructor-
                Start from root and recursively update each son.
            */
            BinaryTree<T>(BinaryTree<T> &t)
            {
                if(t.root == NULL){
                    root = NULL;
                }
                else{
                    copy(this->root, t.root);
                }
            }
            /*
                Recursive function that copy the tree fron given node.
            */
            void copy(Node* &root, Node* &otherRoot)
            {
                if(otherRoot == NULL)
                {
                    root = NULL;
                }
                else
                {
                    root = new Node(otherRoot->value);
                    copy(root->leftSon, otherRoot->leftSon);
                    copy(root->rightSon, otherRoot->rightSon);
                }
            }

            BinaryTree<T> &operator=(BinaryTree<T> &&other) noexcept {
                delete root;
                root = other.root;
                other.root = nullptr; 
            }

            BinaryTree<T>(BinaryTree<T> &&other) noexcept {
                root = other.root;
                other.root = nullptr; 
            }

            BinaryTree<T> &operator=(BinaryTree<T> other){
                if (this == &other) {
                    return *this;
                }
                delete root;
                root = new Node(other.root->value);
                copy(this->root,other.root);
                return *this;
            }
            /*
                Add root to this tree.
            */
            BinaryTree& add_root(const T& element){
                if(root != nullptr){
                    root->value = element;
                }else{
                    root = new Node(element);
                }
                return *this;
            }

            /*
                Add right son to node that contain @parent value,
                if none - throw exception.
            */
            BinaryTree& add_right(const T& parentVal,const T& rightSonVal){
                for(iterator itr = begin(); itr != end();++itr){
                    if(*itr == parentVal){
                        if(itr.getCurr()->rightSon != nullptr){
                            itr.getCurr()->rightSon->value = rightSonVal;
                        }else{
                            itr.getCurr()->rightSon = new Node(rightSonVal);
                        }
                        return *this;
                    }
                }
                throw invalid_argument("This tree doesn't contain this parent!");
            }

            /*
                Add left son to node that contain @parent value,
                if none - throw exception.
            */
            BinaryTree& add_left(const T& parentVal,const T& leftSonVal){
                for(iterator itr = begin(); itr != end();++itr){
                    if(*itr == parentVal){
                        if(itr.getCurr()->leftSon != nullptr){
                            itr.getCurr()->leftSon->value = leftSonVal;
                        }else{
                            itr.getCurr()->leftSon = new Node(leftSonVal);
                        }
                        return *this;
                    }
                }
                throw std::invalid_argument("This tree doesn't contain this parent!");
            }

            /*
            Output operator-
                Print this tree.
                Because i will not present this task, i decide to just print it "inorder"
                Source: https://www.geeksforgeeks.org/inorder-tree-traversal-without-recursion/
            */
            friend std::ostream& operator<<(std::ostream& os, const BinaryTree &tree){
                os<<"\nPrint the tree:\n";
                std::stack<Node *> s;
                Node *curr = tree.root;
            
                while (curr != NULL || !s.empty()){
                    while (curr !=  NULL){
                        s.push(curr);
                        curr = curr->leftSon;
                    }
                    curr = s.top();
                    s.pop();
                    os<< curr->value << " ";
                    curr = curr->rightSon;
                } 
                os<<endl;
                return os;
            }

            /*
                Return pointer to the first node on tree (by default - inorder).
            */
            iterator begin(){
                return iterator(Order::inorder,root);
            }

            /*
                Return pointer to one more then last node on tree (by default - inorder).
            */
            iterator end(){
                return iterator();
            }

            /*
                Return pointer to the first node on tree in preorder concept (parent - left - right)
            */
            iterator begin_preorder(){
                return iterator(Order::preorder,root);
            }
            /*
                Return pointer to one more then last node on tree in preorder concept (parent - left - right)
            */
            iterator end_preorder(){
                return iterator(Order::preorder);
            }

            /*
                Return pointer to the first node on tree in inorder concept (left - parent - right),
                Actual, call to the default begin().
            */            
            iterator begin_inorder(){
                return begin();
            }
            /*
                Return pointer to one more then last node on tree in inorder concept (left - parent - right)
                Actual, call to the default end().

            */   
            iterator end_inorder(){
                return end();

            }

            /*
                Return pointer to the first node on tree in postorder concept (left - right - parent)
            */            
            iterator begin_postorder(){
                return iterator(Order::postorder, root);

            }
            /*
                Return pointer to one more then last node on tree in postorder concept (left - right - parent)
            */             
            iterator end_postorder(){
                return iterator(Order::postorder);
            }

            /*
                Return const pointer to the first node on tree (by default - inorder).
            */
            const_iterator cbegin(){
                return const_iterator(root);
            }

            /*
                Return const pointer to one more then last node on tree (by default - inorder).
            */
            const_iterator cend(){
                return const_iterator();
            }

            /*
                Return const pointer to the first node on tree in preorder concept (parent - left - right)
            */
            const_iterator cbegin_preorder(){
                return const_iterator(Order::preorder,root);
            }
            /*
                Return const pointer to one more then last node on tree in preorder concept (parent - left - right)
            */
            const_iterator cend_preorder(){
                return const_iterator(Order::preorder);
            }

            /*
                Return const pointer to the first node on tree in inorder concept (left - parent - right),
                Actual, call to the default cbegin().
            */            
            const_iterator cbegin_inorder(){
                return const_iterator(Order::inorder,root);
            }
            /*
                Return const pointer to one more then last node on tree in inorder concept (left - parent - right)
                Actual, call to the default cend().

            */   
            const_iterator cend_inorder(){
                return const_iterator(Order::inorder);

            }

            /*
                Return const pointer to the first node on tree in postorder concept (left - right - parent)
            */            
            const_iterator cbegin_postorder(){
                return const_iterator(Order::postorder,root);

            }
            /*
                Return const pointer to one more then last node on tree in postorder concept (left - right - parent)
            */             
            const_iterator cend_postorder(){
                return const_iterator(Order::postorder);
            }
        };
}