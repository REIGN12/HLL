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
    regex re_double(R"(\.)"),re_char(R"(')"),re_string(R"(")");
    
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
        else
        {
            if(i==0)
            {
                root = new Node<int>(stoi(terms[i]));
                tmp = root;
            }
            else tmpn = new Node<int>(stoi(terms[i]));
        }
        if(0!=i)
        {
            tmp->link_n(tmpn);
            tmpn->link_f(tmp);
            tmp = tmpn;
        }
    }
    root->link_f(tmp);
    tmp->link_n(root);
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


int main()
{
    /*
    BaseNode* p1 = new Node<int>(100);
    BaseNode* p2 = new Node<double>(20.1,p1);
    BaseNode* p3 = new Node<char>('a',p2,p1);
    p1->link(p3,p2);
    p2->link(nullptr,p3);
    */
    string s(R"(3.1 ,2,3,"hello" )");//,"hello world!",'x')");
    LL l(s);
    l.traverse(cout)<<"\n";
    l.r_traverse(cout);
    return 0;
}