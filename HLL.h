#include<iostream>
#include<string>
#include<regex>
#include<vector>

using std::ostream;
using std::string;

class BaseNode
{
    public:
        BaseNode* forward;
        BaseNode* next;
        BaseNode(BaseNode *f=nullptr, BaseNode* n=nullptr):forward{f},next{n}{}
        virtual ~BaseNode(){/*cout<<"delete basenode!\n";*/}
        virtual ostream& to_stream(ostream& s) = 0;
        void link_f(BaseNode*f=nullptr){forward=f;}
        void link_n(BaseNode*n=nullptr){next=n;}
        void link(BaseNode*f=nullptr, BaseNode*n=nullptr)
        {
            forward = f; next=n;
        }
};
template<typename T>
class Node: public BaseNode
{
    T data;
    public:
        Node():data{}{}
        Node(T _data,BaseNode* f=nullptr, BaseNode* n=nullptr): data{_data},BaseNode(f,n) {}
        ~Node(){/*cout<<"delete node!\n";*/}
        ostream& to_stream(ostream& s){s << data;return s;}
};

class LL
{
    public:
        LL():root{nullptr}{}
        LL(BaseNode* _root):root{_root}{}
        ~LL();
        // Construct from legal string
        LL(string& s);
        ostream& traverse(ostream& s);
        ostream& r_traverse(ostream& s);
        BaseNode* root;
};

