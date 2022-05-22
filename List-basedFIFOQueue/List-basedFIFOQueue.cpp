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



void add_beg(Node*& beg, Node*& act, Node*& end, Node*& prev)
{
    int value;
    cin >> value;
    Node* new_node = new Node;
    new_node->val = value;
    new_node->xnp = beg;

    if (beg != nullptr)
    {
        beg->xnp = XOR(new_node, beg->xnp);
        if (prev == nullptr)
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

    if (end != nullptr)
    {
        end->xnp = XOR(new_node, end->xnp);
        if (next == nullptr)
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

    if (act != nullptr)
    {
        new_node->xnp = XOR(prev, act);
        act->xnp = XOR(new_node, next);
        if (prev == nullptr)
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
        new_node->xnp = nullptr;
        beg = new_node;
        act = new_node;
        end = new_node;
    }
}



void del_beg(Node*& beg, Node*& act, Node*& end, Node*& prev, Node*& next)
{
    Node* temp = beg;
    if (beg != end)
    {
        beg = temp->xnp;
        beg->xnp = XOR(temp, beg->xnp);
        if (temp == prev)
        {
            prev = nullptr;
        }
        else if (temp == act)
        {
            act = end;
            prev = end->xnp;
            next = nullptr;
        }
    }
    else
    {
        beg = nullptr;
        act = nullptr;
        end = nullptr;
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
            next = nullptr;
        }
        else if (temp == act)
        {
            act = end;
            prev = end->xnp;
            next = nullptr;
        }
    }
    else
    {
        beg = nullptr;
        act = nullptr;
        end = nullptr;
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
        prev = nullptr;
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



void print_forward(Node*& beg, Node*& end)
{
    Node* temp_act = beg;
    Node* temp_prev = nullptr;
    Node* temp_next;
    while (temp_act != nullptr)
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
    Node* temp_next = nullptr;
    Node* temp_prev;

    while (temp_act != nullptr)
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



void push(Node*& beg, Node*& act, Node*& end, Node*& prev, Node*& next, Node*& front, Node*& back, Node*& frontprev, Node*& backprev, int& size, int& count, bool& isloop)
{
    int value;
    if (count == 0 && size == 0)
    {
        add_beg(beg, act, end, prev);
        size++;
        front = end;
        back = end;
    }
    else if (count == 0)
    {
        cin >> value;
        end->val = value;
        front = end;
        back = end;
        frontprev = end->xnp;
        backprev = end->xnp;
    }
    else if (count == size && beg == end)
    {
        add_beg(beg, act, end, prev);
        size++;
        back = beg;
        frontprev = back;
        backprev = nullptr;
    }
    else if (count == size)
    {
        act = back;
        prev = backprev;
        next = XOR(prev, act->xnp);
        add_act(beg, act, end, prev, next);
        size++;
        back = prev;
        backprev = XOR(prev->xnp, act);
    }
    else
    {
        cin >> value;
        if (backprev == nullptr)
        {
            back = end;
            back->val = value;
            backprev = back->xnp;
            isloop = true;
        }
        else
        {
            Node* temp = backprev;
            backprev = XOR(back, backprev->xnp);
            back = temp;
            back->val = value;
        }
    }
    count++;
}



int pop(Node*& end, Node*& front, Node*& back, Node*& frontprev, Node*& backprev, int& count, bool& isloop)
{
    int value;
    if (count == 1)
    {
        value = front->val;
        front = nullptr;
        frontprev = nullptr;
        back = nullptr;
        backprev = nullptr;
        isloop = false;
    }
    else if (frontprev == nullptr)
    {
        value = front->val;
        front = end;
        frontprev = front->xnp;
        isloop = false;
    }
    else
    {
        value = front->val;
        Node* temp = frontprev;
        frontprev = XOR(frontprev->xnp, front);
        front = temp;
    }
    count--;
    return value;
}



void print_queue(Node*& end, Node*& front, Node*& back, Node*& frontprev)
{
    Node* temp_act = front;
    Node* temp_next = XOR(frontprev, front->xnp);
    Node* temp_prev;

    while (temp_act != back)
    {
        if (temp_act == nullptr)
        {
            if (end == back)
            {
                temp_act = back;
                break;
            }
            temp_act = end;
            temp_next = nullptr;
        }
        temp_prev = XOR(temp_next, temp_act->xnp);
        printf("%d ", temp_act->val);
        temp_next = temp_act;
        temp_act = temp_prev;
    }
    if (temp_act != nullptr)
        printf("%d\n", temp_act->val);
}



void garbage_soft(Node*& end, Node*& front, Node*& back, Node*& backprev, Node*& beg, int& count)
{
    if (count > 0)
    {
        Node* temp_act = backprev;
        Node* temp_next = back;
        Node* temp_prev;
        while (temp_act != front)
        {
            if (temp_act == nullptr)
            {
                if (end == front)
                {
                    temp_act = front;
                    break;
                }
                temp_act = end;
                temp_next = nullptr;
            }
            temp_prev = XOR(temp_next, temp_act->xnp);
            temp_act->val = 0;
            temp_next = temp_act;
            temp_act = temp_prev;
        }
    }
    else
    {
        Node* temp_act = beg;
        Node* temp_prev = nullptr;
        Node* temp_next;
        while (temp_act != nullptr)
        {
            temp_next = XOR(temp_prev, temp_act->xnp);
            temp_act->val = 0;
            temp_prev = temp_act;
            temp_act = temp_next;
        }
    }

}



void garbage_hard(Node*& beg, Node*& act, Node*& end, Node*& prev, Node*& next, Node*& front, Node*& back, Node*& backprev, int& count, int& size)
{
    if (count > 0)
    {
        Node* temp_act = backprev;
        Node* temp_next = back;
        Node* temp_prev;
        while (temp_act != front)
        {
            int flag = 0;
            if (temp_act == nullptr)
            {
                if (end == front)
                {
                    temp_act = front;
                    break;
                }
                temp_act = end;
                temp_next = nullptr;
            }
            temp_prev = XOR(temp_next, temp_act->xnp);
            if (temp_act == beg)
            {
                del_beg(beg, act, end, prev, next);
                temp_act = nullptr;
            }
            else if (temp_act == end)
            {
                del_end(beg, act, end, prev, next);
            }
            else
            {
                del_act(beg, temp_act, end, temp_prev, temp_next);
                flag = 1;
            }
            if (flag == 0)
            {
                temp_next = temp_act;
                temp_act = temp_prev;
            }
            size--;
        }
    }
    else
    {
        while (act != nullptr)
            del_beg(beg, act, end, prev, next);
        size = 0;
    }
    if (back == beg)
    {
        backprev = nullptr;
    }
    else
    {
        backprev = front;
    }

}



int main()
{
    Node* act = nullptr;
    Node* beg = nullptr;
    Node* end = nullptr;
    Node* prev = nullptr;
    Node* next = nullptr;
    Node* front = nullptr;
    Node* back = nullptr;
    Node* frontprev = nullptr;
    Node* backprev = nullptr;
    int size = 0;
    int count = 0;
    bool isloop = false;
    string input;
    while (cin >> input)
    {
        if (input == "ADD_BEG")
        {
            if (beg == end)
            {
                add_beg(beg, act, end, prev);
                backprev = beg;
                frontprev = beg;
            }
            else if (back == beg)
            {
                add_beg(beg, act, end, prev);
                backprev = beg;
            }
            else if (front == beg)
            {
                add_beg(beg, act, end, prev);
                frontprev = beg;
            }
            else
            {
                add_beg(beg, act, end, prev);
            }
            if (isloop == true)
            {
                count++;
            }
            size++;
        }
        else if (input == "ADD_END")
        {
            add_end(beg, act, end, next);
            if (isloop == true)
            {
                count++;
            }
            size++;
        }
        else if (input == "DEL_BEG")
        {
            if (act != nullptr)
            {
                if (beg == end)
                {
                    front = nullptr;
                    frontprev = nullptr;
                    back = nullptr;
                    backprev = nullptr;
                    isloop = false;
                    count = 0;
                }
                else if (beg == back)
                {
                    back = beg->xnp;
                    backprev = nullptr;
                    count--;
                }
                else if (beg == front)
                {
                    pop(end, front, back, frontprev, backprev, count, isloop);
                }
                else if (beg == backprev)
                {
                    backprev = nullptr;
                }
                else if (beg == frontprev)
                {
                    frontprev = nullptr;
                    count--;
                }
                else if (isloop == true)
                {
                    count--;
                }
                del_beg(beg, act, end, prev, next);
                size--;
            }
        }
        else if (input == "DEL_END")
        {
            if (act != nullptr)
            {
                if (beg == end)
                {
                    front = nullptr;
                    frontprev = nullptr;
                    back = nullptr;
                    backprev = nullptr;
                    isloop = false;
                    count = 0;
                }
                else if (end == back)
                {
                    back = beg;
                    backprev = nullptr;
                    count--;
                }
                else if (end == front)
                {
                    pop(end, front, back, frontprev, backprev, count, isloop);
                }
                else if (isloop == true)
                {
                    count--;
                }
                del_end(beg, act, end, prev, next);
                size--;
            }
        }
        else if (input == "DEL_ACT")
        {
            if (act != nullptr)
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
                size--;
            }
        }
        else if (input == "PRINT_FORWARD")
        {
            if (act != nullptr)
                print_forward(beg, end);
            else
                printf("NULL\n");
        }
        else if (input == "PRINT_BACKWARD")
        {
            if (act != nullptr)
                print_backward(beg, end);
            else
                printf("NULL\n");
        }
        else if (input == "PUSH")
        {
            push(beg, act, end, prev, next, front, back, frontprev, backprev, size, count, isloop);
        }
        else if (input == "POP")
        {
            if (count != 0)
                cout << pop(end, front, back, frontprev, backprev, count, isloop) << endl;
            else
                printf("NULL\n");
        }
        else if (input == "COUNT")
        {
            cout << count << endl;
        }
        else if (input == "SIZE")
        {
            cout << size << endl;
        }
        else if (input == "PRINT_QUEUE")
        {
            if (count != 0)
                print_queue(end, front, back, frontprev);
            else
                printf("NULL\n");
        }
        else if (input == "GARBAGE_SOFT")
        {
            if (count < size)
                garbage_soft(end, front, back, backprev, beg, count);
        }
        else if (input == "GARBAGE_HARD")
        {
            if (count < size)
                garbage_hard(beg, act, end, prev, next, front, back, backprev, count, size);
        }
    }
    while (act != nullptr)
        del_beg(beg, act, end, prev, next);
    return 0;
}