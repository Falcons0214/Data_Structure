#include <iostream>
#include <vector>

using namespace std;

typedef struct node node;
struct node 
{
    char key;
    int data;
    node(): key('\0'), data(0){};
    node(char alpha, int num): key(alpha), data(num){}; 
};

class Minheap
{
private:
    vector<node> heap;
    void swap(node &n1, node &n2);
    int find_position(int node);
    int get_parent(int node);
public:
    Minheap()
    {
        heap.resize(1);
    }
    Minheap(int n)
    {
        heap.resize(n + 1);
    }
    void create(node *data, int length); // ok
    bool is_heap_empty(); // ok
    void Minheapify(int node); // ok
    void Build_min_heap(); // ok
    void Decrease_key(); 
    void insert(char alpha, int num); // ok
    void print_data(); // ok
    int Minimum(); // ok
    node *Extractmin(); // ok
};

void Minheap::swap(node &n1, node &n2)
{
    node temp = n1;
    n1 = n2;
    n2 = temp;
}

int Minheap::find_position(int node)
{
    int index;
    for(int i=1; i<heap.size()-1; i++)
        if(heap[i].data == node)
            index = node;
    return index;
}

int Minheap::get_parent(int node)
{
    if(node == 1)
        return 1;
    return node/2;
}

bool Minheap::is_heap_empty()
{
    if( heap.size() <= 1)
        return true;
    return false;
}

void Minheap::print_data()
{
    cout << "heap size: " << heap.size() <<endl;
    for(int i=0; i<heap.size()-1; i++)
        cout << i+1 <<" "<<heap[i+1].key << " " << heap[i+1].data <<endl;
}

void Minheap::create(node *temp, int length)
{
    for(int i=0; i<length; i++)
    {
        heap[i+1].key = temp[i].key;
        heap[i+1].data = temp[i].data;
    }
}

void Minheap::Minheapify(int node)
{
    int right = node * 2 + 1,
        left = node * 2,
        smallest;
    if( node >= heap.size()/2 )
        return ; // root  < (total node / 2)
    if( heap.size()-1 >= right && heap[right].data < heap[left].data)
        smallest = right;
    else
        smallest = left;
    if( heap[smallest].data < heap[node].data )
    {
        swap(heap[smallest], heap[node]);
        Minheapify(smallest);
    }
}

void Minheap::Build_min_heap()
{
    for(int i = (heap.size()-1)/2; i>=1; i--)
        Minheapify(i);
}

node *Minheap::Extractmin()
{
    node *temp = new(node);
    if(is_heap_empty())
        return NULL;

    temp->key = heap[1].key, temp->data = heap[1].data;
    heap[1] = heap[heap.size() - 1];
    heap.erase(heap.begin() + heap.size() - 1);
    Minheapify(1);
    return temp; 
}

int Minheap::Minimum()
{
    return 1;
}

void Minheap::Decrease_key()
{
    //code
}

void Minheap::insert(char alpha, int num)
{
    heap.push_back(node(alpha, num));
    Build_min_heap();
}

int main()
{
    Minheap n(9);
    node data[9];

    data[0].key = 'A', data[1].key = 'B', data[2].key = 'C';
    data[3].key = 'D', data[4].key = 'E', data[5].key = 'F';
    data[6].key = 'G', data[7].key = 'H', data[8].key = 'I';
    data[0].data = 5, data[1].data = 9, data[2].data = 1;
    data[3].data = 2, data[4].data = 3, data[5].data = 7;
    data[6].data = 6, data[7].data = 0, data[8].data = 4;

    n.create(data, 9);
    n.print_data();

    n.Build_min_heap();

    n.print_data();

    node *n1 = n.Extractmin();
    cout << n1->data << " " << n1->key <<endl;

    n.print_data();

    n1 = n.Extractmin();
    cout << n1->data << " " << n1->key <<endl;

    n.print_data();

    n.insert('Z', 11);

    n.print_data();

    n.insert('J', -5);

    n.print_data();

    n.insert('O', 12);

    n.print_data();

    n1 = n.Extractmin();
    cout << n1->data << " " << n1->key <<endl;

    n.print_data();

    n1 = n.Extractmin();
    cout << n1->data << " " << n1->key <<endl;

    n.print_data();

    n1 = n.Extractmin();
    cout << n1->data << " " << n1->key <<endl;

    n.print_data();

    return 0;
}