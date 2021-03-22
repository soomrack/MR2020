#include <queue>
#include <vector>

using namespace std;

class leaf{
    private:
        vector<leaf> neighbours;

    vector<leaf> expand(){
        return neighbours;
    }

};

class graph{

    vector expand(){

    }
};

void BFS(int start_node, int goal_node){

    int visited[10][10];

    for(all nodes i) visited[i] = false; // изначально список посещённых узлов пуст
    queue.push(start_node);              // начиная с узла-источника
    visited[start_node] = true;
    while(! queue.empty() ) {            // пока очередь не пуста
    node = queue.pop();                 // извлечь первый элемент в очереди
    if(node == goal_node) {
    return true;                       // проверить, не является ли текущий узел целевым
    }
    foreach(child in expand(node)) {    // все преемники текущего узла, ...
    if(visited[child] == false) {      // ... которые ещё не были посещены ...
        queue.push(child);                // ... добавить в конец очереди...
        visited[child] = true;            // ... и пометить как посещённые
    }
    }
    }
    return false;                        // Целевой узел недостижим
}

int main(void){

}