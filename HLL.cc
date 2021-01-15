#include"HLL.h"

using std::cin;using std::cout;
using std::string;
using std::stod;using std::stoi;
using std::regex;
using std::vector;
using std::sregex_token_iterator;
using std::regex_search;

// construct from string
LL::LL(string& s)
{
    regex re_comma(",");
    auto end = sregex_token_iterator();
    vector<string> terms(sregex_token_iterator(s.begin(),s.end(),re_comma,-1),end);
    //if(1 == terms.size())
    regex re_double(R"(\.)"),re_char(R"(')"),re_string(R"(")"),re_num(R"([0-9])");
    
    BaseNode* tmp=nullptr;
    BaseNode* tmpn = nullptr;
    
    for(int i = 0; i<terms.size();++i)
    {
        if(regex_search(terms[i],re_double))
        {
            if(i==0)
            {
                root = new Node<double>(stod(terms[i]));
                tmp = root;
            }
            else tmpn = new Node<double>(stod(terms[i]));
        }
        else if(regex_search(terms[i],re_char))
        {
            if(i==0)
            {
                root = new Node<char>(terms[i][1]);
                tmp = root;
            }
            else tmpn = new Node<char>(terms[i][1]);
        }
        else if(regex_search(terms[i],re_string))
        {
            if(i==0)
            {
                root = new Node<string>(terms[i]);
                tmp = root;
            }
            else tmpn = new Node<string>(terms[i]);
        }
        else if(regex_search(terms[i],re_num))
        {
            if(i==0)
            {
                root = new Node<int>(stoi(terms[i]));
                tmp = root;
            }
            else tmpn = new Node<int>(stoi(terms[i]));
        }
        else
        {
            root = nullptr;
        }
        if(0!=i)
        {
            tmp->link_n(tmpn);
            tmpn->link_f(tmp);
            tmp = tmpn;
        }
    }
    if(root != nullptr && tmp != root)
    {
        root->link_f(tmp);
        tmp->link_n(root);
    }
}

LL::LL(LL& l)
{
    if(l.root != nullptr)
    {
        this->root = l.root->clone();
        BaseNode* tmp = l.root;
        BaseNode* ntmp = this->root;
        BaseNode* ntmp_n;
        if(tmp->next != nullptr)
        {
            do
            {
                tmp = tmp->next;
                ntmp_n = tmp->clone();
                ntmp->link_n(ntmp_n);
                ntmp_n->link_f(ntmp);
                ntmp = ntmp_n;
            } while (tmp->next != l.root);
            ntmp->link_n(this->root);
            this->root->link_f(ntmp);
        }
    }
    else
    {
        this->root = nullptr;
    }
}


LL::~LL()
{
    if(root != nullptr)
    {
        BaseNode* tmpn = root->next;
        BaseNode* tmpf = root->forward;
        delete root;
        while (tmpn != tmpf && tmpn->next != tmpf)
        {
            tmpn = tmpn->next;
            tmpf = tmpf->forward;
            delete tmpn->forward;
            delete tmpf->next;
        }
        if (tmpn != nullptr)
        {
            if(tmpn == tmpf) delete tmpn;
            if(tmpn->next == tmpf) {delete tmpn;delete tmpf;}
        }
    }
}

ostream& LL::traverse(ostream& s)
{
    if(root != nullptr)
    {
        BaseNode* tmp = root;
        do
        {
            tmp->to_stream(s) << " ";
            if(tmp->next != nullptr) tmp = tmp->next;
        } while (tmp!=root);
    }
    return s;
}

ostream& LL::r_traverse(ostream& s)
{
    if(root->next == nullptr)
    {
        root->to_stream(s);
        return s;
    }

    BaseNode* tmp = root->forward;
    BaseNode* tmp1 = tmp;
    do
    {
        tmp1->to_stream(s)<<" ";
        tmp1 = tmp1->forward;
    } while (tmp1!=tmp);
    return s;
}

/*  
    INSERT an element before or after pos( true: before, false: after)
    if pos is negative means reversingly traverse
    default args means insert before the root 
    if pos=-1, tag=false means append the ele after the last
*/
void LL::insert(BaseNode* t, int pos ,bool tag )
{
    if(root==nullptr){ root = t; return; }
    BaseNode* tmp = root;
    if(pos > 0) for(int i = 0; i<pos; ++i) tmp = tmp->next;
    if(pos < 0) for(int i = 0;i<-pos;++i) tmp = tmp->forward;
    BaseNode* tmp1;
    if(tag)
    {
        if(root->next == nullptr)
        {
            root->link(t,t);
            t->link(root,root);
        }
        else
        {
            tmp1 = tmp->forward;
            t->link(tmp1,tmp);
            tmp1->link_n(t);
            tmp->link_f(t);
        }
        if(pos == 0) root = t;
    }
    else
    {
        if(root->next == nullptr)
        {
            root->link(t,t);
            t->link(root,root);
        }
        else
        {
            tmp1 = tmp->next;
            t->link(tmp,tmp1);
            tmp1->link_f(t);
            tmp->link_n(t);
        }
    }
}

/*
    REMOVE the element in pos
    if pos is negative means reversingly traverse
    default arg means remove the last element
*/
void LL::remove(int pos )
{
    if(root == nullptr) return;
    if(root->next == nullptr)
    {
        delete root;
    }
    else
    {
        BaseNode* tmp = root;
        if(pos > 0)for(int i = 0 ;i<pos;++i) tmp = tmp->next;
        if(pos < 0)for(int i = 0;i<-pos;++i) tmp = tmp->forward;
        tmp->forward->link_n(tmp->next);
        tmp->next->link_f(tmp->forward);
        if(pos == 0) root = root->next;
        delete tmp;
    }
    return;
}

/*
    merge 2 LL
*/
void LL::merge(LL& l)
{
    if(l.root == nullptr) return;
    if(l.root->next == nullptr)
    {
        if(this->root->next != nullptr) this->insert(l.root->clone(),-1,false);
        else this->insert(l.root->clone(),0,false);
    }
    else
    {
        BaseNode* tmp = l.root;
        do
        {
            this->insert(tmp->clone(),-1,false);
            tmp = tmp->next;
        } while (tmp != l.root);        
    }
}