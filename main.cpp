#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct node{
    int neighbour, total_neighbour;
    char letter;
};

struct node_queue{
    int info;
    node_queue *next;
};

void push(node_queue *&first, node_queue *&last, int x)
{
    if(first==0)
    {
        first = new node_queue;
        first->info = x;
        first->next = NULL;
        last = first;
    }
    else
    {
        node_queue *p;
        p = new node_queue;
        p->info = x;
        p->next = NULL;
        last->next = p;
        last = p;
    }
}

int pop(node_queue *&first, node_queue *&last)
{
    node_queue *p;
    if(first == NULL)
        return -1;
    int val=0;
    val = first->info;
    p = first;
    first = first->next;
    delete p;
    return val;
}

int size(node_queue *first)
{
    node_queue *p;
    p = first;
    int m = 0;

    while(p != 0)
    {
        m++;
        p = p->next;
    }
    return m;
}

int main()
{
    ifstream f("data.in");
    node **graph = NULL;
    node_queue *first = NULL, *last = NULL;
    int final_state[100] = {0}, visited[100] = {0}, aux[100], n, m, init, nr_fin, x;
    char s[1000];

    f>>s;
    f>>n>>m>>init>>nr_fin;
    for(int i = 0; i < nr_fin; i++)
    {
        f>>x;
        final_state[x] = 1;
    }

    if(!strcmp(s, "lambda"))
    {
        if(final_state[0] == 1)
            cout<<"The word is accepted!\n";
        else
            cout<<"The word is refused!\n";
        return 0;
    }

    graph = new node*[n];
    for(int i = 0; i <= n; i++)
    {
        graph[i] = new node[100];
        graph[i][0].total_neighbour = 0;
    }

    for(int i = 1; i <= m; i++)
    {
        int a, b;
        char c;
        f>>a>>b>>c;
        graph[a][++graph[a][0].total_neighbour].neighbour = b;
        graph[a][graph[a][0].total_neighbour].letter = c;
    }

    push(first, last, init);
    visited[init] = 1;
    int lungime_cuvant=strlen(s), contor = 0;

    while(first != NULL && contor < lungime_cuvant)
    {
        int queue_length = size(first), k = 0;

        for(int i = 0; i < queue_length; i++)
        {
            x = pop(first, last);
            aux[++k] = x;
            visited[x] = 0;
        }


        for(int i = 1; i <= queue_length; i++)
        {
            x = aux[i];

            for(int j = 1; j <= graph[x][0].total_neighbour; j++)
            {
                if(graph[x][j].letter == s[contor])
                {
                    if(visited[graph[x][j].neighbour] == 0)
                        push(first, last, graph[x][j].neighbour);
                    visited[graph[x][j].neighbour] = 1;
                }
            }
        }
        contor++;
    }

    int ok = 0;
    while(first != NULL)
    {
        x = pop(first, last);
        visited[x] = 0;
        if(final_state[x] == 1)
            ok=1;
    }

    if(ok == 1)
        cout<<"The word is accepted!\n";
    else
        cout<<"The word is refused!\n";

    return 0;
}
