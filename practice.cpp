#include <bits/stdc++.h>

using namespace std;


int d;
int t;
// class NodeElement;
class IndexNode;
class Node;
Node* root;
int dataNodes=0;
int indexNodes=0;
class NodeElement{
    public:
    Node* left;
    Node* right;
    int data;
    bool empty;
    NodeElement(){
        left=NULL;
        right=NULL;
        empty=true;
    }
    NodeElement(int x){
        left=NULL;
        right=NULL;
        empty=false;
        data=x;
    }
    NodeElement(int x, Node* left, Node* right){
        this->left=left;
        this->right=right;
        empty=false;
        data=x;
    }
    void set(int x){
        data = x;
        empty = false;
    }
    bool operator<(NodeElement const &e){
        return this->data < e.data;
    }
};

bool compare(NodeElement* p1, NodeElement* p2){
    return p1->data < p2->data;
}
class Node{
    public:
        vector<NodeElement *> v;
        int overflowSize;
        Node* parent;
        int type;
        void initOS(){
            if(type){
                overflowSize = 2*t+2;
            }else{
                overflowSize = 2*d+1;
            }
        }
        Node(){
            parent = NULL;
            type=0;
            dataNodes++;
            initOS();
        }
        Node(int ty){
            type = ty;
            if(ty){
                indexNodes++;
            }else{
                dataNodes++;
            }
            initOS();
        }
        Node * search(int x){
            if(type == 0){
                return this;
            }
            for(auto y: v){
                if(x < y->data){
                    return y->left->search(x);
                }
            }
            return v.back()->right->search(x);
        }

        Node * findParent(Node * prev, Node * curr, Node* target,  int x){
            if(target == curr){
                return prev;
            }
            if(curr->type == 0){
                return prev;
            }
            for(auto y: curr->v){
                if(x < y->data){
                    return findParent(curr,y->left,target , x);
                }
            }
            return findParent(curr,curr->v.back()->right,target, x);
        }
        Node * getSplit(){
            if(type == 0){
                auto node = new Node();
                for(auto i=0; i<d+1; i++){
                    node->v.push_back(v[d+i]);
                }
                v.resize(d);
                return node;
            }
            auto nn = new Node(1);
            for(int i=0; i<t+1; i++){
                nn->v.push_back(v[t+i+1]);
            }
            v.resize(t);
            return nn;
        };
        int getSplitValue(){
            if(type == 0) return v[d]->data;
            return v[t]->data;
        };
        void insert(int x, Node * left, Node * right){
            auto ne = new NodeElement(x, left, right);
            bool pc = false;
            if(v.size() == 0) pc = true;
            for(int i=0; i<v.size(); i++){
                if(x < v[i]->data){
                    v[i]->left = right;
                    if(i>0) v[i-1]->right = left;
                    pc = true;
                    break;
                }
            }
            if(!pc){
                v.back()->right = left;
            }
            v.push_back(ne);
            sort(v.begin(), v.end(), compare);
            split_check();
        }
        void split_check(){
            // cout << "overflowSize: " << overflowSize << endl;
            // cout << "oc: ";
            // for(auto s: v){
            //     cout << s->data << " ";
            // }
            // cout << endl;
            if(v.size() == overflowSize){
                int sv = getSplitValue();
                // cout << "splitValue: " << sv << endl;
                Node * nn = getSplit();
                // if(parent == NULL){
                //     auto ind = new Node(1);
                //     parent = ind;
                //     if(this == root){
                //         root=parent;
                //     }
                // }
                auto par = findParent(NULL, root, this, v[0]->data);
                if(par == NULL){
                    auto ind = new Node(1);
                    parent = ind;
                    par=ind;
                    if(this == root){
                        root=parent;
                    }
                }
                nn->parent = par;
                par->insert(sv, this, nn);
            }
        }
        void insert(int x){
            auto ne = new NodeElement(x);
            v.push_back(ne);
            sort(v.begin(), v.end(), compare);
            split_check();
        }
};

void insert(int y){
    if(root == NULL){
        root = new Node();
        root->insert(y);
        return;
    }
    Node* ti = root->search(y);
    // cout << "vs: " << ti->v.size() << endl;
    // for(auto g: ti->v){
    //     cout << g->data << ",";
    // }
    // cout << endl;
    ti->insert(y);
}
void print(){
    // Index Nodes | Data Nodes | root contents
    cout << indexNodes << " " << dataNodes << " ";
    if(root != NULL){
        for(auto x: root->v){
            cout << x->data << " ";
        }
    }
    cout << endl;
}

void print_all(){
    queue<Node *> q;
    q.push(root);
    cout << "----------------" << endl;
    while(!q.empty()){
        auto n = q.front(); q.pop();
        for(auto x: n->v){
            cout << x->data << " ";
            if(x->left != NULL)
            q.push(x->left);
            if(x->right != NULL)
            q.push(x->right);
        }
        cout << endl;
    }
}

int main(){
    cin >> d >> t;
    while(true){
        int x;
        cin >> x;
        if(x == 1){
            int y;
            cin >> y;
            // cout << "----------------------- INSERT " << y << "-----------------------" << endl;
            insert(y);
            // print_all();
        }
        else if(x == 2){
            print();
        }else if(x == 3){
            break;
        }
    }
    return 0;
}