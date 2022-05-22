#pragma warning(disable:4996)
#include <iostream>
#include <string>

using namespace std;

struct Node {
    int val;
    Node* xnp;
};



Node* XOR(Node* prev, Node* next)
{
    return (Node*)((uintptr_t)(prev) ^ (uintptr_t)(next));
}



void nextnode(Node*& act, Node*& next, Node* beg, Node*& prev)
{
    if (act == NULL)
        printf("NULL\n");
    else if (next == NULL)
    {
        printf("%d\n", beg->val);
        act = beg;
        prev = NULL;
        next = act->xnp;
    }
    else
    {
        printf("%d\n", next->val);
        prev = act;
        act = next;
        next = XOR(prev, act->xnp);
    }
}



void prevnode(Node*& act, Node*& next, Node* end, Node*& prev)
{
    if (act == NULL)
        printf("NULL\n");
    else if (prev == NULL)
    {
        printf("%d\n", end->val);
        act = end;
        next = NULL;
        prev = act->xnp;
    }
    else
    {
        printf("%d\n", prev->val);
        next = act;
        act = prev;
        prev = XOR(next, act->xnp);
    }
}



void add_beg(Node*& beg, Node*& act, Node*& end, Node*& prev)
{
    int value;
    cin >> value;
    Node* new_node = new Node;
    new_node->val = value;
    new_node->xnp = beg;

    if (beg != NULL)
    {
        beg->xnp = XOR(new_node, beg->xnp);
        if (prev == NULL) 
        {
            prev = new_node;
        }
    }
    else
    {
        end = new_node;
        act = new_node;
    }
    beg = new_node;
}



void add_end(Node*& beg, Node*& act, Node*& end, Node*& next)
{
    int value;
    cin >> value;
    Node* new_node = new Node;
    new_node->val = value;
    new_node->xnp = end;

    if (end != NULL)
    {
        end->xnp = XOR(new_node, end->xnp);
        if (next == NULL)
        {
            next = new_node;
        }
    }
    else
    {
        beg = new_node;
        act = new_node;
    }
    end = new_node;
}



void add_act(Node*& beg, Node*& act, Node*& end, Node*& prev, Node*& next)
{
    int value;
    cin >> value;
    Node* new_node = new Node;
    new_node->val = value;

    if (act != NULL)
    {
        new_node->xnp = XOR(prev, act);
        act->xnp = XOR(new_node, next);
        if (prev == NULL)
        {
            beg = new_node;
        }
        else
        {
            prev->xnp = XOR(XOR(prev->xnp, act), new_node);
        }
        prev = new_node;
    }
    else
    {
        new_node->xnp = NULL;
        beg = new_node;
        act = new_node;
        end = new_node;
    }
}



void del_beg(Node*& beg, Node*&act, Node*& end, Node*& prev, Node*& next)
{
    Node* temp = beg;
    if (beg != end)
    {
        beg = temp->xnp;
        beg->xnp = XOR(temp, beg->xnp);
        if (temp == prev)
        {
            prev = NULL;
        }
        else if (temp == act)
        {
            act = end;
            prev = end->xnp;
            next = NULL;
        }
    }
    else
    {
        beg = NULL;
        act = NULL;
        end = NULL;
    }
    delete temp;
}



void del_end(Node*& beg, Node*& act, Node*& end, Node*& prev, Node*& next)
{
    Node* temp = end;
    if (beg != end)
    {
        end = temp->xnp;
        end->xnp = XOR(temp, end->xnp);
        if (temp == next)
        {
            next = NULL;
        }
        else if (temp == act)
        {
            act = end;
            prev = end->xnp;
            next = NULL;
        }
    }
    else
    {
        beg = NULL;
        act = NULL;
        end = NULL;
    }
    delete temp;
}



void del_act(Node*& beg, Node*& act, Node*& end, Node*& prev, Node*& next)
{
    Node* temp = act;

    act = prev;
    if (act == beg)
    {
        act->xnp = next;
        prev = NULL;
    }
    else
    {
        prev = XOR(act->xnp, temp);
        act->xnp = XOR(prev, next);
    }
    if (next == end)
    {
        next->xnp = act;
    }
    else
    {
        next->xnp = XOR(act, XOR(temp, next->xnp));
    }
    delete temp;
}



void del_val(Node*& beg, Node*& act, Node*& end, Node*& prev, Node*& next)
{
    int value;
    cin >> value;
    Node* temp_act = beg;
    Node* temp_prev = NULL;
    Node* temp_next;
    if (beg == end && temp_act->val == value)
    {
        beg = NULL;
        end = NULL;
        act = NULL;
        prev = NULL;
        next = NULL;
        delete temp_act;
    }
    else
    {
        while (temp_act != NULL)
        {
            temp_next = XOR(temp_prev, temp_act->xnp);

            if (temp_act->val == value)
            {
                if (temp_act == beg)
                {
                    del_beg(beg, act, end, prev, next);
                    temp_act = NULL;
                }
                else if (temp_act == end)
                {
                    del_end(beg, act, end, prev, next);
                }
                else if (temp_act == act)
                {
                    del_act(beg, act, end, prev, next);
                    temp_act = act;
                    temp_next = next;
                    temp_prev = prev;
                }
                else
                {
                    del_act(beg, temp_act, end, temp_prev, temp_next);
                }
            }

            temp_prev = temp_act;
            temp_act = temp_next;
        }
    }
}



void print_forward(Node*& beg, Node*& end)
{
    Node* temp_act = beg;
    Node* temp_prev = NULL;
    Node* temp_next;
    while (temp_act != NULL)
    {
        temp_next = XOR(temp_prev, temp_act->xnp);
        if (temp_act == end)
            printf("%d\n", temp_act->val);
        else
            printf("%d ", temp_act->val);
        temp_prev = temp_act;
        temp_act = temp_next;
    }
}



void print_backward(Node*& beg, Node*& end)
{
    Node* temp_act = end;
    Node* temp_next = NULL;
    Node* temp_prev;

    while (temp_act != NULL)
    {
        temp_prev = XOR(temp_next, temp_act->xnp);
        if (temp_act == beg)
            printf("%d\n", temp_act->val);
        else
            printf("%d ", temp_act->val);
        temp_next = temp_act;
        temp_act = temp_prev;
    }
}



int main()
{
    Node* act = NULL;
    Node* beg = NULL;
    Node* end = NULL;
    Node* prev = NULL;
    Node* next = NULL;
    string input;
    while (cin>>input)
    {
        if (input == "ACTUAL")
        {
            if (act == NULL)
            {
                printf("NULL\n");
            }
            else printf("%d\n", act->val);
        }
        else if (input == "NEXT")
        {
            nextnode(act, next, beg, prev);
        }
        else if (input == "PREV")
        {
            prevnode(act, next, end, prev);
        }
        else if (input == "ADD_BEG")
        {
            add_beg(beg, act, end, prev);
        }
        else if (input == "ADD_END")
        {
            add_end(beg, act, end, next);
        }
        else if (input == "ADD_ACT")
        {
            add_act(beg, act, end, prev, next);
        }
        else if (input == "DEL_BEG")
        {
            if (act != NULL)
                del_beg(beg, act, end, prev, next);
        }
        else if (input == "DEL_END")
        {
            if (act != NULL)
                del_end(beg, act, end, prev, next);
        }
        else if (input == "DEL_ACT")
        {
            if (act != NULL)
            {
                if (act == beg)
                {
                    del_beg(beg, act, end, prev, next);
                }
                else if (act == end)
                {
                    del_end(beg, act, end, prev, next);
                }
                else
                {
                    del_act(beg, act, end, prev, next);
                }
            }
                
        }
        else if (input == "DEL_VAL")
        {
            if (act != NULL)
                del_val(beg, act, end, prev, next);
        }
        else if (input == "PRINT_FORWARD")
        {
            if (act != NULL)
                print_forward(beg, end);
            else
                printf("NULL\n");
        }
        else if (input == "PRINT_BACKWARD")
        {
            if (act != NULL)
                print_backward(beg, end);
            else
                printf("NULL\n");
        }
    }
    while(act!=NULL)
        del_beg(beg, act, end, prev, next);
    return 0;
}
